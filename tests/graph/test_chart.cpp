
#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include "core/graph/graph.h"

BOOST_AUTO_TEST_SUITE(test_chart_suite)

using namespace core::graph;

typedef boost::mpl::list< in_chart<UNDIRECTED>, in_chart<DIRECTED>, in_chart<BIDIRECTIONAL>> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_chart_types, T, test_types) {
    typedef typename T::vertex_type vertex;
    typedef typename T::edge_type edge;
    typedef typename T::chart_type chart;

    //BOOST_CHECK_EQUAL( std::is_same<vertex, typename chart::vertex_type>::value , true);
    //BOOST_CHECK_EQUAL( std::is_same<edge, typename chart::edge_type>::value , true);

    chart c;
    vertex v1, v2;
    edge e1, e2;

    }

BOOST_AUTO_TEST_CASE_TEMPLATE(test_chart_vertices, T, test_types) {
    typedef typename T::vertex_type vertex;
    typedef typename T::edge_type edge;
    typedef typename T::chart_type chart;
    typedef chart::vertex_type_ptr vertex_type_ptr;
    typedef chart::edge_type_ptr edge_type_ptr;

    typedef std::pair<chart::vertex_id, bool> _t_vertex_added;

    chart c;
    vertex_type_ptr v1(new vertex());
    vertex_type_ptr v2(new vertex());
    _t_vertex_added v1_ret, v1_ret2, v2_ret;
    
    // add vertex 1
    BOOST_CHECK_NO_THROW(v1_ret = c.add_vertex(v1));
    BOOST_CHECK_EQUAL(v1_ret.second, true);
    BOOST_CHECK_EQUAL(c.get_vertices().size(), 1);
    BOOST_CHECK_EQUAL(c.get_vertex(v1_ret.first), v1);
    BOOST_CHECK_EQUAL(c.get_vertex_id(v1), v1_ret.first);

    // cannot add the same vertex twice
    BOOST_CHECK_NO_THROW(v1_ret2 = c.add_vertex(v1));
    BOOST_CHECK_EQUAL(v1_ret2.second, false);
    BOOST_CHECK_EQUAL(v1_ret2.first, v1_ret.first);
    BOOST_CHECK_EQUAL(c.get_vertices().size(), 1);
    BOOST_CHECK_EQUAL(c.get_vertex(v1_ret.first), v1);
    BOOST_CHECK_EQUAL(c.get_vertex_id(v1), v1_ret.first);

    // add vertex 2
    BOOST_CHECK_NO_THROW(v2_ret = c.add_vertex(v2));
    BOOST_CHECK_EQUAL(v2_ret.second, true);
    BOOST_CHECK_EQUAL(c.get_vertices().size(), 2);
    BOOST_CHECK_EQUAL(c.get_vertex(v2_ret.first), v2);
    BOOST_CHECK_EQUAL(c.get_vertex_id(v2), v2_ret.first);

    // remove vertex 2
    BOOST_CHECK_NO_THROW(c.remove_vertex(v2));
    BOOST_CHECK_NO_THROW(c.remove_vertex(v2)); // no throw, although it doesn't belong to the chart
    BOOST_CHECK_EQUAL(c.get_vertices().size(), 1);
    //      vertex_id must be the same
    BOOST_CHECK_EQUAL(c.get_vertex(v1_ret.first), v1);
    BOOST_CHECK_EQUAL(c.get_vertex_id(v1), v1_ret.first);
    //      raises for removed data
    //! \todo TODO: raises a "memory access violation" which is not catchable (without changing project properties) \sa: http://msdn.microsoft.com/en-us/library/1deeycx5%28v=vs.80%29.aspx
    //BOOST_CHECK_THROW(c.get_vertex(v2_ret.first), std::runtime_error);
    //BOOST_CHECK_THROW(c.get_vertex_id(v2), std::runtime_error);

    // remove vertex 1
    BOOST_CHECK_NO_THROW(c.remove_vertex(v1));
    BOOST_CHECK_EQUAL(c.get_vertices().size(), 0);
    }

