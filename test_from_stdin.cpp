
#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/graphml.hpp>

#include "include_and_types.cpp"
#include "my_pearce.cpp"
#include "my_nuutila.cpp"
#include "my_tarjan.cpp"
#include "my_pearce_not_recursive.cpp"

using namespace boost;


// Utility function to check if the results of the various algorithms are correct
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
    // read graph from stdin
    read_graphml(std::cin, g, dp);


    // the boost graph library implementation, used to check correctness of the results
    std::vector<int> bgl_component(num_vertices(g)), discover_time(num_vertices(g));
    std::vector<default_color_type> bgl_color(num_vertices(g));
    std::vector<Vertex> bgl_root(num_vertices(g));
    int num_bgl = strong_components(g,
                                    make_iterator_property_map(bgl_component.begin(), get(vertex_index, g)),
                                    root_map(make_iterator_property_map(bgl_root.begin(), get(vertex_index, g))).
                                    color_map(make_iterator_property_map(bgl_color.begin(), get(vertex_index, g))).
                                    discover_time_map(make_iterator_property_map(discover_time.begin(), get(vertex_index, g))));


    // warm up run
    std::cout << "Dirty\t\t" << std::flush;
    TarjanClass<typeInt, typeInt, typeInt, typeBool, typeBool, typeInt> t(&g);
    t.tarjan_scc();

    // Tarjan's algorithm over the given graph
    std::cout << "Tarjan\t\t" << std::flush;
    TarjanClass<typeInt, typeInt, typeInt, typeBool, typeBool, typeInt> tarjan(&g);
    std::vector<int>* component = tarjan.tarjan_scc();

    // Nuutila's algorithm over the given graph
    std::cout << "Nuutila\t\t" << std::flush;
    NuutilaClass<typeInt, typeInt, typeBool> nuutila(&g);
    std::vector<int>* root_nuutila = nuutila.nuutila_scc();

    // Pearce's recursive algorithm over the given graph
    std::cout << "Pearce\t\t" << std::flush;
    PearceClass<typeInt> pearce(&g);
    std::vector<int>* rindex = pearce.pearce_scc();

    // Pearce's non recursive algorithm over the given graph
    std::cout << "PearceNR\t\t" << std::flush;
    PearceNR <typeBool, typeInt> pearcenr(&g);
    std::vector<int>* rindexNR = pearcenr.pearce_not_recursive_scc();

    // Print the number of components returned by the bgl implementation
    std::cout << "Components:\t" << num_bgl << std::endl;
    // check correctness of the results
    std::cout << "Correct:\t" << (compare_results(bgl_component, *component) && compare_results(bgl_component, *root_nuutila) &&
        compare_results(bgl_component, *rindex) && compare_results(bgl_component, *rindexNR)) << std::endl;
}


