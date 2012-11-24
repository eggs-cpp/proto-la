/**
 * Eggs.LA <eggs/la/vector_traits.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_VECTOR_TRAITS_HPP
#define EGGS_LA_VECTOR_TRAITS_HPP

#include <eggs/la/common_traits.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/utility/enable_if.hpp>

#include <cstddef>

namespace eggs { namespace la {

    template< typename Type, typename Enable = void >
    struct is_vector
      : boost::mpl::false_
    {};

    template< typename Vector, typename Enable = void >
    struct vector_traits
    {
        // typedef -user-defined- scalar_type;
        // static std::size_t const dimension = -user-defined-;

        // template< std::size_t Index >
        // static scalar_type& at( Vector& v );
        // template< std::size_t Index >
        // static scalar_type const& at( Vector const& v );
    };

    template< typename Vector >
    struct scalar_type<
        Vector
      , typename boost::enable_if<
            is_vector< Vector >
        >::type
    >
    {
        typedef
            typename vector_traits< Vector >::scalar_type
            type;
    };

    template< typename Vector, typename Enable = void >
    struct dimension
    {
        typedef
            boost::mpl::size_t< vector_traits< Vector >::dimension >
            type;
    };

    template<
        typename LeftVector, typename RightVector
    > struct is_same_dimension<
        LeftVector, RightVector
      , typename boost::enable_if<
            boost::mpl::and_<
                is_vector< LeftVector >
              , is_vector< RightVector >
            >
        >::type
    > : boost::mpl::equal_to<
            dimension< LeftVector >
          , dimension< RightVector >
        >::type
    {};

} } // namespace eggs::la

#endif /*EGGS_LA_VECTOR_TRAITS_HPP*/
