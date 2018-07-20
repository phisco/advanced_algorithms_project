//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;

template <class Root, class Num, class InComponent>
class NuutilaClass{
private:
    Graph* g;
    Root root;
    int i, c;
    Num num;
    InComponent inComponent;

    std::stack<Vertex> s; // v*w
    std::vector<int> number;
    std::vector<bool> inComponentVec;
    std::vector<int> rootVet;

    void nuutila(const Vertex& v) {
        i += 1;
        put(root, v, v);
        put(inComponent, v, false);
        put(num, v, i);
        std::pair<vertex_iter, vertex_iter> vp;
        typename graph_traits<Graph>::adjacency_iterator w, ai_end;
        // iterate over outgoing edges
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
            while(!s.empty() && get(num, s.top()) > get(num, v)){
                Vertex w = s.top();
                s.pop();
                put(inComponent, w, true);
            }
        } else {
            s.push(v);
        }

    }

public:
    NuutilaClass(Graph* graph){
        g=graph;

        IndexMap index = get(vertex_index, *g);
        int n = num_vertices(*g);

        number = *new std::vector<int>(n);
        inComponentVec = *new std::vector<bool>(n);
        rootVet=*new std::vector<int>(n);

        for (int i = 0; i < num_vertices(*g); i++){
            inComponentVec[i] = false;
        }

        num = make_iterator_property_map(number.begin(), index); // v*w
        inComponent = make_iterator_property_map(inComponentVec.begin(), index); // v
        root= make_iterator_property_map(rootVet.begin(), get(vertex_index, *g));

        // needed counters
        i = 0;
        c = 0;
    }

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

        // return the vector of component found
        return &rootVet;
    }

};



