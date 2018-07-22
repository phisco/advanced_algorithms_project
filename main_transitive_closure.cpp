#include "include_and_types.cpp"
#include <set>
#include "my_transitive_closure.cpp"
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/transitive_closure.hpp>

typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;

//Ad-hoc typedef interator_property_map types
typedef boost::iterator_property_map<__gnu_cxx::__normal_iterator<long unsigned int*, std::vector<long unsigned int> >,
        boost::vec_adj_list_vertex_id_map<boost::no_property, long unsigned int>,
                long unsigned int, long unsigned int&> typeVertex;

typedef boost::iterator_property_map<__gnu_cxx::__normal_iterator<std::set<long unsigned int>**,
        std::vector<std::set<long unsigned int>*> >,
        boost::vec_adj_list_vertex_id_map<boost::no_property, long unsigned int>, std::set<long unsigned int>*,
                std::set<long unsigned int>*&> typeSetVertex;

using namespace std;


int main(int, char*[]){
    //for debugging purpouses
    /*std::ifstream in("/home/emanuele/Scrivania/advanced_algorithms_project/graphs/6_0.2_6.xml");
    std::cin.rdbuf(in.rdbuf());*/

    //Reading graph from stdin
    Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);

    //Graph printing
    std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index, g));
    std::cout << std::endl;

    //Declaration of TransitiveClosure object
    TransitiveClosure <typeVertex, typeBool, typeInt, typeSetVertex> transitive_cl(&g);
    transitive_cl.transitive_closure_scc();

    //used only to compare results. This applies the built-in function of Boost for applying transitive closure
    std::cout << "BGL"<<std::endl;
    Graph gt;
    transitive_closure(g,gt);
    print_graph(gt, get(vertex_index,gt));

    return 0;
}