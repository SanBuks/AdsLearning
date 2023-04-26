#ifndef DS_CPP_06_GRAPH_INCLUDE_TASK_EDGE_H_
#define DS_CPP_06_GRAPH_INCLUDE_TASK_EDGE_H_

#include <string>

namespace task_graph {

class TaskEdge {
 public:
  enum TaskEdgeType {
    NormalForward = 0, // 正常步骤
    CondForward,       // 判断
    TimeCycle          // 时间自循环
  };

  TaskEdge(int id,
           const std::string &tooltip,
           const std::string &content,
           TaskEdgeType type);

 private:
  int id_;              // ID 边
  int id_start_;        // ID 起始
  int id_end_;          // ID 结束
  std::string tooltip_; // 描述
  std::string content_; // 步骤
  TaskEdgeType type_;   // 类别

};

}

#endif
