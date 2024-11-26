#include <iostream>
#include <fstream>

using namespace std;

// Шаблонный узел стека
template <typename T>
struct NodeS {
    T data;
    NodeS* next;
};

// Шаблонный стек
template <typename T>
struct Stack {
    NodeS<T>* head = nullptr;
};

// Шаблонная функция для добавления в стек
template <typename T>
void push_stack(Stack<T>* stack, const T& data) {
    NodeS<T>* newNode = new NodeS<T>{data, nullptr};
    newNode->next = stack->head;
    stack->head = newNode;
}

// Шаблонная функция для удаления из стека
template <typename T>
void pop_stack(Stack<T>* stack) {
    if (stack->head == nullptr) {
        cout << "stack is empty" << endl;
        return;
    }

    NodeS<T>* newHead = stack->head->next;
    delete stack->head;
    stack->head = newHead;
}

// Шаблонная функция для печати стека
template <typename T>
void print_stack(Stack<T>* stack) {
    if (stack->head == nullptr) {
        return;
    }

    NodeS<T>* current = stack->head;
    
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Шаблонная функция для очистки стека
template <typename T>
void free_stack(Stack<T>* stack) {
    if (!stack) return;
    while (stack->head) {
        pop_stack(stack);
    }
}