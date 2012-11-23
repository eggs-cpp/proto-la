/**
 * Eggs.LA <eggs/la/matrix_traits.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_MATRIX_TRAITS_HPP
#define EGGS_LA_MATRIX_TRAITS_HPP

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
    struct rows;
    
    template< typename Matrix, typename Enable = void >
    struct columns;

    template< typename LeftMatrix, typename RightMatrix, typename Enable = void >
    struct is_same_dimension;

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
