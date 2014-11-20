
#include "stdafx.h"
#include <boost/test/unit_test.hpp>

#include "core/graph/graph.h"
#include "fixture_graph_simple.h"

BOOST_AUTO_TEST_SUITE(test_dfs_suite)

typedef core::graph::in_chart<core::graph::UNDIRECTED>::chart_type chart_type;

BOOST_AUTO_TEST_CASE(test_connected_components) {
    chart_type chart;

    chart_type::_t_connected_components cmp_connected;

    // vertices
    std::pair<chart_type::vertex_id, bool> a,b,c,d,e,f,g;
    chart_type::vertex_type_ptr A(new chart_type::vertex_type());
    chart_type::vertex_type_ptr B(new chart_type::vertex_type());
    chart_type::vertex_type_ptr C(new chart_type::vertex_type());
    chart_type::vertex_type_ptr D(new chart_type::vertex_type());
    chart_type::vertex_type_ptr E(new chart_type::vertex_type());
    chart_type::vertex_type_ptr F(new chart_type::vertex_type());
    chart_type::vertex_type_ptr G(new chart_type::vertex_type());
    
    a = chart.add_vertex(A);
    b = chart.add_vertex(B);
    c = chart.add_vertex(C);
    d = chart.add_vertex(D);
    e = chart.add_vertex(E);
    f = chart.add_vertex(F);
    g = chart.add_vertex(G);

    // edges
    std::pair<chart_type::edge_id, bool> ab;
    
    ab = chart.create_edge(a.first, b.first);

    int n = chart.connected_components(cmp_connected);
    }

BOOST_AUTO_TEST_SUITE_END()