//
// Created by phisco on 6/23/18.
//


#include "include_and_types.cpp"


using namespace boost;

typedef typename graph_traits<Graph>::out_edge_iterator out_edge_it;

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
    auto rw = get(rindex,w);
    if(rw<get(rindex,v)){
        put(rindex,v,rw);
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
bool beginEdge(const Graph& g, const Vertex v, int k, out_edge_it it, Stack vs, StackInt is, int* index, Rindex rindex, Root root){
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
void visitLoop(const Graph& g, Stack vs, StackInt is, int*index, Stack s, int*c, Rindex rindex, Root root){
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
void visit(const Graph& g, const Vertex v, Stack vs, StackInt is, Rindex rindex, int* index, Stack s, int*c, Root root){
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