#include <iostream>
using std::cout;
using std::endl;
/*
    C++函数模板
    模板的意义：对类型可以进行参数化了
    
    函数模板是不进行编译的，因为不知道类型
    模板的实例化 <- 函数调用点进行实例化
    模板函数 <- 才是要被编译器所编译的

    模板类型参数 typename/class
    模板非类型参数

    模板的实参推演 -> 可以根据用户传入的实参类型自动识别
    模板的特例化（并不是编译器提供，需要用户自定义）

    模板代码是不能在一个文件中定义，在另一个文件中使用的
    模板代码调用前，一定要看到模板定义的地方这样模板才能够进行正常的实例化

    所以模板都包含在头文件当中，在源文件中直接进行#include
*/


// //模板的声明
// template<typename T>
// bool compare(T a, T,b);
// bool compare(const char *a, const char *b);

//函数模版
template<typename T,typename E> //定义一个模版参数列表 template<class T, class E>同理
bool compare(T a,E b) //compare是一个函数模板
{
    cout << "template compare" << endl;
    return a > b;
}
//针对compare()函数模板，提供const char*类型特例化
template<>
bool compare<const char *>(const char *a, const char *b)
{
    cout << "compare< const char *>" << endl;
    return strcmp(a,b)>0;
}
//非模板函数， 即普通函数
bool compare(const char*a,const char*b)
{
    cout << "normal compare" << endl;
    return strcmp(a,b) > 0;
}
/*
    在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来
    bool compare<int>(int a, int b)
    {
        return a > b;
    }
    bool compare<double>(double a, double b)
    {
        return a > b;
    }
    bool compare<const char*>(const char* a, const char* b)
    {   
        return strcmp(a,b) > 0;
    }
*/

int main()
{
    //函数的调用
    compare<int>(10,20); //函数名 = 模版名+参数列表
    compare<double>(10.3,10.5);
    //模板的推演
    compare(20,30); //模板的实参推演 -> 根据用户传入的实参类型，推导出模板类型参数的具体类型
    //compare(30,40.5); //推演无法推倒2个不同参数类型
    compare(30,40.5); 
    compare("aaa","bbb");//编译器优先看作普通函数
    compare<const char*>("aaa","bbb"); //没有普通函数则函数模板特例化
    return 0;
}