// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_SUM_HPP
#define TAOCPP_SEQUENCES_INCLUDE_SUM_HPP

#include <type_traits>
#include <utility>

#include "integer_sequence.hpp"

#ifndef __cpp_fold_expressions
#ifdef __clang__
#if ( __clang_major__ > 3 ) || ( ( __clang_major__ == 3 ) && ( __clang_minor__ >= 6 ) )
#define __cpp_fold_expressions
#endif
#endif
#endif

#ifndef __cpp_fold_expressions
#include <cstddef>
#include "make_integer_sequence.hpp"
#endif

namespace tao
{
  namespace seq
  {

#ifdef __cpp_fold_expressions

    template< typename T, T... Ns >
    struct sum
      : std::integral_constant< T, ( Ns + ... ) >
    {};

#else

    namespace impl
    {
      template< std::size_t, std::size_t N >
      struct chars
      {
        char dummy[ N + 1 ];
      };

      template< typename, std::size_t... >
      struct collector;

      template< std::size_t... Is, std::size_t... Ns >
      struct collector< index_sequence< Is... >, Ns... >
        : chars< Is, Ns >...
      {};

      template< std::size_t N, typename T, T... Ns >
      using sum = std::integral_constant<
        T,
        T( sizeof( collector< make_index_sequence< N >, ( ( Ns > 0 ) ? Ns : 0 )... > ) - N ) -
        T( sizeof( collector< make_index_sequence< N >, ( ( Ns < 0 ) ? -Ns : 0 )... > ) - N ) >;
    }

    template< typename T, T... Ns >
    struct sum
      : impl::sum< sizeof...( Ns ) + 1, T, Ns..., 0 >
    {};

#endif

    template< typename T, T... Ns >
    struct sum< integer_sequence< T, Ns... > >
      : sum< T, Ns... >
    {};
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_SUM_HPP