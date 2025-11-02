#include <iostream>

void countPositiveElements(const int* arr, int size, int& count) {
    count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            count++;
        }
    }
}

void LowestPositiveElements(const int* arrA, int size, const int* arrB) {
    int countA = 0, countB = 0;
    countPositiveElements(arrA, size, countA);
    countPositiveElements(arrB, size, countB);
    if (countA < countB) {
        std::cout << "Массив A имеет меньше положительных элементов: " << countA << std::endl;
        std::cout << "Элементы массива A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
        std::cout << "\n";
        std::cout << "Элементы массива B: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrB[i] << " ";
        }
    }
    else {
        std::cout << "Массив B имеет меньше положительных элементов: " << countB << std::endl;
        std::cout << "Элементы массива B: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrB[i] << " ";
        }
        std::cout << "\n";
        std::cout << "Элементы массива A: ";
        for (int i = 0; i < size; i++) {
            std::cout << arrA[i] << " ";
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "");
    int* A = new int[5]; 
    int* B = new int[5]; 

    std::cout << "Введите 5 элементов для массива A:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cin >> A[i];
    }

    std::cout << "Введите 5 элементов для массива B:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cin >> B[i];
    }

    LowestPositiveElements(A, 5, B);

    return 0;
}
