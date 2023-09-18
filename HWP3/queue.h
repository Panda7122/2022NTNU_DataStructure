#ifndef _QUEUE_H
#define _QUEUE_H
#include <iostream>

#include "list.h"
template <class T>
class Queue {
   private:
    List<T> arr;

   public:
    void push(const T& val) { arr.push_back(val); }
    void pop() { arr.pop_front(); }
    T& front() { return arr.front(); }
    T& back() { return arr.back(); }
    int32_t size() { return arr.size(); }
    bool empty() { return arr.empty(); }
};
#endif