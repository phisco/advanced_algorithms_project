//
// Created by root on 03/07/18.
//


#include "include_and_types.cpp"
#include <set>
#include "my_transitive_closure.cpp"
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/transitive_closure.hpp>

typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;


using namespace std;


int main(int, char*[]){
    /*enum { A, B, C, D, E, F, G, H, I, N };
    const int num_nodes = N;
    const char* name = "ABCDEFGHI";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
            { Edge(A,B), Edge(B,A), Edge(A,C), Edge(C,A), Edge(B,D), Edge(C,D),
              Edge(E,C), Edge(E,F), Edge(F,D), Edge(D,F), Edge(E,H), Edge(H,F), Edge(H,G), Edge(G,E),
              Edge(I,G), Edge(I,H), Edge(I,I)};
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);


    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, num_nodes);*/


    Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index, g));
    std::cout << std::endl;

    std::vector<Vertex> root(num_vertices(g));
    std::vector<bool> inComp(num_vertices(g));
    std::vector<std::set<Vertex>*> sets(num_vertices(g));
    std::vector<int> num(num_vertices(g));



    transitive_closure_scc(g,  make_iterator_property_map(root.begin(), get(vertex_index,g)),
                           make_iterator_property_map(inComp.begin(), get(vertex_index,g)),
                           make_iterator_property_map(sets.begin(), get(vertex_index,g)),
                           make_iterator_property_map(num.begin(), get(vertex_index,g)),sets);

    //used only to compare results
    std::cout << "Result provided by BGL"<<std::endl;
    Graph gt;

    transitive_closure(g,gt);
    print_graph(gt, get(vertex_index,g));
    return 0;

}