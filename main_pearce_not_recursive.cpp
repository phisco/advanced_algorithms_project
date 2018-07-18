//
// Created by phisco on 6/23/18.
//


#include "my_pearce_not_recursive.cpp"
#include "include_and_types.cpp"

using namespace boost;

int main(int, char*[])
{
    typedef std::pair<int, int> Edge;

    enum { A, B, C, D, E, F, G, H, I, N };
    const int num_nodes = N;
    const char* name = "ABCDEFGHI";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
            { Edge(A,B), Edge(B,A), Edge(A,C), Edge(C,A), Edge(B,D), Edge(C,D),
              Edge(E,C), Edge(E,F), Edge(F,D), Edge(D,F), Edge(E,H), Edge(H,F), Edge(H,G), Edge(G,E),
              Edge(I,G), Edge(I,H), Edge(I,I)};
    const int num_arcs = sizeof(edge_array)/sizeof(edge_array[0]);
    /*const int num_nodes = 8;

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
    */
    Graph g(edge_array, edge_array + num_arcs, num_nodes);

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    std::vector<int> rindex(num_vertices(g));
    //Recursive Version
    //int num = pearce_scc(g, make_iterator_property_map(rindex.begin(), get(vertex_index, g)));
    //Imperative Version
    int num = pearce_not_recursive_scc(g, make_iterator_property_map(rindex.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num << std::endl;

    for (int i = 0; i != num_vertices(g); ++i){
        std::cout << name[i] << " -> " << rindex[i] << std::endl;
    }
    return 0;
}
