/**
 * Eggs.LA <eggs/la/matrix.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_MATRIX_HPP
#define EGGS_LA_MATRIX_HPP

#include <eggs/la/matrix_traits.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/static_assert.hpp>

#include <cstddef>
#include <iosfwd>

namespace eggs { namespace la {
    
    template< typename Type, std::size_t Rows, std::size_t Columns >
    class matrix
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
        
        matrix& operator =( matrix< Type, Rows, Columns > const& right )
        {
            for( std::size_t i = 0; i < Rows * Columns; ++i )
                _value[ i ] = right[ i ];

            return *this;
        }
        template< typename RightType >
        matrix& operator =( matrix< RightType, Rows, Columns > const& right )
        {
            for( std::size_t i = 0; i < Rows * Columns; ++i )
                _value[ i ] = right[ i ];

            return *this;
        }

    //private: exposition-only
        Type _value[ Rows * Columns ];
    };

    template< typename Type, std::size_t Rows, std::size_t Columns >
    struct is_matrix< matrix< Type, Rows, Columns > >
      : boost::mpl::true_
    {};

    template< typename Type, std::size_t Rows, std::size_t Columns >
    struct rows< matrix< Type, Rows, Columns > >
      : boost::mpl::size_t< Rows >
    {};

    template< typename Type, std::size_t Rows, std::size_t Columns >
    struct columns< matrix< Type, Rows, Columns > >
      : boost::mpl::size_t< Columns >
    {};

    /** Operators **/

    template< typename Type, std::size_t Rows, std::size_t Columns >
    std::ostream& operator <<( std::ostream& left, matrix< Type, Rows, Columns > const& right )
    {
        left << "matrix{";
        for( std::size_t i = 0; i < Rows * Columns; ++i )
            left << ( i ? ", " : "" ) << right[i];
        left << "}";

        return left;
    }

} } // namespace eggs::la

#endif /*EGGS_LA_MATRIX_HPP*/
