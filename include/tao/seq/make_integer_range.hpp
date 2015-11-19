// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_RANGE_HPP
#define TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_RANGE_HPP

#include "make_integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      template< typename T, T N, T M, bool B = ( M < N ), typename = make_integer_sequence< T, B ? ( N - M ) : ( M - N ) > >
      struct range_t;

      template< typename T, T N, T M, T... Ns >
      struct range_t< T, N, M, false, integer_sequence< T, Ns... > >
      {
        using type = integer_sequence< T, N + Ns... >;
      };

      template< typename T, T N, T M, T... Ns >
      struct range_t< T, N, M, true, integer_sequence< T, Ns... > >
      {
        using type = integer_sequence< T, N - Ns... >;
      };
    }

    template< typename T, T N, T M >
    using make_integer_range = typename impl::range_t< T, N, M >::type;

    template< std::size_t N, std::size_t M >
    using make_index_range = make_integer_range< std::size_t, N, M >;

  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_RANGE_HPP