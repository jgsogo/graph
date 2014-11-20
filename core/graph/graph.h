
#pragma once

#include "traits.h"
#include "vertex_traits.h"
#include "edge_traits.h"
#include "chart_impl.h"

namespace core {
    namespace graph {

        
        /*! API entrance for graph utilities
        */
        template <int Behaviour>
        struct standalone {
            // Define vertex and edge types
            class vertex_type;
            class edge_type : public detail::edge<vertex_type, edge_type, Behaviour> {
                };            

            class vertex_type : public detail::vertex<edge_type, Behaviour> {
                };
            };

        template <class VertexInner, class EdgeInner, int Behaviour>
        struct inner_standalone {
            // Define vertex and edge types
            class vertex_type;
            class edge_type : public detail::edge<vertex_type, edge_type, Behaviour, void, EdgeInner> {
                public:
                    edge_type(typename std::shared_ptr<EdgeInner> inner) : detail::edge<vertex_type, edge_type, Behaviour, void, EdgeInner>(inner) {};
                };            

            class vertex_type : public detail::vertex<edge_type, Behaviour, void, VertexInner> {
                public:
                    vertex_type(typename std::shared_ptr<VertexInner> inner) : detail::vertex<edge_type, Behaviour, void, VertexInner>(inner) {};
                };
            };
        template <class EdgeInner, int Behaviour>
        struct inner_standalone<void, EdgeInner, Behaviour> {
            // Define vertex and edge types
            class vertex_type;
            class edge_type : public detail::edge<vertex_type, edge_type, Behaviour, void, EdgeInner> {
                public:
                    edge_type(typename std::shared_ptr<EdgeInner> inner) : detail::edge<vertex_type, edge_type, Behaviour, void, EdgeInner>(inner) {};
                };            

            class vertex_type : public detail::vertex<edge_type, Behaviour, void, void> {
                };
            };
        template <class VertexInner, int Behaviour>
        struct inner_standalone<VertexInner, void, Behaviour> {
            // Define vertex and edge types
            class vertex_type;
            class edge_type : public detail::edge<vertex_type, edge_type, Behaviour, void, void> {
                };            

            class vertex_type : public detail::vertex<edge_type, Behaviour, void, VertexInner> {
                public:
                    vertex_type(typename std::shared_ptr<VertexInner> inner) : detail::vertex<edge_type, Behaviour, void, VertexInner>(inner) {};
                };
            };

        /*****************
        *   CHART 
        *****************/
        template <int Behaviour>
        struct in_chart {
            class vertex_type;
            class edge_type;

            typedef chart<vertex_type, edge_type, Behaviour> chart_type;

            class edge_type : public detail::edge<vertex_type, edge_type, Behaviour, chart_type> {
                };

            //typedef detail::vertex<edge_type, Behaviour, chart_type> vertex_type;
            class vertex_type : public detail::vertex<edge_type, Behaviour, chart_type> {
                };
            };

        template <class VertexInner, class EdgeInner, int Behaviour>
        struct inner_chart {
            class vertex_type;
            class edge_type;

            typedef chart<vertex_type, edge_type, Behaviour> chart_type;

            class edge_type : public detail::edge<vertex_type, edge_type, Behaviour, chart_type, EdgeInner> {
                public:
                    edge_type(typename std::shared_ptr<EdgeInner> inner) : detail::edge<vertex_type, edge_type, Behaviour, chart_type, EdgeInner>(inner) {};
                };           

            class vertex_type : public detail::vertex<edge_type, Behaviour, chart_type, VertexInner> {
                public:
                    vertex_type(typename std::shared_ptr<VertexInner> inner) : detail::vertex<edge_type, Behaviour, chart_type, VertexInner>(inner) {};
                };
            };


        }
    }