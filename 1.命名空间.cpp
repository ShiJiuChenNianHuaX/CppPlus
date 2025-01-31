#include <iostream>
using std::cout;
using std::endl;

namespace wd
{
    int number = 10;
    void print()
    {
        cout << "wd::print()" << endl;
    }
}//end of namespace wd

void test0()
{
    cout << "wd::number =" << wd::number << std::endl;
    wd::print();
}

int main(void)
{
    test0();
    return 0;
}