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
    
    //This function takes a graph formatted by graphml fashion from the stdin
    Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);
    
    //Printing the graph
    std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index,g));
    std::cout << std::endl;

    //PearceClass object
    PearceClass<typeInt> pearce(&g);
    std::vector<int>* rindex = pearce.pearce_scc();

    //Printing the result
    IndexMap index=get(vertex_index,g);
    for (int i = 0; i != num_vertices(g); ++i){
        std::cout << index[i] << " -> " << (*rindex)[i] << std::endl;
    }
    return 0;
}
