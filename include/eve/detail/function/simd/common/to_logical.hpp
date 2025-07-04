//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/constant/iota.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/arch/fundamental_cardinal.hpp>

#include <bitset>

#include <type_traits>

namespace eve::detail
{
//================================================================================================
// Wide to Logical
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
to_logical(wide<T, N> const& v) noexcept
{
  if constexpr( is_aggregated_v<abi_t<T, N>> )
  {
    as_logical_t<wide<T, N>> that;
    that.storage().for_each([](auto& s, auto const& o) { s = to_logical(o); }, v);
    return that;
  }
  else
  {
    return map([](auto e) { return logical<T>(e != 0); }, v);
  }
}

template<value T>
EVE_FORCEINLINE auto
to_logical(logical<T> v) noexcept
{
  return v;
}

template<scalar_value T>
EVE_FORCEINLINE auto
to_logical(T v) noexcept
{
  return logical<T>(v);
}

template<relative_conditional_expr C, simd_value T>
EVE_FORCEINLINE auto to_logical_impl(cpu_, C c, eve::as<T> tgt) noexcept
{
  using l_t = typename as_logical<T>::type;

  // When dealing with large vector of small integer, the size can't be
  // represented. We then use an unsigned version of the index type.
  // We don't just use unsigned indexes all the time cause on most cases,
  // signed comparisons are faster and this will lead to pessimisation.
  using i_t = std::conditional_t<(T::size() >= 128 && sizeof(element_type_t<l_t>) == 1),
                                 typename l_t::bits_type,
                                 as_integer_t<typename l_t::bits_type, signed>>;

  if constexpr( std::same_as<C, ignore_all_> ) return l_t {false};
  else if constexpr( std::same_as<C, ignore_none_> )
  {
    if constexpr (T::size() < fundamental_cardinal_v<element_type_t<as_arithmetic_t<T>>>)
    {
      return to_logical(keep_first(cardinal_v<T>), tgt);
    }
    else
    {
      return l_t {true};
    }
  }
  else if constexpr( !eve::use_complete_storage<l_t>)
  {
    // Use the most full type to be sure to fill outside values of small wide with false
    using e_t   = eve::element_type_t<i_t>;
    using abi_t = typename i_t::abi_type;
    using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t>>;

    if constexpr( std::same_as<C, keep_first> || std::same_as<C, ignore_last> )
    {
      return call_simd_cast(to_logical(keep_first(c.count(as<l_t> {})), as<w_t> {}), as<l_t> {});
    }
    else
    {
      std::ptrdiff_t offset = c.offset(as<T> {});
      std::ptrdiff_t count  = c.count(as<T> {});
      keep_between   full_c {offset, offset + count};
      return call_simd_cast(to_logical(full_c, as<w_t> {}), as<l_t> {});
    }
  }
  else
  {
    auto           i     = eve::iota(eve::as<i_t>());
    std::ptrdiff_t count = c.count(as<i_t> {});

    if constexpr( std::same_as<C, keep_first> || std::same_as<C, ignore_last> )
    {
      return bit_cast(i < i_t(count), as<l_t> {});
    }
    else if constexpr( std::same_as<C, keep_last> || std::same_as<C, ignore_first> )
    {
      return bit_cast(i >= i_t(l_t::size() - count), as<l_t> {});
    }
    else
    {
      std::ptrdiff_t offset = c.offset(as<i_t> {});
      return bit_cast((i >= i_t {offset}) && (i < i_t {offset + count}), as<l_t> {});
    }
  }
}

template<relative_conditional_expr C, simd_value T>
EVE_FORCEINLINE auto
to_logical(C c, eve::as<T> tgt) noexcept
{
  return to_logical_impl(current_api, c, tgt);
}
}
