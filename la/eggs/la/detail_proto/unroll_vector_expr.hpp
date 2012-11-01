/**
 * Eggs.LA <eggs/la/detail_proto/unroll_vector_expr.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_UNROLL_VECTOR_EXPR_HPP
#define EGGS_LA_DETAIL_PROTO_UNROLL_VECTOR_EXPR_HPP

#include <eggs/la/detail_proto/distribute_subscript.hpp>
#include <eggs/la/detail_proto/vector_literal.hpp>

#include <eggs/la/vector_traits.hpp>

#include <boost/mpl/size_t.hpp>

#include <boost/proto/proto.hpp>

#include <boost/ref.hpp>

#include <boost/type_traits/remove_reference.hpp>

#include <cstddef>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;
    
    template< std::size_t I, std::size_t N >
    struct unroll_vector_expr_c;

    template< std::size_t I, std::size_t N >
    struct unroll_vector_expr_c
      : transform< unroll_vector_expr_c< I, N > >
    {
        template< typename Expr, typename State, typename Data >
        struct impl
          : transform_impl< Expr, State, Data >
        {
            typedef
                typename result_of::make_expr<
                    tag::comma
                  , typename boost::result_of<
                        distribute_subscript(
                            Expr
                          , typename result_of::make_expr<
                                tag::terminal
                              , boost::mpl::size_t< I - 1 >
                            >::type
                        )
                    >::type
                  , typename boost::result_of<
                        unroll_vector_expr_c< I + 1, N >(
                            Expr
                        )
                    >::type
                >::type
                result_type;

            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                return
                    make_expr< tag::comma >(
                        distribute_subscript()(
                            expr
                          , make_expr< tag::terminal >( 
                                boost::mpl::size_t< I - 1 >()
                            )
                        )
                      , unroll_vector_expr_c< I + 1, N >() (
                            expr
                        )
                    );
            }
        };
    };

    template< std::size_t N >
    struct unroll_vector_expr_c< N, N >
      : transform< unroll_vector_expr_c< N, N > >
    {
        template< typename Expr, typename State, typename Data >
        struct impl
          : transform_impl< Expr, State, Data >
        {
            typedef
                typename boost::result_of<
                    distribute_subscript(
                        Expr
                      , typename result_of::make_expr<
                            tag::terminal
                          , boost::mpl::size_t< N - 1 >
                        >::type
                    )
                >::type
                result_type;

            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                return
                    distribute_subscript()(
                        expr
                      , make_expr< tag::terminal >( 
                            boost::mpl::size_t< N - 1 >()
                        )
                    );
            }
        };
    };

    struct unroll_vector_expr
      : transform< unroll_vector_expr >
    {
        template< typename Expr, typename State, typename Data >
        struct impl
          : transform_impl< Expr, State, Data >
        {
            typedef
                typename dimension<
                    typename boost::remove_reference<
                        typename boost::result_of<
                            _value( State )
                        >::type
                    >::type
                >::type
                dimension;

            typedef
                typename result_of::make_expr<
                    tag::comma
                  , typename boost::result_of<
                        unroll_vector_expr_c< 1, dimension::value >(
                            Expr
                        )
                    >::type
                  , State&
                >::type
                result_type;

            result_type operator ()(
                typename impl::expr_param expr
              , typename impl::state_param state
              , typename impl::data_param data
            ) const
            {
                return
                    make_expr< tag::comma >(
                        unroll_vector_expr_c< 1, dimension::value >()(
                            expr
                        )
                      , boost::ref( state )
                    );
            }
        };
    };

} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_UNROLL_VECTOR_EXPR_HPP*/
