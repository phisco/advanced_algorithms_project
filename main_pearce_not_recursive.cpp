#include "my_pearce_not_recursive.cpp"
#include "include_and_types.cpp"
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>

using namespace boost;

int main(int, char*[])
{
    /*This is an example of how to modify this code for describing a graph "by hand" without using graphml parser and
    stdin*/
    /*typedef std::pair<int, int> Edge;

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
    Graph g(edge_array, edge_array + num_arcs, num_nodes);*/

    //Reading graph from stdin
    Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);

    //Graph printing
    std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index,g));
    std::cout << std::endl;

    //Instantiation of the PearceNR class object
    PearceNR <typeBool, typeInt> pearcenr(&g);
    std::vector<int>* rindex = pearcenr.pearce_not_recursive_scc();

    //Results printing
    IndexMap index=get(vertex_index,g);
    for (int i = 0; i != num_vertices(g); ++i){
        std::cout << index[i] << " -> " << (*rindex)[i] << std::endl;
    }
    return 0;
}
