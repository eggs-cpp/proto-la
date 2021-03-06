/**
 * Eggs.LA <main.cpp>
 * 
 * Copyright Agust�n Berg�, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#include <eggs/la/matrix.hpp>
#include <eggs/la/vector.hpp>

#include <boost/proto/proto.hpp>
#include <boost/proto/proto_typeof.hpp>

#include <boost/timer.hpp>

#include <iostream>
#include <sstream>

#ifdef NDEBUG
static const int cloops = 100000000;
#else
static const int cloops = 1;
#endif /*NDEBUG*/

typedef eggs::la::vector< int, 3 > ivec3;

ivec3 eager_time( ivec3 const& p, ivec3 const& q, ivec3 const& r )
{
    ivec3 ret;

    boost::timer tim;
    tim.restart();
    for( int i = 0; i < cloops; ++i )
    {
        ret += ivec3( ivec3( p * 3 ) + ivec3( r - q ) );
    }
    double d = tim.elapsed();
    
    std::cout << d << 's' << '\n';
    return ret;
}

ivec3 lazy_time( ivec3 const& p, ivec3 const& q, ivec3 const& r )
{
    ivec3 ret;

    boost::timer tim;
    tim.restart();
    for( int i = 0; i < cloops; ++i )
    {
        ret += ( p * 3 + ( r - q ) );
    }
    double d = tim.elapsed();
    
    std::cout << d << 's' << '\n';
    return ret;
}

ivec3 unrolled_time( ivec3 const& p, ivec3 const& q, ivec3 const& r )
{
    ivec3 ret;

    boost::timer tim;
    tim.restart();
    for( int i = 0; i < cloops; ++i )
    {
        ret[0] += ( p[0] * 3 + ( r[0] - q[0] ) );
        ret[1] += ( p[1] * 3 + ( r[1] - q[1] ) );
        ret[2] += ( p[2] * 3 + ( r[2] - q[2] ) );
    }
    double d = tim.elapsed();
    
    std::cout << d << 's' << '\n';
    return ret;
}

int main( int argc, char** argv )
{
    std::cout << "\n\n --- timing --- \n\n" << std::endl;
            
    std::stringstream input( "0 1 2\n3 4 5\n6 7 8" );
    ivec3 p, q, r;
            
    input.seekg( 0, std::ios::beg );
    input
        >> p[0] >> p[1] >> p[2]
        >> q[0] >> q[1] >> q[2]
        >> r[0] >> r[1] >> r[2]
        ;
    std::cout << "Eager: ";
    std::cout << eager_time( p, q, r );
    std::cout << "\n" << std::endl;
            
    input.seekg( 0, std::ios::beg );
    input
        >> p[0] >> p[1] >> p[2]
        >> q[0] >> q[1] >> q[2]
        >> r[0] >> r[1] >> r[2]
        ;
    std::cout << "Lazy: ";
    std::cout << lazy_time( p, q, r );
    std::cout << "\n" << std::endl;
            
    input.seekg( 0, std::ios::beg );
    input
        >> p[0] >> p[1] >> p[2]
        >> q[0] >> q[1] >> q[2]
        >> r[0] >> r[1] >> r[2]
        ;
    std::cout << "Unrolled: ";
    std::cout << unrolled_time( p, q, r );
    std::cout << "\n" << std::endl;

    int breakpoint = 3;
    std::cin >> breakpoint;

    return 0;
}
