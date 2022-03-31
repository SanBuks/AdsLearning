#include "cover.h"

namespace ds_cpp {

namespace cover {

Table::Table(RankType rank) : rank_(rank % (kMaxRank + 1)),
                              length_(1ULL << rank_) {
  table_ = new char *[length_];
  for (LengthType i = 0; i != length_; ++i) {
    table_[i] = new char[length_];
    for (LengthType j = 0; j != length_; ++j)
      table_[i][j] = '*';
  }
}

Table::~Table() {
  for (LengthType i = 0; i != length_; ++i) {
    delete[] table_[i];
  }
  delete [] table_;
}

void Table::Print() const {
  for (LengthType i = length_ - 1; i >= 0 && i < length_; --i) {
    for (LengthType j = 0; j < length_; ++j) {
      std::cout << table_[j][i] << "|";
    }
    std::cout << "\n";
  }
}

void Table::Cover(Pos abs) {
  table_[abs.first][abs.second] = ' ';
  std::cout << "Origin: \n";
  Print();

  // 当前棋盘原点为 (0, 0)
  Process(rank_, Pos(0, 0), abs);
  std::cout << "Processed: \n";
  Print();
}

void Table::Process(RankType rank, Pos origin, Pos abs) {
  // 递归基
  if (rank < 2) {
    return;
  }
  // 当前棋盘的半个长度
  LengthType half_len = 1ULL << (rank - 1);
  // 根据缺口判断当前棋盘的中心缺口方位
  PosRank slot_pos = PosRank((abs.first - origin.first) / half_len,
                             (abs.second - origin.second) / half_len);
  // 计算当前棋盘中心 2 * 2 区域的原点
  Pos center_origin = Pos(origin.first + half_len - 1,
                         origin.second + half_len - 1);
  // 在当前棋盘中心 2 * 2 区域中根据缺口位置放置空缺
  Place(center_origin, slot_pos);
  // 对四个划分区域递归
  if (rank > 2) {
    // 四个分区的原坐标
    Pos NW_origin = Pos(origin.first,            origin.second + half_len);
    Pos NE_origin = Pos(origin.first + half_len, origin.second + half_len);
    Pos SW_origin = Pos(origin.first,            origin.second);
    Pos SE_origin = Pos(origin.first + half_len, origin.second);

    // 四个分区的缺口坐标位置
    Pos NW_p = Reflection(NW_origin, slot_pos, NW_POS_RANK, abs, half_len);
    Pos NE_p = Reflection(NE_origin, slot_pos, NE_POS_RANK, abs, half_len);
    Pos SW_p = Reflection(SW_origin, slot_pos, SW_POS_RANK, abs, half_len);
    Pos SE_p = Reflection(SE_origin, slot_pos, SE_POS_RANK, abs, half_len);

    // 递归
    Process(rank - 1, NW_origin, NW_p);
    Process(rank - 1, NE_origin, NE_p);
    Process(rank - 1, SW_origin, SW_p);
    Process(rank - 1, SE_origin, SE_p);
  }
}

Table::Pos Table::Reflection(Pos origin, PosRank slot_pos, PosRank rank_pos,
                             Pos abs, LengthType next_len) {
  // 缺口所在分区正是本分区, 直接返回绝对坐标
  if (slot_pos == rank_pos) {
    return abs;
  }
  // 按照分区位置计算缺口坐标, 位置等价于 place 的在此分区的置空
  LengthType temp_x = (!rank_pos.first) ? next_len - 1 : 0;
  LengthType temp_y = (!rank_pos.second) ? next_len - 1 : 0;
  return {origin.first + temp_x, origin.second + temp_y};
}

void Table::Place(Pos center_origin, PosRank slot_pos) {
  table_[center_origin.first + !slot_pos.first][center_origin.second + !slot_pos.second] = ' ';
  table_[center_origin.first +  slot_pos.first][center_origin.second + !slot_pos.second] = ' ';
  table_[center_origin.first + !slot_pos.first][center_origin.second +  slot_pos.second] = ' ';
}

} // namespace ds_cpp::cover

} // namespace ds_cpp
