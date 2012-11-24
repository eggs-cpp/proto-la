/**
 * Eggs.LA <eggs/la/common_traits.hpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#ifndef EGGS_LA_COMMON_TRAITS_HPP
#define EGGS_LA_COMMON_TRAITS_HPP

namespace eggs { namespace la {

    template< typename Type, typename Enable = void >
    struct scalar_type;

    template< typename Left, typename Right, typename Enable = void >
    struct is_same_dimension;

} } // namespace eggs::la

#endif /*EGGS_LA_COMMON_TRAITS_HPP*/
