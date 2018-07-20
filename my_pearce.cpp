#include "include_and_types.cpp"

using namespace boost;

template<class Rindex>
class PearceClass{
private:
    //The graph pointer
    Graph* g;

    //Property Map Objects. These are the attributes associated to a vertex
    Rindex rindex;

    //The data structure which will compose the Property Map Object.
    std::vector<int> rind;

    //The SCC stack
    std::stack<Vertex> s; // v*w

    //DFS index
    int index;
    //SCC Counter
    int c;

    /**
    * This function is the core of the procedure. It visits the vertex passed as parameter and all the vertex reachable
    * by that following the graph edges. For each vertex, it finds all the vertices belonging to its same SCC, if it
    * is not formed yet.
    * This is the C++ implementation of the pseudo-code described by Pearce in his paper.
    * @param v, is the vertex visited
    */
    void pearce(const Vertex& v) {
        //Property Map attributes attached to the vertex
        put(rindex, v, index);
        bool root = true;
        index += 1;

        typename graph_traits<Graph>::adjacency_iterator w, ai_end;
        // iterate over the outgoing edges
        for (boost::tie(w, ai_end) = adjacent_vertices(v, *g); w != ai_end; ++w){
            if (get(rindex, *w) == 0){ // if not already been visited
                pearce(*w);
            }

            if (get(rindex, *w) < get(rindex, v)) {
                put(rindex, v, get(rindex, *w));
                root = false;
            }
        }

        if(root){
            index -= 1;
            // pop from stack vertices in the component, if it is not a trivial one
            while(!s.empty() && get(rindex, s.top()) >= get(rindex, v)){
                Vertex w = s.top();
                s.pop();
                put(rindex, w, c);
                index -= 1;
            }
            put(rindex, v, c);
            c -= 1;
        } else {
            s.push(v);
        }
    }

public:
    /**
    * This is the constructor of the PearceClass class. It takes the reference of the graph already allocated by the
    * caller function in main_pearce.cpp. It initializes all the data structures and Property Map Objects
    * @param graph
    */
    PearceClass(Graph* graph){
        g = graph;
        int n=num_vertices(*g);

        //Data structure allocation and initialization
        rind=*new std::vector<int>(n);
        rindex=make_iterator_property_map(rind.begin(), get(vertex_index, *g));

        // the needed counters
        index = 1;
        c = n - 1;
    }

    /**
     * This function is the one called by the main_pearce's main function. It starts the procedure of pearce by visiting
     * all the vertex of the graph.
     * @return the reference of the rindex vector, useful for stdout printing purposes
     */
    std::vector<int>* pearce_scc() {
        std::pair<vertex_iter, vertex_iter> vp;
        timer::auto_cpu_timer t; // initialize the timer
        // iterate over vertices
        for (vp = vertices(*g); vp.first != vp.second; ++vp.first){
            Vertex v = *vp.first;
            if (get(rindex, v) == 0){ // if not already visited
                pearce(v);
            }
        }

        return &rind;
    }

};
