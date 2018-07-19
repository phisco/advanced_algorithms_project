//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;

template <class Graph, class Num, class Lowpt, class Lowvine, class Component, class Stack, class StackMember, class Ancestor>
void tarjan(const Graph& g, const Vertex& v, int* i, int* c, Num& num, Lowpt& lowpt, Lowvine& lowvine, Component& component, Stack s, StackMember& sm, Ancestor& ancestor) {
    *i += 1;
    put(lowvine, v, *i);
    put(lowpt, v, *i);
    put(num, v, *i);
    s->push(v);
    put(ancestor, *i, true);
    put(sm, *i, true);
    std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    //std::cout << get(num, v) << " enters" << std::endl;

    // iterate over the outgoing edges from vertex v
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        //std::cout << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
        auto nw = get(num, *w);
        auto lptv = get(lowpt, v);
        auto lvinev = get(lowvine, v);

        // if w has not already been visited then call recursively tarjan over it
        if (nw == 0){
            //std::cout << "cond 1 : " << get(num, v) << " " <<  *i+1 << std::endl;
            tarjan(g, *w, i, c, num, lowpt, lowvine, component, s, sm, ancestor);
            auto lptw = get(lowpt, *w);
            put(lowpt, v,  lptw > lptv ? lptv : lptw);
            auto lvinew = get(lowvine, *w);
            put(lowvine, v,  lvinew > lvinev ? lvinev : lvinew);
        } else if (get(ancestor, nw)) /* w is an ancestor of v */{
            //std::cout << "cond 2 : " << get(num, v) << " " << get(num, *w) << std::endl;
            put(lowpt, v, nw > lptv ? lptv : nw);
        } else if (nw < get(num, v) && (get(sm, nw))){ // check if w is still in the stack
            //std::cout << "cond 3 : " << get(num, v) << " " << get(num, *w) << std::endl;
            put(lowvine, v, nw > lvinev ? lvinev : nw);
        }
    }
    //std::cout << "final : " << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
    auto nv = get(num, v);
    if ((get(lowpt, v) == nv) && (get(lowvine, v) == nv)){
        *c += 1;
        //std::cout << *c << " : ";
        while (!s->empty() && get(num, s->top()) >= nv){
            Vertex w = s->top();
            s->pop();
            put(sm, get(num, w), false);
            put(component, w, *c);
            //std::cout << get(num, w) << " ";
        }
        //std::cout << std::endl;
    }
    //std::cout << get(num, v) << " exits" << std::endl;
    put(ancestor, nv, false);
}

template <class Graph, class Num, class Lowpt, class Lowvine, class Component, class StackMember, class Ancestor>
int tarjan_main(const Graph& g, Num num, Lowpt lowpt, Lowvine lowvine, Component& component, StackMember sm, Ancestor ancestor) {

    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s; // v*w
    int i = 0;
    int c = 0;

    // start the timer
    timer::auto_cpu_timer t;

    // iterate over the vertices
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(num, v) == 0){
            tarjan(g, v, &i, &c, num, lowpt, lowvine, component, &s, sm, ancestor);
        }
    }
    // return the number of components found
    return c;
}

template <class Graph, class Component>
int tarjan_scc(const Graph& g, Component component)
{
    // initialize needed structures
    int n = num_vertices(g);
    std::vector<int> lowvine(n),
            number(n),
            lowpt(n);

    std::vector<bool> stackmember(n), ancestor(n); // structures needed, but not specified in the paper

    IndexMap index = get(vertex_index, g);

    for (int i = 0; i < n; i++){
        stackmember[i] = false;
        ancestor[i] = false;
    }

    return tarjan_main(g,
                       make_iterator_property_map(number.begin(), index), // v*w
                       make_iterator_property_map(lowpt.begin(), index),  // v*w
                       make_iterator_property_map(lowvine.begin(), index), // v*w
                       component, // v*w
                       make_iterator_property_map(ancestor.begin(), index), // v
                       make_iterator_property_map(stackmember.begin(), index)); //v
}
