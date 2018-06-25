
#include <boost/config.hpp>
#include "my_pearce.cpp"
#include "my_nuutila.cpp"
#include "my_tarjan.cpp"
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

using namespace boost;

typedef adjacency_list < listS, vecS, directedS> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;


template <class Result1, class Result2>
bool compare_results(Result1 r1, Result2 r2){
    if (r1.size() != r2.size())
        return false;
    int maxVal=0;
    for(int i=0; i!=r1.size(); i++){
        maxVal = std::max(maxVal, r1[i]);
    }
    for(int i=0; i!=r2.size(); i++){
        maxVal = std::max(maxVal, r2[i]);
    }
    int comp[maxVal+1];
    for (int i=0; i != maxVal+1; i++)
        comp[i]=0;

    for (int i = 0; i != r1.size(); i++){
        if (comp[r1[i]]==0)
            comp[r1[i]]=r2[i];
        if (comp[r1[i]]!=r2[i]){
            return false;
        }
    }
    return true;
}

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

    std::vector<int> component(num_vertices(g));
    int num_tarjan = tarjan_scc(g, make_iterator_property_map(component.begin(), get(vertex_index, g)));


    std::vector<int> root(num_vertices(g));
    int num_nuutila = nuutila_scc(g, make_iterator_property_map(root.begin(), get(vertex_index, g)));

    std::vector<int> rindex(num_vertices(g));
    int num_pearce = pearce_scc(g, make_iterator_property_map(rindex.begin(), get(vertex_index, g)));

    //std::cout << "Check same results : " << (num_pearce==num_tarjan) << (num_tarjan==num_nuutila) << compare_results(component, root) << compare_results(root, rindex) << std::endl;
    std::cout << "Check same results : " << ((num_pearce==num_tarjan) && (num_tarjan==num_nuutila) && compare_results(component, root) && compare_results(root, rindex)) << std::endl;
    std::cout << "Number of components: "<< num_tarjan << std::endl;
    //std::cout << "Total number of components: " << num << std::endl;


    std::cout << "No" << "\t->\tTa\tNu\tPe"<< std::endl;
    for (int i = 0; i != component.size(); ++i){
        std::cout << name[i] << "\t->\t" << component[i] << "\t" << root[i] << "\t" << rindex[i] << std::endl;
    }
    return 0;
}


