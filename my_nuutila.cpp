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
    // std::cout << v << " as " << get(num, v) << " enters" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        if (get(num, *w) == 0){
            // std::cout << "cond 1, check : " << v << ", " << *i+1 << std::endl;
            nuutila(g, *w, i, c, num, root, inComponent, s);
        }
        if (!get(inComponent, *w)) {
            // std::cout << "cond 2, check : " << v << ", " << *w << std::endl;
            // std::cout << "root of " << v << " <- " << get(root, v) << " (" << get(num, v) << ")"<< std::endl;
            // std::cout << "root of " << *w << " <- " << get(root, *w) << " (" << get(num, *w) << ")"<< std::endl;
            auto rw = get(root, *w);
            auto rv = get(root, v);
            put(root, v, get(num, rv) > get(num, rw) ? rw : rv);
            // std::cout << "post root of " << v << " <- " << get(root, v) << std::endl;
        }
    }
    if(get(root, v) == v){
        // std::cout << "cond 3, check : " << get(num, v) << std::endl;
        *c += 1;
        put(inComponent, v, true);
        while(!s->empty() && get(num, s->top()) > get(num, v)){
            Vertex w = s->top();
            // std::cout << get(num, v) << " <- " << w << std::endl;
            // std::cout << "stack pop : " << w << std::endl;
            s->pop();
            put(inComponent, w, true);
        }
    } else {
        // std::cout << "stack push : " << get(num, v) << std::endl;
        s->push(v);
    }
    // std::cout << "exit : " << v << std::endl;
}
template <class Graph, class Num, class InComponent, class Root>
int nuutila_main(const Graph& g, Num num, Root& root, InComponent inComponent) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s; // v*w
    int i = 0;
    int c = 0;
    timer::auto_cpu_timer t;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(num, v) == 0){
            nuutila(g, v, &i, &c, num, root, inComponent, &s);
        }
    }
    return c;
}

template <class Graph, class Root>
int nuutila_scc(const Graph& g, Root root)
{
    int n = num_vertices(g);
    std::vector<int> number(n);
    std::vector<bool> inComponent(n);
    IndexMap index = get(vertex_index, g);

    for (int i = 0; i < n; i++){
        inComponent[i] = false;
    }

    return nuutila_main(g,
                       make_iterator_property_map(number.begin(), index), // v*w
                       root,  // v*w
                       make_iterator_property_map(inComponent.begin(), index)); // v
}
