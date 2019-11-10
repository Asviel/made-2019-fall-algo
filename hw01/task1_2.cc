/*
    Реализовать дек с динамическим зацикленным буфером, обрабатывающий команды
    push*, pop*.

    Формат входных данных
    В первой строке количество команд n. n ≤ 1000000
    Каждая команда задаётся как 2 целых числа: a b
    a = 1 - push front
    a = 2 - pop front
    a = 3 - push back
    a = 4 - pop back
    Если дана команда pop*, то число b - ожидаемое значение. Если команда pop
    вызвана для пустой структуры данных, то ожидается “-1”.

    Формат выходных данных.
    Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если
    хотя бы одно ожидание не оправдалось, то напечатать NO.
*/

#include <cassert>
#include <iostream>

class Deque {
  int *buff;
  int size;
  int front;
  int back;

  bool is_empty();
  bool is_only_one();
  void increase_buff();

 public:
  Deque();
  ~Deque();

  bool push_front(int element);
  bool push_back(int element);
  int pop_front();
  int pop_back();
};

int main() {
  int n, a, b;
  bool ans = true;
  Deque deque = Deque();

  std::cin >> n;
  assert(n > 0);

  for (int i = 0; i < n; i++) {
    std::cin >> a >> b;
    assert(a == 1 || a == 2 || a == 3 || a == 4);

    switch (a) {
      case 1:
        deque.push_front(b);
        break;
      case 2:
        ans = (deque.pop_front() == b);
        break;
      case 3:
        deque.push_back(b);
        break;
      case 4:
        ans = (deque.pop_back() == b);
        break;
    }

    if (!ans) {
      std::cout << "NO";
      return 0;
    }
  }

  std::cout << "YES";
  return 0;
}

Deque::Deque() : size(4), front(-1), back(-1) { buff = new int[size]; }

Deque::~Deque() { delete[] buff; }

bool Deque::push_front(int element) {
  if (is_empty()) {
    front++;
    back++;
    buff[front] = element;
  } else {
    // Т.к в C++ (-1 % 2 == -1), нужен + size для корректного перехода в конец
    // массива. Взятие остатка нужно, если уменьшение на 1 не привело к
    // отрицательному front
    if ((front - 1 + size) % size == back) increase_buff();

    front = (front - 1 + size) % size;
    buff[front] = element;
  }

  return true;
}

bool Deque::push_back(int element) {
  if (is_empty()) {
    front++;
    back++;
    buff[back] = element;
  } else {
    if ((back + 1) % size == front) increase_buff();

    back = (back + 1) % size;
    buff[back] = element;
  }

  return true;
}

int Deque::pop_front() {
  if (is_empty()) {
    return -1;
  } else {
    int element = buff[front];

    if (is_only_one())
      front = back = -1;
    else
      front = (front + 1) % size;

    return element;
  }
}

int Deque::pop_back() {
  if (is_empty()) {
    return -1;
  } else {
    int element = buff[back];

    if (is_only_one())
      front = back = -1;
    else
      back = (back - 1 + size) % size;

    return element;
  }
}

bool Deque::is_empty() { return front == -1 && back == -1 ? true : false; }

bool Deque::is_only_one() { return front == back ? true : false; }

void Deque::increase_buff() {
  int *temp_buff = new int[size * 2];

  for (int i = 0; i < size; i++, front++) temp_buff[i] = buff[front % size];

  front = 0;
  back = size - 1;
  size *= 2;

  delete[] buff;
  buff = temp_buff;
}
