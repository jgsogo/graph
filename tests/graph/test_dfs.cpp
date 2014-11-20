
#include "stdafx.h"
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include "core/graph/graph.h"
#include "core/graph/depth_first_search.h"
#include "fixture_graph_simple.h"
#include "visitor_recorder.h"

BOOST_AUTO_TEST_SUITE(test_dfs_suite)

typedef fixture_graph_simple<core::graph::UNDIRECTED> fixture_graph_simple_undirected;
typedef fixture_graph_simple<core::graph::DIRECTED> fixture_graph_simple_directed;
typedef fixture_graph_simple<core::graph::BIDIRECTIONAL> fixture_graph_simple_bidirectional;
typedef boost::mpl::list<   fixture_graph_simple_undirected,
                            fixture_graph_simple_directed,
                            fixture_graph_simple_bidirectional> test_types;





BOOST_AUTO_TEST_CASE_TEMPLATE(test_dfs_simple, T, test_types) {
    typedef typename T::vertex_type vertex_type;
    typedef typename T::vertex_type_ptr vertex_type_ptr;
    typedef typename T::edge_type edge_type;
    typedef typename T::edge_type_ptr edge_type_ptr;
    
    T fx;
    fx.build_graph();

    // depth_first_search from vertex A
    const std::map<std::string, vertex_type_ptr>& vertices = fx.get_vertices();
    vertex_type_ptr A = vertices.at("A");
    
    dfs_visitor_recorder<vertex_type, edge_type> visitor;
    core::graph::depth_first_search<vertex_type, edge_type>(visitor, *A.get(), core::graph::FORWARDS);

    // Check it all
    std::string errors;
    BOOST_CHECK_MESSAGE(fx.check(visitor, "A", errors), "DFS visitor failed: [visitor != expected]\n" << errors);

    //BOOST_CHECK_MESSAGE(fx.check_dfs_discovered("A", visitor._vertex_discovered), "check dfs_discovered failed ['" << visitor._vertex_discovered << "']");
    //BOOST_CHECK_MESSAGE(fx.check_dfs_finished("A", visitor._vertex_finished), "check dfs_finished failed ['" << visitor._vertex_finished << "']");
    //BOOST_CHECK_MESSAGE(fx.check_dfs_peeked("A", visitor._vertex_peeked), "check dfs_peeked failed ['" << visitor._vertex_peeked << "']");
    //BOOST_CHECK_EQUAL(imploded.str(), "ABFDECG");
    //  - peek order:
    /*
    imploded.str(std::string()); imploded.clear();
    std::copy(visitor._vertex_peeked.begin(), visitor._vertex_peeked.end(), std::ostream_iterator<std::string>(imploded, ""));
    BOOST_CHECK_EQUAL(imploded.str(), "FDBEGCA");     
    //  - finish order:
    imploded.str(std::string()); imploded.clear();
    std::copy(visitor._vertex_finished.begin(), visitor._vertex_finished.end(), std::ostream_iterator<std::string>(imploded, ""));
    BOOST_CHECK_EQUAL(imploded.str(), "FDBEGCA");     
    */
    }

BOOST_AUTO_TEST_CASE(test_dfs_A2A) {
    /* \todo TODO: Utilizar el algoritmo dfs para buscar un elemento empezando desde otro elemento, 
        en el caso en el que ''el elemento de partida es el mismo que el que se busca''.
    */
    
    }

BOOST_AUTO_TEST_SUITE_END()