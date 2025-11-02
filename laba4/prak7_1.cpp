#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>
#include <iterator>

void arifm_mean_sets_intersection(std::set<int> A, std::set<int> B) {
    std::set<int> a_b;
    std::set_intersection(
        A.begin(), A.end(),
        B.begin(), B.end(),
        std::inserter(a_b, a_b.begin())
    );
    if (a_b.empty()) {
        std::cout << "Пересечение множеств пусто" << std::endl;
        return;
    }
    int c = 0;
    for (const auto& element : a_b) {
        c += element;
    }
    std::cout << "Среднее арифметическое элементов пересечения: "
        << static_cast<double>(c) / a_b.size() << std::endl;
}

int main() {
    std::set<int> A;
    std::set<int> B;
    int x;

    std::cout << "Введите элементы множества A (0 для завершения):" << std::endl;
    while (std::cin >> x && x != 0) {
        A.insert(x);
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Введите элементы множества B (0 для завершения):" << std::endl;
    while (std::cin >> x && x != 0) {
        B.insert(x);
    }

    arifm_mean_sets_intersection(A, B);

    return 0;
}