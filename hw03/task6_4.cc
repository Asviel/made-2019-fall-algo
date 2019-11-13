// Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной
// N. Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если
// root->Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое
// поддерево root. Рекурсия запрещена. Выведите элементы в порядке level-order
// (по слоям, “в ширину”).

// Формат ввода
// В первой строке записано число N.
// Во последующих N строках — целые числа исходной последовательности.

// Формат вывода
// N целых чисел, разделенных пробелом.

#include <cassert>
#include <iostream>
#include <queue>

class BinaryTree {
 public:
  BinaryTree();
  ~BinaryTree();

  bool Insert(int key);
  void PrintInLevelOrder() const;

 private:
  struct BinaryTreeNode {
    int key;
    BinaryTreeNode* left = nullptr;
    BinaryTreeNode* right = nullptr;

    explicit BinaryTreeNode(int key) : key(key) {}
  };

  static void DeleteNode(BinaryTreeNode* node);

  BinaryTreeNode* root_ = nullptr;
};

BinaryTree::BinaryTree() = default;

BinaryTree::~BinaryTree() { DeleteNode(root_); }

bool BinaryTree::Insert(int key) {
  if (!root_) {
    root_ = new BinaryTreeNode(key);
    return true;
  }

  BinaryTreeNode* current = root_;
  while (true) {
    if (key < current->key) {
      if (current->left) {
        current = current->left;
      } else {
        current->left = new BinaryTreeNode(key);
        break;
      }
    } else {
      if (current->right) {
        current = current->right;
      } else {
        current->right = new BinaryTreeNode(key);
        break;
      }
    }
  }

  return true;
}

void BinaryTree::PrintInLevelOrder() const {
  if (!root_) return;

  // Для запоминания порядка вывода узлов
  std::queue<BinaryTreeNode*> queue;
  queue.push(root_);

  while (!queue.empty()) {
    BinaryTreeNode* current = queue.front();
    queue.pop();

    std::cout << current->key << ' ';

    if (current->left) queue.push(current->left);
    if (current->right) queue.push(current->right);
  }
}

void BinaryTree::DeleteNode(BinaryTree::BinaryTreeNode* node) {
  if (!node) return;

  // Удалять будем в level-order. Т.к. не храним parent'ов, нужно не потерять
  // потомков после удаления родителя.
  std::queue<BinaryTreeNode*> queue;
  queue.push(node);

  while (!queue.empty()) {
    BinaryTreeNode* current = queue.front();
    queue.pop();

    if (current->left) queue.push(current->left);
    if (current->right) queue.push(current->right);

    delete current;
  }
}

int main() {
  int N;
  BinaryTree b_tree;

  std::cin >> N;
  assert(N > 0);

  for (int i = 0; i < N; ++i) {
    int key;
    std::cin >> key;
    b_tree.Insert(key);
  }

  b_tree.PrintInLevelOrder();

  return 0;
}
