#ifndef _LIST_H
#define _LIST_H
#include <iostream>
template <class T>
class List {
   public:
    struct node {
        T val;
        node *next, *pref;
    };
    node first;
    int32_t SIZE;
    List() {
        first.next = &first;
        first.pref = &first;
        first.val = '\0';
        SIZE = 0;
    }
    void insert(node* locate, const T& val) {
        node* newnode;
        newnode = new node;
        newnode->val = val;
        locate->next->pref = newnode;
        newnode->next = locate->next;
        locate->next = newnode;
        newnode->pref = locate;
        ++SIZE;
    }
    void erase(node* locate) {
        if (locate == &first) return;
        locate->next->pref = locate->pref;
        locate->pref->next = locate->next;
        --SIZE;
        delete locate;
    }
    void push_back(const T& val) { insert(first.pref, val); }
    void push_front(const T& val) { insert(&first, val); }
    void pop_back() { erase(first.pref); }
    void pop_front() { erase(first.next); }
    T& back() { return first.pref->val; }
    T& front() { return first.next->val; };
    int32_t size() { return SIZE; }
    bool empty() { return (SIZE == 0); }
    void clear() {
        while (SIZE) {
            erase(first.pref);
        }
    }
};

#endif