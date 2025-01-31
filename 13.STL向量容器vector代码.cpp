#include <iostream>
#include <cstdlib> 
using std::endl;
using std::cout;
/*
    类模板 -> 实现一个C++ STL里面一个顺序容器 vector: 向量容器
    SeqStack，Queue定义的对象都可以称为容器
    容器：空间配置器allocator做四件事 内存开辟/内存释放、对象构造/对象析构
*/

//定义容器的空间配置器和C++标准库的allocator实现一样
template<typename T>
class Allocator
{
public:
    // 类型关联风格 (Type-centric)
    //int* a;   // 强调"指向int的指针"类型
    //int* b;   // 每个指针单独声明
    //内存开辟
    T* allocate(size_t size) //负责内存开辟
    {
        return (T*)malloc(sizeof(T)*size);
    }
    void deallocate(void *p) //负责内存释放
    {
        free(p);
    }
    void construct(T *p,const T &val) //在已经存在的内存上负责对象构造
    {
        new (p) T (val); //定位new，在指定的内存上构造一个对象
    }
    void destroy(T *p)//负责对象的构造
    {
        p -> ~T(); //~T()带表了T类型的析构函数
    }
};
/*
    容器底层内存开辟，内存释放，对象构造和析构
    都通过allocator空间配置器来实现
*/
template<typename T, typename Alloc = Allocator<T> >
class vector
{
public:
    /*
        vector(int size = 10, const Alloc &alloc = Allocator<T>())
        :_allocator(alloc)
    */
    vector(int size = 10)
    {
        //需要把内存开辟和构造对象分开
        //_first = new T[size];
        _first = _allocator.allocate(size);
        _last = _first;
        _end = _first + size;
    }
    ~vector()
    {
        //析构容器有效元素，然后释放*first指向的堆内存
        //delete[]_first;
        for(T *p = _first; p!= _last; ++p)
        {
            _allocator.destroy(p); //把_first指向的数组有效元素析构
        }
        _allocator.deallocate(_first);//释放堆上的数组内存
        _first = _last = _end = nullptr;
    }

    //拷贝构造函数
    //这段代码实现了一个 vector类的拷贝构造函数，其功能是创建一个与传入的vector对象（rhs）内容完全相同的副本。
    vector(const vector<T> &rhs)
    {
        int size = rhs._end - rhs._first;  //计算原vector的总容量（即分配的内存空间大小）
        //_first = new T[size]; //为新vector分配内存，容量与原vector相同（可能包含未使用的预留空间）
        int len = rhs._last - rhs._first; //计算原vector的实际元素数量（即已存储的元素个数）
        for(int i = 0; i< len; ++i) //通过 for 循环将原vector的元素逐个复制到新内存中
        {
            //_first[i] = rhs._first[i];
            _allocator.construct(_first+i, rhs._first[i]);
        }
        _last = _first + len;//标记新vector中有效元素的末尾位置
        _end = _first + size;//标记新vector的内存末尾位置（总容量）
    }
    vector<T>& operator=(const vector<T> &rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }
        //delete[]_first;
        for(T *p = _first; p!= _last; ++p)
        {
            _allocator.destropy(p); //把_first指向的数组有效元素析构
        }
        _allocator.dealoocate(_first);//释放堆上的数组内存
        int size = rhs._end - rhs._first;  //计算原vector的总容量（即分配的内存空间大小）
        //_first = new T[size]; //为新vector分配内存，容量与原vector相同（可能包含未使用的预留空间）
        int len = rhs._last - rhs._first; //计算原vector的实际元素数量（即已存储的元素个数）
        for(int i = 0; i< len; ++i) //通过 for 循环将原vector的元素逐个复制到新内存中
        {
            //_first[i] = rhs._first[i];
            _allocator.construct(_first+i, rhs._first[i]);
        }
        _last = _first + len;//标记新vector中有效元素的末尾位置
        _end = _first + size;//标记新vector的内存末尾位置（总容量）
        return *this;
    }

    void push_back(const T &val) //向容器末尾添加元素
    {
        if(full())
        {
            expend();
        }
        //*_last++ = val;//_last指针指向内存构造一个值为Val的对象
        _allocator.construct(_last,val); 
        _last++;
    }
    void pop_back()// 从容器末尾删除元素
    {
        if(empty())
        {
            return;
        }
        //--_last; //不仅要把_last指针--，还要析构删除的元素
        --_last;
        _allocator.destroy(_last);
    }
    T back() const //返回容器末尾元素值
    {
        return *(_last - 1);
    }
    bool full() const //只读，所以给常方法。普通对象和常对象都可以调用 
    {
        return _last == _end;
    }   
    bool empty() const 
    {
        return _first == _last;
    }
    int size() const
    {
        return _last - _first;
    }

private:
    T *_first;//指向数组其实的位置
    T *_last;//指向数组中有效元素的后继位置
    T *_end;//指向数组空间的后继位置
    Alloc _allocator; //定义容器的空间配置器对象
    
    void expend()//容器的2倍扩容
    {
        int size = _end - _first;
        //T *ptmp = new T[2*size];
        T *ptmp = _allocator.allocate(2*size);
        for(int i = 0; i < size; ++i)
        {
            //ptmp[i] = _first[i];
            _allocator.construct(ptmp+i,_first[i]);
        }
        //delete[]_first;
        for(T *p = _first; p != _last; ++p)
        {
            _allocator.destroy(p);
        }
        _allocator.deallocate(_first);
        _first = ptmp; //*first指向新内存起始地址
        _last = _first + size; //_last指向新内存中有效元素后继位置
        _end = _first + 2*size; //_end指向新内存的后继位置
    }
};

class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }
    Test(const Test&) 
    {
        cout << "Test(const Test&) "<< endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }
};

int main()
{
    // vector<int> vec;
    // for(int i = 0; i < 20; ++i)
    // {
    //     vec.push_back(rand() % 100);
    // }
    // vec.pop_back();
    // while(!vec.empty())
    // {
    //     cout <<  vec.back() << " ";
    //     vec.pop_back();
    // }
    // cout << endl;
    Test t1,t2,t3;
    cout << "--------------------------" << endl;
    vector<Test> vec; /*空容器却构造了10个对象
                        _first = new T[size]
                        new不仅仅开辟了空间，还构造了对象
                        但是这里的对象不是我们想要的对象
                        */
    vec.push_back(t1);
    vec.push_back(t2);
    vec.push_back(t3);
    cout << "-----------------------------" << endl;
    vec.pop_back(); //只需要析构对象，要把对象的析构和释放也分离开 
    cout << "-----------------------------" << endl;
    return 0;
}