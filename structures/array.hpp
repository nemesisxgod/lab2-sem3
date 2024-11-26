#include <iostream>
#include <fstream>

using namespace std;

 
struct DynamicArray{
    string* data = nullptr; 
    size_t size = 0;
    size_t capacity = 1;
};

 
void increase_array(DynamicArray& array){
    size_t newCapacity = array.capacity*2;
    string* newData = new string[newCapacity];

    for (size_t i=0; i<array.size; i++){
        newData[i] = array.data[i];
    }

    delete[] array.data;

    array.data=newData;         //перекидываем указатель на новый массив
    array.capacity=newCapacity;
} 

 
void push_back_array(DynamicArray& array, const string& value){
    if (array.size==array.capacity){
        increase_array(array);
    }

    array.data[array.size]=value;
    array.size++;
}

 
void push_in_array(DynamicArray& array, const string& value, const int index){
    if (index<0 or index>=array.size){
        cout<<"invalid index"<<endl;
        return;
    }

    if (array.size==array.capacity){
        increase_array(array);
    }

    for (size_t i=array.size; i>index; i--){
        array.data[i] = array.data[i-1];
    }
    array.data[index] = value;
    array.size++;
}

 
void pop_back_array(DynamicArray& array){
    if (array.size>0){
        array.size--;
    }
    else { 
        cout<<"array is empty"<<endl;
    }
}

 
void pop_at_array(DynamicArray& array, const int index){
    if (index<0 or index>=array.size){
        cout<<"invalid index"<<endl;
        return;
    }

    for (size_t i=index; i<array.size-1; i++){
        array.data[i] = array.data[i+1];
    }
    array.size--;
}

 
void search_array(DynamicArray& array, const string& value){
    for (size_t i=0; i<array.size; i++){
        if (array.data[i]==value){
            cout<<"index is "<<i<<endl;
            return;
        }
    }
    cout<<"not found"<<endl;
}

 
void search_by_index_array(DynamicArray& array, const int index){
    if (index<0 or index>=array.size){
        cout<<"invalid index"<<endl;
        return;
    }
    else {
        cout<<array.data[index]<<endl;
    }
}   

 
void set_array (DynamicArray& array, const string& value, const int index){
    if (index<0 or index>=array.size){
        cout<<"invalid index"<<endl;
        return;
    }
    else {
        array.data[index] = value;
    }
}

 
void print_array (DynamicArray& array){
    if (array.size == 0)return; 
    for (size_t i=0; i<array.size; i++){
        cout<<array.data[i]<<' ';
    }
    cout<<endl;
}

 
void free_array(DynamicArray& array) {
    if (array.data != nullptr) {  // Проверка, что указатель не является нулевым
        delete[] array.data;
        array.data = nullptr;  // Установка указателя в nullptr после удаления
    }
    array.size = 0;
    array.capacity = 0;
}

 
void load_from_file_array(DynamicArray& array, const string& filename){
     if (array.data != nullptr){
        free_array(array);  // Освобождение памяти, если массив уже инициализирован
    }
    array.size = 0;
    array.capacity = 10;  // Начальная емкость
    array.data = new std::string[array.capacity];
    ifstream file(filename);
    if (!file.is_open()){
        cout<<"file isnot found" << endl;
        return;
    }

    string stroka;
    while(getline(file, stroka)){
        push_back_array(array, stroka);    
    }

    file.close();
}

 
void upload_to_file_array(DynamicArray& array, const string& filename){
    ofstream file(filename);
    if (!file.is_open()) {
            cout << "File not found" << endl;
            return;
        }

    for (size_t i = 0; i < array.size; i++) {
        file << array.data[i] << endl;
    }

    file.close();
}

