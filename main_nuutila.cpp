#include "my_nuutila.cpp"
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/transitive_closure.hpp>

using namespace boost;

#ifndef TYPEDEF
#define TYPEDEF

typedef adjacency_list <vecS, vecS, directedS> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;

#endif

int main(int, char*[])
{
    //An example of how to design a graph "by hand" without using Graphml and stdin
    /*enum { A, B, C, D, E, F, G, H, I, N };
    const int num_nodes = N;
    const char* name = "ABCDEFGHI";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
            { Edge(A,B), Edge(B,A), Edge(A,C), Edge(C,A), Edge(B,D), Edge(C,D),
              Edge(E,C), Edge(E,F), Edge(F,D), Edge(D,F), Edge(E,H), Edge(H,F), Edge(H,G), Edge(G,E),
              Edge(I,G), Edge(I,H), Edge(I,I)};

    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, num_nodes);*/


    //This function takes a graph formatted by graphml fashion from the stdin
    Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);

    //Printing the graph
    std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index,g));
    std::cout << std::endl;

    //NuutilaClass instance
    NuutilaClass<typeInt, typeInt, typeBool> nuutila(&g);
    std::vector<int>* root = nuutila.nuutila_scc();

    //Printing the results
    IndexMap index = get(vertex_index,g);
    
    for (int i = 0; i != root->size(); ++i){
        std::cout << index[i] << " -> " << index[(*root)[i]] << std::endl;
    }
    return 0;
}
