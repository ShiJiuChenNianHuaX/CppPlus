#include <iostream>

using namespace std;

class Test
{
public:
    void func(){cout << "call Test::func" << endl;}
    static void static_func(){
        cout << "Test::static_func" << endl;
    }
    int ma;
    static int mb;
};
int Test::mb;

int main()
{
    Test t1;
    Test *t2 = new Test();
    //int a = 10; int *p = &a; *p = 30;
    int Test::*p = &Test::ma; //无法从int Test：：* 转换为int *
    t1.*p = 20;
    cout << t1.*p << endl;
    t2->*p = 30;
    cout << t2->*p << endl;
    delete t2;

    int *p1 = &Test::mb;
    *p1 = 40;
    cout << *p1 << endl;
    return 0;
}