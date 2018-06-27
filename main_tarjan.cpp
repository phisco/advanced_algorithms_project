
#include <boost/config.hpp>
#include <boost/timer/timer.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include "my_tarjan.cpp"


using namespace boost;

typedef adjacency_list <vecS, vecS, directedS> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;
typedef std::pair<int, int> Edge;

int main(int, char*[])
{

    const int num_nodes = 8;
    enum nodes { A, B, C, D, E, F, G, H, I, L};
    char name[] = "ABCDEFGHIL";

    Edge edge_array[] = { Edge(A, G),
                          Edge(B, F),
                          Edge(D, C),
                          Edge(H, A),
                          Edge(I, L),
                          Edge(E, I)
    };

    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, num_nodes);

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    std::vector<int> component(num_vertices(g));
    int num_tarjan = tarjan_scc(g, make_iterator_property_map(component.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num_tarjan << std::endl;
    //std::cout << "Total number of components: " << num << std::endl;


    for (int i = 0; i != component.size(); ++i){
        std::cout << name[i] << " -> " << component[i] << std::endl;
    }
    return 0;
}
