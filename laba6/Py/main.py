import ctypes
from ctypes import CDLL
import random
import time
import os

dll_name = './dll_dz_C.dll'  
if not os.path.exists(dll_name):
    print(f"Ошибка: Файл {dll_name} не найден!")
    exit()

cpp_lib = CDLL(dll_name)

# --- PYTHON РЕАЛИЗАЦИЯ ---
def mult(v1, v2):
    return sum(x * y for x, y in zip(v1, v2))

def python_test(v1, v2, iterations):
    start_time = time.time()
    for _ in range(iterations):
        result = mult(v1, v2)
    end_time = time.time()  
    return end_time - start_time

# --- C++ РЕАЛИЗАЦИЯ ---
def cpp_test(v1, v2, size, iterations):
    scalar_func = cpp_lib.scalar_proizv
    
    scalar_func.restype = ctypes.c_double
    scalar_func.argtypes = [ctypes.POINTER(ctypes.c_double), 
                            ctypes.POINTER(ctypes.c_double), 
                            ctypes.c_int, 
                            ctypes.c_int]

    v1_c_array = (ctypes.c_double * size)(*v1)
    v2_c_array = (ctypes.c_double * size)(*v2)

    time_taken = scalar_func(v1_c_array, v2_c_array, size, iterations)
    
    return time_taken

if __name__ == "__main__":
    VECTOR_SIZE = 1000  
    ITERATION_TESTS = [10000, 50000, 100000]

    vec1 = [random.random() for _ in range(VECTOR_SIZE)]
    vec2 = [random.random() for _ in range(VECTOR_SIZE)]

    results = []
    
    print(f"Загружена библиотека: {dll_name}")
    print(f"Тестируемая функция C++: scalar_proizv")
    print("-" * 50)

    for iters in ITERATION_TESTS:
        print(f"Тест: {iters} итераций...")

        # Запускаем C++
        try:
            cpp_time = cpp_test(vec1, vec2, VECTOR_SIZE, iters)
            print(f"Время C++:    {cpp_time:.4f} с")
        except OSError as e:
            print(f"ОШИБКА вызова C++: {e}")
            print("Скорее всего, аргументы в C++ коде не совпадают с Python.")
            break
        
        # Запускаем Python
        py_time = python_test(vec1, vec2, iters)
        print(f"Время Python: {py_time:.4f} с")
        
        results.append([iters, round(cpp_time, 4), round(py_time, 4)])
        print("-" * 30)

    if results:
        print("\nИтоговая таблица:")
        print(f"{'№':<3} {'Итераций':<12} {'C++ (с)':<10} {'Python (с)':<10}") 
        c = 0
        for i in results:
            c += 1
            print(f"{c:<3} {i[0]:<12} {i[1]:<10} {i[2]:<10}")