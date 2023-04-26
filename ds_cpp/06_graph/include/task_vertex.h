#ifndef DS_CPP_06_GRAPH_INCLUDE_TASK_VERTEX_H_
#define DS_CPP_06_GRAPH_INCLUDE_TASK_VERTEX_H_

#include <list>

#include "task_edge.h"

namespace task_graph {

class TaskVertex {
 public:
  enum TaskType {
    Null = 0,
    Start,     // 启动
    End,       // 结束
    Warn,      // 警告  路径识别
    Rect,      // 步骤  测试内容
    Cond,      // 判定  判断开始时间, 判断结束时间
  };
  enum TaskStatus {
    Undiscovered,
    Discovered,
    Visited
  };
  TaskVertex(int id, int in_degree, int out_degree, TaskType type,
             TaskStatus status, int d_time, int f_time, int priority);

  std::list<TaskVertex> &edge_list() const;

 private:
  int id_;             // 任务节点 id
  int inDegree_;       // 入度
  int outDegree_;      // 出度
  TaskType type_;      // 任务类别
  TaskStatus status_;  // 任务当前状态
  int dTime;           // 任务开始时间
  int fTime;           // 任务结束时间
  int priority;        // 优先级

  std::list<TaskEdge> edge_list_;  // 邻接表
};

}

#endif
