// 单例模式
/*
 * 1. 懒汉
 * 2. 线程安全
 * 3. 销毁安全
 */

#include <iostream>
class Singleton{
public:
	static Singleton &getInstance(){
		static Singleton instance;  // 懒汉
		return instance;
	}

	Singleton(const Singleton &)=delete;  // 禁止复制
	Singleton& operator=(const Singleton&)=delete; 

private:
	Singleton(){}  // 禁止用户创建对象
};

int main(){
	auto &p=Singleton::getInstance();
	return 0;
}
