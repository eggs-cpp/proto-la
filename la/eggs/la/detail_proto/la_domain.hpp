/**
 * Eggs.LA <eggs/la/detail_proto/la_domain.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_LA_DOMAIN_HPP
#define EGGS_LA_DETAIL_PROTO_LA_DOMAIN_HPP

#include <boost/proto/proto.hpp>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;

    template< typename Expr >
    struct la_expr;

    struct scalar_grammar;
    struct vector_grammar;
    struct matrix_grammar;

    struct la_grammar
      : or_<
            scalar_grammar
          , vector_grammar
          , matrix_grammar
        >
    {};

    struct la_domain
      : domain<
            pod_generator< la_expr >
          , la_grammar
        >
    {};

    template< typename Expr >
    struct la_expr
    {
        BOOST_PROTO_EXTENDS( Expr, la_expr< Expr >, la_domain );
    };

} } } // namespace eggs::la::detail_proto

#include <eggs/la/detail_proto/matrix_grammar.hpp>
#include <eggs/la/detail_proto/scalar_grammar.hpp>
#include <eggs/la/detail_proto/vector_grammar.hpp>

#endif /*EGGS_LA_DETAIL_PROTO_LA_DOMAIN_HPP*/
