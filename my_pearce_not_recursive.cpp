#include "include_and_types.cpp"


using namespace boost;

typedef typename graph_traits<Graph>::out_edge_iterator out_edge_it;

template <class Root, class Rindex>
class PearceNR{

private:
    Graph*g;

    Root root;
    Rindex rindex;

    int c;
    int index;

    std::vector<bool> rootVet;
    std::stack<Vertex> vs;
    std::stack<int> is;
    std::stack<Vertex> s;
    std::vector<int> rind;


    void finishVisiting(Vertex v){
        vs.pop();
        is.pop();

        if(get(root,v)){
            index=index-1;
            while(!s.empty()&&get(rindex,v)<=get(rindex,s.top())){
                Vertex w = s.top();
                s.pop();
                put(rindex, w, c);
                index=index-1;
            }
            put(rindex,v,c);
            c=c-1;
        }else{
            s.push(v);
        }
    }


    void finishEdge(Vertex v, int k, out_edge_it it){
        Vertex w=target(*(it+k),*g);
        auto rw = get(rindex,w);
        if(rw<get(rindex,v)){
            put(rindex,v,rw);
            put(root,v,false);
        }
    }


    void beginVisiting(Vertex v){
        vs.push(v);
        is.push(0);
        put(root, v, true);
        put(rindex, v, index);
        index=index+1;
    }


    bool beginEdge(Vertex v, int k, out_edge_it it){
        Vertex w = target(*(it+k),*g);

        if(get(rindex,w)==0){
            is.pop();
            is.push(k+1);
            beginVisiting(w);
            return true;
        }else{
            return false;
        }
    }

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

    void visit(Vertex v){
        beginVisiting(v);

        while(!vs.empty()){
            visitLoop();
        }
    }

public:
    PearceNR(Graph* graph){
        g=graph;
        int n=num_vertices(*g);

        rootVet=*new std::vector<bool>(n);
        rind=*new std::vector<int>(n);

        index = 1;
        c = n - 1;

        root=make_iterator_property_map(rootVet.begin(),get(vertex_index,*g));
        rindex=make_iterator_property_map(rind.begin(), get(vertex_index, *g));

    }

    std::vector<int>* pearce_not_recursive_scc() {
        std::pair<vertex_iter, vertex_iter> vp;
        timer::auto_cpu_timer t;
        for (vp = vertices(*g); vp.first != vp.second; ++vp.first){
            Vertex v = *vp.first;
            if (get(rindex, v) == 0){
                visit(v);
            }
        }

        return &rind;
    }

};