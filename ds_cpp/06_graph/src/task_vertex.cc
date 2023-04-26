#include "../include/task_vertex.h"

namespace task_graph {

TaskVertex::TaskVertex(int id,
                       int in_degree,
                       int out_degree,
                       TaskVertex::TaskType type,
                       TaskVertex::TaskStatus status,
                       int d_time,
                       int f_time,
                       int priority)
    : id_(id),
      inDegree_(in_degree),
      outDegree_(out_degree),
      type_(type),
      status_(status),
      dTime(d_time),
      fTime(f_time),
      priority(priority) {}

std::list<TaskVertex> &TaskVertex::edge_list() const {
}

}

