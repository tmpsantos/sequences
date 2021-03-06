// Copyright (c) 2015-2017 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_MINUS_HPP
#define TAOCPP_SEQUENCES_INCLUDE_MINUS_HPP

#include <type_traits>

#include "zip.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename T, T A, T B >
         using minus = std::integral_constant< T, A - B >;
      }

      template< typename A, typename B >
      using minus = zip< impl::minus, A, B >;

      template< typename A, typename B >
      using minus_t = typename minus< A, B >::type;
   }
}

#endif  // TAOCPP_SEQUENCES_INCLUDE_MINUS_HPP
