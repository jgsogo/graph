
#pragma once

#include <stack>

#include "search_algorithm.h"

namespace core {
    namespace graph {
        
        template <class VertexType, class EdgeType>
        class dfs_visitor : public search_algorithm<VertexType, EdgeType> {
            typedef typename visitor_dfs<VertexType, EdgeType> _t_visitor_impl;
            public:
                dfs_visitor(_t_visitor_impl& vis, VertexType& start_vertex) : _visitor(vis), _start_vertex(start_vertex), search_algorithm<VertexType, EdgeType>(vis) {};
                ~dfs_visitor() {};

                void search(const _e_direction& direction) {
                    std::stack<VertexType*> s;
                    
                    // dfs_algorithm
                    this->discover_vertex(_start_vertex); // mark as discovered
                    _visitor.start_vertex(_start_vertex);
                    s.push(&_start_vertex);

                    while (!s.empty()) {
                        this->_work_on_top_vertex(s, direction);
                        }                    
                    };

            protected:
                void back_edge(EdgeType& edge) {
                    this->label_edge(edge, detail::edge_visitable::BACK_EDGE);
                    _visitor.back_edge(edge);
                    };

                void forward_or_cross_edge(EdgeType& edge) {
                    this->label_edge(edge, detail::edge_visitable::FORWARD_OR_CROSS_EDGE);
                    _visitor.forward_or_cross_edge(edge);
                    };

                void _work_on_top_vertex(std::stack<VertexType*>& s, const _e_direction& direction) {
                    VertexType* adjacent_vertex;
                    std::vector<EdgeType*> adjacent_edges;

                    // algorithm
                    VertexType* t = s.top();
                    if (!_visitor.peek(*t)) {  // If 't' is not what we are looking for, continue searching
                        this->adjacent_edges(*t, adjacent_edges, direction);
                        std::for_each(adjacent_edges.begin(), adjacent_edges.end(), [this, &adjacent_vertex, &t, &s, &direction](EdgeType* edge) {
                            if (edge->get_label() != detail::edge_visitable::NON_TREE_EDGE) {
                                //continue;
                                }
                            else {
                                this->adjacent_vertex(*t, *edge, adjacent_vertex, direction);
                                _visitor.examine_edge(*edge);
                                if ((adjacent_vertex->get_label() != detail::vertex_visitable::DISCOVERED) && (adjacent_vertex->get_label() != detail::vertex_visitable::EXPLORED)) {
                                    this->tree_edge(*edge);
                                    this->discover_vertex(*adjacent_vertex);
                                    s.push(adjacent_vertex);
                                    this->_work_on_top_vertex(s, direction);
                                    }
                                else if (adjacent_vertex->get_label() == detail::vertex_visitable::DISCOVERED) {
                                    this->back_edge(*edge);
                                    }
                                else {
                                    this->forward_or_cross_edge(*edge);
                                    }
                                }
                            });
                        this->finish_vertex(*t); // mark as explored
                        }
                    s.pop();
                    };

            protected:
                _t_visitor_impl& _visitor;
                VertexType& _start_vertex;
            };


        // algorithm call
        template <class VertexType, class EdgeType>
        void depth_first_search(visitor_dfs<VertexType, EdgeType>& vis, VertexType& v, const _e_direction& direction) {
            dfs_visitor<VertexType, EdgeType> visitor(vis, v);
            visitor.search(direction);
            };

        }
    }