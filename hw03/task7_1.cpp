#include <iostream>
#include <cassert>

class Treap {
 public:
  Treap() = default;
  ~Treap() { DeleteSubtree(root_); }

  void Insert(int key, int value);
  int FindValue(int key);
  int FindKey(int value);
  void Delete(int key);

 private:
  struct TreapNode {
    TreapNode() : key(0), value(1), priority(0) {}
    TreapNode(int key, int priority) : key(key), value(1), priority(priority) {};

    int key;
    int value; // Хранит кол-во элементов в ноде
    int priority;
    TreapNode* left = nullptr;
    TreapNode* right = nullptr;
  };

  static void Split(TreapNode* node, int key, TreapNode*& left, TreapNode*& right);
  static TreapNode* Merge(TreapNode* left, TreapNode* right);

  static int FixValue(TreapNode* node);
  static int getLeftValue(TreapNode* node) { return node->left ? node->left->value : 0; };

  static void DeleteSubtree(TreapNode* node);

  TreapNode* root_ = nullptr;
};

// При первом не рекурсивном вызове Split, в качестве left и right нужно использовать new TreapNode* (!! Т.е. не node->left и node->right !!)
void Treap::Split(Treap::TreapNode* node, int key, Treap::TreapNode*& left, Treap::TreapNode*& right) {
  if (!node) {
    left = right = nullptr;
  } else if (node->key <= key) {
    Split(node->right, key, node->right, right);
    left = node;
    node->value = FixValue(node);
  } else {
    Split(node->left, key, left, node->left);
    right = node;
    node->value = FixValue(node);
  }
}

Treap::TreapNode* Treap::Merge(Treap::TreapNode* left, Treap::TreapNode* right) {
  if (!left || !right) return left ? left : right;

  if (left->priority > right->priority) {
    left->right = Merge(left->right, right);
    left->value = FixValue(left);
    return left;
  } else {
    right->left = Merge(left, right->left);
    right->value = FixValue(right);
    return right;
  }
}

void Treap::Insert(int key, int value) {
  if (!root_) {
    root_ = new TreapNode(key, value);
  } else {
    // Деревья под Split
    TreapNode* t1 = new TreapNode();
    TreapNode* t2 = new TreapNode();
    Split(root_, key, t1, t2);

    TreapNode* new_node = new TreapNode(key, value);
    root_ = Merge(Merge(t1, new_node), t2);
  }
}

int Treap::FindValue(int key) {
  TreapNode* current = root_;
  int key_idx = 0;

  while (current->key != key) {
    if (key < current->key) {
      current = current->left;
    } else {
      key_idx += getLeftValue(current) + 1;
      current = current->right;
    }
  }
  key_idx += getLeftValue(current) + 1;

  return root_->value - key_idx;
}

int Treap::FindKey(int value) {
  if (!root_) return -1;

  TreapNode* current = root_;
  int current_value = getLeftValue(current);

  while (current_value != value) {
    if (current_value < value) {
      value -= current_value + 1;
      current = current->right;
    } else {
      current = current->left;
    }
  }

  return current->value;
}

void Treap::Delete(int key) {
  if (!root_) return;

  // Деревья под Split
  TreapNode* t1 = new TreapNode();
  TreapNode* t2 = new TreapNode();
  TreapNode* to_delete = new TreapNode();

  Split(root_, key, t1, t2);
  Split(t1, key - 1, t1, to_delete);
  root_ = Merge(t1, t2);

  delete to_delete;
}

int Treap::FixValue(Treap::TreapNode* node) {
  int left_value = node->left ? node->left->value : 0;
  int right_value = node->right ? node->right->value : 0;

  return left_value + right_value + 1;
}

void Treap::DeleteSubtree(Treap::TreapNode* node) {
  if (node) {
    DeleteSubtree(node->left);
    DeleteSubtree(node->right);
    delete node;
  }
}

int main() {
  int n;
  Treap treap;

  std::cin >> n;
  assert(n > 0);

  srand(time(nullptr));
  for (int i = 0; i < n; ++i) {
    int command, value;

    std::cin >> command >> value;
    assert(command == 1 || command == 2);

    if (command == 1) {
      treap.Insert(value, rand());
      std::cout << treap.FindValue(value) << std::endl;
    } else {
      treap.Delete(treap.FindKey(value));
    }
  }

//  treap.Insert(100, 15);
//  treap.Insert(90, 8);
//  treap.Insert(80, 3);
//  treap.Insert(70, 1);
//  treap.Insert(85, 1);
//  treap.Insert(95, 4);
//  treap.Insert(92, 2);
//  treap.Insert(97, 1);
//  treap.Insert(93, 1);
//  treap.Insert(105, 6);
//  treap.Insert(110, 5);
//  treap.Insert(107, 3);
//  treap.Insert(106, 1);
//  treap.Insert(108, 1);
//  treap.Insert(111, 1);
//  treap.Insert(109, -1);
//  srand(time(nullptr));
//  treap.Insert(100, rand());
//  treap.Insert(90, rand());
//  treap.Insert(80, rand());
//  treap.Insert(70, rand());
//  treap.Insert(85, rand());
//  treap.Insert(95, rand());
//  treap.Insert(92, rand());
//  treap.Insert(97, rand());
//  treap.Insert(93, rand());
//  treap.Insert(105, rand());
//  treap.Insert(110, rand());
//  treap.Insert(107, rand());
//  treap.Insert(106, rand());
//  treap.Insert(108, rand());
//  treap.Insert(111, rand());
//  treap.Insert(96, rand());

  return 0;
}
