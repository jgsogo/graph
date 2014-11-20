
#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include "core/graph/graph.h"

BOOST_AUTO_TEST_SUITE(test_edge_suite)

using namespace core::graph;

typedef boost::mpl::list< standalone<UNDIRECTED>, standalone<DIRECTED>, standalone<BIDIRECTIONAL>> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_edge, T, test_types) {
    typedef typename T::vertex_type vertex;
    typedef typename T::edge_type edge;

    BOOST_CHECK_EQUAL( detail::is_edge_connected<edge>::value, true);

    edge e;
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    BOOST_CHECK_NO_THROW(e.disconnect());

    vertex v1, v2;
    // connect v1 -> v2
    BOOST_CHECK_NO_THROW(e.connect(&v1, &v2));
    BOOST_CHECK_THROW(e.connect(&v1, &v2), std::runtime_error);
    BOOST_CHECK_EQUAL(e.is_connected(), true);
    
    BOOST_CHECK_NO_THROW(e.disconnect());
    BOOST_CHECK_EQUAL(e.is_connected(), false);
    }

BOOST_AUTO_TEST_SUITE_END()