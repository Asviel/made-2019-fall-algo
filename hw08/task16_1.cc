// Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки ­– n
// (p <= 30000, n <= 300000). Время O(n + p), доп. память – O(p).
// Использовать префикс-функцию (алгоритм Кнута-Морриса-Пратта).

// Формат ввода
// В первой строке записан шаблон. Во второй - текст.

// Формат вывода
// Позиции вхождения шаблона в тексте.

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> Kmp(const std::string& pattern, const std::string& text);
std::vector<int> Prefix(const std::string& s);

int main() {
  std::string pattern, text;

  std::cin >> pattern;
  std::cin >> text;
  assert(!pattern.empty() || !text.empty());

  std::vector<int> occurrences = Kmp(pattern, text);
  for (const int& occurrence : occurrences) std::cout << occurrence << ' ';

  return 0;
}

std::vector<int> Kmp(const std::string& pattern, const std::string& text) {
  std::vector<int> occurrences;
  auto pi_values = Prefix(pattern);

  int pi = 0;
  for (int i = 0; i < text.length(); ++i) {
    while (pi > 0 && text[i] != pattern[pi]) pi = pi_values[pi - 1];

    if (text[i] == pattern[pi]) ++pi;

    if (pi == pattern.length()) {
      occurrences.push_back(i - pi + 1);
      pi = pi_values[pi - 1];
    }
  }

  return occurrences;
}

std::vector<int> Prefix(const std::string& s) {
  std::vector<int> pi_values(s.length());
  pi_values[0] = 0;

  int pi = 0;
  for (int i = 1; i < s.length(); ++i) {
    while (pi > 0 && s[i] != s[pi]) pi = pi_values[pi - 1];

    if (s[i] == s[pi]) ++pi;
    pi_values[i] = pi;
  }

  return pi_values;
}
