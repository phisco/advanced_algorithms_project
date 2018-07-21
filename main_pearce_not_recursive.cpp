#include "my_pearce_not_recursive.cpp"
#include "include_and_types.cpp"

using namespace boost;

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

    //Imperative Version
    PearceNR <typeBool, typeInt> pearcenr(&g);
    std::vector<int>* rindex = pearcenr.pearce_not_recursive_scc();

    IndexMap index=get(vertex_index,g);
    for (int i = 0; i != num_vertices(g); ++i){
        std::cout << index[i] << " -> " << (*rindex)[i] << std::endl;
    }
    return 0;
}
