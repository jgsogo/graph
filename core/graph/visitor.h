
#pragma once

namespace core {
    namespace graph {

        template <class VertexType, class EdgeType>
        class visitor {
            public:
                typedef VertexType vertex_type;
                typedef EdgeType edge_type;
            public:
                virtual bool peek(vertex_type& v) {return false;}; //! Is this what we are looking for?

                //! This is invoked when a vertex is encountered for the first time.
                virtual void discover_vertex(vertex_type& v) {};
                
                //! This is invoked on every out-edge of each vertex after it is discovered.
                virtual void examine_edge(edge_type& e) {};

                //! This is invoked on each edge as it becomes a member of the edges that form the search tree.
                virtual void tree_edge(edge_type& e) {};

                /*! This is invoked on vertex u after finish_vertex has been called for all the vertices
                        in the DFS-tree rooted at vertex u. If vertex u is a leaf in the DFS-tree,
                        then the finish_vertex function is call on u after all the out-edges of u have been examined.
                */
                virtual void finish_vertex(vertex_type& v) {};
            };


        template <class VertexType, class EdgeType>
        class visitor_dfs : public visitor<VertexType, EdgeType> {
            public:
                //! This is invoked on the source vertex once before the start of the search
                virtual void start_vertex(vertex_type& v) {};

                /*! This is invoked on the back edges in the graph. For an undirected graph there is some
                    ambiguity between tree edges and back edges since the edge (u,v) and (v,u) are the same edge,
                    but both the tree_edge() and back_edge() functions will be invoked. One way to resolve
                    this ambiguity is to record the tree edges, and then disregard the back-edges
                    that are already marked as tree edges. An easy way to record tree edges is to record predecessors
                    at the tree_edge event point.
                */
                virtual void back_edge(edge_type& e) {};

                /*! This is invoked on forward or cross edges in the graph. In an undirected graph
                        this method is never called.
                */
                virtual void forward_or_cross_edge(edge_type& e) {}; 
            };

        template <class VertexType, class EdgeType>
        class visitor_bfs : public visitor<VertexType, EdgeType> {
            public:
                //! This is invoked on a vertex as it is popped from the queue. This happens immediately before examine_edge() is invoked on each of the out-edges of vertex u.
                virtual void examine_vertex(vertex_type& e) {};
                
                //! This is invoked on back or cross edges for directed graphs and cross edges for undirected graphs.
                virtual void non_tree_edge(edge_type& e) {};

                //! This is invoked on the subset of non-tree edges who's target vertex is colored gray at the time of examination. The color gray indicates that the vertex is currently in the queue.
                virtual void gray_target(edge_type& e) {};

                //! This is invoked on the subset of non-tree edges who's target vertex is colored black at the time of examination. The color black indicates that the vertex has been removed from the queue.
                virtual void black_target(edge_type& e) {};
            };
        
        }
    }

//
//#pragma once
//
//#include <boost/graph/depth_first_search.hpp>
//#include <boost/graph/breadth_first_search.hpp>
//
//#include "chart.h"
//
//namespace core {
//    namespace graph {
//
//        class visitor {
//            public:
//                typedef std::shared_ptr<chart> chart_ptr;
//            public:
//                visitor();
//                virtual ~visitor();
//                virtual void run_on_chart(chart_ptr ptr) = 0;
//            };
//
//        class dfs_visitor : public visitor, public boost::default_dfs_visitor {
//            public:
//                dfs_visitor();
//                ~dfs_visitor();
//                void run_on_chart(chart_ptr ptr);
//
//                // Funcs: http://www.boost.org/doc/libs/1_37_0/libs/graph/doc/DFSVisitor.html
//                //virtual void initialize_vertex(chart::vertex_id& u, const chart::_t_graph& g) const;
//            };
//
//        class bfs_visitor : public visitor, public boost::default_bfs_visitor {
//            public:
//                bfs_visitor();
//                ~bfs_visitor();
//                void run_on_chart(chart_ptr ptr);
//
//                // Funcs: http://www.boost.org/doc/libs/1_37_0/libs/graph/doc/BFSVisitor.html
//            };
//
//        }
//    }