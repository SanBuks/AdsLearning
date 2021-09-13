#include <string>
#include <iostream>
using namespace std;

string replaceSpace(string s) {
	unsigned count = 0;
	for(auto it = s.begin(); it != s.end(); ++it)	
		if(*it == ' ')
			++count;
	unsigned origin_size = s.size();
	unsigned target_size = s.size() + count * 2;
	s.resize(target_size);
	auto q = s.rbegin();
	for(auto it = s.rbegin() + target_size - origin_size; it != s.rend(); ++it){
		if(*it != ' ')
			*q++ = *it;
		else{
			*q++ = '0';
			*q++= '2';
			*q++ = '%';
		}
	}
	return s;
}


int main(){
	string s("We Are Happy");
	std::cout<<replaceSpace(s);
	return 0;
}

