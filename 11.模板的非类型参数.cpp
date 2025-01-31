#include <iostream>
using std::cout;
using std::endl;

/*
    模板的非类型参数 必须是整数类型（整数或者地址/引用都可以）都是常量 只能使用，不可修改
*/

template<typename T, int SIZE>
void sort(T *arr)
{
    for(int i = 0; i < SIZE-1; ++i)
    {
        for(int j = 0; j< SIZE-1-i; ++j)
        {
            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main()
{
    int arr[] = {12,5,7,89,32,21,35};
    const int size = sizeof(arr) / sizeof(arr[0]);
    sort<int,size>(arr);
    for(int val:arr)
    {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}