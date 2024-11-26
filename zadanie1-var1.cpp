#include <iostream>
#include <string>
#include "structures/stack.hpp"

using namespace std;

// арифметические операции между двумя числами
int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        default:
            cout << "error: invalid operation '" << op << "'" << endl;
            exit(1); 
    }
}

// приоритет
int precedence(char op) {
    if (op == '+' || op == '-') return 1;  
    if (op == '*') return 2;               
    return 0;
}

// Выполняет операцию из стека операторов над двумя верхними числами из стека значений
void performOperation(Stack<int>* values, Stack<char>* ops) {
    if (values->head == nullptr || values->head->next == nullptr) {
        cout << "error: insufficient operands for operation" << endl;
        exit(1);
    }
    int b = values->head->data; pop_stack(values); 
    int a = values->head->data; pop_stack(values); 
    char op = ops->head->data; pop_stack(ops);     
    push_stack(values, applyOperation(a, b, op)); 
}

// вычисление значения выражения
int evaluate(Stack<int>* values, Stack<char>* ops, const string& expression) {
    for (size_t i = 0; i < expression.length(); i++) {
        char ch = expression[i];

        if (ch == ' ') continue;
        
        if (isdigit(ch)) { 
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0'); 
                i++;
            }
            i--;
            push_stack(values, value);
        }
        else if (ch == '(') {
            push_stack(ops, ch);
        }
        else if (ch == ')') {
            while (ops->head != nullptr && ops->head->data != '(') {
                performOperation(values, ops);
            }
            if (ops->head != nullptr) pop_stack(ops); 
        }
        else if (ch == '+' || ch == '-' || ch == '*') {
            while (ops->head != nullptr && precedence(ops->head->data) >= precedence(ch)) {
                performOperation(values, ops);
            }
            push_stack(ops, ch);
        }
        else {
            cout << "error: invalid character " << ch << endl;
            exit(1);
        }
    }

    while (ops->head != nullptr) {
        performOperation(values, ops);
    }

    if (values->head != nullptr && values->head->next == nullptr) {
        return values->head->data;
    } else {
        cout << "error: expression could not be evaluated" << endl;
        exit(1);
    }
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);

    Stack<int> values;
    Stack<char> ops;

    int result = evaluate(&values, &ops, expression);
    cout << "Result: " << result << endl;
    return 0;
}