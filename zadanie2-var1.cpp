#include <iostream>
#include "set.hpp"

using namespace std;

void processQuery(HashSet<int>& set, const string& query, const string& filePath) {
    if (query.substr(0, 6) == "SETADD") {
        int value = stoi(query.substr(7));
        add(set, value);
        upload_to_file_hash(set, filePath); 
    } 
    else if (query.substr(0, 6) == "SETDEL") {
        int value = stoi(query.substr(7));
        remove(set, value);
        upload_to_file_hash(set, filePath);  
    } 
    else if (query.substr(0, 6) == "SET_AT") {
        int value = stoi(query.substr(7));
        if (contains(set, value)) {
            cout << value << " is in the set." << endl;
        } else {
            cout << value << " is not in the set." << endl;
        }
    } else {
        cout << "Invalid command." << endl;
    }
}

int main(int argc, char* argv[]) {
    string filePath = argv[2];
    string query = argv[4];

    HashSet<int> set;

    // Загрузка данных из файла
    ifstream file(filePath);
    if (!file) {
        cerr << "Error: Could not open file " << filePath << endl;
        return 1;
    }

    int value;
    while (file >> value) {
        add(set, value);
    }
    file.close();

    // Выполнение команды
    processQuery(set, query, filePath);

    return 0;
}