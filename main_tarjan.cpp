
#include "my_tarjan.cpp"
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/transitive_closure.hpp>

using namespace boost;

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
    int n= 100000;
    Edge edge_array[n-1];


    for(int i=0;i<n-1;i++){
        edge_array[i]=Edge(i,i+1);
    }

    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, n);

    //delete [] edge_array;

    TarjanClass<typeInt, typeInt, typeInt, typeBool, typeBool, typeInt> tarjan(&g);
    std::vector<int>* comp_tarjan = tarjan.tarjan_scc();

    /*IndexMap index = get(vertex_index,g);

    for (int i = 0; i != comp_tarjan->size(); ++i){
        std::cout << index[i] << " -> " << (*comp_tarjan)[i] << std::endl;
    }*/
    return 0;
}
