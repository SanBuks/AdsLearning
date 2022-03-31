#ifndef DS_CPP_INTRO_COVER_H
#define DS_CPP_INTRO_COVER_H

#include <iostream>
#include <utility>

namespace ds_cpp {

namespace cover {

/**
 * 打印 三角覆盖图形
 */
class Table {
 public:
  // 2^阶数 = 边长
  using LengthType = unsigned long long;  // 边长类型
  using RankType = unsigned;              // 阶数类型
  using Pos = std::pair<LengthType, LengthType>;  // 坐标
  using PosRank = std::pair<RankType, RankType>;  // 标记缺口位置

  // 四个位置的分区的标记
  static constexpr PosRank NW_POS_RANK{0, 1};
  static constexpr PosRank NE_POS_RANK{1, 1};
  static constexpr PosRank SW_POS_RANK{0, 0};
  static constexpr PosRank SE_POS_RANK{1, 0};

  static constexpr unsigned kMaxRank = sizeof(LengthType) * 8 - 1; // 最大阶数

  explicit Table(RankType rank);
  ~Table();

  /**
   * 从左上打印棋盘, 坐标原点在西南处, 横轴为 x 轴, 纵轴为 y 轴
   */
  void Print() const ;
  /**
   * 任意位置放置缺口, 生成图形
   * T(n) = O(4^n) (n 为阶)
   * T(N) = O(N^2) (N 为边长 2^n)
   * T(M) = O(M)   (M 为面积)
   * @param abs (x, y) 缺口的坐标
   */
  void Cover(Pos abs);
  /**
   * @param rank 当前棋盘阶数
   * @param origin 当前棋盘的原点坐标(西南角)
   * @param abs 缺口坐标
   */
  void Process(RankType rank, Pos origin, Pos abs);
  /**
   * 在中心 2 * 2 区域内放置空缺
   * @param center_origin 中心区域
   * @param slot_pos 空缺位置
   */
  void Place(Pos center_origin, PosRank slot_pos);
  /**
   * 返回下一个分区缺口的绝对坐标
   * @param next_origin 下一个分区原点坐标
   * @param slot_pos 缺口所在分区位置
   * @param rank_pos 分区位置标记
   * @param abs  当前缺口的绝对位置
   * @param nest_len 下一个分区边长
   */
  Pos Reflection(Pos next_origin, PosRank slot_pos, PosRank rank_pos,
                 Pos abs, LengthType next_len);

 private:
  RankType rank_;      // 阶数
  LengthType length_;  // 边长
  char **table_;       // 指向棋盘, 纵轴为第一维度, 横轴为第二维度
};

constexpr Table::PosRank Table::NW_POS_RANK;
constexpr Table::PosRank Table::NE_POS_RANK;
constexpr Table::PosRank Table::SW_POS_RANK;
constexpr Table::PosRank Table::SE_POS_RANK;

} // namespace ds_cpp::cover

} // namespace ds_cpp

#endif