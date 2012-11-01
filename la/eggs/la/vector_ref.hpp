/**
 * Eggs.LA <eggs/la/vector_ref.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_VECTOR_REF_HPP
#define EGGS_LA_VECTOR_REF_HPP

#include <eggs/la/vector_traits.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/static_assert.hpp>

#include <cstddef>

namespace eggs { namespace la {

    template< typename Vector >
    class vector_ref_wrapper
    {
    public:
        explicit vector_ref_wrapper( Vector& vector )
          : _vector( vector )
        {}

    private:
        Vector& _vector;
    };

    template< typename Vector >
    struct is_vector< vector_ref_wrapper< Vector > >
      : boost::mpl::true_
    {};

    template< typename Vector >
    inline vector_ref_wrapper< Vector >
        vector_ref( Vector& v )
    {
        BOOST_STATIC_ASSERT(( is_vector< Vector >::type::value ));

        return vector_ref_wrapper< Vector >( v );
    }
    template< typename Vector >
    inline vector_ref_wrapper< Vector >
        vector_ref( vector_ref_wrapper< Vector >& v )
    {
        return v;
    }

    template< typename Vector >
    inline vector_ref_wrapper< Vector const >
        vector_cref( Vector const& v )
    {
        BOOST_STATIC_ASSERT(( is_vector< Vector >::type::value ));

        return vector_ref_wrapper< Vector const >( v );
    }
    template< typename Vector >
    inline vector_ref_wrapper< Vector const >
        vector_cref( vector_ref_wrapper< Vector const >& v )
    {
        return v;
    }

} } // namespace eggs::la

#endif /*EGGS_LA_VECTOR_REF_HPP*/
