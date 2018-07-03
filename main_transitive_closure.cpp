//
// Created by root on 03/07/18.
//


#include "include_and_types.cpp"
#include <set>
#include "my_transitive_closure.cpp"

int main(int, char*[]){
    enum { A, B, C, D, E, F, G, H, I, N };
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
    Graph g(edge_array, edge_array + num_arcs, num_nodes);

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;


    std::vector<Vertex> root(num_vertices(g));
    std::vector<bool> inComp(num_vertices(g));
    std::vector<std::set<Vertex>*> sets(num_vertices(g));
    std::vector<int> num(num_vertices(g));



    transitive_closure_scc(g,  make_iterator_property_map(root.begin(), get(vertex_index,g)),
                           make_iterator_property_map(inComp.begin(), get(vertex_index,g)),
                           make_iterator_property_map(sets.begin(), get(vertex_index,g)),
                           make_iterator_property_map(num.begin(), get(vertex_index,g)),sets, name);


    return 0;

}