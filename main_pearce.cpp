//
// Created by phisco on 6/23/18.
//

#include "my_pearce.cpp"
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
    /*typedef std::pair<int, int> Edge;


    enum nodes { A, B, C, D, E, F, G, H, I, L, M, N};
    char name[] = "ABCDEFGHILMN";
    const int num_nodes = N - A + 1;

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

    //This function takes a graph formatted by graphml fashion from the stdin
    /*Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);*/

    typedef std::pair<int, int> Edge;
    int n= 100000;
    Edge edge_array[n-1];


    for(int i=0;i<n-1;i++){
        edge_array[i]=Edge(i,i+1);
    }

    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, n);

    /*std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index,g));
    std::cout << std::endl;*/

    //PearceClass object
    PearceClass<typeInt> pearce(&g);
    std::vector<int>* rindex = pearce.pearce_scc();

    /*IndexMap index=get(vertex_index,g);
    for (int i = 0; i != num_vertices(g); ++i){
        std::cout << index[i] << " -> " << (*rindex)[i] << std::endl;
    }*/
    return 0;
}
