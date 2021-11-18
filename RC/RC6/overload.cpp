
#include <iostream>
using namespace std;
#define TEST

/*
    测试基类
 */
class base
{
public:
    char * strName;
    base(char *);
    base(const base &);
    ~base();

#ifdef TEST
    base & operator = (const base &);
#endif
};

/*
    构造函数，在构造函数里有动态申请。
 */
base::base(char * str)
{
    strName = new char[strlen(str) + 1];
    strcpy(strName, str);
}

//拷贝构造函数
base::base(const base & r)
{
    strName = new char[strlen(r.strName) + 1];
    strcpy(strName, r.strName);
}

/*
    析构函数，释放空间
 */
base::~base()
{
    if (NULL == strName)
    {
        return ;
    }
    else
    {
        cout << "释放的空间地址为：" << &strName << endl;
        delete [] strName;
    }
}


#ifdef TEST
/*
    赋值运算符。
 */
base & base::operator = (base const & r)
{
    if (this == &r)
    {
        cout << "the same object" << endl;
    }
    else
    {
        if (NULL != this->strName)
        {
            delete [] this->strName;
        }
        this->strName = new char[strlen(r.strName) + 1];
        strcpy(this->strName, r.strName);
    }
    return *this;
}
#endif

int main()
{
    base a("base_a");
    base b("base_b");
    a = b;
    return 0;
}