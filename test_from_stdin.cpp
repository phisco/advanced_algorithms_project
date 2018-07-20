
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/config.hpp>
#include <boost/graph/graphml.hpp>

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

#include "include_and_types.cpp"
#include "my_pearce.cpp"
#include "my_nuutila.cpp"
#include "my_tarjan.cpp"
#include "my_pearce_not_recursive.cpp"


#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>

using namespace boost;

typedef boost::erdos_renyi_iterator<boost::minstd_rand, Graph> ERGen;

template <class Result1, class Result2>
bool compare_results(const Result1 r1, const Result2 r2){
    if (r1.size() != r2.size())
        return false;
    int maxVal=0;
    int minVal=0;
    for(int i=0; i!=r1.size(); i++){
        maxVal = std::max(maxVal, r1[i]);
        minVal = std::min(minVal, r2[i]);
    }
    minVal-=1;
    maxVal+=1;
    int comp[maxVal];
    for (int i=0; i != maxVal; i++)
        comp[i]=minVal;

    for (int i = 0; i != r1.size(); i++){
        if (comp[r1[i]]==minVal) {
            for (int j = 0; j < i; j++) {
                if (r1[i] != r1[j] && r2[i] == r2[j])
                    return false;
            }
            comp[r1[i]] = r2[i];
        }
        if (comp[r1[i]]!=r2[i]){
            return false;
        }
    }
    return true;
}

std::vector<int> correct_nuutila_root(std::vector<int> vec){
    bool ok = false;
    while(!ok){
        ok = true;
        for(int i=0; i<vec.size(); i++){
            if(vec[i] != i && vec[i]!= vec[vec[i]]){
                vec[i]=vec[vec[i]];
                ok=false;
            }
        }
    }
    return vec;
}
int main(int, char*[])
{
    Graph g;
    dynamic_properties dp;
    read_graphml(std::cin, g, dp);

    std::vector<int> bgl_component(num_vertices(g)), discover_time(num_vertices(g));
    std::vector<default_color_type> bgl_color(num_vertices(g));
    std::vector<Vertex> bgl_root(num_vertices(g));
    int num_bgl = strong_components(g,
                                    make_iterator_property_map(bgl_component.begin(), get(vertex_index, g)),
                                    root_map(make_iterator_property_map(bgl_root.begin(), get(vertex_index, g))).
                                    color_map(make_iterator_property_map(bgl_color.begin(), get(vertex_index, g))).
                                    discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, g))));

    // warm up run
    std::cout << "Tarjan\t\t" << std::flush;
    std::vector<int> component(num_vertices(g));
    for(int i = 0; i<component.size(); i++)
        component[i]=0;
    TarjanClass<typeInt, typeInt, typeInt, typeBool, typeBool, typeInt> tarjan(g,make_iterator_property_map(component.begin(), get(vertex_index, g)));
    int num_tarjan = tarjan.tarjan_scc();

    std::cout << "Nuutila\t\t" << std::flush;
    std::vector<int> root_nuutila(num_vertices(g));
    for(int i = 0; i<root_nuutila.size(); i++)
        root_nuutila[i]=0;
    NuutilaClass<typeInt, typeInt, typeBool> n(g, make_iterator_property_map(root_nuutila.begin(), get(vertex_index, g)));
    int num_nuutila = n.nuutila_scc();
    root_nuutila = correct_nuutila_root(root_nuutila);

    std::cout << "Pearce\t\t" << std::flush;
    std::vector<int> rindex(num_vertices(g));
    for (int i = 0; i < num_vertices(g); i++){
        rindex[i] = 0;
    }
    PearceClass<typeInt> p(g, make_iterator_property_map(rindex.begin(), get(vertex_index, g)));
    int num_pearce = p.pearce_scc();

    std::cout << "PearceNR\t\t" << std::flush;
    std::vector<int> rindexNR(num_vertices(g));
    for(int i = 0; i<rindexNR.size(); i++)
        rindexNR[i]=0;
    int num_pearce_nr = pearce_not_recursive_scc(g, make_iterator_property_map(rindexNR.begin(), get(vertex_index, g)));

    /*std::cout << "Pearce_NR\t" << std::flush;
    std::vector<int> rindex_not_recursive(num_vertices(g));
    int num_pearce_not_recursive = pearce_not_recursive_scc(g, make_iterator_property_map(rindex_not_recursive.begin(), get(vertex_index, g)));
    */

    std::cout << "Components:\t" << num_bgl << std::endl;
    std::cout << "Correct:\t" << (compare_results(bgl_component, component) && compare_results(bgl_component, root_nuutila) &&
        compare_results(bgl_component, rindex) && compare_results(bgl_component, rindexNR) /*&&  compare_results(bgl_component, rindex_not_recursive)*/) << std::endl;
}


