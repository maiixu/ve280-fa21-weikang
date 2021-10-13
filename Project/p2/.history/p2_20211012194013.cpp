/*
 * @Author: your name
 * @Date: 2021-10-12 10:28:22
 * @LastEditTime: 2021-10-12 19:40:13
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p2\p2.cpp
 */

#include "p2.h"

using namespace std;

int size(list_t list)
{
    if (list_isEmpty(list))
    {
        return 0;
    }
    return size(list_rest(list)) + 1;
}

int sum_helper(list_t list){

};

int sum(list_t list)
{
    if (size(list) == 0)
    {
        return 0;
    }
    return sum(list_rest(list)) + (struct list_node *)list->ln_elt;
}