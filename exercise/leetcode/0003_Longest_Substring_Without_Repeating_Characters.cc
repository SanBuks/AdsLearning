// https://cloud.tencent.com/developer/article/1796631
// 3. Longest Substring Without Repeating Characters
// Given a string s, find the length of the longest substring without repeating characters.
//
#include <iostream>
#include <string>

using namespace std;

int dp[50010] = {};

int lengthOfLongestSubstring(string s) {
	if( s.size() == 0 )	return 0;		

	dp[0] = 1;

	for(decltype(s.size()) i = 1; i != s.size(); ++i){
		bool noRepeat = true;
		for( size_t j = 1; j < dp[i-1] + 1; ++j){
			if(s[i-j] == s[i]){
				s[i] = 1;
				noRepeat = false;
				break;
			}
		}
		if(noRepeat)
			dp[i] = dp[i-1] + 1;
	}

	int maxLength = dp[0]; 
	for(decltype(s.size()) i = 1; i != s.size(); ++i){
		if(maxLength < dp[i])
			maxLength = dp[i];
	}

	return maxLength;
}

int main(){
	string s("abcabcbb");
	cout<<lengthOfLongestSubstring(s);
	return 0;
}
