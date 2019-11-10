/*
  Решение предполагает использование кучи

  На вокзале есть некоторое количество тупиков, куда прибывают электрички.
  Этот вокзал является их конечной станцией. Дано расписание движения
  электричек, в котором для каждой электрички указано время ее прибытия, а
  также время отправления в следующий рейс. Электрички в расписании упорядочены
  по времени прибытия. Когда электричка прибывает, ее ставят в свободный тупик
  с минимальным номером. При этом если электричка из какого-то тупика
  отправилась в момент времени X, то электричку, которая прибывает в момент
  времени X, в этот тупик ставить нельзя, а электричку, прибывающую в момент
  X+1 — можно. В данный момент на вокзале достаточное количество тупиков для
  работы по расписанию.

  Напишите программу, которая по данному расписанию определяет, какое
  минимальное количество тупиков требуется для работы вокзала.

  Формат входных данных
  Вначале вводится n - количество электричек в расписании. Затем вводится n
  строк для каждой электрички, в строке - время прибытия и время отправления.
  Время - натуральное число от 0 до 10^9. Строки в расписании упорядочены по
  времени прибытия.

  Формат выходных данных
  Натуральное число - минимальное количеством тупиков.

  Максимальное время: 50мс, память: 5Мб.
*/

#include <cassert>
#include <iostream>
#include <vector>

class MinHeap {
  std::vector<int> data;

  void sift_up(int idx);
  void sift_down(int idx);

 public:
  MinHeap();
  ~MinHeap();

  bool push(int element);
  int pop();
  int get_min() const;
  int get_size() const;
};

int main() {
  int n;
  int ans = 0;
  MinHeap min_heap = MinHeap();

  std::cin >> n;
  assert(n > 0);

  for (int i = 0; i < n; i++) {
    int a, b;
    std::cin >> a >> b;
    assert(a >= 0);
    assert(b >= 0);

    while (min_heap.get_size() && a > min_heap.get_min()) min_heap.pop();
    min_heap.push(b);

    if (ans < min_heap.get_size()) ans = min_heap.get_size();
  }

  std::cout << ans;
  return 0;
}

MinHeap::MinHeap() {}

MinHeap::~MinHeap() {}

bool MinHeap::push(int element) {
  data.push_back(element);
  sift_up(data.size() - 1);
  return true;
}

int MinHeap::pop() {
  int element = data[0];
  std::swap(data[0], data.back());
  data.pop_back();
  sift_down(0);
  return element;
}

int MinHeap::get_min() const { return data[0]; }
int MinHeap::get_size() const { return data.size(); }

void MinHeap::sift_up(int idx) {
  while (data[idx] < data[(idx - 1) / 2] && idx != 0) {
    std::swap(data[idx], data[(idx - 1) / 2]);
    idx = (idx - 1) / 2;
  }
}

void MinHeap::sift_down(int idx) {
  int left_idx = 2 * idx + 1;
  int right_idx = 2 * idx + 2;

  // Нет сыновей
  if (left_idx >= data.size()) return;

  // Один сын
  if (right_idx >= data.size()) {
    if (data[idx] > data[left_idx]) std::swap(data[idx], data[left_idx]);
    return;
  }

  // Выбор минимального из 2-х сыновей
  if (data[idx] > std::min(data[left_idx], data[right_idx])) {
    int min_idx = data[left_idx] < data[right_idx] ? left_idx : right_idx;
    std::swap(data[idx], data[min_idx]);
    sift_down(min_idx);
  }

}
