#pragma once

#ifdef SCALARDLL_EXPORTS
#define SCALARDLL_API __declspec(dllexport) // Если компилируем DLL
#else
#define SCALARDLL_API __declspec(dllimport) // Если используем DLL
#endif

extern "C" {
    // Функция принимает количество итераций (для теста скорости) и размер вектора
    // Возвращает время выполнения в секундах (float)
    SCALARDLL_API double scalar_proizv(double* v1, double* v2, int size, int iterations);
}