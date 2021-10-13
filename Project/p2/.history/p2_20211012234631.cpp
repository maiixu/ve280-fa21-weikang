/*
 * @Author: your name
 * @Date: 2021-10-12 10:28:22
 * @LastEditTime: 2021-10-12 23:46:30
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
{
    if (list_isEmpty(list))
    {
        return base;
    }
    return fn(list_first(list), accumulate(list_rest(list), fn, base));
}

list_t reverse(list_t list)
{
    if (size(list) == 0 || 1)
    {
        return list;
    }
    return append(reverse(list_rest(list)), list_make(list_first(list), list_make()));
}

list_t append(list_t first, list_t second)
{
    if (list_isEmpty(second))
    {
        return first;
    }
    return append(first, list_make(list_first(second), list_make()));
}

static bool isOdd(int n) { return n % 2 ? 1 : 0; }

static bool isEven(int n) { return n % 2 ? 0 : 1; }

list_t filter_odd(list_t list)
{
    list_t result;
    if (list_isEmpty(list))
    {
        return list;
    }
    if (isOdd(list_first(list)))
    {
        append(result, list_make(list_first(list), list_make()));
    }
    return filter_odd(list_rest(list));
}

list_t filter_even(list_t list)
{
    list_t result;
    if (list_isEmpty(list))
    {
        return list;
    }
    if (isEven(list_first(list)))
    {
        append(result, list_make(list_first(list), list_make()));
    }
    filter_even(list_rest(list));
}

list_t filter(list_t list, bool (*fn)(int))
{
    list_t result;
    if (list_isEmpty(list))
    {
        return list;
    }
    if (fn)
    {
        append(result, list_make(list_first(list), list_make()));
    }
    filter_even(list_rest(list));
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
    list_t result = list_make();
    if (n == 0)
    {
        return append(second, first);
    }
    append(result, list_make(list_first(first), list_make()));
    return insert_list(list_rest(first), second, n - 1);
}

static list_t chop_first(list_t list, unsigned int n)
{
    if (n == 0)
    {
        return list;
    }
    return chop_first(list_rest(list), n - 1);
}

list_t chop(list_t list, unsigned int n)
{
    list = reverse(list);
    list = chop_first(list, n);
    list = reverse(list);
    return list;
}

static int tree_sum_helper(tree_t tree)
{
    return tree_elt(tree_right(tree)) + tree_elt(tree_left(tree)) + tree_sum(tree_right(tree)) + tree_sum(tree_left(tree));
}

int tree_sum(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return 0;
    }
    return tree_elt(tree) + tree_sum_helper(tree);
}

bool tree_search(tree_t tree, int key)
{
    if (tree_isEmpty(tree))
    {
        return key == tree_elt(tree);
    }
    return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key);
}

static int getMax(int m, int n) { return m >= n ? m : n; }

static int getMin(int m, int n) { return m <= n ? m : n; }

static int depth_helper(tree_t tree, int depth, int max)
{
    depth++;
    max = getMax(depth_helper(tree_right(tree), depth, max), depth_helper(tree_left(tree), depth, max));
}

int depth(tree_t tree)
{
    int depth = 1;
    int max = 1;
    if (tree_isEmpty(tree))
    {
        return getMax(depth, max);
    }
    return depth_helper(tree, depth, max);
}

int tree_min(tree_t tree)
{
    int min = tree_elt(tree);
    if (tree_isEmpty(tree))
    {
        return getMin(min, tree_elt(tree));
    }
    return getMin(min, getMin(tree_elt(tree_right(tree)), tree_elt(tree_left(tree))));
}

list_t traversal(tree_t tree)
{
    if (tree_isEmpty(tree))
    {
        return list_make();
    }
    return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

bool tree_hasPathSum(tree_t tree, int sum)
{
    if (tree_isEmpty(tree))
    {
        return false;
    }
    return (tree_hasPathSum((tree_left(tree)), sum - tree_elt(tree)) || tree_hasPathSum((tree_right(tree)), sum - tree_elt(tree)));
}

bool covered_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A))
    {
        return tree_elt(A) == tree_elt(B);
    }
    return covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B));
}

bool contained_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A))
    {
        return tree_search(B, tree_elt(A));
    }
    return contained_by(tree_left(A), tree_left(B)) && contained_by(tree_right(A), tree_right(B));
}

tree_t insert_tree(int elt, tree_t tree)
{
}