/**
 * Eggs.LA <main.cpp>
 * 
 * Copyright Agustín Bergé, Fusion Fenix 2012
 * 
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * Library home page: http://github.com/eggs-cpp/eggs-la
 */

#include <eggs/la/domain.hpp>
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

ivec3 unrolled_time( ivec3 const& p, ivec3 const& q, ivec3 const& r )
{
    ivec3 ret;

    boost::timer tim;
    tim.restart();
    for (int i = 0; i < cloops; ++i)
    {
        ret[0] += ( p[0] * 3 + ( r[0] - q[0] ) );
        ret[1] += ( p[1] * 3 + ( r[1] - q[1] ) );
        ret[2] += ( p[2] * 3 + ( r[2] - q[2] ) );
    }
    double d = tim.elapsed();

    std::cout << " time: " << d << std::endl;
    return ret;
}

template< typename Expr >
ivec3 do_proto_time( Expr& expr )
{
    ivec3 ret;

    boost::timer tim;
    tim.restart();
    for (int i = 0; i < cloops; ++i)
    {
        ret += expr;
    }
    double d = tim.elapsed();
    
    std::cout << " time: " << d << std::endl;
    return ret;
}

ivec3 proto_time( ivec3 const& p, ivec3 const& q, ivec3 const& r )
{
    return do_proto_time( p * 3 + ( r - q ) );
}

ivec3 full_proto_time( ivec3 const& p, ivec3 const& q, ivec3 const& r )
{
    ivec3 ret;

    boost::timer tim;
    tim.restart();
    for (int i = 0; i < cloops; ++i)
    {
        ret += ( p * 3 + ( r - q ) );
    }
    double d = tim.elapsed();

    std::cout << " time: " << d << std::endl;
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
    std::cout << "Unrolled: ";
    print( std::cout, unrolled_time( p, q, r ) );
    std::cout << "\n\n";
            
    input.seekg( 0, std::ios::beg );
    input
        >> p[0] >> p[1] >> p[2]
        >> q[0] >> q[1] >> q[2]
        >> r[0] >> r[1] >> r[2]
        ;
    std::cout << "Proto: ";
    print( std::cout, proto_time( p, q, r ) );
    std::cout << "\n\n";
            
    input.seekg( 0, std::ios::beg );
    input
        >> p[0] >> p[1] >> p[2]
        >> q[0] >> q[1] >> q[2]
        >> r[0] >> r[1] >> r[2]
        ;
    std::cout << "Full Proto: ";
    print( std::cout, full_proto_time( p, q, r ) );
    std::cout << "\n\n";

    int breakpoint = 3;
    std::cin >> breakpoint;

    return 0;
}
