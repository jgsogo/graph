
#pragma once

#include <queue>
#include <set>
#include "search_algorithm.h"

namespace core {
    namespace graph {

        template <class VertexType, class EdgeType>
        class bfs_visitor : public search_algorithm<VertexType, EdgeType> {
            typedef typename visitor_bfs<VertexType, EdgeType> _t_visitor_impl;
            public:
                bfs_visitor(_t_visitor_impl& vis, VertexType& start_vertex) : _visitor(vis), _start_vertex(start_vertex), search_algorithm<VertexType, EdgeType>(vis) {};
                ~bfs_visitor() {};

                void search(const _e_direction& direction) {
                    std::queue<VertexType*> q;
                    std::set<VertexType*> v;
                    VertexType* adjacent_vertex; 
                    VertexType* t;
                    std::vector<EdgeType*> adjacent_edges;

                    // bfs_algorithm
                    this->discover_vertex(_start_vertex); // mark as discovered
                    q.push(&_start_vertex);
                    v.insert(&_start_vertex);

                    while (!q.empty()) {
                        // algorithm
                        t = q.front(); q.pop();
                        _visitor.examine_vertex(*t);
                        if (_visitor.peek(*t)) { return;}; // If 't' is what we are looking for
                    
                        this->adjacent_edges(*t, adjacent_edges, direction);
                        std::for_each(adjacent_edges.begin(), adjacent_edges.end(), [this, &adjacent_vertex, &t, &q, &v](EdgeType* edge) {
                            this->adjacent_vertex(*t, *edge, adjacent_vertex, direction);
                            std::set<VertexType*>::iterator it; bool inserted;
                            std::tie(it, inserted) = v.insert(adjacent_vertex);
                            if (inserted) {
                                this->discover_vertex(*adjacent_vertex);
                                q.push(adjacent_vertex);
                                }                        
                            });
                        this->finish_vertex(*t);
                        }                  

                    };

            protected:

            protected:
                _t_visitor_impl _visitor;
                VertexType& _start_vertex;
            };

        // algorithm call
        template <class VertexType, class EdgeType>
        void breadth_first_search(visitor_bfs<VertexType, EdgeType>& vis, VertexType& v, const _e_direction& direction) {
            bfs_visitor<VertexType, EdgeType> visitor(vis, v);
            visitor.search(direction);
            };

        }
    }