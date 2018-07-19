//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;
template <class Graph, class Num, class Root, class InComponent, class Stack>
void nuutila(const Graph& g, const Vertex v, int* i, int*c, Num& num, Root& root, InComponent& inComponent, Stack s) {
    *i += 1;
    put(root, v, v);
    put(inComponent, v, false);
    put(num, v, *i);
    std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    // iterate over outgoing edges
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){

        if (get(num, *w) == 0){ // if not already visited
            nuutila(g, *w, i, c, num, root, inComponent, s);
        }

        if (!get(inComponent, *w)) { // if not yet in a component
            auto rw = get(root, *w);
            auto rv = get(root, v);
            put(root, v, get(num, rv) > get(num, rw) ? rw : rv);
        }
    }

    if(get(root, v) == v){ // if it's the root of itself
        *c += 1;
        put(inComponent, v, true);
        while(!s->empty() && get(num, s->top()) > get(num, v)){
            Vertex w = s->top();
            s->pop();
            put(inComponent, w, true);
        }
    } else {
        s->push(v);
    }
    
}

template <class Graph, class Num, class InComponent, class Root>
int nuutila_main(const Graph& g, Num num, Root& root, InComponent inComponent) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s; // v*w

    // needed counters
    int i = 0;
    int c = 0;

    // initialize the timer
    timer::auto_cpu_timer t;

    // iterate over vertices
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(num, v) == 0){ // if not already visited
            nuutila(g, v, &i, &c, num, root, inComponent, &s);
        }
    }

    // return the number of component found
    return c;
}

template <class Graph, class Root>
int nuutila_scc(const Graph& g, Root root)
{
    int n = num_vertices(g);
    IndexMap index = get(vertex_index, g);

    // initialize needed structures
    std::vector<int> number(n);
    std::vector<bool> inComponent(n);

    for (int i = 0; i < n; i++){
        inComponent[i] = false;
    }

    return nuutila_main(g,
                       make_iterator_property_map(number.begin(), index), // v*w
                       root,  // v*w
                       make_iterator_property_map(inComponent.begin(), index)); // v
}
