/*
 * @Author: your name
 * @Date: 2021-10-12 10:28:22
 * @LastEditTime: 2021-10-15 16:46:28
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p2\p2.cpp
 */

#include "p2.h"
#define MAX_INT (((unsigned int)(-1)) >> 1)

// EFFECTS: Returns true if the imput n is odd
// Applied in filter_odd()
static bool isOdd(int n) {
    return (n % 2 == 1) ? true : false;
}

// EFFECTS: Returns true if the imput n is even
// Applied in filter_even()
static bool isEven(int n) {
    return (n % 2 == 0) ? true : false;
}

// EFFECTS: Returns the larger one of m and n
// Applied in depth()
static int getMax(int m, int n) {
    return (m >= n) ? m : n;
}

// EFFECTS: Returns the smaller one of m and n
// Applied in tree_min()
static int getMin(int m, int n) {
    return (m <= n) ? m : n;
}

static list_t chop_first(list_t list, unsigned int n) {
    // REQUIRES: "list" has at least n elements.
    // EFFECTS: Returns the list equal to "list" without its first nelements.
    if (n == 0) {
        return list;
    }
    return chop_first(list_rest(list), n - 1);
}

int size(list_t list) {
    if (list_isEmpty(list)) {
        return 0;
    }
    return size(list_rest(list)) + 1;
}

int sum(list_t list) {
    if (list_isEmpty(list)) {
        return 0;
    }
    return sum(list_rest(list)) + list_first(list);
}

int product(list_t list) {
    if (list_isEmpty(list)) {
        return 1;
    }
    return product(list_rest(list)) * list_first(list);
}

int accumulate(list_t list, int (*fn)(int, int), int base) {
    if (list_isEmpty(list)) {
        return base;
    }
    return fn(list_first(list), accumulate(list_rest(list), fn, base));
}

list_t reverse(list_t list) {
    if (list_isEmpty(list)) {
        return list_make();
    }
    // Append the initial first value to the end of the list
    return append(reverse(list_rest(list)), list_make(list_first(list), list_make()));
}

list_t append(list_t first, list_t second) {
    if (list_isEmpty(first)) {
        return second;
    }
    else {
        // Append the first value of list **first** to the rest of the list and list **second**
        return list_make(list_first(first), append(list_rest(first), second));
    }
}

list_t filter_odd(list_t list) {
    if (list_isEmpty(list)) {
        return list_make();
    }
    if (isOdd(list_first(list))) {
        // Append the first value of the list to the rest of the filtered list.
        return append(list_make(list_first(list), list_make()), filter_odd(list_rest(list)));
    }
    else {
        return filter_odd(list_rest(list));
    }
}

list_t filter_even(list_t list) {
    if (list_isEmpty(list)) {
        return list_make();
    }
    if (isEven(list_first(list))) {
        return append(list_make(list_first(list), list_make()), filter_even(list_rest(list)));
    }
    else {
        return filter_even(list_rest(list));
    }
}

list_t filter(list_t list, bool (*fn)(int)) {
    if (list_isEmpty(list)) {
        return list_make();
    }
    if (fn(list_first(list))) {
        return append(list_make(list_first(list), list_make()),
                      filter(list_rest(list), fn));
    }
    else {
        return filter(list_rest(list), fn);
    }
}

list_t insert_list(list_t first, list_t second, unsigned int n) {
    list_t first_right = chop_first(first, n);
    list_t first_left = reverse(chop_first(reverse(first), (size(first) - n)));
    return append(append(first_left, second), first_right);
}

list_t chop(list_t list, unsigned int n) {
    list = reverse(list);
    // first reverse, then chop first n elements, then reverse back
    list = chop_first(list, n);
    list = reverse(list);
    return list;
}

int tree_sum(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return 0;
    }
    return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

bool tree_search(tree_t tree, int key) {
    if (tree_isEmpty(tree)) {
        return false;
    }
    return tree_search(tree_left(tree), key) || tree_search(tree_right(tree), key) || tree_elt(tree) == key;
}

int depth(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return 0;
    }
    return 1 + getMax(depth(tree_left(tree)), depth(tree_right(tree)));
}

int tree_min(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return MAX_INT;
    }
    return getMin(tree_elt(tree), getMin(tree_min(tree_right(tree)), tree_min(tree_left(tree))));
}

list_t traversal(tree_t tree) {
    if (tree_isEmpty(tree)) {
        return list_make();
    }
    return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

bool tree_hasPathSum(tree_t tree, int sum) {
    if (tree_isEmpty(tree)) {
        return false;
    }
    else if (tree_elt(tree) == sum && tree_isEmpty(tree_right(tree)) && tree_isEmpty(tree_left(tree))) {
        return true;
    }
    return (tree_hasPathSum((tree_left(tree)), sum - tree_elt(tree)) || tree_hasPathSum((tree_right(tree)), sum - tree_elt(tree)));
}

bool covered_by(tree_t A, tree_t B) {
    if (tree_isEmpty(A)) {
        return true;
    }
    if (tree_isEmpty(B)) {
        return false;
    }
    return covered_by(tree_left(A), tree_left(B)) && covered_by(tree_right(A), tree_right(B)) && tree_elt(A) == tree_elt(B);
}

bool contained_by(tree_t A, tree_t B) {
    if (covered_by(A, B)) {
        return true;
    }
    if (tree_isEmpty(B)) {
        return false;
    }
    return contained_by(A, tree_left(B)) || contained_by(A, tree_right(B));
}

tree_t insert_tree(int elt, tree_t tree) {
    if (tree_isEmpty(tree)) {
        return tree_make(elt, tree_make(), tree_make());
    }
    if (elt < tree_elt(tree)) {
        return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
    }
    else {
        return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
    }
}