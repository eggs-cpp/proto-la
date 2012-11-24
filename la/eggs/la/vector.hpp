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

#include <eggs/la/domain.hpp>
#include <eggs/la/vector_traits.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/proto/proto.hpp>

#include <boost/static_assert.hpp>

#include <algorithm>
#include <cstddef>
#include <iosfwd>

namespace eggs { namespace la {

    namespace detail {

        template< typename Vector, typename Expr, typename AssignOp >
        struct vector_proto_assign
        {
            explicit vector_proto_assign( Vector& vector, Expr const& expr )
              : _vector( vector )
              , _expr( expr )
            {}

            template< typename Index >
            BOOST_FORCEINLINE void operator()( Index /*index*/ ) const
            {
                AssignOp()(
                    vector_traits< Vector >::at< Index::value >( _vector )
                  , boost::proto::eval(
                        boost::proto::as_expr( _expr )
                      , detail_proto::component_context< Index::value >()
                    )
                );
            }

            Vector& _vector;
            Expr const& _expr;
        };

        struct assign
        {
            template< typename Left, typename Right >
            void operator()( Left& left, Right const& right ) const
            {
                left = right;
            }
        };
        struct plus_assign
        {
            template< typename Left, typename Right >
            void operator()( Left& left, Right const& right ) const
            {
                left += right;
            }
        };
        struct minus_assign
        {
            template< typename Left, typename Right >
            void operator()( Left& left, Right const& right ) const
            {
                left -= right;
            }
        };
        struct multiplies_assign
        {
            template< typename Left, typename Right >
            void operator()( Left& left, Right const& right ) const
            {
                left *= right;
            }
        };
        struct divides_assign
        {
            template< typename Left, typename Right >
            void operator()( Left& left, Right const& right ) const
            {
                left /= right;
            }
        };
        
        template< typename AssignOp, typename Vector, typename Expr >
        void assign_component_wise( Vector& vector, Expr const& expr )
        {
            boost::mpl::for_each<
                boost::mpl::range_c<
                    std::size_t
                  , 0, dimension< Vector >::type::value
                >
            >(
                vector_proto_assign< Vector, Expr, AssignOp >( vector, expr )
            );
        }

    } // namespace detail

    template< typename Type, std::size_t Dimension >
    class vector
      : public boost::proto::extends<
            typename boost::proto::terminal< Type[ Dimension ] >::type
          , vector< Type, Dimension >
          , domain
        >
    {
    public:
        vector()
        {
            std::fill(
                data() + 0, data() + Dimension
              , Type()
            );
        }

        vector( vector const& right )
        {
            std::copy(
                right.data() + 0, right.data() + Dimension
              , data()
            );
        }
        template< typename Expr >
        vector( Expr const& right )
        {
            detail::assign_component_wise< detail::assign >( *this, right );
        }

        Type* data()
        {
            return boost::proto::value( *this );
        }
        Type const* data() const
        {
            return boost::proto::value( *this );
        }

        Type& operator []( std::size_t index )
        {
            return boost::proto::value( *this )[ index ];
        }
        Type const& operator []( std::size_t index ) const
        {
            return boost::proto::value( *this )[ index ];
        }
        
        vector& operator =( vector const& right )
        {
            std::copy(
                right.data() + 0, right.data() + Dimension
              , data()
            );
            return *this;
        }
        template< typename Expr >
        vector& operator =( Expr const& right )
        {
            detail::assign_component_wise< detail::assign >( *this, right );
            return *this;
        }
    };

    template< typename Type, std::size_t Dimension >
    struct is_vector< vector< Type, Dimension > >
      : boost::mpl::true_
    {};
    
    template< typename Type, std::size_t Dimension >
    struct vector_traits< vector< Type, Dimension > >
    {
        typedef vector< Type, Dimension > vector_type;

        typedef Type scalar_type;
        static std::size_t const dimension = Dimension;

        template< std::size_t Index >
        static scalar_type& at( vector_type& v )
        {
            return v[ Index ];
        }
        template< std::size_t Index >
        static scalar_type const& at( vector_type const& v )
        {
            return v[ Index ];
        }
    };

    /** Operators **/

    template<
        typename Type, std::size_t Dimension
      , typename Expr
    >
    vector< Type, Dimension >& operator +=( vector< Type, Dimension >& left, Expr const& right )
    {
        detail::assign_component_wise< detail::plus_assign >( left, right );
        return left;
    }
    template<
        typename Type, std::size_t Dimension
      , typename Expr
    >
    vector< Type, Dimension >& operator -=( vector< Type, Dimension >& left, Expr const& right )
    {
        detail::assign_component_wise< detail::minus_assign >( left, right );
        return left;
    }
    template<
        typename Type, std::size_t Dimension
      , typename Expr
    >
    vector< Type, Dimension >& operator *=( vector< Type, Dimension >& left, Expr const& right )
    {
        detail::assign_component_wise< detail::multiplies_assign >( left, right );
        return left;
    }
    template<
        typename Type, std::size_t Dimension
      , typename Expr
    >
    vector< Type, Dimension >& operator /=( vector< Type, Dimension >& left, Expr const& right )
    {
        detail::assign_component_wise< detail::divides_assign >( left, right );
        return left;
    }
    
    template< typename Type, std::size_t Dimension >
    void print( std::ostream& stream, vector< Type, Dimension > const& v )
    {
        stream << "vector{";
        for( std::size_t i = 0; i < Dimension; ++i )
            stream << ( i ? ", " : "" ) << v[i];
        stream << "}";
    }

} } // namespace eggs::la

#endif /*EGGS_LA_VECTOR_HPP*/
