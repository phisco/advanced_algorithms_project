//
// Created by phisco on 6/23/18.
//

#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
/*
  Sample output:
A directed graph:
A --> B
B --> C H
C --> D G
D --> E
E --> F C
F -->
G --> F D
H --> A G

Total number of components: 3
Vertex A is in component 2
Vertex B is in component 2
Vertex C is in component 1
Vertex D is in component 1
Vertex E is in component 1
Vertex F is in component 0
Vertex G is in component 1
Vertex H is in component 2
 */
using namespace boost;

int main(int, char*[])
{
    typedef adjacency_list < listS, vecS, directedS> graph_t;
    typedef std::pair<int, int> Edge;

    const int num_nodes = 8;
    enum nodes { A, B, C, D, E, F, G, H};
    char name[] = "ABCDEFGH";
    Edge edge_array[] = { Edge(A, B),
                          Edge(B, C), Edge(B, H),
                          Edge(C, D), Edge(C, G),
                          Edge(D, E),
                          Edge(E, F), Edge(E, C),
                          Edge(G, F), Edge(G, D),
                          Edge(H, A), Edge(H, G)
    };
    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    graph_t g(edge_array, edge_array + num_arcs, num_nodes);

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;

    typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;

    std::vector<int> component(num_vertices(g)), discover_time(num_vertices(g));
    std::vector<default_color_type> color(num_vertices(g));
    std::vector<Vertex> root(num_vertices(g));

    int num = strong_components(g,
            make_iterator_property_map(component.begin(), get(vertex_index, g)),
            root_map(make_iterator_property_map(root.begin(), get(vertex_index, g))).
            color_map(make_iterator_property_map(color.begin(), get(vertex_index, g))).
            discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, g))));

    std::cout << "Total number of components: " << num << std::endl;
    std::vector<int>::size_type i;
    for (i = 0; i != component.size(); ++i)
        std::cout << "Vertex " << name[i]
                  <<" is in component " << component[i] << std::endl;

    return 0;
}

