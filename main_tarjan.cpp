
#include "my_tarjan.cpp"
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/transitive_closure.hpp>


using namespace boost;

int main(int, char*[])
{

    /*enum nodes { A, B, C, D, E, F, G, H, I, L};
    const int num_nodes = L - A + 1;
    char name[] = "ABCDEFGHIL";

    Edge edge_array[] = { Edge(A, G),
                          Edge(B, F),
                          Edge(D, C),
                          Edge(H, A),
                          Edge(I, L),
                          Edge(E, I)
    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, num_nodes);

    };*/

    Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);


    std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index,g));
    std::cout << std::endl;

    std::vector<int> component(num_vertices(g));
    int num_tarjan = tarjan_scc(g, make_iterator_property_map(component.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num_tarjan << std::endl;
    //std::cout << "Total number of components: " << num << std::endl;

    IndexMap index = get(vertex_index,g);

    for (int i = 0; i != component.size(); ++i){
        std::cout << index[i] << " -> " << component[i] << std::endl;
    }
    return 0;
}
