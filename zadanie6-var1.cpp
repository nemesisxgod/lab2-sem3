#include <iostream>
#include "structures/hashtable.hpp"
#include <string>
using namespace std;

bool areIsomorphic(const string& str1, const string& str2) {
    // Если строки разной длины, они не могут быть изоморфными
    if (str1.length() != str2.length()) {
        return false;
    }

    NodeH* table1[TABLE_SIZE] = {nullptr}; // Хэш-таблица для первой строки
    NodeH* table2[TABLE_SIZE] = {nullptr}; // Хэш-таблица для второй строки

    // Проходим по символам строк
    for (size_t i = 0; i < str1.length(); ++i) {
        // Проверяем отображение символов из первой строки
        NodeH* node1 = search_hash(table1, string(1, str1[i]));
        if (node1 == nullptr) {
            push_hash(table1, string(1, str1[i]), string(1, str2[i]));  // Добавляем новое отображение
        } else if (node1->value != string(1, str2[i])) {
            return false;  // Если уже существует неправильное соответствие
        }

        // Проверяем отображение символов из второй строки
        NodeH* node2 = search_hash(table2, string(1, str2[i]));
        if (node2 == nullptr) {
            push_hash(table2, string(1, str2[i]), string(1, str1[i]));  // Добавляем новое отображение
        } else if (node2->value != string(1, str1[i])) {
            return false;  // Если уже существует неправильное соответствие
        }
    }

    return true;  // Если все проверки прошли успешно, строки изоморфны
}

int main() {
    string str1 = "lall";
    string str2 = "redd";

    if (areIsomorphic(str1, str2)) {
        cout << "Строки " << str1 << " и " << str2 << " изоморфны" << endl;
    } else {
        cout << "Строки " << str1 << " и " << str2 << " не изоморфны" << endl;
    }

    return 0;
}