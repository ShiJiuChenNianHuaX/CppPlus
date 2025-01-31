#include <iostream>

using std::endl;
using std::cout;

class CDate
{
public:
    CDate(int y, int m, int d)
    {
        _year = y;
        _month = m;
        _day = d;
    }
    void show()
    {
        cout << _year << "/" << _month << "/" << _day << endl;
    }
private:
    int _year;
    int _month;
    int _day;
};
/*
    构造函数的初始化列表：可以指定当前对象成员变量的初始化方式
    Cdata信息是CGoods商品信息的一部分 两个类是组和关系
*/
class CGoods
{
    public:
        CGoods(const char *n, int a, double p,int y, int m, int d)
        :_date(y,m,d), //CDate _data(y,m,d) 直接指定了CDate对象的构造方式（直接使用了有参构造函数）
        _amount(a), // int _amount = a直接初始化
        _price(p) // #1 构造函数的初始化列表 对当前对象的成员变量指定初始化方式
        {
          //#2 当前类类型构造函数体
          strcpy(_name,n);
          //_amount = a; //int _amount; int _amount = a;
          //_price = p; 
        }
        void show()
        {
            cout << "name:" << _name << endl;
            cout << "amount:" << _amount << endl;
            cout << "price:" << _price << endl;
            _date.show();
        }
    private:
        char _name[20];
        int _amount;
        double _price;
        //构造函数的初始化列表
        //Cdata信息是CGoods商品信息的一部分 两个类是组和关系
        CDate _date; //实例化成员对象 1.分配内存 2.调用构造函数
};

int main()
{
    CGoods good("商品",100, 35.0, 2025, 5, 12);
    good.show();
    return 0;
}