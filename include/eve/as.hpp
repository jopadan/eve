//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //! @struct as
  //! @brief Lightweight type-wrapper
  //!
  //! **Required header:** `#include <eve/as.hpp>`
  //!
  //! Wraps type into a constexpr, trivially constructible empty class to optimize passing type
  //! parameters via object instead of via template parameters.
  //!
  //! @tparam T Type to wrap
  //!
  //! @}
  //================================================================================================
  template<typename T>
  struct as
  {
    //! @brief Wrapped type
    using type = T;

    constexpr as()          noexcept {}
    explicit constexpr as(T const&)  noexcept {}
  };

  template<>
  struct as<void>
  {
    using type = void;

    constexpr as() noexcept {}
  };
}
