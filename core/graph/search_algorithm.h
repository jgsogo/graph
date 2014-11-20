
#pragma once

#include "visitor.h"
#include "vertex_traits.h"
#include "edge_traits.h"

namespace core {
    namespace graph {

        // Look for adjacent edges
        template <class VertexType, class EdgeType>
        typename std::enable_if< detail::test_type_connection<VertexType, UNDIRECTED>::value, void >::type
        push_adjacent_edges(const VertexType& v, std::vector<EdgeType*>& edges, const _e_direction& direction) {
            // direction makes no sense for UNDIRECTED graph
            typename const detail::_impl::vertex_connected<EdgeType>::_t_edges& all = v.get_edges();
            std::for_each(all.begin(), all.end(), [&edges](EdgeType* item){ edges.push_back(item);});
            };
        template <class VertexType, class EdgeType>
        typename std::enable_if< detail::test_type_connection<VertexType, DIRECTED>::value, void >::type
        push_adjacent_edges(const VertexType& v, std::vector<EdgeType*>& edges, const _e_direction& direction) {
            if (direction == FORWARDS) {
                typename const detail::_impl::vertex_connected<EdgeType>::_t_edges& all = v.get_outgoing();
                std::for_each(all.begin(), all.end(), [&edges](EdgeType* item){ edges.push_back(item);});
                }
            else {
                throw std::runtime_error("There is no 'BACKWARDS' direction for 'DIRECTED' graphs");
                }
            };
        template <class VertexType, class EdgeType>
        typename std::enable_if< detail::test_type_connection<VertexType, BIDIRECTIONAL>::value, void >::type
        push_adjacent_edges(const VertexType& v, std::vector<EdgeType*>& edges, const _e_direction& direction) {
            typedef typename detail::_impl::vertex_connected<EdgeType>::_t_edges _t_edges;
            if (direction == FORWARDS) {
                const _t_edges& all_out = v.get_outgoing();
                std::for_each(all_out.begin(), all_out.end(), [&edges](EdgeType* item){ edges.push_back(item);});
                }
            else {
                const _t_edges& all_out = v.get_incoming();
                std::for_each(all_out.begin(), all_out.end(), [&edges](EdgeType* item){ edges.push_back(item);});
                }
            };

        // Look for adjacent vertex
        template <class VertexType, class EdgeType>
        typename std::enable_if< detail::test_type_connection<VertexType, UNDIRECTED>::value, void >::type
        get_adjacent_vertex(const VertexType& v, const EdgeType& edge, VertexType*& vertex, const _e_direction& direction) {
            // direction makes no sense for UNDIRECTED graph
            std::pair<VertexType*, VertexType*> pair = edge.get_connected();
            if (&v == pair.first) {
                vertex = pair.second;
                }
            else {
                assert(&v==pair.second);
                vertex = pair.first;
                }            
            }
        template <class VertexType, class EdgeType>
        typename std::enable_if< detail::test_type_connection<VertexType, DIRECTED>::value, void >::type
        get_adjacent_vertex(const VertexType& v, const EdgeType& edge, VertexType*& vertex, const _e_direction& direction) {
            if (direction == FORWARDS) {
                vertex = edge.get_target();
                }
            else {
                throw std::runtime_error("There is no 'BACKWARDS' direction for 'DIRECTED' graphs");
                }            
            }
        template <class VertexType, class EdgeType>
        typename std::enable_if< detail::test_type_connection<VertexType, BIDIRECTIONAL>::value, void >::type
        get_adjacent_vertex(const VertexType& v, const EdgeType& edge, VertexType*& vertex, const _e_direction& direction) {
            if (direction == FORWARDS) {
                vertex = edge.get_target();
                assert(&v != vertex);
                }
            else {
                vertex = edge.get_source();
                assert(&v != vertex);
                }
            }


        // search algorithm base class
        template <class VertexType, class EdgeType>
        class search_algorithm {
            public:
                search_algorithm(visitor<VertexType, EdgeType>& vis) : _visitor(vis) {};
                ~search_algorithm() {
                    // Reset vertices and edges
                    std::for_each(_vertices.begin(), _vertices.end(), [](VertexType* item) {
                        item->_label = detail::vertex_visitable::UNDISCOVERED;
                        });
                    std::for_each(_edges.begin(), _edges.end(), [](EdgeType* item) {
                        item->_label = detail::edge_visitable::NON_TREE_EDGE;
                        });
                    };
                void discover_vertex(VertexType& vertex) {
                    this->label_vertex(vertex, detail::vertex_visitable::DISCOVERED);
                    _visitor.discover_vertex(vertex);
                    };
                void finish_vertex(VertexType& vertex) {
                    this->label_vertex(vertex, detail::vertex_visitable::EXPLORED);
                    _visitor.finish_vertex(vertex);
                    };
            
                void tree_edge(EdgeType& edge) {
                    this->label_edge(edge, detail::edge_visitable::TREE_EDGE);
                    _visitor.tree_edge(edge);
                    };
                
                void adjacent_edges(const VertexType& v, std::vector<EdgeType*>& edges, const _e_direction& direction) {
                    edges.clear();
                    push_adjacent_edges(v, edges, direction);
                    };
                
                void adjacent_vertex(const VertexType& v, const EdgeType& edge, VertexType*& vertex, const _e_direction& direction) {
                    get_adjacent_vertex(v, edge, vertex, direction);
                    };
                
            protected:
                void label_edge(EdgeType& edge, const detail::edge_visitable::_e_visitor_labels& label) {
                    edge._label = label;
                    _edges.push_back(&edge);
                    };

                void label_vertex(VertexType& vertex, const detail::vertex_visitable::_e_visitor_labels& label) {
                    vertex._label = label;
                    _vertices.push_back(&vertex);
                    };

            protected:
                visitor<VertexType, EdgeType>& _visitor;
            private:
                // Vectors to record vertices and edges in order to reset visit state after search
                std::vector<VertexType*> _vertices;
                std::vector<EdgeType*> _edges;
            };

        }
    }