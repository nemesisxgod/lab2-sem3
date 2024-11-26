#include <iostream>
#include <numeric>
#include "structures/set.hpp"
#include <algorithm>

using namespace std;

// Рекурсивная функция для проверки разбиения на k подмножеств
bool canPartitionKSubsets(const int* nums, int size, int k, int target, int currentSum, int index, HashSet<int>& included, HashSet<int> subsets[]) {
    if (k == 0) {
        return true; // Все подмножества найдены
    }

    if (currentSum == target) {
        // Когда подмножество с нужной суммой найдено, начинаем искать следующее подмножество
        return canPartitionKSubsets(nums, size, k - 1, target, 0, 0, included, subsets);
    }

    for (int i = index; i < size; ++i) {
        if (!contains(included, nums[i]) && currentSum + nums[i] <= target) {
            add(included, nums[i]);
            add(subsets[k - 1], nums[i]);  // Добавляем элемент в подмножество

            if (canPartitionKSubsets(nums, size, k, target, currentSum + nums[i], i + 1, included, subsets)) {
                return true;
            }

            remove(included, nums[i]);  // Откатываем изменения
            remove(subsets[k - 1], nums[i]);  // Убираем элемент из текущего подмножества
        }
    }

    return false; // Если не удалось найти подходящее разбиение
}

void printSubsets(HashSet<int> subsets[], int k) {
    cout << "Подмножества с равной суммой:" << endl;
    for (int i = 0; i < k; ++i) {
        cout<<'{';
        printSet(subsets[i]);  // Печать каждого подмножества
        cout<<'}'<<endl;
    }
}

int main() {
    cout << "Введите количество элементов в множестве: ";
    int size;
    cin >> size;

    int* elements = new int[size]; // Массив для хранения элементов
    cout << "Введите элементы множества (натуральные числа):" << endl;
    for (int i = 0; i < size; ++i) {
        cin >> elements[i];
    }

    int sum = accumulate(elements, elements + size, 0);

    // Перебор от 2 до size подмножеств
    for (int k = 2; k <= size; ++k) {
        if (sum % k == 0) { // Проверка делимости суммы на k
            int target = sum / k;
            HashSet<int> included; // Хеш-таблица для отслеживания включенных элементов
            HashSet<int> subsets[k]; // Массив подмножеств

            if (canPartitionKSubsets(elements, size, k, target, 0, 0, included, subsets)) {
                printSubsets(subsets, k);
                delete[] elements;
                return 0; // Завершаем, как только нашли решение
            }
        }
    }

    cout << "Невозможно разбить множество на подмножества с равной суммой." << endl;
    delete[] elements;
    return 0;
}
