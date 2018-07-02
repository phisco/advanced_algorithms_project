//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;

template <class Graph, class Num, class Lowpt, class Lowvine, class Component, class Stack, class StackMember, class Ancestor>
void tarjan(const Graph g, const Vertex v, int* i, int* c, Num num, Lowpt lowpt, Lowvine lowvine, Component component, Stack s, StackMember sm, Ancestor ancestor) {
    *i += 1;
    put(lowvine, v, *i);
    put(lowpt, v, *i);
    put(num, v, *i);
    s->push(v);
    put(ancestor, *i, true);
    put(sm, *i, true);
    //std::cout << get(num, v) << " enters" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        //std::cout << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
        if (get(num, *w) == 0){
            //std::cout << "cond 1 : " << get(num, v) << " " <<  *i+1 << std::endl;
            tarjan(g, *w, i, c, num, lowpt, lowvine, component, s, sm, ancestor);
            put(lowpt, v, get(lowpt, *w) > get(lowpt, v) ? get(lowpt, v) : get(lowpt, *w));
            put(lowvine, v, get(lowvine, *w) > get(lowvine, v) ? get(lowvine, v) : get(lowvine, *w));
        } else if (get(ancestor, get(num, *w))) /* w is an ancestor of v */{
            //std::cout << "cond 2 : " << get(num, v) << " " << get(num, *w) << std::endl;
            put(lowpt, v, get(num, *w) > get(lowpt, v) ? get(lowpt, v) : get(num, *w));
        } else if (get(num, *w) < get(num, v) && (get(sm, get(num, *w)))){
                //std::cout << "cond 3 : " << get(num, v) << " " << get(num, *w) << std::endl;
                put(lowvine, v, get(num, *w) > get(lowvine, v) ? get(lowvine, v) : get(num, *w));
        }
    }
    //std::cout << "final : " << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
    if ((get(lowpt, v) == get(num, v)) && (get(lowvine, v) == get(num, v))){
        *c += 1;
        //std::cout << *c << " : ";
        int vn = get(num, v);
        while(!s->empty() && get(num, s->top()) >= vn){
            Vertex w = s->top();
            s->pop();
            put(sm, get(num, w), false);
            put(component, w, *c);
            //std::cout << get(num, w) << " ";
        }
        //std::cout << std::endl;
    }
    //std::cout << get(num, v) << " exits" << std::endl;
    put(ancestor, get(num, v), false);
}
template <class Graph, class Num, class Lowpt, class Lowvine, class Component, class StackMember, class Ancestor>
int tarjan_main(const Graph& g, Num num, Lowpt lowpt, Lowvine lowvine, Component component, StackMember sm, Ancestor ancestor) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s;
    int i = 0;
    int c = 0;
    timer::auto_cpu_timer t;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(num, v) == 0){
            tarjan(g, v, &i, &c, num, lowpt, lowvine, component, &s, sm, ancestor);
        }
    }
    return c;
}

template <class Graph, class Component>
int tarjan_scc(const Graph& g, Component component)
{
    int n = num_vertices(g);
    std::vector<int> lowvine(n),
            number(n),
            lowpt(n);
    std::vector<bool> stackmember(n), ancestor(n);
    IndexMap index = get(vertex_index, g);

    for (int i = 0; i < n; i++){
        stackmember[i] = false;
        ancestor[i] = false;
    }

    return tarjan_main(g,
                       make_iterator_property_map(number.begin(), index),
                       make_iterator_property_map(lowpt.begin(), index),
                       make_iterator_property_map(lowvine.begin(), index),
                       component,
                       make_iterator_property_map(ancestor.begin(), index),
                       make_iterator_property_map(stackmember.begin(), index));
}
