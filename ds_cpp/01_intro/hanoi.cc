#include <iostream>

void move(char source, char target) {
	std::cout << source << " ---> " << target << "\n";
}

void hanoi(int n, char source, char temp, char target) {
	if(n > 0) {
		hanoi(n-1, source, target, temp);	
		move(source, target);
		hanoi(n-1, temp, source, target); 
	}
}

int main() {
	hanoi(3, 'x', 'y', 'z');
	return 0;
}
