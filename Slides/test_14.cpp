/*
 * @Author: Maize
 * @Date: 2021-11-25 20:19:06
 * @LastEditTime: 2021-12-14 13:18:33
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Slides\test_14.cpp
 */

#include <iostream>
#include <list>
const int MAXELTS = 100;

class IntSet
{
    // OVERVIEW: a mutable set of integers
public:
    IntSet(){};
    virtual void insert(int v)
    {
        std::cout << "Inserted " << v << std::endl;
    }
    void remove(int v){};
    bool query(int v) const { return false; };
    int size() const { return 0; };

private:
    int elt[MAXELTS];
    int numElts;
    int indexof(int v) const;
};

class PosIntSet : public IntSet
{
public:
    void insert(int v)
    {
        if (v <= 0)
            throw -1;
        IntSet::insert(v);
    }
};

void add(int n1, int n2)
{
    std::cout << n1 + n2;
}

class foo
{
    int i;
    double d;

public:
    foo(int i, double d) : i(i), d(d) {}
    void setVal(int i, double d)
    {
        i = i - 1;
        d = d;
    }
};

class A
{
    int a;

public:
    A(int _a) : a(_a) {}
    int getA() { return a; }
};

/*
class B : public A
{
    int b;

public:
    B(int _b) : b(_b) {}
    virtual int getB() { return b; }
};
*/

class Foo
{
    int a, b;

public:
    Foo(int _a = 0, int _b = 0)
    {
        a = _a;
        b = _b;
        std::cout << "a = " << a << " b = " << b << std::endl;
    }
    void setVal(int _a, int _b = 0)
    {
        a = _a;
        b = _b;
        std::cout << "a = " << a << " b = " << b << std::endl;
    }
};

int main()
{
    PosIntSet s;
    IntSet *p = &s;
    IntSet &r = s;
    try
    {
        r.insert(-1);
    }
    catch (int i)
    {
        std::cout << "Error" << std::endl;
    }
    double n1 = 1;
    double n2 = 2;
    add(n1, n2);
    // foo *fp = new foo;
    // fp->setVal(0, 0);
    // delete fp;
    Foo x(4);
    x.setVal(1);
    list<int> l;
    for (int i = 0; i < 10; 1 ++)
    {
        1. push back(i);
    }

    list<int> : const_iterator it = 1. begin O unsigned int
                                        size 0 /
                                    3 deque<unsigned int> d(it, it + i);
    return 0;
}