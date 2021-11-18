//
// Created by user on 2021/11/16.
//

/*
	FileName: MemoryLeakFaults.cpp
	Author: ACb0y
	Create Time: 2011年2月26日22:09:59
	Last modify Time: 2011年2月26日22:53:04
 */


#include <iostream>
using namespace std;
typedef int type;

struct node
{
    type data;
    node * pNext;
};

/*
	type：第一类的MLF故障 (Memory Leak Faults)
	desc: 在完整路径p申请了内存，但在p上无任何的内存释放函数，称为第一类MLF故障。
 */
node * MLF_one(node * entry, type value)
{
    node * pNew = (node *)malloc(sizeof(node));
    if (NULL == pNew)
    {
        return NULL;
    }

    pNew->data = value;

    //这里没有对pNew申请的空间进行释放。
    if (NULL == entry)
    {
        return NULL;
    }
    pNew->pNext = entry->pNext;
    entry->pNext = pNew;
    return pNew;
}

/*
	type: 第二类MLF
	desc: pointer是用malloc分配的变量，若存在p且p上存在一个free(pointer)，那么
		  pointer的使用是正确的。反之，如果存在两个或两个以上free(pointer)，或者
		  存在一个或一个以上的delete(pointer)，则称之为第二类的MLF。
 */
void MLF_two()
{
    char * str = (char *)malloc(100);
//    delete str;
    free(str);
}

/*
	type: 第三类MLF
	desc: pointer是用new分配的变量，若存在p且p上存在一个delete(pointer)，那么
		  pointer的使用是正确的。反之，如果存在两个或两个以上delete(pointer)，或者
		  存在一个或一个以上的free(pointer)，则称之为第三类的MLF。
 */
void MLF_three()
{
    int * pNew = new int[100];
    free(pNew);
    free(pNew);
}

/*
	type: 第四类MLF
	desc: pointer是用new[]分配的变量，若存在p且p上存在一个delete[]，那么
		  pointer的使用是正确的。反之，如果用free或用delete释放，
		  则称之为第四类的MLF。
 */
void MLF_four()
{
    int * pNew = new int[10];
    delete pNew;
}

/*
	type: 第五类MLF
	desc: 多余的delete和free是第五类MLF
 */
void MLF_five()
{
    char * str = "abc";
    free(str);
}

/*
	type: 第六类MLF
	desc: 当申请内存的pointer发生变化后，用delete和free释放
		  变化后的pointer是第六类MLF。
 */
void MLF_six()
{
    char * pStr = (char *)malloc(10);
    ++pStr;
    free(pStr);
}

int main()
{
//    node * pList = (node *)malloc(sizeof(node));
//    MLF_one(pList, 5);
//    MLF_two();
//    MLF_three();
//    MLF_four();
//    MLF_five();
//    MLF_six();
    return 0;
}
