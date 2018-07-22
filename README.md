# advance_algorithms_project
Strongly connected component algorithms implementations using BGL (boost graph library)

## Files:
-   my_tarjan.cpp : Tarjan's algorithm implementation with timer
-   my_nuutila.cpp : Nuutila's algorithm implementation with timer
-   my_pearce.cpp : Pearce's algorithm recursive implementation with timer
-   my_pearce_not_recursive.cpp : Pearce's algorithm non recursive implementation with timer
-   my_transitive_closure.cpp : Pearce's paper application example with transitive closure computation
-   main.cpp : simple test running the three versions against the bgl implementation on a randomly generated graph, build with ```g++ -O2 -lboost_graph -lboost_timer main.cpp -o main```, run with ```./main```
-   main_*.cpp : examples of application and timing with graphs passed from stdin in graphml format
    build with ```g++ -O2 -lboost_graph -lboost_timer  main_*.cpp -o main_*```, run with
    ```./main_* < graphml_file```
-   test_from_stdin.cpp : runs the three versions of the algorithm against the bgl implementation timing them and checking for correctness, reads graph from stdin in graphml format, used to measure timing samples, build with ```g++ -O2 -lboost_graph -lboost_timer test_from_stdin.cpp -o test_from_stdin```, run with ```./test_from_stdin < graphml_file```
-   main_*.cpp : examples of application and timing with graphs passed from stdin in graphml format
-   time_test.sh : runs test_from_stdin for each of the graphs in the specified directory and prints to stdout the results (time and correctness)
-   generate_graph.cpp : outputs to stdout a graph in graphml format with a specified number of vertices and probability of having an edge between two vertices, build with ```g++ -O2 -lboost_graph -lboost_timer generate_graph.cpp -o generate_graph```, run with ```./generate_graph number_of_vertices edge_probability```
-   generate_graph.sh : script generate in a specified direcotory graphs to be used for timing measures, run with ```./generate_graph.sh root_dir min_nodes step max_nodes step_edges max_edges```
-   time_analysis.ipynb : notebook taking the output from time_test.sh, generate a csv and plot the measurements
-   test_tc.sh : test transitive closure over all the graphs in a directory and store to file results
-   g0_1000/* : randomly generated graphs with 0 to 1000 vertices (V) with step 10 and 0 to 1000 edges, increasing probability s.t. number of edges is between 0 and V*(V-1) with step 10
