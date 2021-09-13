//PATB1012 数字分类
#include <cstdio>

inline bool isEven(int n){ return !(n%2); }
int exsit[6]={0};
int main(){
    int n, num, a1, a2, a3, a4, a5;
    double a4s; a4s=0.0;
    a1=a2=a3=a4=0; a5=0x80000000;
    bool tag=true;
    scanf("%d", &n);
    while(n--){
        scanf("%d", &num);
        switch(num%5){
            case 0: 
                if(isEven(num)){
                    exsit[1]=1;
                    a1+=num;
                }
                break;
            case 1:
                exsit[2]=1;
                if(tag){
                    a2+=num;
                    tag=false;
                }else{
                    a2-=num;
                    tag=true;
                }
                break;
            case 2:
                exsit[3]=1;
                a3++;
                break;
            case 3:
                exsit[4]=1;
                a4s+=num;
                a4++;
                break;
            case 4:
                exsit[5]=1;
                if(num>a5)
                    a5=num;
                break;
            default: 
                break;
        } 
    }
    if(exsit[1]) printf("%d ", a1);
    else printf("N ");

    if(exsit[2]) printf("%d ", a2);
    else printf("N ");

    if(exsit[3]) printf("%d ", a3);
    else printf("N ");

    if(exsit[4]) { a4s/=a4; printf("%.1f ", a4s); }
    else printf("N ");

    if(exsit[5]) printf("%d", a5);
    else printf("N");

	return 0;
}

