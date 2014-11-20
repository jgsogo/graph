
#include "stdafx.h"
#include <boost/test/unit_test.hpp>

#include "core/graph/graph.h"

BOOST_AUTO_TEST_SUITE(test_edge_undirected_suite)

using namespace core::graph;

typedef standalone<UNDIRECTED>::edge_type edge;
typedef standalone<UNDIRECTED>::vertex_type vertex;

typedef std::pair<vertex*, vertex*> _t_vertices;

struct fixture {
    vertex v1;
    vertex v2;
    };


BOOST_FIXTURE_TEST_CASE(test_edge_undirected, fixture) {

    // types
    BOOST_CHECK_EQUAL( detail::is_edge_connected<edge>::value, true);
    
    edge e;
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    BOOST_CHECK_NO_THROW(e.disconnect());

    // connect v1 -> v2
    BOOST_CHECK_NO_THROW(e.connect(&v1, &v2));
    BOOST_CHECK_THROW(e.connect(&v1, &v2), std::runtime_error);
    BOOST_CHECK_EQUAL(e.is_connected(), true);
    _t_vertices vertices = e.get_connected();
    BOOST_CHECK_EQUAL( vertices.first==&v1 ||vertices.second==&v1, true);
    BOOST_CHECK_EQUAL( vertices.first==&v2 ||vertices.second==&v2, true);
    
    BOOST_CHECK_NO_THROW(e.disconnect());
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    vertices = e.get_connected();
    BOOST_CHECK_EQUAL(vertices.first, (vertex*)0);
    BOOST_CHECK_EQUAL(vertices.second, (vertex*)0);
    
    // connect v2 -> v1
    BOOST_CHECK_NO_THROW(e.connect(&v2, &v1));
    BOOST_CHECK_THROW(e.connect(&v2, &v1), std::runtime_error);
    BOOST_CHECK_EQUAL(e.is_connected(), true);
    vertices = e.get_connected();
    BOOST_CHECK_EQUAL( vertices.first==&v1 ||vertices.second==&v1, true);
    BOOST_CHECK_EQUAL( vertices.first==&v2 ||vertices.second==&v2, true);
    
    BOOST_CHECK_NO_THROW(e.disconnect());
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    vertices = e.get_connected();
    BOOST_CHECK_EQUAL(vertices.first, (vertex*)0);
    BOOST_CHECK_EQUAL(vertices.second, (vertex*)0);

    // connect v1 -> v1
    BOOST_CHECK_NO_THROW(e.connect(&v1, &v1));
    BOOST_CHECK_THROW(e.connect(&v1, &v1), std::runtime_error);
    BOOST_CHECK_EQUAL(e.is_connected(), true);
    vertices = e.get_connected();
    BOOST_CHECK_EQUAL(vertices.first, &v1);
    BOOST_CHECK_EQUAL(vertices.second, &v1);
    
    BOOST_CHECK_NO_THROW(e.disconnect());
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    vertices = e.get_connected();
    BOOST_CHECK_EQUAL(vertices.first, (vertex*)0);
    BOOST_CHECK_EQUAL(vertices.second, (vertex*)0);
    }


BOOST_AUTO_TEST_SUITE_END()