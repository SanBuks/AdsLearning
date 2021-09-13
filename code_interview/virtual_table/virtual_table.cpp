class Base {
public:
	char a=1;  // 0
	int b=2;  // 4
	int c=3;  // 8
	float d=4;  // 12
	virtual void test1(){}  // virtual table 16
	virtual void test2(){}
};

class Derived : public Base{
public:
	virtual void test1() override {}
};

int main(){
	Base b1, b2;
	Derived d1, d2;
	return 0;
}
