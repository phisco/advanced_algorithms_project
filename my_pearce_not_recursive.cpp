#include "include_and_types.cpp"


using namespace boost;

typedef typename graph_traits<Graph>::out_edge_iterator out_edge_it;

template <class Root, class Rindex>
class PearceNR{

private:
    //The graph reference
    Graph*g;

    //The Property map objects
    Root root;
    Rindex rindex;

    //DFS index
    int index;
    //SCC Counter
    int c;

    //The data structures which will compose the Property Map objects.
    std::vector<bool> rootVet;
    std::vector<int> rind;

    //Call-stacks
    std::stack<Vertex> vs;
    std::stack<int> is;

    //The SCC Stack
    std::stack<Vertex> s;

    /**
     * This function is responsible to terminate the visitation of a given vertex v, passed as parameter. It checks
     * if v is the root of its SCC, otherwise it puts itself on the stack, waiting for its SCC's root.
     * @param v, the vertex being visiting
     */
    void finishVisiting(Vertex v){
        //The vertex is popped from stacks
        vs.pop();
        is.pop();

        //Root checking
        if(get(root,v)){
            index=index-1;
            //It pops all the vertex of the SCC of which it is root
            while(!s.empty()&&get(rindex,v)<=get(rindex,s.top())){
                Vertex w = s.top();
                s.pop();
                put(rindex, w, c);
                index=index-1;
            }
            put(rindex,v,c);
            c=c-1;
        }else{
            //It is not root, so it pushes itself.
            s.push(v);
        }
    }

    /**
     * This function is responsible to terminate the visit of the k-th outgoing edge of a given vertex v. The iterator
     * is used to access the edge from the graph.
     * @param v, vertex
     * @param k, counter
     * @param it, iterator
     */
    void finishEdge(Vertex v, int k, out_edge_it it){
        //W is the target of the edge
        Vertex w=target(*(it+k),*g);

        //Rindex checking
        auto rw = get(rindex,w);
        if(rw<get(rindex,v)){
            put(rindex,v,rw);
            put(root,v,false);
        }
    }

    /**
     * This function is responsible to begin the visitation of a given vertex V, passed by parameter. It initializes
     * all the Property Map object associated to v and puts it on top of the vs stack.
     * @param v, vertex to be visited
     */
    void beginVisiting(Vertex v){
        vs.push(v);
        is.push(0);
        put(root, v, true);
        put(rindex, v, index);
        index=index+1;
    }

    /**
     * This function begins the visit of the k-th outgoing edge of Vertex v. Since the approach used in Pearce is a Depth-First one,
     * if the target vertex has not been visited yet, the function starts its visitation.
     * @param v, the source vertex of the edge
     * @param k, the iteration counter
     * @param it, the iterator
     * @return true, if the target vertex wasn't already visited. False, otherwise
     */
    bool beginEdge(Vertex v, int k, out_edge_it it){
        //The target vertex of the edge
        Vertex w = target(*(it+k),*g);

        //If it has not been already visited
        if(get(rindex,w)==0){
            is.pop();
            is.push(k+1);
            beginVisiting(w);
            return true;
        }else{
            return false;
        }
    }

    /**
     * This function is responsible for progressively traversing all the out-edges of the vertex situated on top of
     * vs stack.
     */
    void visitLoop(){
        Vertex v = vs.top();
        int i = is.top();
        typename graph_traits<Graph>::degree_size_type num_edges;
        num_edges=out_degree(v, *g);
        out_edge_it it,it_end;
        boost::tie(it,it_end)=out_edges(v,*g);

        while(i<= num_edges){
            if(i>0)
                finishEdge(v, i-1, it);
            if(i< num_edges && beginEdge(v, i, it))
                return;
            i=i+1;
        }
        finishVisiting(v);
    }

    /**
     * This is the starting function called by the pearce_not_recursive_scc(), that starts the visitation of vertex v
     * @param v, the vertex
     */
    void visit(Vertex v){
        beginVisiting(v);

        while(!vs.empty()){
            visitLoop();
        }
    }

public:
    /**
    * This is the constructor of the PearceNR class. It takes the reference of the graph already allocated by the
    * caller function in main_pearce_not_recursive.cpp. It initializes all the data structures and Property Map Objects
    * @param graph
    */
    PearceNR(Graph* graph){
        g=graph;
        int n=num_vertices(*g);

        //Data structure allocation
        rootVet.resize(n);
        rind.resize(n);

        //the needed counters
        index = 1;
        c = n - 1;

        //The Property Map objects instantiation
        root=make_iterator_property_map(rootVet.begin(),get(vertex_index,*g));
        rindex=make_iterator_property_map(rind.begin(), get(vertex_index, *g));

    }

    /**
     * This function is the one called by the main_pearce_not_recursive's main function.
     * It starts the procedure of pearce by visiting all the vertex of the graph.
     * @return the reference of the rindex vector, useful for stdout printing purposes
     */
    std::vector<int>* pearce_not_recursive_scc() {
        std::pair<vertex_iter, vertex_iter> vp;
        //Timer initialitation
        timer::auto_cpu_timer t;
        //Vertex loop
        for (vp = vertices(*g); vp.first != vp.second; ++vp.first){
            Vertex v = *vp.first;
            if (get(rindex, v) == 0){
                visit(v);
            }
        }

        return &rind;
    }

};