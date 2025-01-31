#include <iostream>
using std::cout;
using std::endl;

const int NAME_LEN = 20;

class CGoods
{
    public:
        //商品数据初始化
        void init(const char *name, double price, int amount);
        //打印商品信息
        void show();
        //给成员变量提供get和set方法,类内实现的方法，自动处理成inline内联函数
        void setName(const char *name)
        {
            strcpy(_name,name);
        }
        void setPrice(double price)
        {
            _price = price;
        }
        void setAmount(int amount)
        {
            _amount = amount;
        }
        const char* getName()
        {
            return _name;
        }
        double getPrice()
        {
            return _price;
        }
        int getAmount()
        {
            return _amount;
        }
    private: //属性一般都是成员变量
        char _name[NAME_LEN];
        double _price;
        int _amount;
};

//类外定义成员方法:
void CGoods::init(const char *name, double price, int amount)
{
    //类的成员方法一经编译，所有的方法参数都会加一个this指针接收调用该方法对象的地址 
    strcpy(this->_name,name);
    this->_price = price;
    this->_amount = amount;
}
void CGoods::show()
{
    cout << "name:" << this->_name << endl;
    cout << "price" << this->_price << endl;
    cout << "amout" << this->_amount << endl;
}

int main()
{
    //CGoods可以定义无数个对象，每一个对象都有自己的成员变量，但是他们共享一套成员方法
    /*
        show()怎么知道处理哪个对象的信息？
        init(name,price,amount) -> 怎么知道把信息初始化给哪个对象？
        类的成员方法一经编译，所有的方法参数都会加一个this指针接收调用该方法对象的地址 
    */
    CGoods good1;//实例化第一个对象
    good1.init("面包",10.0,200); //init(&good1,"面包",0.0,200);
    good1.show(); //show(&good1)
    good1.setPrice(20.5);
    good1.setAmount(100);
    good1.show();
    CGoods good2;//实例化第二个对象
    good2.init("空调",10000,50);
    good2.show();
    return 0;
}