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

#include <eggs/la/detail_proto/component_context.hpp>
#include <eggs/la/detail_proto/la_domain.hpp>
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
    
    template< typename Type, std::size_t Dimension >
    class vector;

    namespace detail {

        template< typename Expr >
        struct eval_component_wise_impl
        {
            explicit eval_component_wise_impl( Expr const& expr )
              : _expr( expr )
            {}

            template< typename Index >
            void operator()( Index /*index*/ ) const
            {
                boost::proto::eval(
                    _expr
                  , detail_proto::component_context< Index::value >()
                );
            }

            Expr const& _expr;
        };
        
        template< std::size_t Dimension, typename Expr >
        void eval_component_wise( Expr const& expr )
        {
            boost::mpl::for_each<
                boost::mpl::range_c<
                    std::size_t
                  , 0, Dimension
                >
              , eval_component_wise_impl< Expr > const&
            >(
                eval_component_wise_impl< Expr >( expr )
            );
        }

        template< typename Tag, typename Type, std::size_t Dimension, typename Expr >
        void eval_component_wise( vector< Type, Dimension >& vector, Expr const& expr )
        {
            eval_component_wise< Dimension >(
                boost::proto::make_expr< Tag >(
                    boost::ref( vector ), boost::cref( expr )
                )
            );
        }

    } // namespace detail

    template< typename Type, std::size_t Dimension >
    class vector
      : public boost::proto::extends<
            typename boost::proto::terminal< Type[ Dimension ] >::type
          , vector< Type, Dimension >
          , detail_proto::la_domain
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
            detail::eval_component_wise< boost::proto::tag::assign >( *this, right );
        }
        template< typename Expr >
        vector( Expr const& right )
        {
            detail::eval_component_wise< boost::proto::tag::assign >( *this, right );
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
            detail::eval_component_wise< boost::proto::tag::assign >( *this, right );
            return *this;
        }
        template< typename Expr >
        vector& operator =( Expr const& right )
        {
            detail::eval_component_wise< boost::proto::tag::assign >( *this, right );
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
        detail::eval_component_wise< boost::proto::tag::plus_assign >( left, right );
        return left;
    }
    template<
        typename Type, std::size_t Dimension
      , typename Expr
    >
    vector< Type, Dimension >& operator -=( vector< Type, Dimension >& left, Expr const& right )
    {
        detail::eval_component_wise< boost::proto::tag::minus_assign >( left, right );
        return left;
    }
    template<
        typename Type, std::size_t Dimension
      , typename Expr
    >
    vector< Type, Dimension >& operator *=( vector< Type, Dimension >& left, Expr const& right )
    {
        detail::eval_component_wise< boost::proto::tag::multiplies_assign >( left, right );
        return left;
    }
    template<
        typename Type, std::size_t Dimension
      , typename Expr
    >
    vector< Type, Dimension >& operator /=( vector< Type, Dimension >& left, Expr const& right )
    {
        detail::eval_component_wise< boost::proto::tag::divides_assign >( left, right );
        return left;
    }
    
    template< typename Type, std::size_t Dimension >
    std::ostream& operator <<( std::ostream& left, vector< Type, Dimension > const& right )
    {
        left << "vector{";
        for( std::size_t i = 0; i < Dimension; ++i )
        {
            left << ( i ? ", " : "" ) << right[ i ];
        }
        left << "}";
        return left;
    }

} } // namespace eggs::la

#endif /*EGGS_LA_VECTOR_HPP*/
