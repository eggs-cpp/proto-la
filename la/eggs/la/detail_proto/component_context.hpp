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

#include <boost/proto/proto.hpp>

#include <boost/utility/enable_if.hpp>

#include <cstddef>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;
    
    class component_context
    {
    public:
        explicit component_context( std::size_t index )
          : _index( index )
        {}

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
            typedef int& result_type;

            result_type operator ()(
                Expr& expr
              , component_context const& context
            ) const
            {
                return child( expr )[ context._index ];
            }
        };

    private:
        std::size_t const _index;
    };

} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_COMPONENT_CONTEXT_HPP*/
