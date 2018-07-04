//
// Created by root on 02/07/18.
//

#include "include_and_types.cpp"
#include <set>
#include <boost/graph/detail/set_adaptor.hpp>

typedef graph_traits<Graph>::adjacency_iterator adj_iter;

template <class Graph, class Root, class InComponent, class Set, class Stack, class Num>
void tc(const Graph g, const Vertex v, Root root, InComponent inComp, Set succ, Stack s, Num num, int*index){
    ++*index;
    put(root, v, v);
    put(inComp, v, false);
    put(num, v, *index);
    std::set<Vertex> roots;
    adj_iter ai, a_end;
    for(boost::tie(ai, a_end)= adjacent_vertices(v,g); ai!=a_end;++ai){
        Vertex w=*ai;
        if(get(num,w)==0)
            tc(g,w,root,inComp, succ, s, num, index);
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
        if(get(num,s->top())>=get(num,v)){
            get(succ,v)->insert(v);
            do{
                Vertex w=s->top();
                s->pop();
                put(inComp,w,true);
                if(v!=w){

                    std::set_union(get(succ,w)->begin(),get(succ,w)->end(),get(succ,v)->begin(),
                                   get(succ,v)->end(),std::inserter(*get(succ,v),get(succ,v)->begin()));
                    put(succ,w, get(succ,v));
                }
            }while(get(num,s->top())>=get(num,v));
        }else{
            put(inComp,v,true);
        }
    }else{
        if(get(num,s->top())!=get(num, get(root,v)) || s->empty())
            s->push(get(root,v));
        get(succ,get(root,v))->insert(v);

    }
}

template <class Graph, class Root, class InComponent, class Set, class Num>
void transitive_closure_main(Graph g, Root root, InComponent inComp, Set succ, Num num,  std::vector<std::set<Vertex>*> sets){
    std::stack<Vertex> s;
    Vertex starter=add_vertex(g);
    put(num, starter, -1);
    s.push(starter);
    remove_vertex(starter,g);
    vertex_iter vi,v_end;

    int i=0;
    for(boost::tie(vi,v_end)=vertices(g);vi!=v_end;++vi){
        Vertex v=*vi;
        if(get(num,v)==0){
            tc(g, v, root, inComp, succ, &s, num, &i);

        }
    }
};

template <class Graph, class Root, class InComponent, class Set>
void transitive_closure_scc(Graph& g, Root root, InComponent inComp, Set succ, std::vector<std::set<Vertex>*> sets){

    std::vector<std::set<Vertex>> vect(num_vertices(g));
    int num[num_vertices(g)];

    vertex_iter vi,v_end;
    for(boost::tie(vi,v_end)=vertices(g);vi!=v_end;++vi){
        Vertex v=*vi;
        std::set<Vertex>* punt=&vect[*vi];
        put(succ,v,&vect[*vi]);
        num[v]=0;
    }

    transitive_closure_main(g, root, inComp, succ, make_iterator_property_map(&num[0],get(vertex_index,g)), sets);


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