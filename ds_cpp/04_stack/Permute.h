#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

bool permute(std::vector<int> &vec){
	if(vec.size()<=1) return false;
	auto j=vec.end();
	while(true){
		--j;
		auto i=j-1;
		if(*i<*j){
			auto k=vec.end();
			while( !(*i<*(--k)) ) ;
			std::iter_swap(i,k);
			std::reverse(j,vec.end());
			return true;
		}
		if(i==vec.begin())
			return false;
	}
}
