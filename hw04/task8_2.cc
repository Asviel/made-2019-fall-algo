// Реализуйте структуру данных типа “множество строк” на основе динамической
// хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из
// строчных латинских букв. Хеш-функция строки должна быть реализована с помощью
// вычисления значения многочлена методом Горнера. Начальный размер таблицы
// должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов
// в случае, когда коэффициент заполнения таблицы достигает 3/4. Структура
// данных должна поддерживать операции добавления строки в множество, удаления
// строки из множества и проверки принадлежности данной строки множеству.

// Для разрешения коллизий используйте двойное хеширование.

// Формат входных данных
// Каждая строка входных данных задает одну операцию над множеством. Запись
// операции состоит из типа операции и следующей за ним через пробел строки, над
// которой проводится операция. Тип операции  – один из трех символов:
// +  означает добавление данной строки в множество;
// -  означает удаление  строки из множества;
// ?  означает проверку принадлежности данной строки множеству.
// При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в
// этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он
// присутствует в этом множестве.

// Формат выходных данных
// Программа должна вывести для каждой операции одну из двух строк OK или FAIL,
// в зависимости от того, встречается ли данное слово в нашем множестве

#include <cassert>
#include <iostream>
#include <string>

const int kDefaultCapacity = 8;
const double kThreshold = 0.75;
const std::string kDeletedKeyTag = "<D>";

class HashTable {
 public:
  HashTable();
  ~HashTable() { delete[] table_; };

  bool Add(const std::string& key);
  bool Remove(const std::string& key);
  bool Has(const std::string& key) const;

 private:
  static int Hash(const std::string& key, int module);
  static int Probe(const std::string& key, int module) { return (key.size() * 2 + 1) % module; };

  void Grow();

  std::string* table_;
  int capacity_;
  double threshold_;
  double load_factor_;
};

int main() {
  HashTable table;

  char command;
  std::string value;
  while (std::cin >> command >> value) {
    switch (command) {
      case '?':
        std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
        break;
      case '+':
        std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
        break;
      case '-':
        std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
        break;
      default:
        assert(false);
    }
  }

  return 0;
}

HashTable::HashTable() {
  capacity_ = kDefaultCapacity;
  threshold_ = kThreshold;
  load_factor_ = 0.;
  table_ = new std::string[capacity_];
}

bool HashTable::Add(const std::string& key) {
  assert(!key.empty());

  if (load_factor_ >= threshold_) Grow();

  int hash = Hash(key, capacity_);
  int probe = Probe(key, capacity_);

  // У нас всегда будет свободная ячейка, т.к. выше проверяли коэффициент
  // заполнения, потому можем смело ставить цикл while.
  int idx = hash;
  while (!table_[idx].empty()) {
    if (table_[idx] == key) return false;
    idx = (idx + probe) % capacity_;
  }
  table_[idx] = key;
  load_factor_ += 1. / capacity_;

  return true;
}

bool HashTable::Remove(const std::string& key) {
  assert(!key.empty());

  int hash = Hash(key, capacity_);
  int probe = Probe(key, capacity_);

  int idx = hash;
  while (!table_[idx].empty()) {
    if (table_[idx] == key) {
      table_[idx] = kDeletedKeyTag;
      return true;
    };
    idx = (idx + probe) % capacity_;
  }

  return false;
}

bool HashTable::Has(const std::string& key) const {
  assert(!key.empty());

  int hash = Hash(key, capacity_);
  int probe = Probe(key, capacity_);

  int idx = hash;
  while (!table_[idx].empty()) {
    if (table_[idx] == key) return true;
    idx = (idx + probe) % capacity_;
  }

  return false;
}

int HashTable::Hash(const std::string& key, int module) {
  int hash = 0;
  int a = 73;

  // Взятие остатка происходит каждую итерацию для защиты от переполнения.
  for (char ch : key) hash = (hash * a + ch) % module;

  return hash;
}

void HashTable::Grow() {
  int old_capacity = capacity_;
  std::string* old_table = table_;

  capacity_ += capacity_;
  load_factor_ = 0.;
  std::string* new_table = new std::string[capacity_];
  table_ = new_table;

  for (int i = 0; i < old_capacity; ++i)
    if (!old_table[i].empty() && old_table[i] != kDeletedKeyTag)
      Add(old_table[i]);

  delete[] old_table;
}
