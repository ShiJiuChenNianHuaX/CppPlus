#include <iostream>

using std::cout;
using std::endl;

/*
    
    类的各种成员 - 成员方法/变量 
    （一）普通成员方法 -> 编译器会添加一个this形参变量
    1.属于类的作用域
    2.调用该方法时，需要依赖一个对象
    3.可以任意访问对象的私有成员变量 protected public private

    （二）Static静态成员方法 -> 不会生成this形参
    1.属于类的作用域
    2.用类作用域来调用方法
    3.可以任意访问你对象的私有成员，仅限于不依赖对象的成员（只能调用其他的static成员）

    （三）const常成员方法 -> const CGood *this
    1.属于类的作用域
    2.调用依赖一个对象，普通对抗或者常对象都可以
    3.可以任意访问对象的私有成员，但是只能读而不能写
*/
class CDate
{
public:
    CDate(int y, int m, int d)
    {
        _year = y;
        _month = m;
        _day = d;
    }
    void show() const
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
          _count++; //记录所有产生新对象的数量
          //_amount = a; //int _amount; int _amount = a;
          //_price = p; 
        }
        //普通成员方法 CGoods *this
        void show() //打印商品私有信息 
        {
            cout << "name:" << _name << endl;
            cout << "amount:" << _amount << endl;
            cout << "price:" << _price << endl;
            _date.show();
        }
        //常成员方法 只要是只读操作的成员方法，一律实现未const常成员方法
        void show()const//const CGoods *this
        {
            cout << "name:" << _name << endl;
            cout << "amount:" << _amount << endl;
            cout << "price:" << _price << endl;
            _date.show();
        }
        //静态成员方法 没有this指针，也就是没有“对象“
        static void showCGoodsCount() //打印所有商品共享的信息
        {
            cout << "所有商品种类数量:" << _count << endl;
        }
    private:
        char _name[20];
        int _amount;
        double _price;
        //构造函数的初始化列表
        //Cdata信息是CGoods商品信息的一部分 两个类是组和关系
        CDate _date; //实例化成员对象 1.分配内存 2.调用构造函数
        static int _count; //这里是声明   静态成员变量，一定在类外进行定义并且初始化
        //静态成员变量不属于对象，而是属于类级别
};
int CGoods::_count = 0;

int main()
{
    CGoods good1("商品1",100, 35.0, 2019, 5, 12);
    CGoods good2("商品2",100, 35.0, 2019, 5, 12);
    CGoods good3("商品3",100, 35.0, 2019, 5, 12);
    CGoods good4("商品4",100, 35.0, 2019, 5, 12);
    //统计所有商品的总数量
    CGoods::showCGoodsCount();//静态成员方法的调用

    //常对象调用普通方法
    const CGoods good5("非卖商品5",100, 35.0, 2019, 5, 12);
    good5.show(); //CGoods::show(&good5) CGoods::show() <- const CGoods*  &good5 <-CGoods *this
}