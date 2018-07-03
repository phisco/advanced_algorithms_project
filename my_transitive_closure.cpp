//
// Created by root on 02/07/18.
//

#include "include_and_types.cpp"
#include <set>
#include <boost/graph/detail/set_adaptor.hpp>



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
            put(root, v, get(root,w)<get(root,v) ? get(root,w) : get(root,v));
        else
            //complexity logaritmic in size
            roots.insert(get(root,w));
    }
    std::set<Vertex>::iterator it;
    //complexity of set_union: 2*(size_set1+size_set2)-1

    for(it=roots.begin();it!=roots.end();++it){
        Vertex r=*it;
        std::set<Vertex>* succRoot=get(succ, get(root,v));
        get(succ,r)->insert(r);
        set_union(get(succ,r)->begin(),get(succ,r)->end(),succRoot->begin(), succRoot->end(),
                  std::inserter(*succRoot,succRoot->begin()));

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
        if(get(num,s->top())!=get(num, get(root,v)) || s->empty()){
            s->push(get(root,v));
            get(succ,get(root,v))->insert(v);
        }
    }
}

template <class Graph, class Root, class InComponent, class Set, class Num>
int transitive_closure_main(Graph g, Root root, InComponent inComp, Set succ, Num num,  std::vector<std::set<Vertex>*> sets){
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

template <class Graph, class Root, class InComponent, class Set, class Num>
void transitive_closure_scc(Graph& g, Root root, InComponent inComp, Set succ, Num num, std::vector<std::set<Vertex>*> sets,
    const char* name){

    std::vector<std::set<Vertex>> vect(num_vertices(g));

    vertex_iter vi,v_end;
    for(boost::tie(vi,v_end)=vertices(g);vi!=v_end;++vi){
        Vertex v=*vi;
        std::set<Vertex>* punt=&vect[*vi];
        put(succ,v,&vect[*vi]);
    }

    int number = transitive_closure_main(g, root, inComp, succ, num, sets);

    std::cout << "Number of components: "<< number << std::endl;
    vertex_iter it, it_end;
    for(boost::tie(it,it_end)=vertices(g);it!=it_end;++it){
        Vertex v=*it;
        std::set<Vertex>* set=get(succ,v);
        std::cout << name[*it] << "-> ";
        std::set<Vertex>::iterator i;
        for(i=set->begin();i!=set->end();++i){
            std::cout << *i << " ";
        }
        std::cout << std::endl;
    }

}

int main(int, char*[]){
    enum { A, B, C, D, E, F, G, H, I, N };
    const int num_nodes = N;
    const char* name = "ABCDEFGHI";

    // writing out the edges in the graph
    typedef std::pair<int, int> Edge;
    Edge edge_array[] =
            { Edge(A,B), Edge(B,A), Edge(A,C), Edge(C,A), Edge(B,D), Edge(C,D),
              Edge(E,C), Edge(E,F), Edge(F,D), Edge(D,F), Edge(E,H), Edge(H,F), Edge(H,G), Edge(G,E),
              Edge(I,G), Edge(I,H), Edge(I,I)};
    const int num_edges = sizeof(edge_array)/sizeof(edge_array[0]);


    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    Graph g(edge_array, edge_array + num_arcs, num_nodes);

    std::cout << "A directed graph:" << std::endl;
    print_graph(g, name);
    std::cout << std::endl;


    std::vector<Vertex> root(num_vertices(g));
    std::vector<bool> inComp(num_vertices(g));
    std::vector<std::set<Vertex>*> sets(num_vertices(g));
    std::vector<int> num(num_vertices(g));



    transitive_closure_scc(g,  make_iterator_property_map(root.begin(), get(vertex_index,g)),
                                     make_iterator_property_map(inComp.begin(), get(vertex_index,g)),
                                        make_iterator_property_map(sets.begin(), get(vertex_index,g)),
                                     make_iterator_property_map(num.begin(), get(vertex_index,g)),sets, name);


    /*
    for (int i = 0; i != root.size(); ++i){
        std::cout << name[i] << " -> " ;
        (std::set<Vertex>*)::iterator it;
        for(it=succ[i]->begin();it!=succ[i]->end();++it){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }*/

    return 0;

}