//
// Created by phisco on 6/23/18.
//

#include "include_and_types.cpp"

using namespace boost;

template <class Num, class Lowpt, class Lowvine, class StackMember, class Ancestor, class Component>
class TarjanClass {

private:
    Graph g;
    int n;
    std::vector<int> lowvineVet,
            number,
            lowptVet;

    std::vector<bool> stackmember, ancestorVet;

    std::stack<Vertex> s; // v*w
    Component component;
    Lowpt lowpt;
    Lowvine lowvine;
    Num num;
    StackMember sm;
    Ancestor ancestor;
    int i;
    int c;

    void tarjan(const Vertex &v) {
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
        for (boost::tie(w, ai_end) = adjacent_vertices(v, g); w != ai_end; ++w) {
            //std::cout << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
            auto nw = get(num, *w);
            auto lptv = get(lowpt, v);
            auto lvinev = get(lowvine, v);
            if (nw == 0) {
                //std::cout << "cond 1 : " << get(num, v) << " " <<  *i+1 << std::endl;
                //tarjan(g, *w, i, c, num, lowpt, lowvine, component, s, sm, ancestor);
                tarjan(*w);
                auto lptw = get(lowpt, *w);
                put(lowpt, v, lptw > lptv ? lptv : lptw);
                auto lvinew = get(lowvine, *w);
                put(lowvine, v, lvinew > lvinev ? lvinev : lvinew);
            } else if (get(ancestor, nw)) /* w is an ancestor of v */{
                //std::cout << "cond 2 : " << get(num, v) << " " << get(num, *w) << std::endl;
                put(lowpt, v, nw > lptv ? lptv : nw);
            } else if (nw < get(num, v) && (get(sm, nw))) {
                //std::cout << "cond 3 : " << get(num, v) << " " << get(num, *w) << std::endl;
                put(lowvine, v, nw > lvinev ? lvinev : nw);
            }
        }
        //std::cout << "final : " << get(num, v) << ", lowpt : " << get(lowpt, v) << ", lowvine : " << get(lowvine, v) << std::endl;
        if ((get(lowpt, v) == get(num, v)) && (get(lowvine, v) == get(num, v))) {
            c += 1;
            //std::cout << *c << " : ";
            int vn = get(num, v);
            while (!s.empty() && get(num, s.top()) >= vn) {
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

public: TarjanClass(Graph& graph, Component comp) {
        g=graph;
        component = comp;
        n=num_vertices(g);
        lowvineVet = *new std::vector<int>(n);
        number = *new std::vector<int>(n);
        lowptVet = *new std::vector<int>(n);
        stackmember = *new std::vector<bool>(n);
        ancestorVet = *new std::vector<bool>(n);
        num = make_iterator_property_map(number.begin(), get(vertex_index, g));
        lowpt = make_iterator_property_map(lowptVet.begin(), get(vertex_index, g));
        lowvine = make_iterator_property_map(lowvineVet.begin(), get(vertex_index, g));
        sm = make_iterator_property_map(stackmember.begin(), get(vertex_index, g));
        ancestor = make_iterator_property_map(ancestorVet.begin(), get(vertex_index, g));
        i = 0;
        c = 0;
    }

    int tarjan_scc() {
        for (int i = 0; i < n; i++) {
            stackmember[i] = false;
            ancestor[i] = false;
        }
        std::pair<vertex_iter, vertex_iter> vp;
        timer::auto_cpu_timer t;
        for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
            Vertex v = *vp.first;
            if (get(num, v) == 0) {
                //tarjan(g, v, &i, &c, num, lowpt, lowvine, component, &s, sm, ancestor);
                tarjan(v);
            }
        }
        return c;
    }

};