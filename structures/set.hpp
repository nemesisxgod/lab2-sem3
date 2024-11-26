#include <iostream>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 100;

// Узел связного списка для разрешения коллизий
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T value, Node<T>* nextNode = nullptr) : data(value), next(nextNode) {}
};

// Хэш-таблица
template <typename T>
struct HashSet {
    Node<T>* table[TABLE_SIZE]; // массив указателей на начало списков

    HashSet() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
};

template <typename T>
T hashFunction(T value) {
    return abs(value) % TABLE_SIZE; // остаток от деления
}

// Добавление элемента в множество
template <typename T>
void add(HashSet<T>& set, int value) {
    int index = hashFunction(value);
    Node<T>* current = set.table[index];
    
    // Проверяем, есть ли уже элемент
    while (current != nullptr) {
        if (current->data == value) {
            cout << "Element " << value << " already exists in the set." << endl;
            return;
        }
        current = current->next;
    }
    
    // Если элемента нет, добавляем в начало списка
    Node<T>* newNode = new Node{value, set.table[index]};
    set.table[index] = newNode;
}

// Удаление элемента из множества
template <typename T>
void remove(HashSet<T>& set, int value) {
    int index = hashFunction(value);
    Node<T>* current = set.table[index];
    Node<T>* prev = nullptr;

    // Ищем элемент в списке
    while (current != nullptr && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Element " << value << " not found in the set." << endl;
        return;
    }

    // Удаляем элемент
    if (prev == nullptr) {
        set.table[index] = current->next; // Удаляем из головы списка
    } else {
        prev->next = current->next; // Удаляем из середины/конца списка
    }
    delete current;
}

// Проверка наличия элемента в множестве
template <typename T>
bool contains(const HashSet<T>& set, int value) {
    int index = hashFunction(value);
    Node<T>* current = set.table[index];

    while (current != nullptr) {
        if (current->data == value) {
            return true; // Элемент найден
        }
        current = current->next;
    }

    return false; // Элемент не найден
}

// Печать множества
template <typename T>
void printSet(const HashSet<T>& set) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node<T>* current = set.table[i];
        if (current != nullptr) {
            while (current != nullptr) {
                cout << current->data << " ";
                current = current->next;
            }
        }
    }
}

// Освобождение памяти
template <typename T>
void freeSet(HashSet<T>& set) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node<T>* current = set.table[i];
        while (current != nullptr) {
            Node<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        set.table[i] = nullptr;
    }
}

template <typename T>
void load_from_file_hash(HashSet<T> set, const string& filename){
    ifstream file(filename); 
    if (!file.is_open()){ 
        cout<<"file isnot found" << endl;
        return;
    }

    freeSet(set);

    string value;
    while (file >> value) {
        add(set, stoi(value));
    }

    file.close();
}

template <typename T>
void upload_to_file_hash(HashSet<T> set, const string& filename){
    ofstream file(filename);
    if (!file.is_open()) {
            cout << "File not found" << endl;
            return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node<T>* current = set.table[i];
        while (current) {
            file << current->data << endl;
            current = current->next;
        }
    }

    file.close();
}