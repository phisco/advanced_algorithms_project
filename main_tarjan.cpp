
#include "my_tarjan.cpp"
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/transitive_closure.hpp>
#include <mcheck.h>

using namespace boost;

typedef typename boost::iterator_property_map<__gnu_cxx::__normal_iterator<int*, std::vector<int> >,
        boost::vec_adj_list_vertex_id_map<boost::no_property, long unsigned int>, int, int&> typeInt;

typedef typename boost::iterator_property_map<std::_Bit_iterator,
        boost::vec_adj_list_vertex_id_map<boost::no_property, long unsigned int>, bool, std::_Bit_reference> typeBool;

int main(int argc, char*argv[])
{

    /*Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);*/


    /*Graph g;
    typedef std::pair<int, int> Edge;
    int n=100000;
    for(int i=0;i<n;i++){
        add_vertex(g);
    }
    vertex_iter it1,it2;
    Vertex v,w;
    for(boost::tie(it1,it2)=vertices(g);it1!=it2-1;++it1){
        v=*it1;
        w=*(it1+1);
        add_edge(v,w,g);
    }*/

    /*
    typedef std::pair<int, int> Edge;
    int n=10000;
    Edge * edge_array=new Edge[n*(n-1)];

    int k=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j){
                edge_array[k]=Edge(i,j);
                k++;
            }

        }
    }



    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(&edge_array[0], &edge_array[n*(n-1)], n);

    delete [] edge_array;*/


    /*std::cout << "A directed graph:" << std::endl;
    print_graph(g, get(vertex_index,g));
    std::cout << std::endl;*/

    typedef std::pair<int, int> Edge;
    int n;
    if(argc==2){
        n=atof(argv[1]);
    }else{
        return 0;
    }
    Edge edge_array[n-1];


    for(int i=0;i<n-1;i++){
        edge_array[i]=Edge(i,i+1);
    }

    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, n);

    //delete [] edge_array;

    std::vector<int> component(num_vertices(g));
    TarjanClass<typeInt, typeInt, typeInt, typeBool, typeBool> tarjan(g);
    int num_tarjan = tarjan.tarjan_scc(make_iterator_property_map(component.begin(), get(vertex_index, g)));

    std::cout << "Number of components: "<< num_tarjan << std::endl;
    //std::cout << "Total number of components: " << num << std::endl;

    IndexMap index = get(vertex_index,g);

    for (int i = 0; i != component.size(); ++i){
        std::cout << index[i] << " -> " << component[i] << std::endl;
    }
    return 0;
}
