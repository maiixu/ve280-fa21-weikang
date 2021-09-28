#include <iostream>
using namespace std;
int main()
{
    char a[] = {'a', 'b'}; // 没有添加 \0, 输出结果不可预测
    cout << a << endl;

    char b[] = {'a', 'b', '\0'};
    cout << b << endl;

    char c[] = "abc";
    cout << c << endl;

//    char d[3] = "efg";// error: initializer-string for array of chars is too long
    char d[4] = "efg"; // \0 will be added automatically.
    cout << d << endl;
}