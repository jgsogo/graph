
#include "stdafx.h"
#include <boost/test/unit_test.hpp>

#include "core/graph/graph.h"

BOOST_AUTO_TEST_SUITE(test_edge_directed_suite)

using namespace core::graph;

typedef standalone<DIRECTED>::edge_type edge;
typedef standalone<DIRECTED>::vertex_type vertex;

struct fixture {
    vertex v1;
    vertex v2;
    };

BOOST_FIXTURE_TEST_CASE(test_edge_directed, fixture) {
    // BIDIRECTIONAL edge_connected

    // types
    BOOST_CHECK_EQUAL( detail::is_edge_connected<edge>::value, true);
    
    edge e;
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    BOOST_CHECK_NO_THROW(e.disconnect());

    // connect v1 -> v2
    BOOST_CHECK_NO_THROW(e.connect(&v1, &v2));
    BOOST_CHECK_THROW(e.connect(&v1, &v2), std::runtime_error);
    BOOST_CHECK_EQUAL(e.is_connected(), true);
    //BOOST_CHECK_EQUAL(e.get_source(), &v1);
    BOOST_CHECK_EQUAL(e.get_target(), &v2);
    
    BOOST_CHECK_NO_THROW(e.disconnect());
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    //BOOST_CHECK_EQUAL(e.get_source(), (vertex*)0);
    BOOST_CHECK_EQUAL(e.get_target(), (vertex*)0);
    
    // connect v2 -> v1
    BOOST_CHECK_NO_THROW(e.connect(&v2, &v1));
    BOOST_CHECK_THROW(e.connect(&v2, &v1), std::runtime_error);
    BOOST_CHECK_EQUAL(e.is_connected(), true);
    //BOOST_CHECK_EQUAL(e.get_source(), &v2);
    BOOST_CHECK_EQUAL(e.get_target(), &v1);
    
    BOOST_CHECK_NO_THROW(e.disconnect());
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    //BOOST_CHECK_EQUAL(e.get_source(), (vertex*)0);
    BOOST_CHECK_EQUAL(e.get_target(), (vertex*)0);

    // connect v1 -> v1
    BOOST_CHECK_NO_THROW(e.connect(&v1, &v1));
    BOOST_CHECK_THROW(e.connect(&v1, &v1), std::runtime_error);
    BOOST_CHECK_EQUAL(e.is_connected(), true);
    //BOOST_CHECK_EQUAL(e.get_source(), &v1);
    BOOST_CHECK_EQUAL(e.get_target(), &v1);
    
    BOOST_CHECK_NO_THROW(e.disconnect());
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    //BOOST_CHECK_EQUAL(e.get_source(), (vertex*)0);
    BOOST_CHECK_EQUAL(e.get_target(), (vertex*)0);
    }

BOOST_AUTO_TEST_SUITE_END()