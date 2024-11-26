#include <iostream>
#include <fstream>

using namespace std;

const int TABLE_SIZE = 10; // Размер хэш-таблицы

struct NodeH {
    string key;
    string value;
    NodeH* next;
};

// Функция хэширования
int hash_function(const string& key) {
    size_t hash = 2566341;
    for (auto c : key) {
        hash += 31 * c;
    }   
    return hash % TABLE_SIZE;  // Возвращаем индекс в пределах размера таблицы
}

// Функция вставки в хэш-таблицу
void push_hash(NodeH* table[], const string& key, const string& value) {
    int index = hash_function(key);
    NodeH* newNode = new NodeH;
    newNode->key = key;
    newNode->value = value;
    newNode->next = nullptr;

    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        NodeH* temp = table[index];
        while (temp->next != nullptr) {
            if (temp->key == key) {
                temp->value = value;
                delete newNode;  // Если ключ уже существует, обновляем значение
                return;
            }
            temp = temp->next;
        }
        temp->next = newNode;  // Вставляем новый узел в конец цепочки
    }
}

// Функция поиска в хэш-таблице
NodeH* search_hash(NodeH* table[], const string& key) {
    int index = hash_function(key);
    NodeH* temp = table[index];
    while (temp != nullptr) {
        if (temp->key == key) {
            return temp;  // Возвращаем указатель на узел, если ключ найден
        }
        temp = temp->next;
    }
    return nullptr;  // Если не найдено
}

 
void pop_hash(NodeH* table[], const string& key) {
    int index = hash_function(key) % TABLE_SIZE;
    NodeH* temp = table[index];
    NodeH* prev = nullptr;

    while (temp != nullptr) {
        if (temp->key == key) {
            // Если элемент найден, удаляем его
            if (prev == nullptr) {
                // Если удаляем первый элемент в цепочке
                table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Key not found!" << endl;
}

 
void print_hash(NodeH* table[]) {
    bool isEmpty = true;

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != nullptr) {
            isEmpty = false;
            break;
        }
    }

    if (isEmpty) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "Table[" << i << "]: ";
        NodeH* temp = table[i];
        while (temp != nullptr) {
            cout << "{" << temp->key << ": " << temp->value << "} -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }
}

 
void clear_hash(NodeH* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        NodeH* current = table[i];
        while (current) {
            NodeH* temp = current;
            current = current->next;
            delete temp; // Освобождаем память
        }
        table[i] = nullptr; // Обнуляем указатели
    }
}

 
void load_from_file_hash(NodeH* table[], const string& filename){
    ifstream file(filename); 
    if (!file.is_open()){ 
        cout<<"file isnot found" << endl;
        return;
    }

    clear_hash(table);

    string key, value;
    while (file >> key >> value) {
        push_hash(table, key, value);
    }

    file.close();
}

 
void upload_to_file_hash(NodeH* table[], const string& filename){
    ofstream file(filename);
    if (!file.is_open()) {
            cout << "File not found" << endl;
            return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        NodeH* current = table[i];
        while (current) {
            file << current->key << " " << current->value << endl;
            current = current->next;
        }
    }

    file.close();
}

