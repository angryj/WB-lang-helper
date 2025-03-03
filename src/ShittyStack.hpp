#ifndef SHITTYSTACK_HPP
#define SHITTYSTACK_HPP

#include <string>

class ListNode {
public:
    std::string val;
    ListNode *next;
    ListNode *prev;
    ListNode(std::string x) : val(x), next(nullptr), prev(nullptr) {}
    ListNode(std::string x, ListNode* next, ListNode* prev) : val(x), next(next), prev(prev) {}
};

class ShittyStack {
private:
    ListNode* dummy_head; // dummy_head->next is the top of the stack
    ListNode* dummy_tail; // dummy_tail->prev is the bottom of the stack
    int size;
public:
    ShittyStack();
    ~ShittyStack();
    void push(std::string x);
    std::string pop();
    std::string peek();
    bool empty();
    
    // rule of five
    /* ShittyStack(const ShittyStack& other) = delete;
    ShittyStack& operator=(const ShittyStack& other) = delete;
    ShittyStack(ShittyStack&& other) = delete;
    ShittyStack& operator=(ShittyStack&& other) = delete; */
};
#endif