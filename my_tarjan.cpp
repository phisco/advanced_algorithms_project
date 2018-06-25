//
// Created by phisco on 6/23/18.
//

#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
/*
  Sample output:
A directed graph:
A --> B
B --> C H
C --> D G
D --> E
E --> F C
F -->
G --> F D
H --> A G

Total number of components: 3
Vertex A is in component 2
Vertex B is in component 2
Vertex C is in component 1
Vertex D is in component 1
Vertex E is in component 1
Vertex F is in component 0
Vertex G is in component 1
Vertex H is in component 2
 */
using namespace boost;

typedef adjacency_list < listS, vecS, directedS> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;

template <class Graph, class Num, class Lowpt, class Lowvine, class Component, class Stack, class StackMember, class Ancestor>
void strongconnect(const Graph g, const Vertex v, int* i, int* c, Num num, Lowpt lowpt, Lowvine lowvine, Component component, Stack s, StackMember sm, Ancestor ancestor) {
    *i += 1;
    put(lowvine, v, *i);
    put(lowpt, v, *i);
    put(num, v, *i);
    s->push(v);
    put(ancestor, *i, true);
    put(sm, *i, true);
    // std::cout << get(num, v) << " enters" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        // std::cout << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
        if (get(num, *w) == 0){
            // std::cout << "cond 1 : " << get(num, v) << " " <<  *i+1 << std::endl;
            strongconnect(g, *w, i, c, num, lowpt, lowvine, component, s, sm, ancestor);
            put(lowpt, v, get(lowpt, *w) > get(lowpt, v) ? get(lowpt, v) : get(lowpt, *w));
            put(lowvine, v, get(lowvine, *w) > get(lowvine, v) ? get(lowvine, v) : get(lowvine, *w));
        } else if (get(ancestor, get(num, *w))) /* w is an ancestor of v */{
            // std::cout << "cond 2 : " << get(num, v) << " " << get(num, *w) << std::endl;
            put(lowpt, v, get(num, *w) > get(lowpt, v) ? get(lowpt, v) : get(num, *w));
        } else if (get(num, *w) < get(num, v) && (get(sm, get(num, v)))){
                // std::cout << "cond 3 : " << get(num, v) << " " << get(num, *w) << std::endl;
                put(lowvine, v, get(num, *w) > get(lowvine, v) ? get(lowvine, v) : get(num, *w));
        }
    }
    // std::cout << "final : " << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
    if ((get(lowpt, v) == get(num, v)) && (get(lowvine, v) == get(num, v))){
        *c += 1;
        //std::cout << *c << " : ";
        int vn = get(num, v);
        while(!s->empty() && get(num, s->top()) >= vn){
            Vertex w = s->top();
            s->pop();
            put(sm, get(num, w), false);
            put(component, w, v);
            // std::cout << get(num, w) << " ";
        }
        // std::cout << std::endl;
    }
    // std::cout << get(num, v) << " exits" << std::endl;
    put(ancestor, get(num, v), false);
}
template <class Graph, class Num, class Lowpt, class Lowvine, class Component, class StackMember, class Ancestor>
int strongconnect_main(const Graph& g, Num num, Lowpt lowpt, Lowvine lowvine, Component component, StackMember sm, Ancestor ancestor) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s;
    int i = 0;
    int c = 0;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(num, v) == 0){
            strongconnect(g, v, &i, &c, num, lowpt, lowvine, component, &s, sm, ancestor);
        }
    }
    return c;
}

template <class Graph, class Component>
int my_strong_components(const Graph& g, Component component)
{
    std::vector<int> lowvine(num_vertices(g)),
            number(num_vertices(g)),
            lowpt(num_vertices(g));
    bool stackmember[num_vertices(g)], ancestor[num_vertices(g)];
    IndexMap index = get(vertex_index, g);

    for (int i = 0; i < num_vertices(g); i++){
        stackmember[i] = false;
        ancestor[i] = false;
    }

    return strongconnect_main(g,
                       make_iterator_property_map(number.begin(), get(vertex_index, g)),
                       make_iterator_property_map(lowpt.begin(), get(vertex_index, g)),
                       make_iterator_property_map(lowvine.begin(), get(vertex_index, g)),
                       component,
                       make_iterator_property_map(&ancestor[0], get(vertex_index,g)),
                       make_iterator_property_map(&stackmember[0], get(vertex_index,g)));
}

int main(int, char*[])
{
    typedef std::pair<int, int> Edge;

    const int num_nodes = 8;
    enum nodes { A, B, C, D, E, F, G, H, I, L, M, N};
    char name[] = "ABCDEFGHILMN";

    Edge edge_array[] = { Edge(A, B),
                          Edge(B, C), Edge(B, H),
                          Edge(C, D), Edge(C, G),
                          Edge(D, E),
                          Edge(E, F), Edge(E, C),
                          Edge(G, F), Edge(G, D),
                          Edge(H, A), Edge(H, G),
                          Edge(I, L),
                          Edge(M, N), Edge(N, M)
    };
    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, num_nodes);
    std::vector<Vertex> component(num_vertices(g));

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    int num = my_strong_components(g, make_iterator_property_map(component.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num << std::endl;
    //std::cout << "Total number of components: " << num << std::endl;


    for (int i = 0; i != component.size(); ++i){
        std::cout << name[i] << " -> " << name[component[i]] << std::endl;
    }
    return 0;
}

