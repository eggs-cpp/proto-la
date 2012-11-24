/**
 * Eggs.LA <eggs/la/detail_proto/vector_grammar.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_VECTOR_GRAMMAR_HPP
#define EGGS_LA_DETAIL_PROTO_VECTOR_GRAMMAR_HPP

#include <eggs/la/detail_proto/vector_literal.hpp>

#include <boost/proto/proto.hpp>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;

    struct vector_grammar_impl
    {
        template< typename Tag >
        struct case_
          : not_< _ >
        {};
    };

    template<>
    struct vector_grammar_impl::case_< tag::terminal >
      : vector_literal
    {};
    
    template<>
    struct vector_grammar_impl::case_< tag::plus >
      : or_<
            plus< vector_grammar, vector_grammar >
          , plus< vector_grammar, scalar_grammar >
          , plus< scalar_grammar, vector_grammar >
        >
    {};
    
    template<>
    struct vector_grammar_impl::case_< tag::minus >
      : or_<
            minus< vector_grammar, vector_grammar >
          , minus< vector_grammar, scalar_grammar >
          , minus< scalar_grammar, vector_grammar >
        >
    {};
    
    template<>
    struct vector_grammar_impl::case_< tag::multiplies >
      : or_<
            multiplies< vector_grammar, vector_grammar >
          , multiplies< vector_grammar, scalar_grammar >
          , multiplies< scalar_grammar, vector_grammar >
        >
    {};
    
    template<>
    struct vector_grammar_impl::case_< tag::divides >
      : or_<
            divides< vector_grammar, vector_grammar >
          , divides< vector_grammar, scalar_grammar >
          , divides< scalar_grammar, vector_grammar >
        >
    {};

    template<>
    struct vector_grammar_impl::case_< tag::comma >
      : _
    {};

    struct vector_grammar
      : switch_< vector_grammar_impl >
    {};

} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_VECTOR_GRAMMAR_HPP*/
