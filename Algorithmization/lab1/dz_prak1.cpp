#include <iostream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

// Функция добавления элемента в конец массива
int* addToEnd(int* arr, int size, int value)
{
    int* newArr = new int[size + 1];

    for (int i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }

    newArr[size] = value;

    delete[] arr;

    return newArr;
}

int main()
{
    vector<int> sizes = { 10, 100, 1000, 10000, 50000, 100000, 200000, 300000, 400000, 500000 };

    cout << "Size\tTime (ms)\n";

    for (int size : sizes)
    {
        int* arr = new int[size];

        for (int i = 0; i < size; i++)
            arr[i] = i;

        auto start = high_resolution_clock::now();

        arr = addToEnd(arr, size, 999);

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - start);

        cout << size << "\t" << duration.count() << endl;

        delete[] arr;
    }

    return 0;
}