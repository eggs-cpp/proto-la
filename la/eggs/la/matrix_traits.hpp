/**
 * Eggs.LA <eggs/la/matrix_traits.hpp>
 * 
 * Copyright Agust�n Berg�, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_MATRIX_TRAITS_HPP
#define EGGS_LA_MATRIX_TRAITS_HPP

#include <eggs/la/common_traits.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>

#include <boost/utility/enable_if.hpp>

namespace eggs { namespace la {
    
    template< typename Type >
    struct is_matrix
      : boost::mpl::false_
    {};

    template< typename Matrix, typename Enable = void >
    struct matrix_traits
    {
        // typedef -user-defined- scalar_type;
        // static std::size_t const rows = -user-defined-;
        // static std::size_t const columns = -user-defined-;

        // template< std::size_t Row, std::size_t Column >
        // static scalar_type& at( Matrix& m );
        // template< std::size_t Row, std::size_t Column >
        // static scalar_type const& at( Matrix const& m );
    };

    template< typename Matrix >
    struct scalar_type<
        Matrix
      , typename boost::enable_if<
            is_matrix< Matrix >
        >::type
    >
    {
        typedef
            typename matrix_traits< Matrix >::scalar_type
            type;
    };

    template< typename Matrix, typename Enable = void >
    struct rows
    {
        typedef
            boost::mpl::size_t< matrix_traits< Matrix >::rows >
            type;
    };
    
    template< typename Matrix, typename Enable = void >
    struct columns
    {
        typedef
            boost::mpl::size_t< matrix_traits< Matrix >::columns >
            type;
    };

    template<
        typename LeftMatrix, typename RightMatrix
    > struct is_same_dimension<
        LeftMatrix, RightMatrix
      , typename boost::enable_if<
            boost::mpl::and_<
                is_matrix< LeftMatrix >
              , is_matrix< RightMatrix >
            >
        >::type
    > : boost::mpl::and_<
            boost::mpl::equal_to<
                rows< LeftMatrix >
              , rows< RightMatrix >
            >
          , boost::mpl::equal_to<
                columns< LeftMatrix >
              , columns< RightMatrix >
            >
        >::type
    {};

} } // namespace eggs::la

#endif /*EGGS_LA_MATRIX_TRAITS_HPP*/
