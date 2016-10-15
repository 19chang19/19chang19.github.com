/***************************************** 
 * 感知器判断数字奇偶性 
 * 
 * 关键点,阈值应该怎么定? 
 ****************************************/  
#include <stdlib.h>  
#include <stdio.h>  
#include <time.h>  
  
  
int M[10];  /** 权值 **/  
int X[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; /** 输入向量 **/  
int Y[10] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};  /** 理想输出向量, 0 表示奇数， 1表示偶数 **/  
int O[10];  /** 保存输出向量 训练出来的答案**/  
int ST = 52; /** 阈值 **/   
  
  
/** 初始化权值 **/  
void initM ()  
{  
    int x = 0;  
    srand ((unsigned int)time(0));  
    for (x = 0; x < 10; ++x) {  
        /** 随机数在 0 - 99 之间 **/  
        M[x] = rand () % 100;  
    }  
}  
  
/** 训练过程2,跃迁型激活函数??? //返回值相当于减分?*
反回值表示 权值是小还是大，1是太大，0是太小
又表示1是应该是偶数，0是奇数，这里还要理解下
*/  
int active (int m, int x)  //权值和参考值
{  
    int o = m * x;  
    if (o > ST) 
    {  
        return 1;  //test 中说这个就是偶数
    } else {  
        return 0;  //test 中说这个就是奇数
    }      
}  
  
/** 训练过程1,计算输出向量??? **/  
void calcY ()  
{  
    int x = 0;  
    for (x = 0; x < 10; ++x) 
    {  
        O[x] = active (M[x], X[x]);  //反回0或1
    }  
}  
  
  
/** 训练3打分? 
根据实际输出向量和理想输出向量调整权向量,  
    返回 实际输出和理想输出不匹配的数目 **/  
int adjustM ()  
{  
    int err = 0;  
    int x = 0;  
    for (x = 0; x < 10; ++x) 
    {  
        if (O[x] != Y[x]) //训练的结果的和理想结果的比较 
        {  //做错了
            err ++;  
            if (0 == O[x]) 
            {  
                M[x] += X[x];  //相当权向量+1到10,
            } else 
            {  
                M[x] -= X[x];  //相当权向量-1
            }  
        }  
    }  
    return err;  
}  
  
  
/** 打印权向量 **/  
void printM ()  
{  
    int x = 0;  
    for (x = 0; x < 10; ++x) 
    {  
        printf ("M[%i] = %i/n", x, M[x]);  
    }  
}  
  
  
void test (int input)  
{  
    printf ("[%i] [%i] ", M[input], X[input]);  
    if (active (M[input], X[input]))  
    {  
        printf ("%d 是 偶数/n", input);  
    } else 
    {  
        printf ("%d 是 奇数/n", input);  
    }  
}  
  
int main ()  
{  
    int n = 0;  
    initM ();  
  
    /** 一直训练直到能够100%正确为止 **/  
    while (1) 
    {  
        n ++;  
        calcY ();  
        int err = adjustM ();  
        if (0  >= err) 
        {  
            /** 能够 100 %正确地回答问题了，结束训练 **/  
            break;  
        }  
        printf ("错误数 %d/n", err);  
    }  
  
    printM ();  
    printf ("阈值 %d 训练次数 %d/n", ST, n);  
  
  
    while (1) 
    {  
        int a = 0;  
        scanf ("%i", &a);  
        if (0 > a || 9 < a) 
        {  
            break;  
        }  
  
        test (a);  
    }  
    return 0;  
}



/*

测试, 选择 阈值 52 作为测试，经过25次训练之后，能够给100 % 回答问题.
M[0] = 53  
M[1] = 26  
M[2] = 40  
M[3] = 11  
M[4] = 59  
M[5] = 4  
M[6] = 21  
M[7] = -1  
M[8] = 68  
M[9] = 4  
阈值 52 训练次数 25  


http://blog.csdn.net/helloaya/article/details/4224425

输入0,1,2,3,
代入test()
0 53*1  > 52 => 1
1 26*2 !> 52 => 0
2 40*3  > 52 => 1
3 11*4 !> 52 => 0
4 59*5  > 52 => 1
5  4*6 !> 52 => 0
6 21*7  > 52 => 1
7 -1*8 !> 52 => 0
8 68*9  > 52 => 1
9  4*10!> 52 => 0


*/