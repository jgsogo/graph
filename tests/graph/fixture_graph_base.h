
#pragma once

#include "core/graph/graph.h"
#include "core/utils/str_cast.h"
#include "visitor_recorder.h"

template <int Behaviour>
inline std::string build_edge_id(const std::string& source, const std::string& target);

template <>
inline std::string build_edge_id<core::graph::UNDIRECTED>(const std::string& source, const std::string& target) {
    return "(" + source + target + ")";
    };

template <>
inline std::string build_edge_id<core::graph::DIRECTED>(const std::string& source, const std::string& target) {
    return "(" + source + target + ")";
    };

template <>
inline std::string build_edge_id<core::graph::BIDIRECTIONAL>(const std::string& source, const std::string& target) {
    return "(" + source + target + ")";
    };


template <int Behaviour>
class fixture_graph_base {
    public:
        typedef typename core::graph::inner_chart<std::string, std::string, Behaviour>::vertex_type vertex_type;
        typedef typename core::graph::inner_chart<std::string, std::string, Behaviour>::edge_type edge_type;
        typedef typename core::graph::inner_chart<std::string, std::string, Behaviour>::chart_type chart_type;

        typedef typename chart_type::vertex_type_ptr vertex_type_ptr;
        typedef typename chart_type::edge_type_ptr edge_type_ptr;

        typedef std::map<std::string, vertex_type_ptr> _t_vertices;
        typedef std::vector<edge_type_ptr> _t_edges;

    public:
        fixture_graph_base() {
            //this->build_graph();
            };

        virtual ~fixture_graph_base() {
            };

        virtual void build_graph() = 0;

        const _t_vertices& get_vertices() const { return _vertices;};
        const _t_edges& get_edges() const { return _edges;};

        vertex_type_ptr create_vertex(const std::string& id) {
            std::shared_ptr<std::string> inner_data(new std::string(id));
            vertex_type_ptr vertex(new vertex_type(inner_data));
            _vertices.insert(std::make_pair(id, vertex));
            return vertex;
            };
        edge_type_ptr create_edge(const std::string& source, const std::string& target) {
            std::shared_ptr<std::string> inner_data(new std::string(build_edge_id<Behaviour>(source, target)));
            edge_type_ptr edge(new edge_type(inner_data));
            _edges.push_back(edge);
            return edge;
            };


        struct valid_visit {
            valid_visit(const std::string& init_vertex,
                        const std::string& visitor_strategy,
                        const std::string& behaviour,
                        const std::string& vertex_discovered,
                        const std::string& vertex_finished,
                        const std::string& vertex_peeked,
                        const std::string& edge_examined,
                        const std::string& edge_tree,
                        const std::string& edge_back,
                        const std::string& edge_forward_or_cross
                        ) : _init_vertex(init_vertex),
                            _visitor_strategy(visitor_strategy),
                            _behaviour(behaviour),
                            _vertex_discovered(vertex_discovered),
                            _vertex_finished(vertex_finished),
                            _vertex_peeked(vertex_peeked),
                            _edge_examined(edge_examined),
                            _edge_tree(edge_tree),
                            _edge_back(edge_back),
                            _edge_forward_or_cross(edge_forward_or_cross)
                {
                };
            const std::string _init_vertex;
            const std::string _visitor_strategy;
            const std::string _behaviour;

            const std::string _vertex_discovered;
            const std::string _vertex_finished;
            const std::string _vertex_peeked;
            
            const std::string _edge_examined;
            const std::string _edge_tree;
            const std::string _edge_back;
            const std::string _edge_forward_or_cross;
            };
        std::vector<valid_visit> _valid_visits;

        virtual bool check(const visitor_recorder& vis, const std::string& start_vertex, std::string& error) const {
            std::vector<valid_visit>::const_iterator it = _valid_visits.begin();
            std::vector<valid_visit>::const_iterator it_end = _valid_visits.end();
            std::map<int, std::string> errors;
            std::string behaviour = core::utils::to_string(Behaviour);
            
            while( it != it_end) {
                const valid_visit& valid = *it;
                std::stringstream ss;
                unsigned int tics = 0;
             
                if (    ( start_vertex.compare(valid._init_vertex) != 0)
                    ||  ( vis._strategy.compare(valid._visitor_strategy) != 0)
                    ||  (std::string(valid._behaviour).find(behaviour) == std::string::npos )) {
                    ss << "\t\tnot valid candidate defined (test cases incomplete)";
                    }
                else {
                    if (vis._vertex_discovered.compare(valid._vertex_discovered) == 0) {tics++;} else {
                        ss << "\t\t_vertex_discovered fail [" << vis._vertex_discovered << " != " << valid._vertex_discovered << "]" << std::endl;
                        }
                    if (vis._vertex_finished.compare(valid._vertex_finished) == 0) {tics++;} else {
                        ss << "\t\t_vertex_finished fail [" << vis._vertex_finished << " != " << valid._vertex_finished << "]" << std::endl;
                        }
                    if (vis._vertex_peeked.compare(valid._vertex_peeked) == 0) {tics++;} else {
                        ss << "\t\t_vertex_peeked fail [" << vis._vertex_peeked << " != " << valid._vertex_peeked << "]" << std::endl;
                        }
                    if (vis._edge_examined.compare(valid._edge_examined) == 0) {tics++;} else {
                        ss << "\t\t_edge_examined fail [" << vis._edge_examined << " != " << valid._edge_examined << "]" << std::endl;
                        }
                    if (vis._edge_tree.compare(valid._edge_tree) == 0) {tics++;} else {
                        ss << "\t\t_edge_tree fail [" << vis._edge_tree << " != " << valid._edge_tree << "]" << std::endl;
                        }
                    if (vis._edge_back.compare(valid._edge_back) == 0) {tics++;} else {
                        ss << "\t\t_edge_back fail [" << vis._edge_back << " != " << valid._edge_back << "]" << std::endl;
                        }
                    if (vis._edge_forward_or_cross.compare(valid._edge_forward_or_cross) == 0) {tics++;} else {
                        ss << "\t\t_edge_forward_or_cross fail [" << vis._edge_forward_or_cross << " != " << valid._edge_forward_or_cross << "]" << std::endl;
                        }
                    }

                if (tics==7) {
                    return true;
                    }
                errors[7-tics] = ss.str();                
                ++it;
                }
            
            error = errors.begin()->second; // selecciono el que tenga menos errores
            return false;
            };

    protected:

        _t_vertices _vertices;
        _t_edges _edges;
    };
