#include "ShittyStack.hpp"
#include <stdexcept>
#include <iostream>

ShittyStack::ShittyStack() {
    dummy_head = new ListNode(":)");
    dummy_tail = new ListNode(":(");
    dummy_head->next = dummy_tail;
    dummy_tail->prev = dummy_head;
    size = 0;
}

ShittyStack::~ShittyStack() {
    while (!empty()) {
        pop();
    }
    delete dummy_head;
    delete dummy_tail;
}

void ShittyStack::push(std::string x) {
    ListNode* new_node = new ListNode(x, dummy_head->next, dummy_head);
    dummy_head->next->prev = new_node;
    dummy_head->next = new_node;
    size++;
}

std::string ShittyStack::pop() {
    if (empty()) {
        throw std::runtime_error("pop() called on empty stack");
        return "";
    }
    ListNode* top_node = dummy_head->next;
    std::string top_val = top_node->val;
    dummy_head->next = top_node->next;
    top_node->next->prev = dummy_head;
    delete top_node;
    size--;
    return top_val;
}

std::string ShittyStack::peek() {
    if (empty()) {
        throw std::runtime_error("peek() called on empty stack");
        return "";
    }
    return dummy_head->next->val;
}

bool ShittyStack::empty() {
    return size == 0 || (dummy_head->next == dummy_tail && dummy_tail->prev == dummy_head);
}

/* int main() {
    ShittyStack stack;
    stack.push("hello");
    stack.push("world");
    stack.push("foo");
    while (!stack.empty()) {
        std::cout << stack.pop() << std::endl;
    }
} */