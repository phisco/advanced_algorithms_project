#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <iostream>
#include <stdlib.h>     /* atoi */
//#include "include_and_types.cpp"

typedef boost::adjacency_list <boost::setS, boost::vecS, boost::directedS, boost::no_property, boost::disallow_parallel_edge_tag> G;
typedef boost::erdos_renyi_iterator<boost::minstd_rand, G> ERGen;

using namespace std;

int main(int argc,char* argv[])
{
    boost::dynamic_properties dp;
    boost::minstd_rand gen;
    // Create graph with 100 nodes and edges with probability 0.05
    float n, p;
    if (argc <= 1){
        n= 20;
        p= 0.05;
    } else if( argc == 3){
        n = atof(argv[1]);
        p = atof(argv[2]);
    } else return 1;

    G g(ERGen(gen, n, p), ERGen(), n);
    boost::write_graphml(cout, g, dp, true);

    return 0;
}