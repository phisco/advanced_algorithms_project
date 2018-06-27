//
// Created by phisco on 6/23/18.
//

#include <boost/timer/timer.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;

typedef adjacency_list < listS, vecS, directedS> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;

template <class Graph, class Rindex, class Stack>
void pearce(const Graph g, const Vertex v, int* index, int*c, Rindex rindex, Stack s) {
    bool root = true;
    put(rindex, v, *index);
    *index += 1;
    //std::cout << get(rindex, v) << " enters" << std::endl;
    //std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        if (get(rindex, *w) == 0){
            //std::cout << "cond 1, check : " << get(rindex, v) << ", " << *index << std::endl;
            pearce(g, *w, index, c, rindex, s);
        }
        if (get(rindex, *w) < get(rindex, v)) {
            //std::cout << "cond 2, check : " << get(rindex, v) << ", " << get(rindex, *w) << std::endl;
            put(rindex, v, get(rindex, *w));
            root = false;
        }
    }
    if(root){
        //std::cout << "cond 3, check : " << get(rindex, v) << std::endl;
        *index -= 1;
        while(!s->empty() && get(rindex, s->top()) >= get(rindex, v)){
            Vertex w = s->top();
            //std::cout << get(rindex, v) << " <- " << get(rindex, w) << std::endl;
            //std::cout << "stack pop : " << get(rindex, w) << std::endl;
            s->pop();
            put(rindex, w, *c);
            *index -= 1;
        }
        put(rindex, v, *c);
        *c -= 1;
    } else {
        //std::cout << "stack push : " << get(rindex, v) << std::endl;
        s->push(v);
    }
    // std::cout << "exit : " << get(num, v) << std::endl;
}
template <class Graph, class Rindex>
int pearce_main(const Graph& g, Rindex rindex) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> s;
    int index = 1;
    int c = num_vertices(g) - 1;
    timer::auto_cpu_timer t;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(rindex, v) == 0){
            pearce(g, v, &index, &c, rindex, &s);
        }
    }
    return num_vertices(g) - 1 - c;
}

template <class Graph, class Rindex>
int pearce_scc(const Graph& g, Rindex rindex)
{
    for (int i = 0; i < num_vertices(g); i++){
        rindex[i] = 0;
    }

    return pearce_main(g, rindex);
}