BOOST_AUTO_TEST_CASE_TEMPLATE(test_chart_edges, T, test_types) {
    typedef typename T::vertex_type vertex;
    typedef typename T::edge_type edge;
    typedef typename T::chart_type chart;
    typedef chart::vertex_type_ptr vertex_type_ptr;
    typedef chart::edge_type_ptr edge_type_ptr;

    typedef std::pair<chart::vertex_id, bool> _t_vertex_added;
    typedef std::pair<chart::edge_id, bool> _t_edge_added;

    chart c;
    vertex_type_ptr v1(new vertex());
    vertex_type_ptr v2(new vertex());
    _t_vertex_added v1_ret, v2_ret;
    edge_type_ptr e1(new edge());
    edge_type_ptr e2(new edge());
    edge_type_ptr e3(new edge());
    _t_edge_added e1_ret, e1_ret2, e3_ret;

    v1_ret = c.add_vertex(v1);
    v2_ret = c.add_vertex(v2);

    // add edge
    BOOST_CHECK_EQUAL(e1->is_connected(), false);
    BOOST_CHECK_NO_THROW(e1_ret = c.add_edge(e1, v1_ret.first, v2_ret.first));
    BOOST_CHECK_EQUAL(e1_ret.second, true);
    BOOST_CHECK_EQUAL(c.get_edges().size(), 1);
    BOOST_CHECK_EQUAL(c.get_edge(e1_ret.first), e1);
    BOOST_CHECK_EQUAL(c.get_edge_id(e1), e1_ret.first);
    BOOST_CHECK_EQUAL(e1->is_connected(), true);
    BOOST_CHECK_THROW(e1->connect(v1.get(), v2.get()), std::runtime_error);

    // cannot add the same edge twice
    BOOST_CHECK_THROW(e1_ret2 = c.add_edge(e1, v1_ret.first, v2_ret.first), std::runtime_error);
    //BOOST_CHECK_EQUAL(e1_ret2.second, false);
    //BOOST_CHECK_EQUAL(e1_ret2.first, e1_ret.first);
    //BOOST_CHECK_EQUAL(c.get_edges().size(), 1);
    //BOOST_CHECK_EQUAL(c.get_edge(e1_ret2.first), e1);
    //BOOST_CHECK_EQUAL(c.get_edge_id(e1), e1_ret2.first);

    // add edge 2 (outside chart)
    BOOST_CHECK_EQUAL(e2->is_connected(), false);
    BOOST_CHECK_NO_THROW(e2->connect(v1.get(), v2.get()));
    BOOST_CHECK_EQUAL(e2->is_connected(), true);
    BOOST_CHECK_THROW(e3_ret = c.add_edge(e2, v1_ret.first, v2_ret.first), std::runtime_error);
    BOOST_CHECK_EQUAL(c.get_edges().size(), 1);

    // add edge 3
    BOOST_CHECK_EQUAL(e3->is_connected(), false);
    BOOST_CHECK_NO_THROW(e3_ret = c.add_edge(e3, v1_ret.first, v2_ret.first));
    BOOST_CHECK_EQUAL(e3_ret.second, true);
    BOOST_CHECK_EQUAL(c.get_edges().size(), 2);
    BOOST_CHECK_EQUAL(c.get_edge(e3_ret.first), e3);
    BOOST_CHECK_EQUAL(c.get_edge_id(e3), e3_ret.first);
    BOOST_CHECK_EQUAL(e3->is_connected(), true);

    // disconnect edge 2
    BOOST_CHECK_EQUAL(e2->is_connected(), true);
    BOOST_CHECK_NO_THROW(e2->disconnect());
    BOOST_CHECK_EQUAL(e2->is_connected(), false);

    // remove edge 3
    BOOST_CHECK_NO_THROW(c.remove_edge(e3));
    BOOST_CHECK_EQUAL(c.get_edges().size(), 1);
    BOOST_CHECK_EQUAL(e3->is_connected(), true);
    // ... and disconnect
    BOOST_CHECK_NO_THROW(e3->disconnect());
    BOOST_CHECK_EQUAL(e3->is_connected(), false);

    // disconnect edge 1
    BOOST_CHECK_EQUAL(e1->is_connected(), true);
    BOOST_CHECK_NO_THROW(e1->disconnect());
    BOOST_CHECK_EQUAL(e1->is_connected(), false);
    BOOST_CHECK_EQUAL(c.get_edges().size(), 0); /* Not all connections are made through the chart,
                                                *   but every connection must be represented by an 
                                                *   edge_type, so
                                                \todo TODO: edge must be deleted from chart on disconnection

                                                */
    }

BOOST_AUTO_TEST_SUITE_END()