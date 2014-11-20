
#pragma once

#include "fixture_graph_base.h"


template <int Behaviour>
class fixture_graph_simple : public fixture_graph_base<Behaviour> {
    public:
        chart_type chart_simple;

    public:
        fixture_graph_simple() {
            //! \todo TODO: Complete this nightmare
            // behaviours:
            //  -   0: directed
            //  -   1: undirected
            //  -   2: bidirectional

            //                          behaviour   v_discove  v_finishe  v_peeked   e_examined                  e_tree                      e_back                       e_forward
            valid_visit a1( "A", "dfs", "02",       "ABDFCGE", "DFBGCEA", "ABDFCGE", "(AB)(BD)(BF)(AC)(CG)(AE)", "(AB)(BD)(BF)(AC)(CG)(AE)", "",                          ""); _valid_visits.push_back(a1);
            valid_visit a2( "A", "dfs", "02",       "ABFDCGE", "FDBGCEA", "ABFDCGE", "",                         "", "", ""); _valid_visits.push_back(a2);
            valid_visit a3( "A", "dfs", "02",       "ACGBDFE", "GCDFBEA", "ACGBDFE", "",                         "", "", ""); _valid_visits.push_back(a3);
            valid_visit a4( "A", "dfs", "02",       "ACGBFDE", "GCFDBEA", "ACGBFDE", "",                         "", "", ""); _valid_visits.push_back(a4);
            valid_visit a5( "A", "dfs", "02",       "ABDFECG", "DFBEGCA", "ABDFECG", "",                         "", "", ""); _valid_visits.push_back(a5);
            valid_visit a6( "A", "dfs", "02",       "ABFDECG", "FDBEGCA", "ABFDECG", "",                         "", "", ""); _valid_visits.push_back(a6);
            valid_visit a7( "A", "dfs", "02",       "ACGBEDF", "GCEDFBA", "ACGBEDF", "",                         "", "", ""); _valid_visits.push_back(a7);
            valid_visit a8( "A", "dfs", "02",       "ACGBEFD", "GCEFDBA", "ACGBEFD", "",                         "", "", ""); _valid_visits.push_back(a8);
            valid_visit a9( "A", "dfs", "02",       "AEBDFCG", "EDFBGCA", "AEBDFCG", "",                         "", "", ""); _valid_visits.push_back(a9);
            valid_visit a10("A", "dfs", "02",       "AEBFDCG", "EFDBGCA", "AEBFDCG", "",                         "", "", ""); _valid_visits.push_back(a10);
            valid_visit a11("A", "dfs", "02",       "AECGBDF", "EGCDFBA", "AECGBDF", "",                         "", "", ""); _valid_visits.push_back(a11);
            valid_visit a12("A", "dfs", "02",       "AECGBFD", "EGCFDBA", "AECGBFD", "(AE)(AC)(CG)(AB)(BF)(BD)", "(AE)(AC)(CG)(AB)(BF)(BD)", "", ""); _valid_visits.push_back(a12);
            };
        virtual ~fixture_graph_simple() {};

        virtual void build_graph() {
            /* Simple graph: graph without loops.
                
                chart_simple:

                            A
                         ___|_____
                        |     |   |
                        B     C   E
                       _|_    |
                      |   |   |
                      D   F   G
            */

            typedef std::pair<chart_type::vertex_id, bool> _t_chart_vertex_insertion;
            // vertices
            vertex_type_ptr A = this->create_vertex("A"); _t_chart_vertex_insertion a = chart_simple.add_vertex(A);
            vertex_type_ptr B = this->create_vertex("B"); _t_chart_vertex_insertion b = chart_simple.add_vertex(B);
            vertex_type_ptr C = this->create_vertex("C"); _t_chart_vertex_insertion c = chart_simple.add_vertex(C);
            vertex_type_ptr D = this->create_vertex("D"); _t_chart_vertex_insertion d = chart_simple.add_vertex(D);
            vertex_type_ptr E = this->create_vertex("E"); _t_chart_vertex_insertion e = chart_simple.add_vertex(E);
            vertex_type_ptr F = this->create_vertex("F"); _t_chart_vertex_insertion f = chart_simple.add_vertex(F);
            vertex_type_ptr G = this->create_vertex("G"); _t_chart_vertex_insertion g = chart_simple.add_vertex(G);
    
            // edges
            edge_type_ptr AB = this->create_edge("A", "B");
            edge_type_ptr AC = this->create_edge("A", "C");
            edge_type_ptr AE = this->create_edge("A", "E");
            edge_type_ptr BD = this->create_edge("B", "D");
            edge_type_ptr BF = this->create_edge("B", "F");
            edge_type_ptr CG = this->create_edge("C", "G");

            // connect (all in chart)
            chart_simple.add_edge(AB, a.first, b.first);
            chart_simple.add_edge(AC, a.first, c.first);
            chart_simple.add_edge(AE, a.first, e.first);
            chart_simple.add_edge(BD, b.first, d.first);
            chart_simple.add_edge(BF, b.first, f.first);
            chart_simple.add_edge(CG, c.first, g.first);
            };

    };
