class Fib{  // Fib数列生成对象
private:
	int g,f;
public:
	int get(){ return f; }
    Fib(int n):g(0),f(1){// f 初始化为不小于n的最小fib数或者int能表示的最大数
      	if(n>1836311902) n=1836311902; 
        while(f<n) next();}
	void next(){  // 下一个Fib数 最大为 1836311903
        f=g+f; g=f-g;
        if(f<0){ f=1836311903; g=1134903170; } // 溢出修正
	}
	void pre(){  // 上一个Fib数 最小为 1
		g=f-g; f=f-g;
		if(f<1){ f=1; g=0; }
	}
};
