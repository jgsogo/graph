
#pragma once

#include "fixture_graph_base.h"
#include "fixture_graph_simple.h"


template <int Behaviour>
class fixture_graph_full : public fixture_graph_base<Behaviour> {
    public:
        chart_type chart_full;

    public:
        virtual void build_graph() {
            /* Graph: graph with loop
                    
                    chart_full:
                                     A
                                  ___|_____
                                 |     |   |
                                 B     C   E
                                _|_    |   |
                               |   |   |   |
                               D   F   G   |
                                   |       |
                                   |_______|
            */

            // vertices
            vertex_type_ptr A = this->create_vertex("A"); _t_chart_vertex_insertion a = chart_full.add_vertex(A);
            vertex_type_ptr B = this->create_vertex("B"); _t_chart_vertex_insertion b = chart_full.add_vertex(B);
            vertex_type_ptr C = this->create_vertex("C"); _t_chart_vertex_insertion c = chart_full.add_vertex(C);
            vertex_type_ptr D = this->create_vertex("D"); _t_chart_vertex_insertion d = chart_full.add_vertex(D);
            vertex_type_ptr E = this->create_vertex("E"); _t_chart_vertex_insertion e = chart_full.add_vertex(E);
            vertex_type_ptr F = this->create_vertex("F"); _t_chart_vertex_insertion f = chart_full.add_vertex(F);
            vertex_type_ptr G = this->create_vertex("G"); _t_chart_vertex_insertion g = chart_full.add_vertex(G);
    
            // edges
            edge_type_ptr AB = this->create_edge("A", "B");
            edge_type_ptr AC = this->create_edge("A", "C");
            edge_type_ptr AE = this->create_edge("A", "E");
            edge_type_ptr BD = this->create_edge("B", "D");
            edge_type_ptr BF = this->create_edge("B", "F");
            edge_type_ptr CG = this->create_edge("C", "G");
            edge_type_ptr FE = this->create_edge("F", "E");

            // connect
            chart_full.add_edge(AB, a.first, b.first);
            chart_full.add_edge(AC, a.first, c.first);
            chart_full.add_edge(AE, a.first, e.first);
            chart_full.add_edge(BD, b.first, d.first);
            chart_full.add_edge(BF, b.first, f.first);
            chart_full.add_edge(CG, c.first, g.first);
            chart_full.add_edge(FE, f.first, e.first);
            };   

        virtual bool check_dfs_discovered(const std::string& start_vertex, const std::string& to_check) {
            return false;
            };

        virtual bool check_dfs_finished(const std::string& start_vertex, const std::string& to_check) {
            return false;
            };

        virtual bool check_dfs_peeked(const std::string& start_vertex, const std::string& to_check) {
            return false;
            };
    };
