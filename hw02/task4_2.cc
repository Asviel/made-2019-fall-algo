/*
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9]
 * размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число,
 * которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 * Напишите нерекурсивный алгоритм. Требования к дополнительной памяти: O(n).
 * Требуемое среднее время работы: O(n).
 *
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию
 * Partition реализуйте методом прохода двумя итераторами от конца массива к
 * началу.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int partition(std::vector<int> &vector, int first, int last);

int main() {
  int n, k;

  std::cin >> n >> k;
  assert(n > 0);
  assert(k >= 0 && k < n);

  std::vector<int> data;

  for (int i = 0; i < n; ++i) {
    int in;
    std::cin >> in;
    data.push_back(in);
  }

  int first = 0;
  int last = data.size() - 1;
  int found_idx = partition(data, first, last);

  while (found_idx != k) {
    if (found_idx < k) {
      first = found_idx + 1;
      found_idx = partition(data, first, last);
    } else {
      last = found_idx - 1;
      found_idx = partition(data, first, last);
    }
  }
  std::cout << data[found_idx];
  return 0;
}

int partition(std::vector<int> &vector, int first, int last) {
  if (first == last) return first;

  int mid = first + (last - first) / 2;

  // Выбор медианы трех в качестве опорного. В pivot будем хранить индекс
  // опорного для swap.
  int pivot;
  std::vector<int> tmp;
  tmp.push_back(vector[first]);
  tmp.push_back(vector[mid]);
  tmp.push_back(vector[last]);

  std::sort(tmp.begin(), tmp.end());
  int median = tmp[1];

  if (vector[first] == median)
    pivot = first;
  else if (vector[mid] == median)
    pivot = mid;
  else
    pivot = last;
  std::swap(vector[pivot], vector[first]);

  int i = last;
  int j = last;

  // Будем делить на строго меньшие и больше или равные элементы
  for (; j > first;) {
    if (vector[j] < vector[first])
      --j;
    else {
      std::swap(vector[i], vector[j]);
      --i;
      --j;
    }
  }
  std::swap(vector[i], vector[first]);

  return i;
}