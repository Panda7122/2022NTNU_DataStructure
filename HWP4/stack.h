#ifndef _STACK_H
#define _STACK_H
#include <iostream>

#include "list.h"
template <class T>
class Stack {
   private:
    List<T> arr;

   public:
    void push(const T& val) { arr.push_back(val); }
    void pop() { arr.pop_back(); }
    T& top() { return arr.back(); }
    int32_t size() { return arr.size(); }
    bool empty() { return arr.empty(); }
};
#endif