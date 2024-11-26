#include <iostream>
#include <cmath>
using namespace std;

// Структура узла дерева
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция поиска минимального узла в правом поддереве
TreeNode* findMin(TreeNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Рекурсивная функция для удаления узла
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root; // Если дерево пустое

    // Ищем узел с заданным значением
    if (key < root->value) {
        root->left = deleteNode(root->left, key); // Ищем в левом поддереве
    } else if (key > root->value) {
        root->right = deleteNode(root->right, key); // Ищем в правом поддереве
    } else {
        // Узел найден
        // Случай 1: У узла нет потомков
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // Случай 2: У узла только один потомок
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // Случай 3: У узла два потомка
        TreeNode* temp = findMin(root->right); // Минимальный узел в правом поддереве
        root->value = temp->value; // Заменяем значение
        root->right = deleteNode(root->right, temp->value); // Удаляем заменённый узел
    }
    return root;
}

// Вставка элемента в дерево
TreeNode* insert(TreeNode* root, int value) {
    if (root == nullptr) return new TreeNode(value);
    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    return root;
}

// Обход дерева (инфиксный)
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;
    inorderTraversal(root->left);
    cout << root->value << " ";
    inorderTraversal(root->right);
}

int height_tree(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return max(height_tree(node->left), height_tree(node->right)) + 1;
}

void print_lvl(TreeNode* root, int level) {
    if (root == nullptr) {
        return;
    }
    
    int width = pow(2, height_tree(root)) - 1;
    int spacesCnt = width / 2;
    string spacesBefore(spacesCnt, ' ');
    string spacesAfter(spacesCnt + 1, ' ');
    
    
    if (level == 1) {
        cout << spacesBefore << root->value << spacesAfter; // Вывод значения узла
    } else {
        print_lvl(root->left, level - 1);  // Обход левого поддерева
        print_lvl(root->right, level - 1); // Обход правого поддерева
    }
}
 
// Функция для вывода дерева в виде "змейки"
void print_tree(TreeNode* root) {
    int height = height_tree(root); // Определяем высоту дерева

    for (int i = 1; i <= height; i++) {
        print_lvl(root, i); // Выводим узлы на текущем уровне
        cout << endl; // Переход на новую строку после каждого уровня
    }
}

int main() {
    TreeNode* root = nullptr;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    cout << "Дерево до удаления: " << endl;
    print_tree(root);
    cout << endl;

    // Удаление узла
    root = deleteNode(root, 50); // Удаляем корень

    cout << "Дерево после удаления: " << endl;
    print_tree(root);
    cout << endl;

    return 0;
}