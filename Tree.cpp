#include <iostream> // pupupu
#include <vector>
#include <string>
#include <algorithm>
#include <clocale>
#include <windows.h>
#include <iomanip>
using namespace std;

struct Tree {
    int info;
    string fio;
    Tree* left, * right;
} *root;

Tree* CreateTree(int inf, string surn) {
    Tree* t = new Tree;
    t->info = inf;
    t->fio = surn;
    t->left = t->right = nullptr;
    return t;
}

void AddTree(Tree*& root, int key, string surn) {
    if (root == nullptr) {
        root = CreateTree(key, surn);
        return;
    }
    Tree* t = root;
    while (true) {
        if (key == t->info) {
            cout << "Duplicate!";
            return;
        }
        if (key < t->info) {
            if (t->left == nullptr) {
                t->left = CreateTree(key, surn);
                return;
            }
            t = t->left;
        }
        else {
            if (t->right == nullptr) {
                t->right = CreateTree(key, surn);
                return;
            }
            t = t->right;
        }
    }
}

Tree* DeleteTree(Tree* root, int key) {
    Tree* Del, * PrevDel, * PrevR;
    Del = root;
    PrevDel = nullptr;
    while (Del != nullptr && Del->info != key) {
        PrevDel = Del;
        if (key < Del->info) Del = Del->left;
        else Del = Del->right;
    }

    if (Del == nullptr) {
        cout << "Key not found" << endl;
        return root;
    }

    Tree* R = nullptr;
    if (Del->right == nullptr) R = Del->left;
    else if (Del->left == nullptr) R = Del->right;
    else {
        PrevR = Del;
        R = Del->right;
        while (R->left != nullptr) { //поиск мин в правом дереве
            PrevR = R;
            R = R->left;
        }
        if (PrevR != Del) {
            PrevR->left = R->right;
            R->right = Del->right;
        }
        R->left = Del->left;
    }

    if (Del == root) root = R;
    else if (Del->info < PrevDel->info) PrevDel->left = R;
    else PrevDel->right = R;

    delete Del;
    return root;
}

void ViewTree(Tree* p, int level) {
    string str;
    if (p) {
        ViewTree(p->right, level + 1);

        for (int i = 0; i < level; i++)
            str = str + "    ";
        cout << str << p->fio << " " << p->info << endl;

        ViewTree(p->left, level + 1);
    }
}
void BalanceTree(Tree** root, int k, int n, vector<int>& a, vector<string>& s) {
    if (n == k) {
        *root = nullptr;
        return;
    }
    else {
        int m = (n + k) / 2;
        *root = new Tree;
        (*root)->info = a[m];
        (*root)->fio = s[m];
        BalanceTree(&(*root)->left, k, m, a, s);
        BalanceTree(&(*root)->right, m + 1, n, a, s);
    }
}

void FreeTree(Tree* root) {
    if (root != nullptr) {
        FreeTree(root->left);
        FreeTree(root->right);
        delete root;
    }
}

void PostOrderTree(Tree* root) {
    if (root == nullptr) return;
    PostOrderTree(root->left);
    PostOrderTree(root->right);
    cout << root->fio << " " << root->info << "; ";
}

void InOrderTree(Tree* root) {
    if (root == nullptr) return;
    InOrderTree(root->left);
    cout << root->fio << " " << root->info << "; ";
    InOrderTree(root->right);
}

void PreOrderTree(Tree* root) {
    if (root == nullptr) return;
    cout << root->fio << " " << root->info << "; ";
    PreOrderTree(root->left);
    PreOrderTree(root->right);
}

string SearchTree(Tree* root, int key) {
    while (root != nullptr && root->info != key) {
        if (key < root->info) root = root->left;
        else root = root->right;
    }
    return root ? root->fio : "Not Found";
}

int CountTreeLeaves(Tree* root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return CountTreeLeaves(root->left) + CountTreeLeaves(root->right);
}
void StoreNodes(Tree* root, vector<int>& keys, vector<string>& values) {
    if (!root) return;
    StoreNodes(root->left, keys, values);
    keys.push_back(root->info);
    values.push_back(root->fio);
    StoreNodes(root->right, keys, values);
}

void BalanceTreeWrapper(Tree*& root) {
    vector<int> keys;
    vector<string> values;
    StoreNodes(root, keys, values);
    BalanceTree(&root, 0, keys.size(), keys, values);
}
void PrintBalancedTree(Tree* root, int level = 0) {
    if (root == nullptr) return;

    PrintBalancedTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        cout << "    ";
    cout << root->fio << " " << root->info << endl;

    PrintBalancedTree(root->left, level + 1);
}
void SwapMinMax(Tree* root) {
    if (!root || (!root->left && !root->right)) {
        cout << "Недостаточно узлов для обмена" << endl;
        return;
    }

    Tree* min = root;
    while (min->left) {
        min = min->left;
    }

    Tree* max = root;
    while (max->right) {
        max = max->right;
    }


    swap(min->info, max->info);
    swap(min->fio, max->fio);

    cout << "Обмен выполнен: " << min->info << " ↔ " << max->info << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    int key;
    string fio;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Просмотреть дерево\n";
        cout << "4. Поиск элемента\n";
        cout << "5. Сбалансировать дерево\n";
        cout << "6. Прямой обход (Pre-order)\n";
        cout << "7. Симметричный обход (In-order)\n";
        cout << "8. Обратный обход (Post-order)\n";
        cout << "9. Количество листьев\n";
        cout << "10. Обмен min/max\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Введите ключ: ";
            cin >> key;
            cout << "Введите ФИО: ";
            cin.ignore();
            getline(cin, fio);
            AddTree(root, key, fio);
            break;
        }
        case 2: {
            cout << "Введите ключ для удаления: ";
            cin >> key;
            root = DeleteTree(root, key);
            break;
        }
        case 3: {
            cout << "Текущее дерево:\n";
            ViewTree(root, 0);
            break;
        }
        case 4: {
            cout << "Введите ключ для поиска: ";
            cin >> key;
            string result = SearchTree(root, key);
            cout << "Результат поиска: " << (result == "Not Found" ? "Не найдено" : result) << endl;
            break;
        }
        case 5: {
            BalanceTreeWrapper(root);
            cout << "Дерево сбалансировано. Новое дерево:\n";
            PrintBalancedTree(root);
            break;
        }
        case 6: {
            cout << "Прямой обход (Pre-order):\n";
            PreOrderTree(root);
            cout << "\n";
            break;
        }
        case 7: {
            cout << "Симметричный обход (In-order):\n";
            InOrderTree(root);
            cout << "\n";
            break;
        }
        case 8: {
            cout << "Обратный обход (Post-order):\n";
            PostOrderTree(root);
            cout << "\n";
            break;
        }
        case 9: {
            cout << "Количество листьев: " << CountTreeLeaves(root) << endl;
            break;
        }
        case 10: {
            SwapMinMax(root);
            cout << "Дерево после обмена min/max:\n";
            ViewTree(root, 0);
            break;
        }
        case 0: {
            FreeTree(root);
            cout << "Программа завершена\n";
            return 0;
        }
        default: {
            cout << "Неверный выбор!\n";
            break;
        }
        }
    }
}
