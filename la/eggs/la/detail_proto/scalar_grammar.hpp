/**
 * Eggs.LA <eggs/la/detail_proto/scalar_grammar.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_SCALAR_GRAMMAR_HPP
#define EGGS_LA_DETAIL_PROTO_SCALAR_GRAMMAR_HPP

#include <boost/proto/proto.hpp>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;

    struct scalar_grammar
      : or_<
            terminal< float >
            //not_< 
            //    or_< 
            //        if_< is_vector< _value >(), terminal< _ > >
            //      , if_< is_matrix< _value >(), terminal< _ > >
            //    >
            //>
          , plus< scalar_grammar, scalar_grammar >
          , minus< scalar_grammar, scalar_grammar >
          , multiplies< scalar_grammar, scalar_grammar >
          , divides< scalar_grammar, scalar_grammar >
          , subscript< vector_grammar, terminal< int > >
        >
    {};


} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_SCALAR_GRAMMAR_HPP*/
