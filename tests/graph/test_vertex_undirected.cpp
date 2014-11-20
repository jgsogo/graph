
#include "stdafx.h"
#include <boost/test/unit_test.hpp>

#include "core/graph/graph.h"

BOOST_AUTO_TEST_SUITE(test_vertex_undirected_suite)

using namespace core::graph;

typedef standalone<UNDIRECTED>::edge_type edge;
typedef standalone<UNDIRECTED>::vertex_type vertex;

struct fixture {
    vertex v1;
    edge e1;
    edge e2;
    };

BOOST_FIXTURE_TEST_CASE(test_vertex_undirected_1edge, fixture) {
    vertex v; // The one we are testing

    BOOST_CHECK_EQUAL(v.get_edges().size(), 0);

    e1.connect(&v, &v1);
    BOOST_CHECK_EQUAL(v.get_edges().size(), 1);
    BOOST_CHECK_EQUAL(*(v.get_edges().begin()), &e1);

    e1.disconnect();
    BOOST_CHECK_EQUAL(v.get_edges().size(), 0);

    e1.connect(&v1, &v);

    e1.disconnect();
    BOOST_CHECK_EQUAL(v.get_edges().size(), 0);

    e1.connect(&v, &v);
    BOOST_CHECK_EQUAL(v.get_edges().size(), 1);
    BOOST_CHECK_EQUAL(*(v.get_edges().begin()), &e1);

    e1.disconnect();
    BOOST_CHECK_EQUAL(v.get_edges().size(), 0);
    }

BOOST_FIXTURE_TEST_CASE(test_vertex_undirected_2edges, fixture) {
    vertex v; // The one we are testing

    BOOST_CHECK_EQUAL(v.get_edges().size(), 0);

    e1.connect(&v, &v1);
    e2.connect(&v, &v1);
    BOOST_CHECK_EQUAL(v.get_edges().size(), 2);

    e1.disconnect();
    BOOST_CHECK_EQUAL(v.get_edges().size(), 1);

    e2.disconnect();
    BOOST_CHECK_EQUAL(v.get_edges().size(), 0);
    
    e1.connect(&v, &v1);
    e2.connect(&v1, &v);
    BOOST_CHECK_EQUAL(v.get_edges().size(), 2);

    e1.disconnect();
    BOOST_CHECK_EQUAL(v.get_edges().size(), 1);

    e2.disconnect();
    BOOST_CHECK_EQUAL(v.get_edges().size(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()