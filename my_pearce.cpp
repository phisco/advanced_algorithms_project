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

template <class Graph, class Rindex, class Stack>
void visit(const Graph g, const Vertex v, int* index, int*c, Rindex rindex, Stack s) {
    bool root = true;
    put(rindex, v, *index);
    *index += 1;
    //std::cout << get(rindex, v) << " enters" << std::endl;
    //std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        if (get(rindex, *w) == 0){
            //std::cout << "cond 1, check : " << get(rindex, v) << ", " << *index << std::endl;
            visit(g, *w, index, c, rindex, s);
        }
        if (get(rindex, *w) < get(rindex, v)) {
            //std::cout << "cond 2, check : " << get(rindex, v) << ", " << get(rindex, *w) << std::endl;
            put(rindex, v, get(rindex, *w));
            root = false;
        }
    }
    if(root){
        //std::cout << "cond 3, check : " << get(rindex, v) << std::endl;
        *index -= 1;
        while(!s->empty() && get(rindex, s->top()) >= get(rindex, v)){
            Vertex w = s->top();
            //std::cout << get(rindex, v) << " <- " << get(rindex, w) << std::endl;
            //std::cout << "stack pop : " << get(rindex, w) << std::endl;
            s->pop();
            put(rindex, w, *c);
            *index -= 1;
        }
        put(rindex, v, *c);
        *c -= 1;
    } else {
        //std::cout << "stack push : " << get(rindex, v) << std::endl;
        s->push(v);
    }
    // std::cout << "exit : " << get(num, v) << std::endl;
}
template <class Graph, class Rindex>
int strongconnect_main(const Graph& g, Rindex rindex) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s;
    int index = 1;
    int c = num_vertices(g) - 1;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(rindex, v) == 0){
            visit(g, v, &index, &c, rindex, &s);
        }
    }
    return c;
}

template <class Graph, class Rindex>
int pearce_scc(const Graph& g, Rindex rindex)
{
    for (int i = 0; i < num_vertices(g); i++){
        rindex[i] = 0;
    }

    return strongconnect_main(g, rindex);
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
    std::vector<int> rindex(num_vertices(g));

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    int num = pearce_scc(g, make_iterator_property_map(rindex.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num << std::endl;

    for (int i = 0; i != rindex.size(); ++i){
        std::cout << name[i] << " -> " << rindex[i] << std::endl;
    }
    return 0;
}

