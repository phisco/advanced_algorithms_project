//
// Created by root on 02/07/18.
//

#include "include_and_types.cpp"
#include <set>
#include <boost/graph/detail/set_adaptor.hpp>

typedef graph_traits<Graph>::adjacency_iterator adj_iter;

template <class Root, class InComponent, class Num>
class TransitiveClosure{

private:
    Graph*g;
    Root root;
    InComponent inComp;
    Num num;
    Set succ;

    int index;

    std::vector<Vertex> rootVet;
    std::vector<bool> inCompVet;
    std::vector<std::set<Vertex>*> sets;
    std::vector<int> numVet;
    std::vector<std::set<Vertex>> vect;
    std::stack<Vertex> s;

    void tc(Vertex v){
        ++index;
        put(root, v, v);
        put(inComp, v, false);
        put(num, v, index);
        std::set<Vertex> roots;
        adj_iter ai, a_end;
        for(boost::tie(ai, a_end)= adjacent_vertices(v,*g); ai!=a_end;++ai){
            Vertex w=*ai;
            if(get(num,w)==0)
                tc(w);
            if(!get(inComp,get(root,w)))
                put(root, v, get(num, get(root,w))<get(num,get(root,v)) ? get(root,w) : get(root,v));
            else
                //complexity logaritmic in size
                roots.insert(get(root,w));
        }
        std::set<Vertex>::iterator it;
        //complexity of set_union: 2*(size_set1+size_set2)-1
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
                        std::set_union(get(succ,w)->begin(),get(succ,w)->end(),get(succ,v)->begin(),
                                       get(succ,v)->end(),std::inserter(*get(succ,v),get(succ,v)->begin()));
                        put(succ,w, get(succ,v));
                    }
                }while(get(num,s.top())>=get(num,v));
            }else{
                put(inComp,v,true);
            }
        }else{
            if(get(num,s.top())!=get(num, get(root,v)) || s.empty())
                s.push(get(root,v));
            get(succ,get(root,v))->insert(v);

        }
    }

    void transitive_closure_main(){
        vertex_iter vi,v_end;
        timer::auto_cpu_timer t;
        for(boost::tie(vi,v_end)=vertices(g);vi!=v_end;++vi){
            Vertex v=*vi;
            if(get(num,v)==0){
                tc(v);
            }
        }
    };

public:
    TransitiveClosure(Graph*graph){
        g=graph;
        int n=num_vertices(*g);

        //data structures allocation
        rootVet=*new std::vector<Vertex>(n);
        inCompVet=*new std::vector<bool>(n);
        sets=*new std::vector<std::set<Vertex>*>(n);
        numVet=*new std::vector<int>(n);
        vect=*new std::vector<std::set<Vertex>>(n);

        //set<Vertex> allocation
        vertex_iter vi,v_end;
        for(boost::tie(vi,v_end)=vertices(*g);vi!=v_end;++vi){
            Vertex v=*vi;
            std::set<Vertex>* punt=&vect[*vi];
            put(succ,v,&vect[*vi]);
        }

        //Properties instantiation
        root=make_iterator_property_map(root.begin(), get(vertex_index,*g));
        inComp= make_iterator_property_map(inComp.begin(), get(vertex_index,*g));
        num=make_iterator_property_map(numVet.begin(),get(vertex_index,*g));
        succ=make_iterator_property_map(sets.begin(),get(vertex_index,*g));

        //Insertion of a vertex with lowest num possible in order to accomplish algorithm correctness
        Vertex starter=add_vertex(g);
        put(num, starter, -1);
        s.push(starter);
        remove_vertex(starter,g);

        //index needed
        index=0;
    }

    void transitive_closure_scc(){
        transitive_closure_main();

        std::cout << "Ours" << std::endl;
        IndexMap index = get(vertex_index,g);
        vertex_iter it, it_end;
        for(boost::tie(it,it_end)=vertices(g);it!=it_end;++it){
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
