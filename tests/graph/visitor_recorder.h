
#pragma once

#include "core/graph/visitor.h"

class visitor_recorder {
    public:
        visitor_recorder(const std::string& strategy) : _strategy(strategy) {};
        std::string _vertex_discovered;
        std::string _vertex_finished;
        std::string _vertex_peeked;

        std::string _edge_examined;
        std::string _edge_tree;
        std::string _edge_back;
        std::string _edge_forward_or_cross;

        const std::string _strategy;
    };

template <class VertexType, class EdgeType>
class dfs_visitor_recorder :    public core::graph::visitor_dfs<VertexType, EdgeType>,
                                public visitor_recorder {
    public:
        dfs_visitor_recorder() : visitor_recorder("dfs") {};

        virtual bool peek(VertexType& v) {
            _vertex_peeked += v.get_obj();
            return false;
            };
        virtual void discover_vertex(VertexType& v) {
            _vertex_discovered += v.get_obj();
            };
        virtual void examine_edge(EdgeType& e) {
            _edge_examined += e.get_obj();
            };
        virtual void tree_edge(EdgeType& e) {
            _edge_tree += e.get_obj();
            };
        virtual void finish_vertex(VertexType& v) {
            _vertex_finished += v.get_obj();
            };

        // dfs specific
        virtual void back_edge(EdgeType& e) {
            _edge_back += e.get_obj();
            };
        virtual void forward_or_cross_edge(EdgeType& e) {
            _edge_forward_or_cross += e.get_obj();
            };
    public:
        
    };