project(graph)

add_executable(task_graph
               test/test.cc
               src/task_graph.cc
               src/task_vertex.cc
               src/task_edge.cc)