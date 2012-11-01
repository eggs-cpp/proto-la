/**
 * Eggs.LA <eggs/la/detail_proto/distribute_subscript.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_DETAIL_PROTO_DISTRIBUTE_SUBSCRIPT_HPP
#define EGGS_LA_DETAIL_PROTO_DISTRIBUTE_SUBSCRIPT_HPP

#include <eggs/la/detail_proto/scalar_grammar.hpp>
#include <eggs/la/detail_proto/vector_literal.hpp>

#include <boost/proto/proto.hpp>

namespace eggs { namespace la { namespace detail_proto {

    using namespace boost::proto;

    struct distribute_subscript
      : or_<
            scalar_grammar
          , when<
                vector_literal
              , _make_subscript( _, _byval( _state ) )
            >
          , plus< distribute_subscript, distribute_subscript >
          , minus< distribute_subscript, distribute_subscript >
          , multiplies< distribute_subscript, distribute_subscript >
          , divides< distribute_subscript, distribute_subscript >
          , assign< distribute_subscript, distribute_subscript >
        >
    {};

} } } // namespace eggs::la::detail_proto

#endif /*EGGS_LA_DETAIL_PROTO_DISTRIBUTE_SUBSCRIPT_HPP*/
