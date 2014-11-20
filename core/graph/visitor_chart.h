
#pragma once

#include "visitor.h"

namespace core {
    namespace graph {

        A menos que invoque la búsqueda a través de diferentes grafos el parámetro 'Chart&' sería 
            redundante pues en todo momento es aquél en el que he iniciado la búsqueda (quizá en
            las boost sirva para obtener las propiedades del nodo o arista ya que ahí sólo se pasa
            el identificador).

        /*


        template <class Chart>
        class chart_visitor : public visitor<typename Chart::vertex_type, typename Chart::edge_type> {
            typedef typename Chart::vertex_type vertex_type;
            public:
                virtual void initialize_vertex(vertex_type& v, Chart& c) {}; //! This is invoked on every vertex of the graph before the start of the graph search.

                virtual void discover_vertex(vertex_type& v, Chart& c) {}; //! This is invoked when a vertex is encountered for the first time.
                virtual void examine_edge(edge_type& e, Chart& c) {}; //! This is invoked on every out-edge of each vertex after it is discovered.
                virtual void tree_edge(edge_type& e, Chart& c) {}; //! This is invoked on each edge as it becomes a member of the edges that form the search tree.
                virtual void finish_vertex(vertex_type& v, Chart& c) {}; //! This is invoked on vertex u after finish_vertex has been called for all the vertices in the DFS-tree rooted at vertex u. If vertex u is a leaf in the DFS-tree, then the finish_vertex function is call on u after all the out-edges of u have been examined.
            };

        template <class Chart>
        class chart_visitor_dfs : public chart_visitor<Chart> {
            public:
                virtual void start_vertex(vertex_type& v, Chart& c) {}; //! This is invoked on the source vertex once before the start of the search
                virtual void back_edge(edge_type& e, Chart& c) {}; //! This is invoked on the back edges in the graph. For an undirected graph there is some ambiguity between tree edges and back edges since the edge (u,v) and (v,u) are the same edge, but both the tree_edge() and back_edge() functions will be invoked. One way to resolve this ambiguity is to record the tree edges, and then disregard the back-edges that are already marked as tree edges. An easy way to record tree edges is to record predecessors at the tree_edge event point.
                virtual void forward_or_cross_edge(edge_type& e, Chart& c) {}; //! This is invoked on forward or cross edges in the graph. In an undirected graph this method is never called.
            };
        
        template <class Chart>
        class chart_visitor_bfs : public chart_visitor<Chart> {
            public:
                virtual void examine_vertex(vertex_type& e, Chart& c) {}; //! This is invoked on a vertex as it is popped from the queue. This happens immediately before examine_edge() is invoked on each of the out-edges of vertex u.
                virtual void non_tree_edge(edge_type& e, Chart& c) {}; //! This is invoked on back or cross edges for directed graphs and cross edges for undirected graphs.
                virtual void gray_target(edge_type& e, Chart& c) {}; //! This is invoked on the subset of non-tree edges who's target vertex is colored gray at the time of examination. The color gray indicates that the vertex is currently in the queue.
                virtual void black_target(edge_type& e, Chart& c) {}; //! This is invoked on the subset of non-tree edges who's target vertex is colored black at the time of examination. The color black indicates that the vertex has been removed from the queue.
            };

        */
        }
    }