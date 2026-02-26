#include "pch.h"
#include "CppUnitTest.h"
#include "../dz_prak1/dz_prak1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(AddToEndTests)
    {
    public:

        TEST_METHOD(AddElement_NormalArray) // Обычное добавление
        {
            int size = 3;
            int* arr = new int[size] {1, 2, 3};

            arr = addToEnd(arr, size, 10);

            Assert::AreEqual(1, arr[0]);
            Assert::AreEqual(2, arr[1]);
            Assert::AreEqual(3, arr[2]);
            Assert::AreEqual(10, arr[3]);

            delete[] arr;
        }

        TEST_METHOD(AddElement_EmptyArray) // Работа при size = 0
        {
            int size = 0;
            int* arr = new int[size];

            arr = addToEnd(arr, size, 5);

            Assert::AreEqual(5, arr[0]);

            delete[] arr;
        }

        TEST_METHOD(AddElement_NegativeValue) // Корректность для отрицательных чисел
        {
            int size = 2;
            int* arr = new int[size] {7, 8};

            arr = addToEnd(arr, size, -1);

            Assert::AreEqual(7, arr[0]);
            Assert::AreEqual(8, arr[1]);
            Assert::AreEqual(-1, arr[2]);

            delete[] arr;
        }

        TEST_METHOD(AddElement_LargeArray) // Работа на больших массивах
        {
            int size = 1000;
            int* arr = new int[size];

            for (int i = 0; i < size; i++)
                arr[i] = i;

            arr = addToEnd(arr, size, 9999);

            for (int i = 0; i < size; i++)
                Assert::AreEqual(i, arr[i]);

            Assert::AreEqual(9999, arr[size]);

            delete[] arr;
        }
    };
}
