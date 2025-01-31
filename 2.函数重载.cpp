/*
函数重载
1. C++为什么支持函数重载，C不支持？
    C++代码产生函数符号的时候，函数名+参数列表类型组成
    C代码产生函数符号的时候，函数名来决定
2.函数重载需要注意些什么

3.C++和C语言代码之间如何相互调用
    C调用C++
    C++调用C


什么是函数重载？
1.一组函数，其中函数名相同，参数列表的个数或者类型不同，
那么这一组函数就称作函数重载
2.一组函数要称得上重载，一定先是处在同一个作用域当中
3.const或者volatile的时候怎么影响形参类型？
4.一组函数，函数名相同，参数列表也相同，仅仅是返回值不同，不叫重载

请你解释一下什么是多态？
静态（编译时期）的多态：函数重载
动态（运行时期）的多态

*/
#include <iostream>
#include <typeinfo>
using std::cout;
using std::endl;

void func(int a) {}
//void func(const int a ){}

int main()
{
    int a = 10;
    const int b = 10;
    cout << typeid(a).name() << endl;
    cout << typeid(b).name() << endl;
    return 0;
}



#if 0
bool compare(int a,int b)
{
    cout << "compare_int_int" << endl;
    return a > b;
}
bool compare(double a, double b)
{
    cout << "compare_double_double" << endl;
}

bool compare(const char *a, const char*b)
{
    cout << "compare_char*_char*" << endl;
    return strcmp(a,b) > 0;
}
int data = 10;
int main()
{
    int data = 20;
    int a = ::data; //调用全局作用域
    bool compare(int a, int b);//函数的局部作用域声明
    compare(10,20);
    ::compare(10.0,20.0); // double -> int 
    ::compare("aaa","bbb"); // const char* -> int 
    return 0;
}
# endif