#include <iostream>
#include "structures/array.hpp"
#include <string>

using namespace std;

void generateSubsets(DynamicArray& arr, DynamicArray& current, int index, int depth) {
    if (current.size == depth) {
        print_array(current);
        return;
    }

    for (int i = index; i < arr.size; ++i) {
        push_back_array(current, arr.data[i]);       // добавляем в текущее
        generateSubsets(arr, current, i + 1, depth); // рекурсия для некст элемента
        pop_back_array(current);                    // убираем элемент из текущего
    }
}

void printSubs(DynamicArray& arr) {
    cout << "{}" << endl; 
    DynamicArray current;
    current.data = new string[current.capacity]; // Инициализация массива
    for (int depth = 1; depth <= arr.size; ++depth) {
        generateSubsets(arr, current, 0, depth);
    }
    free_array(current);
}

int main() {
    DynamicArray S;
    load_from_file_array(S, "array.txt");

    printSubs(S);

    free_array(S);
}