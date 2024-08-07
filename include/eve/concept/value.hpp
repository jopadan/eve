//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/traits/underlying_type.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @ingroup simd_concepts
  //! @concept value
  //! @brief The concept `value<T>` is satisfied if and only if T satisfies
  //! either `eve::scalar_value` or `eve::simd_value`.
  //!
  //! @groupheader{Examples}
  //! - `eve::logical<eve::wide<char>>`
  //! - `float`
  //! - `eve::wide<std::uint64_t>`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept value                 = simd_value<T> || scalar_value<T>;

  //================================================================================================
  //! @ingroup simd_concepts
  //! @concept integral_value
  //! @brief The concept `integral_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the underlying_type satisfies `std::integral`
  //!
  //! @groupheader{Examples}
  //! - `eve::wide<char>`
  //! - `int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept integral_value        = value<T> && std::integral<underlying_type_t<T>>;

  //================================================================================================
  //! @ingroup simd_concepts
  //! @concept signed_value
  //! @brief The concept `signed_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the underlying_type satisfies `std::is_signed`
  //!
  //! @groupheader{Examples}
  //! - `eve::wide<char>`
  //! - `float`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept signed_value          = value<T> && std::is_signed_v<underlying_type_t<T>>;

  //================================================================================================
  //! @ingroup simd_concepts
  //! @concept unsigned_value
  //! @brief The concept `unsigned_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the underlying_type satisfies `std::unsigned_integral`
  //!
  //! @groupheader{Examples}
  //! - `unsigned int`
  //! - `eve::wide<std::uint8_t, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept unsigned_value        = value<T> && std::unsigned_integral<underlying_type_t<T>>;

  //================================================================================================
  //! @ingroup simd_concepts
  //! @concept signed_integral_value
  //! @brief The concept `signed_integral_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the underlying_type satisfies `std::signed_integral`
  //!
  //! @groupheader{Examples}
  //! - `short int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept signed_integral_value = value<T> && std::signed_integral<underlying_type_t<T>>;

  //================================================================================================
  //! @ingroup simd_concepts
  //! @concept floating_value
  //! @brief The concept `floating_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the underlying_type satisfies `std::floating_point`
  //!
  //! @groupheader{Examples}
  //! - `double`
  //! - `eve::wide<float, eve::fixed<2>>`
  //================================================================================================
  template<typename T> concept floating_value        = value<T> && std::floating_point<underlying_type_t<T>>;

  //================================================================================================
  //! @ingroup simd_concepts
  //! @concept logical_value
  //! @brief The concept `logical_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the underlying_type satisfies is_logical_v
  //!
  //! @groupheader{Examples}
  //! - `eve::logical<eve::wide<char>>`
  //! - `eve::logical<double>`
  //================================================================================================
  template<typename T> concept logical_value         = value<T> && is_logical_v<T>;

}
