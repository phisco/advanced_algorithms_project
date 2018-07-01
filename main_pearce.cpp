//
// Created by phisco on 6/23/18.
//

#include "my_pearce.cpp"

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
    typedef std::pair<int, int> Edge;


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
    Graph g(edge_array, edge_array + num_arcs, num_nodes);

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    std::vector<int> rindex(num_vertices(g));
    int num = pearce_scc(g, make_iterator_property_map(rindex.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num << std::endl;

    for (int i = 0; i != num_vertices(g); ++i){
        std::cout << name[i] << " -> " << rindex[i] << std::endl;
    }
    return 0;
}
