
#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include "core/graph/graph.h"

BOOST_AUTO_TEST_SUITE(test_vertex_suite)

using namespace core::graph;

typedef boost::mpl::list< standalone<UNDIRECTED>, standalone<DIRECTED>, standalone<BIDIRECTIONAL>> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_vertex, T, test_types) {
    typedef typename T::vertex_type vertex;
    typedef typename T::edge_type edge;

    BOOST_CHECK_EQUAL( detail::is_vertex_connected<vertex>::value, true);
    BOOST_CHECK_EQUAL( detail::is_vertex_multichart<vertex>::value, false);

    vertex v1;
    // There is nothing to test
    }

BOOST_AUTO_TEST_SUITE_END()