#include "../include/task_edge.h"

namespace task_graph {

TaskEdge::TaskEdge(int id,
                   const std::string &tooltip,
                   const std::string &content,
                   TaskEdge::TaskEdgeType type)
    : id_(id), tooltip_(tooltip), content_(content), type_(type) {}

}