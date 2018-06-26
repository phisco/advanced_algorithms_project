#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <iostream>

typedef boost::adjacency_list<> Graph;
typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;

using namespace std;

int main(int,char*[])
{
    boost::dynamic_properties dp;
    boost::minstd_rand gen;
    // Create graph with 100 nodes and edges with probability 0.05
    for (int i=10; i <= 100000; i*=10) {
        Graph g(ERGen(gen, 100, 0.05), ERGen(), 100);
        write_graphml(std::cout, g, dp, true);
    }

    return 0;
}