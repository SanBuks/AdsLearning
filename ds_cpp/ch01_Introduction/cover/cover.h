#include <iostream>
#include <utility>

class Table{
public:
  static constexpr unsigned kWordLength = sizeof(long) * 8;

  using LengthType = unsigned long;
  using RankType = unsigned;
  using Pos = std::pair<LengthType, LengthType>; 
  using PosRank = std::pair<RankType, RankType>;

	Table(unsigned rank);
	~Table();

	void Print();

  // abs(first, second) 是缺口的绝对坐标
	void Cover(Pos abs);

  // origin(first, second) 区域原点 
  // abs(first, second) 缺口绝对位置
  void Process(RankType rank, Pos origin, Pos abs);

  // 在中心 2*2 区域内放置 L 型 空缺
  void Place(Pos origin, PosRank rank);

  Pos Reflection(Pos origin, // 分区原点坐标
                 PosRank rank, // 缺口所在分区位置
                 PosRank rank_pos, // 分区位置 
                 Pos abs, // 缺口的绝对位置
                 LengthType halfLength);  // 分区边长
	

private:
	RankType rank_;
	LengthType length_; // length_ = 2 ^ rank_
	char **table_;
};