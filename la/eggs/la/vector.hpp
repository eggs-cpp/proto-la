/**
 * Eggs.LA <eggs/la/vector.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_VECTOR_HPP
#define EGGS_LA_VECTOR_HPP

#include <eggs/la/vector_traits.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/static_assert.hpp>

#include <cstddef>
#include <iosfwd>

namespace eggs { namespace la {

    template< typename Type, std::size_t Dimension >
    class vector
    {
    public:
        Type* data()
        {
            return &_value[0];
        }
        Type const* data() const
        {
            return &_value[0];
        }

        Type& operator []( std::size_t index )
        {
            return _value[ index ];
        }
        Type const& operator []( std::size_t index ) const
        {
            return _value[ index ];
        }
        
        vector& operator =( vector< Type, Dimension > const& right )
        {
            for( std::size_t i = 0; i < Dimension; ++i )
                _value[ i ] = right[ i ];

            return *this;
        }
        template< typename RightType >
        vector& operator =( vector< RightType, Dimension > const& right )
        {
            for( std::size_t i = 0; i < Dimension; ++i )
                _value[ i ] = right[ i ];

            return *this;
        }

    //private: exposition-only
        Type _value[ Dimension ];
    };

    template< typename Type, std::size_t Dimension >
    struct is_vector< vector< Type, Dimension > >
      : boost::mpl::true_
    {};

    template< typename Type, std::size_t Dimension >
    struct dimension< vector< Type, Dimension > >
      : boost::mpl::size_t< Dimension >
    {};

    /** Operators **/
    
    template< typename Type, std::size_t Dimension >
    vector< Type, Dimension > operator +(
        vector< Type, Dimension > left
    )
    {
        return left;
    }
    template< typename Type, std::size_t Dimension >
    vector< Type, Dimension > operator -(
        vector< Type, Dimension > left
    )
    {
        for( std::size_t i = 0; i < Dimension; ++i )
            left[ i ] = -left[ i ];

        return left;
    }
    
    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension >& operator +=(
        vector< LeftType, Dimension >& left
      , vector< RightType, Dimension > const& right 
    )
    {
        for( std::size_t i = 0; i < Dimension; ++i )
            left[ i ] += right[ i ];

        return left;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension >& operator +=(
        vector< LeftType, Dimension >& left
      , RightType const& right 
    )
    {
        vector< RightType, Dimension > right_vector = {};
        for( std::size_t i = 0; i < Dimension; ++i )
            right_vector[ i ] = right;

        return left += right_vector;
    }

    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension > operator +(
        vector< LeftType, Dimension > left
      , vector< RightType, Dimension > const& right
    )
    {
        return left += right;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension > operator +(
        vector< LeftType, Dimension > left
      , RightType const& right 
    )
    {
        return left += right;
    }
    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< RightType, Dimension > operator +(
        LeftType const& left
      , vector< RightType, Dimension > right
    )
    {
        return right += left;
    }

    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension >& operator -=(
        vector< LeftType, Dimension >& left
      , vector< RightType, Dimension > const& right 
    )
    {
        for( std::size_t i = 0; i < Dimension; --i )
            left[ i ] -= right[ i ];

        return left;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension >& operator -=(
        vector< LeftType, Dimension >& left
      , RightType const& right 
    )
    {
        vector< RightType, Dimension > right_vector = {};
        for( std::size_t i = 0; i < Dimension; --i )
            right_vector[ i ] = right;

        return left -= right_vector;
    }

    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension > operator -(
        vector< LeftType, Dimension > left
      , vector< RightType, Dimension > const& right
    )
    {
        return left -= right;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension > operator -(
        vector< LeftType, Dimension > left
      , RightType const& right 
    )
    {
        return left -= right;
    }
    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< RightType, Dimension > operator -(
        LeftType const& left
      , vector< RightType, Dimension > right
    )
    {
        return right -= left;
    }
    
    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension >& operator *=(
        vector< LeftType, Dimension >& left
      , vector< RightType, Dimension > const& right 
    )
    {
        for( std::size_t i = 0; i < Dimension; ++i )
            left[ i ] *= right[ i ];

        return left;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension >& operator *=(
        vector< LeftType, Dimension >& left
      , RightType const& right 
    )
    {
        vector< RightType, Dimension > right_vector = {};
        for( std::size_t i = 0; i < Dimension; ++i )
            right_vector[ i ] = right;

        return left *= right_vector;
    }

    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension > operator *(
        vector< LeftType, Dimension > left
      , vector< RightType, Dimension > const& right
    )
    {
        return left *= right;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension > operator *(
        vector< LeftType, Dimension > left
      , RightType const& right 
    )
    {
        return left *= right;
    }
    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< RightType, Dimension > operator *(
        LeftType const& left
      , vector< RightType, Dimension > right
    )
    {
        return right *= left;
    }

    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension >& operator /=(
        vector< LeftType, Dimension >& left
      , vector< RightType, Dimension > const& right 
    )
    {
        for( std::size_t i = 0; i < Dimension; ++i )
            left[ i ] /= right[ i ];

        return left;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension >& operator /=(
        vector< LeftType, Dimension >& left
      , RightType const& right 
    )
    {
        vector< RightType, Dimension > right_vector = {};
        for( std::size_t i = 0; i < Dimension; ++i )
            right_vector[ i ] = right;

        return left /= right_vector;
    }

    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< LeftType, Dimension > operator /(
        vector< LeftType, Dimension > left
      , vector< RightType, Dimension > const& right
    )
    {
        return left /= right;
    }
    template< typename LeftType, std::size_t Dimension, typename RightType >
    vector< LeftType, Dimension > operator /(
        vector< LeftType, Dimension > left
      , RightType const& right 
    )
    {
        return left /= right;
    }
    template< typename LeftType, typename RightType, std::size_t Dimension >
    vector< RightType, Dimension > operator /(
        LeftType const& left
      , vector< RightType, Dimension > right
    )
    {
        return right /= left;
    }

    template< typename Type, std::size_t Dimension >
    std::ostream& operator <<( std::ostream & left, vector< Type, Dimension > const & right )
    {
        left << "vector{";
        for( std::size_t i = 0; i < Dimension; ++i )
            left << ( i ? ", " : "" ) << right[i];
        left << "}";

        return left;
    }

} } // namespace eggs::la

#endif /*EGGS_LA_VECTOR_HPP*/
