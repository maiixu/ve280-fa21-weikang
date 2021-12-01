/*
 * @Author: Maize
 * @Date: 2021-11-25 20:19:06
 * @LastEditTime: 2021-11-27 12:08:18
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Slides\test_14.cpp
 */

#include <iostream>
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

int main()
{
    PosIntSet s;
    IntSet *p = &s;
    IntSet &r = s;
    s.insert(-1);
    return 0;
}