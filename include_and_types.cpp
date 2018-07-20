#ifndef TYPEDEF
#define TYPEDEF

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/timer/timer.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <boost/graph/strong_components.hpp>

using namespace boost;

typedef adjacency_list <vecS, vecS, directedS, no_property, disallow_parallel_edge_tag> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;
typedef std::pair<int, int> Edge;

typedef typename boost::iterator_property_map<__gnu_cxx::__normal_iterator<int*, std::vector<int> >,
        boost::vec_adj_list_vertex_id_map<boost::no_property, long unsigned int>, int, int&> typeInt;

typedef typename boost::iterator_property_map<std::_Bit_iterator,
        boost::vec_adj_list_vertex_id_map<boost::no_property, long unsigned int>, bool, std::_Bit_reference> typeBool;


#endif
