
#include "stdafx.h"
#include <boost/test/unit_test.hpp>

#include "core/graph/graph.h"

BOOST_AUTO_TEST_SUITE(test_chart_bidirectional_suite)

using namespace core::graph;

typedef in_chart<BIDIRECTIONAL>::vertex_type vertex;
typedef in_chart<BIDIRECTIONAL>::edge_type edge;
typedef in_chart<BIDIRECTIONAL>::chart_type chart_bidirectional;
typedef chart_bidirectional::vertex_type_ptr vertex_type_ptr;
typedef chart_bidirectional::edge_type_ptr edge_type_ptr;

typedef std::pair<chart_bidirectional::vertex_id, bool> _t_vertex_added;
typedef std::pair<chart_bidirectional::edge_id, bool> _t_edge_added;

typedef std::vector<chart_bidirectional::edge_id> _t_edge_ids;

BOOST_AUTO_TEST_CASE(test_chart_bidirectional) {
    chart_bidirectional c;
    vertex_type_ptr v1(new vertex());
    vertex_type_ptr v2(new vertex());
    edge_type_ptr e1(new edge());
    edge_type_ptr e2(new edge());

    // vertices on graph
    _t_vertex_added v1_ret = c.add_vertex(v1);
    _t_vertex_added v2_ret = c.add_vertex(v2);

    // connect in graph
    _t_edge_added e1_ret = c.add_edge(e1, v1_ret.first, v2_ret.first);

    // connect outside graph
    e2->connect(v1.get(), v2.get());

    // Check data from graph
    BOOST_CHECK_EQUAL(c.get_source(e1_ret.first), v1_ret.first);
    BOOST_CHECK_EQUAL(c.get_target(e1_ret.first), v2_ret.first);

    _t_edge_ids _edge_ids;
    c.get_edges_outgoing(v1_ret.first, _edge_ids);
    BOOST_CHECK_EQUAL(_edge_ids.size(), 1);
    BOOST_CHECK_EQUAL(c.get_edge(*_edge_ids.begin()), e1);
    
    _edge_ids.clear();
    c.get_edges_outgoing(v2_ret.first, _edge_ids);
    BOOST_CHECK_EQUAL(_edge_ids.size(), 0);
    
    _edge_ids.clear();
    c.get_edges_incoming(v1_ret.first, _edge_ids);
    BOOST_CHECK_EQUAL(_edge_ids.size(), 0);
    
    _edge_ids.clear();
    c.get_edges_incoming(v2_ret.first, _edge_ids);
    BOOST_CHECK_EQUAL(_edge_ids.size(), 1);
    BOOST_CHECK_EQUAL(c.get_edge(*_edge_ids.begin()), e1);
    
    // Verify data from vertices
    BOOST_CHECK_EQUAL(v1->get_outgoing().size(), 2);
    BOOST_CHECK_EQUAL(v2->get_incoming().size(), 2);
    }

BOOST_AUTO_TEST_SUITE_END()