//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;

template <class Root, class Num, class InComponent>
class NuutilaClass{
private:
    //The graph pointer
    Graph* g;

    //Property Map Objects. These are the attributes associated to a vertex
    Root root;
    Num num;
    InComponent inComponent;

    //The SCC stack
    std::stack<Vertex> s; // v*w

    //The data structures which will compose the Property Map Objects.
    std::vector<int> number;
    std::vector<bool> inComponentVec;
    std::vector<int> rootVet;

    //DFS index
    int i;
    //SCC Counter
    int c;

    /**
    * This function is the core of the procedure. It visits the vertex passed as parameter and all the vertex reachable
    * by that following the graph edges. For each vertex, it finds all the vertices belonging to its same SCC, if it
    * is not formed yet.
    * This is the C++ implementation of the pseudo-code (VISIT 1) described by Nuutila in his paper.
    * @param v, is the vertex visited
    */
    void nuutila(const Vertex& v) {
        i += 1;
        //Property Map attributes attached to the vertex
        put(root, v, v);
        put(inComponent, v, false);
        put(num, v, i);

        std::pair<vertex_iter, vertex_iter> vp;
        typename graph_traits<Graph>::adjacency_iterator w, ai_end;
        //This loop visits all the vertex reached by an edge starting from v
        for (boost::tie(w, ai_end) = adjacent_vertices(v, *g); w != ai_end; ++w){

            if (get(num, *w) == 0){ // if not already visited
                nuutila(*w);
            }

            if (!get(inComponent, *w)) { // if not yet in a component
                auto rw = get(root, *w);
                auto rv = get(root, v);
                put(root, v, get(num, rv) > get(num, rw) ? rw : rv);
            }
        }

        if(get(root, v) == v){ // if it's the root of itself
            c += 1;
            put(inComponent, v, true);
            //All the vertex in the root's SCC are on the stack, except for the root itself. This pops all of them.
            while(!s.empty() && get(num, s.top()) > get(num, v)){
                Vertex w = s.top();
                s.pop();
                put(inComponent, w, true);
            }
        } else {
            //If a vertex is not a root, it pushes itself on the stack
            s.push(v);
        }

    }

public:
    /**
     * This is the constructor of the NuutilaClass class. It takes the reference of the graph already allocated by the
     * caller function in main_nuutila.cpp. It initializes all the data structures and Property Map Objects
     * @param graph
     */
    NuutilaClass(Graph* graph){
        g=graph;
        IndexMap index = get(vertex_index, *g);
        int n = num_vertices(*g);

        //Data structure allocation
        number = *new std::vector<int>(n);
        inComponentVec = *new std::vector<bool>(n);
        rootVet=*new std::vector<int>(n);

        //InComponentVec initialization
        for (int i = 0; i < num_vertices(*g); i++){
            inComponentVec[i] = false;
        }

        //Property Map Objects allocation
        num = make_iterator_property_map(number.begin(), index); // v*w
        inComponent = make_iterator_property_map(inComponentVec.begin(), index); // v
        root= make_iterator_property_map(rootVet.begin(), get(vertex_index, *g));

        //needed counters
        i = 0;
        c = 0;
    }

    /**
     * This function is the one called by the main_nuutila's main function. It starts the procedure of nuutila by visiting
     * all the vertex of the graph.
     * @return the reference of the root vector, useful for stdout printing purposes
     */
    std::vector<int>* nuutila_scc() {
        std::pair<vertex_iter, vertex_iter> vp;

        // initialize the timer
        timer::auto_cpu_timer t;

        // iterate over vertices
        for (vp = vertices(*g); vp.first != vp.second; ++vp.first){
            Vertex v = *vp.first;
            if (get(num, v) == 0){ // if not already visited
                nuutila(v);
            }
        }

        return &rootVet;
    }

};



