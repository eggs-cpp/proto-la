/**
 * Eggs.LA <eggs/la/detail_proto/matrix_grammar.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_MATRIX_GRAMMAR_HPP
#define EGGS_LA_DETAIL_PROTO_MATRIX_GRAMMAR_HPP

#include <eggs/la/detail_proto/matrix_literal.hpp>

#include <boost/proto/proto.hpp>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;
    
    struct matrix_grammar
      : or_<
            matrix_literal
          , vector_grammar
        >
    {};

} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_MATRIX_GRAMMAR_HPP*/
