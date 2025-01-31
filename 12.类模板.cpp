#include <iostream>

using std::cout;
using std::endl;

/*
    类模板 -> 实例化 -> 模板类
*/

template<typename T>
class SeqStack //模板名称  + 类型参数列表 = 类名称 
{
public:
    //构造和析构函数名不用加<T>，其他出现模板的地方都加上类型参数列表
    SeqStack<T>(int size = 10)
        :_pstack(new T[size])
        ,_top(0)
        ,_size(size)
    {}
    SeqStack(const SeqStack<T> &stack)
        :_top(stack._top)
        ,_size(stack._size)
    {
        _pstack = new T[_size];
        for(int i = 0; i < _top; ++i)
        {
            _pstack[i] = stack._pstack[i];
        }
    }
    SeqStack<T>& operator=(const SeqStack<T> &stack)
    /*
        类型部分 SeqStack<T>：
            表示这是与当前对象同类型的栈实例
            当类模板实例化时（如SeqStack<int>），T会被具体类型替换
            保证赋值运算符只能用于相同模板参数类型的对象
        引用符号 &：
            表示传递的是对象引用（内存地址），而非对象副本
            避免拷贝整个栈对象（包括底层数组），提高效率
            允许操作大型对象而不产生拷贝开销
        const修饰符：
            保证在函数内不能修改源对象（stack参数）
            允许函数接受常量对象作为右值
            使赋值操作满足：a = b 不会改变b的内容
            SeqStack<string> s1(5), s2(10);
            s1.push("hello");
            s2 = s1; // 这里stack参数就是s1的const引用

            // 分解参数传递过程：
            // 1. 编译器推导T=string
            // 2. 生成函数签名：SeqStack<string>& operator=(const SeqStack<string>&)
            // 3. 传递s1的引用（不拷贝对象）
            // 4. const保证s1在赋值过程中不会被修改
    */
    {
        if(this == &stack)
        {
            return *this;
        }
        delete[]_pstack;
        _top = stack._top; //外部传入的top给类内的top初始化
        _size = stack._size;//外部传入的size给类内的size 初始化
        _pstack = new T[_size];
        for(int i = 0; i < _top; ++i)
        {
            _pstack[i] = stack._pstack[i];
        }
        return *this;
    }
    void push(const T &val); //入栈
    void pop() //出栈
    {
        if(empty())
        {
            return;
        }
        --_top;
    }
    T top() const
    {
        if(empty())
        {
            throw "stack is empty!";
        }
        return _pstack[_top - 1];
    }
    bool full() const
    {
        return _top == _size;
    }
    bool empty() const
    {
        return _top == 0;
    }
    ~SeqStack<T>()
    {
        delete[]_pstack;
        _pstack = nullptr;
    }
private:
    T *_pstack; //开辟栈空间
    int _top;//栈顶 记录元素个数
    int _size;//数组

    //顺序栈底层数组2倍方式扩容
    void expand()
    {
        T *ptmp = new T[_size*2];
        for(int i = 0; i<_size; ++i)
        {
            ptmp[i] = _pstack[i];
        }
        delete []_pstack;
        _pstack = ptmp;
        _size *= 2;
    }
};  

template<typename E>
void SeqStack<E> :: push(const E &val) //入栈
{
        if(full())
        {
            expand();
        }
        _pstack[_top++] = val; //等价于 *(_pstack + _top++)
}

int main()
{
    SeqStack<int> s1;
    s1.push(20);
    s1.push(78);
    s1.push(32);
    s1.push(15);
    s1.pop();
    cout << "s1.top(): "<< s1.top() << endl;
    return 0;
}