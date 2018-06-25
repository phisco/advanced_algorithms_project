//
// Created by phisco on 6/23/18.
//

#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <boost/timer/timer.hpp>
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

template <class Graph, class Num, class Root, class InComponent, class Stack>
void nuutila(const Graph g, const Vertex v, int* i, int*c, Num num, Root root, InComponent inComponent, Stack s) {
    *i += 1;
    put(root, v, v);
    put(inComponent, v, false);
    put(num, v, *i);
    // std::cout << get(num, v) << " enters" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        if (get(num, *w) == 0){
            // std::cout << "cond 1, check : " << get(num, v) << ", " << *i+1 << std::endl;
            nuutila(g, *w, i, c, num, root, inComponent, s);
        }
        if (!get(inComponent, *w)) {
            // std::cout << "cond 2, check : " << get(num, v) << ", " << get(num, *w) << std::endl;
            // std::cout << "root of " << get(num, v) << " <- " << get(num, get(root, v)) << std::endl;
            // std::cout << "root of " << get(num, *w) << " <- " << get(num, get(root, *w)) << std::endl;
            put(root, v, get(num, get(root, v)) > get(num, get(root, *w)) ? get(root, *w) : get(root, v));
            // std::cout << "post root of " << get(num, v) << " <- " << get(num, get(root, v)) << std::endl;
        }
    }
    if(get(root, v) == v){
        // std::cout << "cond 3, check : " << get(num, v) << std::endl;
        *c += 1;
        put(inComponent, v, true);
        while(!s->empty() && get(num, s->top() )> get(num, v)){
            Vertex w = s->top();
            // std::cout << get(num, v) << " <- " << get(num, w) << std::endl;
            // std::cout << "stack pop : " << get(num, w) << std::endl;
            s->pop();
            put(inComponent, w, true);
        }
    } else {
        // std::cout << "stack push : " << get(num, v) << std::endl;
        s->push(v);
    }
    // std::cout << "exit : " << get(num, v) << std::endl;
}
template <class Graph, class Num, class InComponent, class Root>
int nuutila_main(const Graph& g, Num num, Root root, InComponent inComponent) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s;
    int i = 0;
    int c = 0;
    timer::auto_cpu_timer t;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(num, v) == 0){
            nuutila(g, v, &i, &c, num, root, inComponent, &s);
        }
    }
    return c;
}

template <class Graph, class Root>
int nuutila_scc(const Graph& g, Root root)
{
    std::vector<int> number(num_vertices(g));
    bool inComponent[num_vertices(g)];
    IndexMap index = get(vertex_index, g);

    for (int i = 0; i < num_vertices(g); i++){
        inComponent[i] = false;
    }

    return nuutila_main(g,
                       make_iterator_property_map(number.begin(), get(vertex_index, g)),
                       root,
                       make_iterator_property_map(&inComponent[0], get(vertex_index,g)));
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
    std::vector<Vertex> root(num_vertices(g));

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    int num = nuutila_scc(g, make_iterator_property_map(root.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num << std::endl;

    for (int i = 0; i != root.size(); ++i){
        std::cout << name[i] << " -> " << name[root[i]] << std::endl;
    }
    return 0;
}

