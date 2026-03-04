#include <iostream>
#include <cmath>

// Функция области
double f(double x)
{
    if (x <= 4.0)
        return x - 3.0;
    else
        return -x + 5.0;
}

// Формула Симпсона
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

// Площадь по частям
double calculate_area(int N)
{
    return simpson_rule(f, 3.0, 4.0, N) +
        simpson_rule(f, 4.0, 5.0, N);
}

int main()
{
    double exact = 1.0;
    int N_values[] = { 2, 4, 10, 20, 50, 100 };

    std::cout << "N\tArea\t\tError rate\n";
    std::cout << "----------------------------------\n";

    for (int N : N_values)
    {
        double area = calculate_area(N);
        double error = std::fabs(area - exact);

        std::cout << N << "\t"
            << area << "\t"
            << error << std::endl;
    }

    return 0;
}