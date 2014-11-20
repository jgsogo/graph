
#include "stdafx.h"
//#include "visitor.h"
//
//#include "vertex.h"
//#include "edge.h"
//
//namespace core {
//    namespace graph {
//
//        visitor::visitor() {
//            }
//
//        visitor::~visitor() {
//            }
//
//        // DFS Visitor
//        dfs_visitor::dfs_visitor() {
//            }
//
//        dfs_visitor::~dfs_visitor() {
//            }
//
//        void dfs_visitor::run_on_chart(chart_ptr ptr) {
//            boost::depth_first_search(ptr->_graph, boost::visitor(*this));
//            }
//        /*
//        void dfs_visitor::initialize_vertex(chart::vertex_id& u, const chart::_t_graph& g) const {
//            std::cout << "dfs_visitor::initialize_vertex" << std::endl;
//            vertex_ptr vertex = g[u];
//            vertex->initialize_vertex(*this);
//            }
//        */
//    
//        // BFS Visitor
//        bfs_visitor::bfs_visitor() {
//            }
//
//        bfs_visitor::~bfs_visitor() {
//            }
//
//        void bfs_visitor::run_on_chart(chart_ptr ptr) {
//            //boost::breadth_first_search(ptr->_graph, boost::visitor(*this));
//            }
//        
//        }
//    }