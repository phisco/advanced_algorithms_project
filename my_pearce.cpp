//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;

template<class Rindex>
class PearceClass{
private:
    Graph g;
    int index, c;
    Rindex rindex;
    std::stack<Vertex> s; // v*w
public:
    PearceClass(const Graph& graph, Rindex r){
        g = graph;
        rindex = r;
        IndexMap index = get(vertex_index, g);
    }

    void pearce(const Vertex& v) {
        put(rindex, v, index);
        bool root = true;
        index += 1;


        typename graph_traits<Graph>::adjacency_iterator w, ai_end;
        // iterate over the outgoing edges
        for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
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
            // pop from stack vertices in the component
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
        // std::cout << "exit : " << get(num, v) << std::endl;
    }
    int pearce_scc() {
        std::pair<vertex_iter, vertex_iter> vp;
        // the needed counters
        index = 1;
        c = num_vertices(g) - 1;
        timer::auto_cpu_timer t; // initialize the timer
        // iterate over vertices
        for (vp = vertices(g); vp.first != vp.second; ++vp.first){
            Vertex v = *vp.first;
            if (get(rindex, v) == 0){ // if not already visited
                pearce(v);
            }
        }
        return num_vertices(g) - 1 - c;
    }

};
