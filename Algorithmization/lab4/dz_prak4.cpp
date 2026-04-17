#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

using Clock = std::chrono::high_resolution_clock;

struct ResultRow {
    int size;
    double sequential;
    double parallel2;
    double parallel4;
    double parallel8;
};

const int SMALL_SORT_THRESHOLD = 32;
const int PARALLEL_THRESHOLD = 10000;

int partition_lomuto(std::vector<int>& arr, int low, int high) {
    const int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort_sequential(std::vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }

    if (high - low + 1 <= SMALL_SORT_THRESHOLD) {
        std::sort(arr.begin() + low, arr.begin() + high + 1);
        return;
    }

    int pivot_index = partition_lomuto(arr, low, high);
    quicksort_sequential(arr, low, pivot_index - 1);
    quicksort_sequential(arr, pivot_index + 1, high);
}

void quicksort_parallel(std::vector<int>& arr, int low, int high, int num_threads) {
    if (low >= high) {
        return;
    }

    if (high - low + 1 <= SMALL_SORT_THRESHOLD) {
        std::sort(arr.begin() + low, arr.begin() + high + 1);
        return;
    }

    if (num_threads <= 1 || (high - low + 1) < PARALLEL_THRESHOLD) {
        quicksort_sequential(arr, low, high);
        return;
    }

    int pivot_index = partition_lomuto(arr, low, high);

    int left_threads = num_threads / 2;
    int right_threads = num_threads - left_threads;

    std::thread left_thread([&arr, low, pivot_index, left_threads]() {
        quicksort_parallel(arr, low, pivot_index - 1, left_threads);
        });

    quicksort_parallel(arr, pivot_index + 1, high, right_threads);
    left_thread.join();
}

std::vector<int> generate_random_array(int size, int min_value = 0, int max_value = 1000000) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_value, max_value);

    std::vector<int> arr(size);
    for (int& value : arr) {
        value = dist(gen);
    }
    return arr;
}

double measure_sequential_time(const std::vector<int>& source, int repeats = 3) {
    double total_seconds = 0.0;

    for (int i = 0; i < repeats; ++i) {
        std::vector<int> arr = source;

        auto start = Clock::now();
        quicksort_sequential(arr, 0, static_cast<int>(arr.size()) - 1);
        auto finish = Clock::now();

        if (!std::is_sorted(arr.begin(), arr.end())) {
            std::cerr << "Ошибка: последовательная сортировка выполнилась неверно.\n";
            std::exit(1);
        }

        std::chrono::duration<double> elapsed = finish - start;
        total_seconds += elapsed.count();
    }

    return total_seconds / repeats;
}

double measure_parallel_time(const std::vector<int>& source, int num_threads, int repeats = 3) {
    double total_seconds = 0.0;

    for (int i = 0; i < repeats; ++i) {
        std::vector<int> arr = source;

        auto start = Clock::now();
        quicksort_parallel(arr, 0, static_cast<int>(arr.size()) - 1, num_threads);
        auto finish = Clock::now();

        if (!std::is_sorted(arr.begin(), arr.end())) {
            std::cerr << "Ошибка: параллельная сортировка выполнилась неверно.\n";
            std::exit(1);
        }

        std::chrono::duration<double> elapsed = finish - start;
        total_seconds += elapsed.count();
    }

    return total_seconds / repeats;
}

void print_table_1(const std::vector<ResultRow>& results) {
    std::cout << "\nТаблица 1. Реальные замеры времени выполнения\n";
    std::cout << std::fixed << std::setprecision(6);

    std::cout << std::left
        << std::setw(12) << "Размер"
        << std::setw(16) << "БС (с)"
        << std::setw(22) << "БС_П 2 потока (с)"
        << std::setw(22) << "БС_П 4 потока (с)"
        << std::setw(22) << "БС_П 8 потоков (с)"
        << '\n';

    for (const auto& row : results) {
        std::cout << std::left
            << std::setw(12) << row.size
            << std::setw(16) << row.sequential
            << std::setw(22) << row.parallel2
            << std::setw(22) << row.parallel4
            << std::setw(22) << row.parallel8
            << '\n';
    }
}

void print_table_2(const std::vector<ResultRow>& results) {
    std::cout << "\nТаблица 2. Коэффициенты ускорения\n";
    std::cout << std::fixed << std::setprecision(6);

    std::cout << std::left
        << std::setw(12) << "Размер"
        << std::setw(16) << "БС (с)"
        << std::setw(22) << "БС_П 2 потока (с)"
        << std::setw(22) << "БС_П 4 потока (с)"
        << std::setw(22) << "БС_П 8 потоков (с)"
        << std::setw(16) << "Speedup 2"
        << std::setw(16) << "Speedup 4"
        << std::setw(16) << "Speedup 8"
        << '\n';

    for (const auto& row : results) {
        double speedup2 = row.sequential / row.parallel2;
        double speedup4 = row.sequential / row.parallel4;
        double speedup8 = row.sequential / row.parallel8;

        std::cout << std::left
            << std::setw(12) << row.size
            << std::setw(16) << row.sequential
            << std::setw(22) << row.parallel2
            << std::setw(22) << row.parallel4
            << std::setw(22) << row.parallel8
            << std::setw(16) << speedup2
            << std::setw(16) << speedup4
            << std::setw(16) << speedup8
            << '\n';
    }
}

int main() {
    std::vector<int> sizes = {
        1000,
        5000,
        20000,
        50000,
        75000,
        100000
    };

    std::vector<ResultRow> results;

    std::cout << "Запуск эксперимента...\n";

    for (int size : sizes) {
        std::cout << "Обработка массива размером " << size << "...\n";

        std::vector<int> source = generate_random_array(size);

        double sequential_time = measure_sequential_time(source);
        double parallel2_time = measure_parallel_time(source, 2);
        double parallel4_time = measure_parallel_time(source, 4);
        double parallel8_time = measure_parallel_time(source, 8);

        results.push_back({
            size,
            sequential_time,
            parallel2_time,
            parallel4_time,
            parallel8_time
            });
    }

    print_table_1(results);
    print_table_2(results);

    return 0;
}
