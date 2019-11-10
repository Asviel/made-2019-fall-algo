/*
  Дана очень длинная последовательность целых чисел длины n. Требуется вывести
  в отсортированном виде её первые k элементов. Последовательность может не
  помещаться в память. Время работы O(n * log(k)). Память O(k).
  Использовать слияние.
*/

#include <cassert>
#include <iostream>
#include <vector>

void merge(std::vector<int> &arr1, std::vector<int> &arr2);
void insertion_sort(std::vector<int> &arr);

int main() {
  int n, k;

  std::cin >> n >> k;
  assert(n > 0);
  assert(k > 0 && k <= n);

  std::vector<int> output;  // Далее будем сохранять результаты merge в этом массиве
  std::vector<int> temp;    // Этот массив будем использовать в качестве "напарника"

  // Вводим первые k элементов в output
  for (int i = 0; i < k; ++i) {
    int in;
    std::cin >> in;
    output.push_back(in);
  }
  insertion_sort(output);

  for (int i = k; i < n; i += k) {
    // На случай, если n mod k != 0, чтобы не считать пустой поток
    int border = std::min(k, n - i);
    for (int j = 0; j < border; ++j) {
      int in;
      std::cin >> in;
      temp.push_back(in);
    }

    insertion_sort(temp);
    merge(output, temp);
    temp.clear();
  }

  for (auto it = output.begin(); it != output.end(); ++it)
    std::cout << *it << " ";

  return 0;
}

void merge(std::vector<int> &arr1, std::vector<int> &arr2) {
  std::vector<int> tmp;
  const int arr1_size = arr1.size();
  const int arr2_size = arr2.size();
  int i = 0;
  int j = 0;

  while (i < arr1_size && j < arr2_size && tmp.size() < arr1_size) {
    if (arr1[i] <= arr2[j]) {
      tmp.push_back(arr1[i]);
      ++i;
    } else {
      tmp.push_back(arr2[j]);
      ++j;
    }
  }

  if (tmp.size() == arr1_size) {
    arr1 = tmp;
    return;
  }

  if (i == arr1_size)
    while (j < arr2_size && tmp.size() < arr1_size) {
      tmp.push_back(arr2[j]);
      ++j;
    }
  else
    while (i < arr1_size && tmp.size() < arr1_size) {
      tmp.push_back(arr1[i]);
      ++i;
    }

  arr1 = tmp;
}

void insertion_sort(std::vector<int> &arr) {
  for (int i = 1; i < arr.size(); ++i) {
    int t = arr[i];

    int j = i - 1;
    for (; j >= 0 && t < arr[j]; --j) arr[j + 1] = arr[j];

    arr[j + 1] = t;
  }
}