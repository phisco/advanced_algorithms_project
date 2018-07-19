//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;

Graph g;
int n;
std::vector<int> lowvineVet(n),
        number(n),
        lowptVet(n);
std::vector<bool> stackmember(n), ancestorVet(n);
std::stack<Vertex> s; // v*w

auto num=make_iterator_property_map(number.begin(), get(vertex_index,g));
auto lowpt= make_iterator_property_map(lowptVet.begin(), get(vertex_index,g));
auto lowvine= make_iterator_property_map(lowvineVet.begin(), get(vertex_index,g));
auto sm= make_iterator_property_map(stackmember.begin(), get(vertex_index,g));
auto ancestor=make_iterator_property_map(ancestorVet.begin(), get(vertex_index,g));
int i=0;
int c=0;

template <class Component>
//void tarjan(const Graph& g, const Vertex& v, int* i, int* c, Num& num, Lowpt& lowpt, Lowvine& lowvine, Component& component, Stack s, StackMember& sm, Ancestor& ancestor) {
        void tarjan(const Vertex& v, Component component){
    i += 1;
    /*std::cout << "num " << sizeof(num) << std::endl;
    std::cout << "lowpt " << sizeof(lowpt) << std::endl;
    std::cout << "lowvine " << sizeof(lowvine) << std::endl;
    std::cout << "stackmember " << sizeof(sm) << std::endl;
    std::cout << "ancestor " << sizeof(ancestor) << std::endl;
    std::cout << "Stack s "<< sizeof(s) << std::endl;
    std::cout << "Graph " << sizeof(g) << std::endl;
    std::cout << "Vertex " << sizeof(v) << std::endl;*/
    put(lowvine, v, i);
    put(lowpt, v, i);
    put(num, v, i);
    s.push(v);
    put(ancestor, i, true);
    put(sm, i, true);
    //std::cout << get(num, v) << " enters" << std::endl;
    std::pair<vertex_iter, vertex_iter> vp;
    typename graph_traits<Graph>::adjacency_iterator w, ai_end;
    for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w){
        //std::cout << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
        auto nw = get(num, *w);
        auto lptv = get(lowpt, v);
        auto lvinev = get(lowvine, v);
        if (nw == 0){
            //std::cout << "cond 1 : " << get(num, v) << " " <<  *i+1 << std::endl;
            //tarjan(g, *w, i, c, num, lowpt, lowvine, component, s, sm, ancestor);
            tarjan(*w, component);
            auto lptw = get(lowpt, *w);
            put(lowpt, v,  lptw > lptv ? lptv : lptw);
            auto lvinew = get(lowvine, *w);
            put(lowvine, v,  lvinew > lvinev ? lvinev : lvinew);
        } else if (get(ancestor, nw)) /* w is an ancestor of v */{
            //std::cout << "cond 2 : " << get(num, v) << " " << get(num, *w) << std::endl;
            put(lowpt, v, nw > lptv ? lptv : nw);
        } else if (nw < get(num, v) && (get(sm, nw))){
                //std::cout << "cond 3 : " << get(num, v) << " " << get(num, *w) << std::endl;
                put(lowvine, v, nw > lvinev ? lvinev : nw);
        }
    }
    //std::cout << "final : " << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
    if ((get(lowpt, v) == get(num, v)) && (get(lowvine, v) == get(num, v))){
        c += 1;
        //std::cout << *c << " : ";
        int vn = get(num, v);
        while(!s.empty() && get(num, s.top()) >= vn){
            Vertex w = s.top();
            s.pop();
            put(sm, get(num, w), false);
            put(component, w, c);
            //std::cout << get(num, w) << " ";
        }
        //std::cout << std::endl;
    }
    //std::cout << get(num, v) << " exits" << std::endl;
    put(ancestor, get(num, v), false);
}

template <class Component>
//int tarjan_main(const Graph& g, Num num, Lowpt lowpt, Lowvine lowvine, Component& component, StackMember sm, Ancestor ancestor) {
        int tarjan_main(Component component){
    std::cout << "num " << n;
    std::pair<vertex_iter, vertex_iter> vp;
    timer::auto_cpu_timer t;
    for (vp = vertices(g); vp.first != vp.second; ++vp.first){
        Vertex v = *vp.first;
        if (get(num, v) == 0){
            //tarjan(g, v, &i, &c, num, lowpt, lowvine, component, &s, sm, ancestor);
            tarjan(v, component);
        }
    }
    return c;
}

template <class Component>
int tarjan_scc(Graph& graph, Component component)
{
    g=graph;
    n=num_vertices(g);
    //IndexMap index =  get(vertex_index, g);

    for (int i = 0; i < n; i++){
        stackmember[i] = false;
        ancestor[i] = false;
    }
    std::cout << "component " << sizeof(component) << std::endl;

    /*return tarjan_main(g,
                       num, // v*w
                      lowpt,  // v*w
                       make_iterator_property_map(lowvine.begin(), index), // v*w
                       component, // v*w
                       make_iterator_property_map(ancestor.begin(), index), // v
                       make_iterator_property_map(stackmember.begin(), index)); //v*/
    return tarjan_main(component);
}
