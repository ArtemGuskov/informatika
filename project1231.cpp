#include<iostream>
#include <locale>
#include <cmath>

using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    float x, y;
    cin >> x >> y;
    float R = sqrt((abs(sin(x) / y), 4));
    float S = log10(pow(2, y));
    cout << "R = " << R << ", S = " << S << endl;
    float C = max(R, S);
    cout << "C = " << C << endl;
    cin.get();
    return 0;
}

