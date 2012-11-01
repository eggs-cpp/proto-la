/**
 * Eggs.LA <eggs/la/detail_proto/vector_literal.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_VECTOR_LITERAL_HPP
#define EGGS_LA_DETAIL_PROTO_VECTOR_LITERAL_HPP

#include <eggs/la/vector_traits.hpp>

#include <boost/proto/proto.hpp>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;

    struct vector_literal
      : and_<
            terminal< _ >
          , if_< is_vector< _value >() >
        >
    {};

} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_VECTOR_GRAMMAR_HPP*/
