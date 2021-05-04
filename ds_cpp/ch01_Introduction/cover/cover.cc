#include "cover.h"

Table::Table(RankType rank) : rank_(rank % kWordLength), 
															length_(static_cast<LengthType>(1UL << rank_)) {
	table_ = new char * [length_];	
	for (LengthType i = 0; i != length_; ++i) {
		table_[i] = new char [length_];
		for (LengthType j = 0; j != length_; ++j)
			table_[i][j] = '*';
	}
}

Table::~Table() {
	for (LengthType i = 0; i != length_; ++i)
		delete [] table_[i];
}
	
// 从上打印棋盘, 坐标原点在西南处, 横轴(第一维)为x, 纵轴(第二维)为y 
void Table::Print() {
	for (LengthType i = length_ - 1; i >= 0 && i < length_; --i){
		for (LengthType j = 0; j < length_; ++j)
			std::cout<<table_[j][i]<<" ";
		std::cout<<"\n";
	}
}
	
// abs(first, second) 是缺口的绝对坐标
void Table::Cover(Pos abs) {
	table_[abs.first][abs.second] = ' ';
	std::cout << "Origin : \n";
	Print();
	Process(rank_, Pos(0, 0), abs);
	std::cout << "Processed : \n";
	Print();
}
	
// origin(first, second) 区域原点 
// abs(first, second) 缺口绝对位置
void Table::Process(RankType rank, Pos origin, Pos abs) {
	if(rank < 2) return;

	LengthType halfLength = static_cast<LengthType>(1UL << (rank - 1));

	// 判断缺口分区方位
	PosRank rank_pos = PosRank((abs.first  - origin.first ) / halfLength,	
														 (abs.second - origin.second) / halfLength);

	// 计算分区 中心 2*2 区域的原点
	Pos place_origin = Pos(origin.first + halfLength - 1, 
												 origin.second + halfLength - 1);

	// 在中心 2*2 区域 根据缺口位置放置空值
	Place(place_origin, rank_pos);

	// 按四个分区划分 : 
	// PosRank(0,0)表示缺口在西南处, PosRank(1,0)表示缺口在东南处
	// 对四个划分区域递归
	if (rank > 2) {
		auto p = Reflection(Pos(origin.first, origin.second + halfLength), 
												rank_pos, PosRank(0, 1), abs, halfLength);	
		Process(rank-1, // NW
						Pos(origin.first, origin.second + halfLength), 
						Pos(p.first, p.second));  

		p = Reflection(Pos(origin.first + halfLength, origin.second + halfLength),
									 rank_pos, PosRank(1, 1), abs, halfLength);	
		Process(rank-1, // NE
						Pos(origin.first + halfLength, origin.second + halfLength), 
						Pos(p.first, p.second));  

		p = Reflection(Pos(origin.first, origin.second), 
									 rank_pos, PosRank(0, 0), abs, halfLength);	
		Process(rank-1, // SW 
						Pos(origin.first, origin.second), 
						Pos(p.first, p.second));  

		p = Reflection(Pos(origin.first + halfLength, origin.second), 
									 rank_pos, PosRank(1, 0), abs, halfLength);	
		Process(rank-1, // SE
						Pos(origin.first + halfLength, origin.second), 
						Pos(p.first, p.second));  
	}
}
	
Table::Pos Table::Reflection(Pos origin, // 分区原点坐标
														 PosRank rank, // 缺口所在分区位置
														 PosRank rank_pos, // 分区位置 
														 Pos abs, // 缺口的绝对位置
														 LengthType halfLength) { // 分区边长
	// 缺口所在分区 正是 本分区 直接返回绝对坐标
	if (rank.first == rank_pos.first && rank.second == rank_pos.second) 
		return Pos(abs.first, abs.second);

	// 计算分区的缺口坐标
	LengthType tempx = (!rank_pos.first) ? halfLength -1 : 0; 
	LengthType tempy = (!rank_pos.second) ? halfLength -1 : 0; 

	return Pos(origin.first+ tempx, origin.second+ tempy);
}
	
// 在中心 2*2 区域内放置 L 型 空缺
void Table::Place(Pos origin, PosRank rank){
	table_[origin.first + !rank.first][origin.second + !rank.second] = ' ';
	table_[origin.first +  rank.first][origin.second + !rank.second] = ' ';
	table_[origin.first + !rank.first][origin.second +  rank.second] = ' ';
}

int main(){

	Table table(4);
	table.Cover(Table::Pos(2, 3));

	return 0;
}
