#include "pch.h"
#include "CppUnitTest.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

double f(double x)
{
    if (x <= 4.0)
        return x - 3.0;
    else
        return -x + 5.0;
}

double simpson_rule(double (*func)(double), double a, double b, int n)
{
    if (n % 2 == 1) n++;

    double h = (b - a) / n;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i += 2)
        sum += 4 * func(a + i * h);

    for (int i = 2; i < n; i += 2)
        sum += 2 * func(a + i * h);

    return (h / 3.0) * sum;
}

double calculate_area(int N)
{
    return simpson_rule(f, 3.0, 4.0, N) +
        simpson_rule(f, 4.0, 5.0, N);
}

namespace UnitTestProject1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        const double exact = 1.0;
        const double epsilon = 1e-7;

        TEST_METHOD(Test_N2)
        {
            double result = calculate_area(2);
            Assert::AreEqual(exact, result, epsilon,
                L"Ошибка при N = 2");
        }

        TEST_METHOD(Test_N10)
        {
            double result = calculate_area(10);
            Assert::AreEqual(exact, result, epsilon,
                L"Ошибка при N = 10");
        }

        TEST_METHOD(Test_N50)
        {
            double result = calculate_area(50);
            Assert::AreEqual(exact, result, epsilon,
                L"Ошибка при N = 50");
        }

        TEST_METHOD(Test_N100)
        {
            double result = calculate_area(100);
            Assert::AreEqual(exact, result, epsilon,
                L"Ошибка при N = 100");
        }
    };
}