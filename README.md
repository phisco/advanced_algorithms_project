# advance_algorithms_project
Strongly connected component algorithms implementations using BGL (boost graph library)

## Files:
-   my_tarjan.cpp : Tarjan's algorithm implementation with timer
-   my_nuutila.cpp : Nuutila's algorithm implementation with timer
-   my_pearce.cpp : Pearce's algorithm recursive implementation with timer
-   my_pearce_not_recursive.cpp : Pearce's algorithm non recursive implementation with timer
-   my_transitive_closure.cpp : Pearce's paper application example with transitive closure computation
-   main.cpp : simple test running the three versions against the bgl implementation on a randomly generated graph
-   main_*.cpp : examples of application and timing with graphs passed from stdin in graphml format
-   test_from_stdin.cpp : runs the three versions of the algorithm against the bgl implementation timing them and checking for correctness, reads graph from stdin in graphml format, used to measure timing samples
-   time_test.sh : runs test_from_stdin for each of the graphs in the specified directory and prints to stdout the results (time and correctness)
-   generate_graph.cpp : outputs to stdout a graph in graphml format with a specified number of vertices and probability of having an edge between two vertices
-   generate_graph.sh : script generate in a specified direcotory graphs to be used for timing measures
-   time_analysis.ipynb : notebook taking the output from time_test.sh, generate a csv and plot the measurements
-   test_tc.sh : test transitive closure over all the graphs in a directory and store to file results
-   g0_1000/* : randomly generated graphs with 0 to 1000 vertices (V) with step 10 and 0 to 1000 edges, increasing probability s.t. number of edges is between 0 and V*(V-1) with step 10
