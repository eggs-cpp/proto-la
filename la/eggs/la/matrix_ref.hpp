/**
 * Eggs.LA <eggs/la/matrix_ref.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_MATRIX_REF_HPP
#define EGGS_LA_MATRIX_REF_HPP

#include <eggs/la/matrix_traits.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/static_assert.hpp>

#include <boost/utility/enable_if.hpp>

#include <cstddef>

namespace eggs { namespace la {
    
    template< typename Matrix >
    class matrix_ref_wrapper
    {
    public:
        explicit matrix_ref_wrapper( Matrix& matrix )
          : _matrix( matrix )
        {}

        template< typename RightMatrix >
        typename boost::enable_if<
            boost::mpl::and_<
                is_matrix< RightMatrix >
              , is_same_dimension< Matrix, RightMatrix >
            >
          , matrix_ref_wrapper&
        >::type operator=( RightMatrix const& right )
        {
            for( std::size_t i = 0; i < rows< Matrix >::type::value * columns< Matrix >::type::value; ++i )
            {
                _matrix[ i ] = right[ i ];
            }
            return *this;
        }

    private:
        Matrix& _matrix;
    };

    template< typename Matrix >
    struct is_matrix< matrix_ref_wrapper< Matrix > >
      : boost::mpl::true_
    {};

    template< typename Matrix >
    struct rows< matrix_ref_wrapper< Matrix > >
      : rows< Matrix >::type
    {};

    template< typename Matrix >
    struct columns< matrix_ref_wrapper< Matrix > >
      : columns< Matrix >::type
    {};

    template< typename Matrix >
    typename boost::enable_if<
        typename is_matrix< Matrix >::type
      , matrix_ref_wrapper< Matrix >
    >::type matrix_ref( Matrix& v )
    {
        BOOST_STATIC_ASSERT(( is_matrix< Matrix >::type::value ));

        return matrix_ref_wrapper< Matrix >( v );
    }
    template< typename Matrix >
    matrix_ref_wrapper< Matrix >
        matrix_ref( matrix_ref_wrapper< Matrix >& v )
    {
        return v;
    }

    template< typename Matrix >
    typename boost::enable_if<
        typename is_matrix< Matrix >::type
      , matrix_ref_wrapper< Matrix const >
    >::type matrix_cref( Matrix const& v )
    {
        BOOST_STATIC_ASSERT(( is_matrix< Matrix >::type::value ));

        return matrix_ref_wrapper< Matrix const >( v );
    }
    template< typename Matrix >
    matrix_ref_wrapper< Matrix const >
        matrix_cref( matrix_ref_wrapper< Matrix const >& v )
    {
        return v;
    }

} } // namespace eggs::la

#endif /*EGGS_LA_MATRIX_REF_HPP*/
