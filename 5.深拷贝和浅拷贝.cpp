#include <iostream>
using std::cout;
using std::endl;

class SeqStack
{
    public:
        //构造函数
        SeqStack(int size = 10)
        {
            cout << this << "SeqStack()" << endl;
            _pstack = new int[size];
            _top = -1;
            _size = size;
        }
        //所以自定义拷贝构造函数（深拷贝） <- 对象的浅拷贝有问题
        //在OOP中尽量不使用realloc
        SeqStack(const SeqStack &src)
        {
            cout << "SeqStack(const SeqStack &src)" << endl;
            _pstack = new int[src._size];
            for(int i = 0;i <= src._top; ++i)
            {
                _pstack[i] = src._pstack[i];
            }
            _top = src._top;
            _size = src._size;
        }
        //析构函数
        ~SeqStack()
        {
            cout << this << "~SeqStack()" << endl;
            delete[]_pstack;
            _pstack = nullptr;
        }
        //赋值重载函数
        //赋值比深拷贝多一步，要先释放对象占用的外部资源即可 
        void operator=(const SeqStack &src)
        {
            cout << "operator=" << endl;
            //需要先释放当前对象占用的外部资源
            delete[]_pstack;

            _pstack = new int[src._size];
            for(int i = 0;i <= src._top; ++i)
            {
                _pstack[i] = src._pstack[i];
            }
            _top = src._top;
            _size = src._size;
        }
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
        int *_pstack;
        int _top;
        int _size;

        void resize()
        {
            int *ptmp = new int[_size * 2];
            for(int i = 0;i < _size; ++i)
            {
                ptmp[i] = _pstack[i];
            }
        }
};

int main()
{
     SeqStack s; //没有提供构造函数的时候，编译器会生成默认构造和默认析构,空函数什么也不做
     SeqStack s1(10);
     SeqStack s2 = s1; //默认拷贝构造函数 -> 直接内存数据拷贝
     //SeqStack s3(s1);

     //s2.operator = (s1);
     //void operator = (const SeqStack &src)
     s2 = s1;//赋值操作，编译器会提供一个默认的赋值函数 ->直接做的是浅拷贝，直接把s1赋值给s2，但是*pstack指向的是同一块内存区域

     return 0;
}