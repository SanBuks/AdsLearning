#ifndef DS_CPP_06_GRAPH_INCLUDE_TASK_GRAPH_H_
#define DS_CPP_06_GRAPH_INCLUDE_TASK_GRAPH_H_

#include "task_edge.h"
#include "task_vertex.h"

#include <vector>
#include <list>
#include <unordered_map>

namespace task_graph {

class TaskGraph {

 public:
  TaskGraph();
//  void addEdge(TaskVertex vertex);

 private:
  int node_num_;
  std::unordered_map<int, std::list<TaskVertex>> adj_;  // id=>vertex hash 图
};

}
#endif
