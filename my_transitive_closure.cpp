//
// Created by root on 02/07/18.
//

#include "include_and_types.cpp"
#include <set>
#include <boost/graph/detail/set_adaptor.hpp>

typedef graph_traits<Graph>::adjacency_iterator adj_iter;

template <class Root, class InComponent, class Num, class Set>
class TransitiveClosure{
private:
    //Graph
    Graph*g;

    //Property Map instances
    Root root;
    InComponent inComp;
    Num num;
    Set succ;

    int index;

    //Data Structure feeding Property Map instances
    std::vector<Vertex> rootVet;
    std::vector<bool> inCompVet;
    std::vector<std::set<Vertex>*> sets;
    std::vector<int> numVet;
    std::vector<std::set<Vertex>> vect;
    std::stack<Vertex> s;

    /**
     * This function is the body of the algorithm. It takes the vertex that the procedure is visiting in that time
     * and calculates its successors.
     * This is the C++ implementation of the pseudocode available on the Nuutila's paper
     * @param v, vertex visited
     */
    void tc(Vertex v){
        ++index;
        put(root, v, v);
        put(inComp, v, false);
        put(num, v, index);
        put(succ,v,&vect[v]);
        std::set<Vertex> roots;
        adj_iter ai, a_end;
        for(boost::tie(ai, a_end)= adjacent_vertices(v,*g); ai!=a_end;++ai){
            Vertex w=*ai;
            if(get(num,w)==0)//Checking if w is already visited
                tc(w);
            if(!get(inComp,get(root,w)))//Checking if w's root is already in a SCC
                put(root, v, get(num, get(root,w))<get(num,get(root,v)) ? get(root,w) : get(root,v));
            else
                //complexity logaritmic in size
                roots.insert(get(root,w));
        }
        std::set<Vertex>::iterator it;
        //complexity of set_union: 2*(size_set1+size_set2)-1
        //This loop inserts all the vertex in roots and their successors in v's root successors
        for(it=roots.begin();it!=roots.end();++it){
            Vertex r=*it;
            std::set<Vertex>* succRoot=get(succ, get(root,v));
            set_union(get(succ,r)->begin(),get(succ,r)->end(),succRoot->begin(), succRoot->end(),
                      std::inserter(*succRoot,succRoot->begin()));
            succRoot->insert(r);
        }

        if(get(root,v)==v){
            if(get(num,s.top())>=get(num,v)){
                get(succ,v)->insert(v);
                do{
                    Vertex w=s.top();
                    s.pop();
                    put(inComp,w,true);
                    if(v!=w){
                        //Pointer assignment, not a copy
                        std::set_union(get(succ,w)->begin(),get(succ,w)->end(),get(succ,v)->begin(),
                                       get(succ,v)->end(),std::inserter(*get(succ,v),get(succ,v)->begin()));
                        put(succ,w, get(succ,v));
                    }
                }while(get(num,s.top())>=get(num,v));
            }else{
                //if a vertex is root of a trivial SCC
                put(inComp,v,true);
            }
        }else{
            //If a vertex is not a root, it pushes his root into the stack, if it is not
            if(get(num,s.top())!=get(num, get(root,v)))
                s.push(get(root,v));
            get(succ,get(root,v))->insert(v);

        }
    }

    /**
     * This function launches the procedure and it performs the visit of all the graph's vertex
     */
    void transitive_closure_main(){
        vertex_iter vi,v_end;
        timer::auto_cpu_timer t;
        for(boost::tie(vi,v_end)=vertices(*g);vi!=v_end;++vi){
            Vertex v=*vi;
            if(get(num,v)==0){
                tc(v);
            }
        }
    };

public:
    /**
     * This is the constructor of the TransitiveClosure class. It takes the reference of the already allocated graph
     * done by the caller (main_transitive_closure.cpp).
     * The constructor initializes all the class attributes in proper way
     * @param graph pointer
     */
    TransitiveClosure(Graph*graph){
        g=graph;

        //Insertion and handling of a new vertex with lowest num possible in order to accomplish algorithm correctness
        Vertex starter=add_vertex(*g);
        int n=num_vertices(*g);
        numVet=*new std::vector<int>(n);
        num=make_iterator_property_map(numVet.begin(),get(vertex_index,*g));
        put(num, starter, -1);
        s.push(starter);
        remove_vertex(starter,*g);

        //Updating number of graph's vertices
        n--;

        //data structures allocation
        rootVet=*new std::vector<Vertex>(n);
        inCompVet=*new std::vector<bool>(n);
        sets=*new std::vector<std::set<Vertex>*>(n);
        vect=*new std::vector<std::set<Vertex>>(n);

        //Properties instantiation
        root=make_iterator_property_map(rootVet.begin(), get(vertex_index,*g));
        inComp= make_iterator_property_map(inCompVet.begin(), get(vertex_index,*g));
        succ=make_iterator_property_map(sets.begin(),get(vertex_index,*g));

        //index needed
        index=0;
    }

    /**
     * This function is called by the main_transitive_closure callee. It launches the procedure and prints the
     * procedure's result when it is done.
     */
    void transitive_closure_scc(){
        transitive_closure_main();

        std::cout << "Ours" << std::endl;
        IndexMap index = get(vertex_index,*g);
        vertex_iter it, it_end;
        for(boost::tie(it,it_end)=vertices(*g);it!=it_end;++it){
            Vertex v=*it;
            std::set<Vertex>* set=get(succ,get(root,v));
            std::cout << index[*it] << " --> ";
            std::set<Vertex>::iterator i;
            for(i=set->begin();i!=set->end();++i){
                std::cout << *i << " ";
            }
            std::cout << std::endl;
        }

    }
};
