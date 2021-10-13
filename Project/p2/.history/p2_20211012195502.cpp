/*
 * @Author: your name
 * @Date: 2021-10-12 10:28:22
 * @LastEditTime: 2021-10-12 19:55:02
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

int sum(list_t list)
{
    if (list_isEmpty(list))
    {
        return 0;
    }
    return sum(list_rest(list)) + list_first(list);
}

int product(list_t list)
{
    if (list_isEmpty(list))
    {
        return 1;
    }
    return product(list_rest(list)) * list_first(list);
}

int accumulate(list_t list, int (*fn)(int, int), int base)
/*
// REQUIRES: "fn" must be associative.
//
// EFFECTS: Returns "base" if "list" is empty.
//          Returns fn(list_first(list),
//                      accumulate(list_rest(list), fn, base) otherwise.
//
// For example, if you have the following function:
//
//           int add(int x, int y);
//
// Then the following invocation returns the sum of all elements:
//
//           accumulate(list, add, 0);
*/
{
    if (list_isEmpty(list))
    {
        return base;
    }
    return fn(list_first(list), accumulate(list_rest(list), fn, base);
}
