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

typedef adjacency_list < vecS, vecS, directedS> Graph;
typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<adjacency_list<vecS, vecS, directedS> >::vertex_descriptor Vertex;
typedef typename property_map<Graph, vertex_index_t>::type IndexMap;
typedef typename graph_traits<Graph>::out_edge_iterator out_edge_it;

/*template <class Graph, class Rindex, class Stack>
void pearce_visit_nr(const Graph g, const Vertex v, int* index, int*c, Rindex rindex, Stack vs, Stack is) {
    bool root = true;
    put(rindex, v, *index);
    *index += 1;
    //std::cout << get(rindex, v) << " enters" << std::endl;
    //std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        if (get(rindex, *w) == 0){
            //std::cout << "cond 1, check : " << get(rindex, v) << ", " << *index << std::endl;
            pearce_visit_nr(g, *w, index, c, rindex, s);
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
}*/

template <class Stack, class StackInt, class Root, class Rindex>
void finishVisiting(const Vertex v, Stack vs, StackInt is, int*index, Stack s, int*c, Root root, Rindex rindex){
    vs->pop();
    is->pop();

    if(get(root,v)){
        *index=*index-1;
        while(!s->empty()&&get(rindex,v)<=get(rindex,s->top())){
            Vertex w = s->top();
            s->pop();
            put(rindex, w, *c);
            *index=*index-1;
        }
        put(rindex,v,*c);
        *c=*c-1;
    }else{
        s->push(v);
    }
}

template <class Graph, class Rindex, class Root>
void finishEdge(Graph& g, Vertex v, int k, out_edge_it it, Rindex rindex, Root root){
    Vertex w=target(*(it+k),g);
    if(get(rindex,w)<get(rindex,v)){
        put(rindex,v,get(rindex,w));
        put(root,v,false);
    }
}

template<class Stack, class StackInt, class Rindex, class Root>
void beginVisiting(const Vertex v, Stack vs, StackInt is, int*index, Rindex rindex, Root root){
    vs->push(v);
    is->push(0);
    put(root, v, true);
    put(rindex, v, *index);
    *index=*index+1;
}

template <class Graph, class Stack, class StackInt, class Rindex, class Root>
bool beginEdge(Graph g, const Vertex v, int k, out_edge_it it, Stack vs, StackInt is, int* index, Rindex rindex, Root root){
    Vertex w = target(*(it+k),g);

    if(get(rindex,w)==0){
        is->pop();
        is->push(k+1);
        beginVisiting(w, vs, is, index, rindex, root);
        return true;
    }else{
        return false;
    }
}

template<class Graph, class Stack, class StackInt, class Rindex, class Root>
void visitLoop(Graph g, Stack vs, StackInt is, int*index, Stack s, int*c, Rindex rindex, Root root){
    Vertex v = vs->top();
    int i = is->top();
    typename graph_traits<Graph>::degree_size_type num_edges;
    num_edges=out_degree(v, g);
    out_edge_it it,it_end;
    boost::tie(it,it_end)=out_edges(v,g);

    while(i<= num_edges){
        if(i>0)
            finishEdge(g, v, i-1, it, rindex, root);
        if(i< num_edges && beginEdge(g, v, i, it, vs, is, index, rindex, root))
            return;
        i=i+1;
    }
    finishVisiting(v, vs, is, index, s, c, root, rindex);
}



template<class Graph, class Stack, class StackInt, class Rindex, class Root>
void visit(const Graph g, const Vertex v, Stack vs, StackInt is, Rindex rindex, int* index, Stack s, int*c, Root root){
    beginVisiting(v,vs,is, index, rindex, root);

    while(!vs->empty()){
        visitLoop(g, vs, is, index, s, c, rindex, root);
    }
}


template <class Graph, class Rindex, class Root>
int pearce_not_recursive_main(const Graph& g, Rindex rindex, Root root) {
    std::pair<vertex_iter, vertex_iter> vp;
    std::stack<Vertex> vs;
    std::stack<int> is;
    std::stack<Vertex> s;
    int index = 1;
    int c = num_vertices(g) - 1;
    timer::auto_cpu_timer t;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(rindex, v) == 0){
            visit(g, v, &vs, &is, rindex, &index, &s, &c, root);
        }
    }

    return num_vertices(g) - 1 - c;
}

template <class Graph, class Rindex>
int pearce_not_recursive_scc(const Graph& g, Rindex rindex)
{
    std::vector<bool> root(num_vertices(g));
    for (int i = 0; i < num_vertices(g); i++){
        rindex[i] = 0;
    }

    return pearce_not_recursive_main(g, rindex, make_iterator_property_map(root.begin(),get(vertex_index,g)));
}