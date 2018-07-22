#include "include_and_types.cpp"

using namespace boost;

template <class Num, class Lowpt, class Lowvine, class StackMember, class Ancestor, class Component>
class TarjanClass {

private:
    //The graph pointer
    Graph* g;
    int n;
    //The data structures which will compose the Property Map Objects.
    std::vector<int> lowvineVet,
            number,
            lowptVet, comp;

    std::vector<bool> stackmember, ancestorVet;

    //The SCC stack
    std::stack<Vertex> s; // v*w

    //Property Map Objects. These are the attributes associated to a vertex
    Component component;
    Lowpt lowpt;
    Lowvine lowvine;
    Num num;
    StackMember sm;
    Ancestor ancestor;

    //DFS index
    int i;
    //SCC Counter
    int c;

    /**
     * This function is the core of the procedure. It visits the vertex passed as parameter and all the vertex reachable
     * by that following the graph edges. For each vertex, it finds all the vertices belonging to its same SCC, if it
     * is not formed yet.
     * This is the C++ implementation of the pseudo-code described by Tarjan in his paper.
     * @param v, is the vertex visited
     */
    void tarjan(const Vertex &v) {
        i += 1;
        //Property Map attributes attached to the vertex
        put(lowvine, v, i);
        put(lowpt, v, i);
        put(num, v, i);
        s.push(v);
        put(ancestor, i, true);
        put(sm, i, true);

        std::pair<vertex_iter, vertex_iter> vp;
        typename graph_traits<Graph>::adjacency_iterator w, ai_end;
        //This loop visits all the vertex reached by an edge starting from v
        for (boost::tie(w, ai_end) = adjacent_vertices(v, *g); w != ai_end; ++w) {
            //Property Map attributes of vertex W, the edge target
            auto nw = get(num, *w);
            auto lptv = get(lowpt, v);
            auto lvinev = get(lowvine, v);

            if (nw == 0) {//If w is not visited yet
                tarjan(*w);
                auto lptw = get(lowpt, *w);
                put(lowpt, v, lptw > lptv ? lptv : lptw);
                auto lvinew = get(lowvine, *w);
                put(lowvine, v, lvinew > lvinev ? lvinev : lvinew);
            } else if (get(ancestor, nw)) /* w is an ancestor of v */{
                put(lowpt, v, nw > lptv ? lptv : nw);
            } else if (nw < get(num, v) && (get(sm, nw))) {
                put(lowvine, v, nw > lvinev ? lvinev : nw);
            }
        }

        //When all the reachable vertex starting from v are visited
        if ((get(lowpt, v) == get(num, v)) && (get(lowvine, v) == get(num, v))) {
            c += 1;
            int vn = get(num, v);
            //All the vertex in the root's SCC are on the stack. This pops all of them.
            while (!s.empty() && get(num, s.top()) >= vn) {
                Vertex w = s.top();
                s.pop();
                put(sm, get(num, w), false);
                put(component, w, c);
            }
        }

        put(ancestor, get(num, v), false);
    }

public:
    /**
     * This is the constructor of the TarjanClass class. It takes the reference of the graph already allocated by the
     * caller function in main_tarjan.cpp. It initializes all the data structures and Property Map Objects
     * @param graph
     */
    TarjanClass(Graph* graph) {
        //Graph connection
        g=graph;
        int n=num_vertices(*g);

        //Data structure allocation
        comp.resize(n);
        lowvineVet.resize(n);
        number.resize(n);
        lowptVet.resize(n);
        stackmember.resize(n);
        ancestorVet.resize(n);

        //Boolean vector initialization
        for (int i = 0; i < n; i++) {
            stackmember[i] = false;
            ancestorVet[i] = false;
        }

        //Property Map Objects allocation
        num = make_iterator_property_map(number.begin(), get(vertex_index, *g));
        lowpt = make_iterator_property_map(lowptVet.begin(), get(vertex_index, *g));
        lowvine = make_iterator_property_map(lowvineVet.begin(), get(vertex_index, *g));
        sm = make_iterator_property_map(stackmember.begin(), get(vertex_index, *g));
        ancestor = make_iterator_property_map(ancestorVet.begin(), get(vertex_index, *g));
        component=make_iterator_property_map(comp.begin(), get(vertex_index, *g));

        //Indexes needed
        i = 0;
        c = 0;

    }

    /**
     * This function is the one called by the main_tarjan's main function. It starts the procedure of tarjan by visiting
     * all the vertex of the graph.
     * @return the reference of the component vector, useful for stdout printing purposes
     */
    std::vector<int>* tarjan_scc() {
        std::pair<vertex_iter, vertex_iter> vp;
        timer::auto_cpu_timer t;
        for (vp = vertices(*g); vp.first != vp.second; ++vp.first) {
            Vertex v = *vp.first;
            if (get(num, v) == 0) {
                tarjan(v);
            }
        }
        return &comp;
    }

};