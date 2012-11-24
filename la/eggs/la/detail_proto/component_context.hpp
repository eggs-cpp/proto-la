/**
 * Eggs.LA <eggs/la/detail_proto/component_context.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_COMPONENT_CONTEXT_HPP
#define EGGS_LA_DETAIL_PROTO_COMPONENT_CONTEXT_HPP

#include <eggs/la/detail_proto/vector_literal.hpp>
#include <eggs/la/vector_traits.hpp>

#include <boost/mpl/eval_if.hpp>

#include <boost/proto/proto.hpp>

#include <boost/utility/enable_if.hpp>

#include <cstddef>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;
    
    template< std::size_t Index >
    struct component_context
    {
        template<
            typename Expr
          , typename Tag = typename tag_of< Expr >::type
          , typename Enable = void
        >
        struct eval
          : default_context::eval<
                Expr
              , component_context const
            >
        {};

        template< typename Expr >
        struct eval<
            Expr
          , tag::terminal
          , typename boost::enable_if<
                typename matches<
                    Expr
                  , detail_proto::vector_literal
                >::type
            >::type
        >
        {
            typedef
                typename scalar_type< Expr >::type&
                result_type;

            result_type operator ()(
                Expr& expr
              , component_context const& context
            ) const
            {
                return value( expr )[ Index ];
            }
        };
        template< typename Expr >
        struct eval<
            Expr const
          , tag::terminal
          , typename boost::enable_if<
                typename matches<
                    Expr const
                  , detail_proto::vector_literal
                >::type
            >::type
        >
        {
            typedef
                typename scalar_type< Expr >::type const&
                result_type;

            result_type operator ()(
                Expr const& expr
              , component_context const& context
            ) const
            {
                return value( expr )[ Index ];
            }
        };
    };

} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_COMPONENT_CONTEXT_HPP*/
