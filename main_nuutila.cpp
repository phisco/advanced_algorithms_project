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
#include "my_nuutila.cpp"

using namespace boost;

typedef adjacency_list < listS, vecS, directedS> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;

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

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    std::vector<int> root(num_vertices(g));
    int num = nuutila_scc(g, make_iterator_property_map(root.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num << std::endl;

    for (int i = 0; i != root.size(); ++i){
        std::cout << name[i] << " -> " << name[root[i]] << std::endl;
    }
    return 0;
}
