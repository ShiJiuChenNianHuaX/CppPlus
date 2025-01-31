#include <iostream>

using std::cout;
using std::endl;

/*
    构造函数和析构函数
    函数名字和类名一样
    没有返回值
*/


//实现一个顺序栈
class SeqStack
{
    public:
        //构造函数,可以带参数，可以提供多个构造函数称为构造函数重载
        //可以是默认构造：SeqStack s1; 也可以是SeqStack s2(20);
        SeqStack(int size = 10)
        {
            cout << this << "SeqStack()" << endl;
             _pstack = new int[size];
            _top = -1;
            _size = size;
        }
        //析构函数,不可以带参数，只能有一个
        ~SeqStack()
        {
            cout << this << "~SeqStack()" << endl;
            delete[]_pstack;
            _pstack = nullptr;
        }
        /* 
        void init(int size = 10)
        {
            _pstack = new int[size];
            _top = -1;
            _size = size;
        }
        */
        //释放申请的栈区域
        /*
        void release()
        {
            delete []_pstack;
            _pstack = nullptr; // 防止野指针
        }
        */
        bool empty()
        {
            return _top == -1;
        }
        bool full()
        {
            return _top == _size - 1;
        }
        //入栈
        void push(int val)
        {
            if(full())
            {
                resize(); //扩容
            }
            _pstack[++_top] = val;
        }
        //出栈
        void pop()
        {
            if(empty())
            {    
                return;
            }
            --_top;
        }
        int top()
        {
            return _pstack[_top];
        }
    private:
        int * _pstack; //动态开辟数组，存储顺序栈元素
        int _top; //指向栈顶元素
        int _size; //数组扩容的总大小
        //数组扩容是原来大小的2倍
        void resize()
        {
            int *ptmp = new int[_size *2];
            //把原来内存中的数据拷贝到开辟的新数组中
            for(int i = 0;i < _size; ++i)
            {
                ptmp[i] = _pstack[i];
            } //memcpy(ptmp, _stack, sizeof(int) *_size);
              //realloc()，这两个都是涉及内存拷贝，对于拷贝"对象"可能产生问题
            delete[]_pstack;
            _pstack = ptmp; //让原来的指针指向新开辟的内存
            _size *= 2;
        }
};

SeqStack gs; //定义了一个全局对象

int main()
{
    //1.开辟栈内存 调用构造函数
    SeqStack s;
    //s.init(5); //对象成员变量初始化

    //开辟堆内存
    SeqStack *ps = new SeqStack(60); //堆上的对象一定要手动释放
    ps->push(70);
    ps->push(80);
    ps->pop();
    cout << ps->top() << endl;
    delete ps; /*  delete和free区别：delete先调用对象的析构函数释放指针指向的堆内存ps -> ~SeqStack()
                                    然后再把对象的内存释放 free(ps)
               */
    for(int i = 0; i < 15; ++i)
    {
        s.push(rand()%100);
    }
    while(!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    //s.release(); //释放对象成员变量占用的外部堆内存（外部资源）
    SeqStack s1(50);
    //s1.~SeqStack();//析构函数调用后对象就不存在了，不建议手动调用析构函数   
    //s1.push(30);//堆内存的非法访问
    return 0; //出函数作用域的时候栈上的对象依次调用析构函数
}
