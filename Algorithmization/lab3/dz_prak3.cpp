#include <iostream>
#include <vector>
#include "SortingAlgorithms.h"

void vyvestiMassiv(const std::vector<int>& massiv)
{
    for (int chislo : massiv)
    {
        std::cout << chislo << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::vector<int> ishodnyiMassiv = { 3, 1, 6, 57 };

    std::vector<int> massivVstavki = ishodnyiMassiv;
    std::vector<int> massivPorazryadnyi = ishodnyiMassiv;
    std::vector<int> massivBystryi = ishodnyiMassiv;

    SortingAlgorithms::sortirovkaVstavkami(massivVstavki);
    SortingAlgorithms::porazryadnayaSortirovka(massivPorazryadnyi);
    SortingAlgorithms::bystrayaSortirovka(massivBystryi);

    std::cout << "Ishodnyi massiv: ";
    vyvestiMassiv(ishodnyiMassiv);

    std::cout << "Posle sortirovki vstavkami: ";
    vyvestiMassiv(massivVstavki);

    std::cout << "Posle porazryadnoi sortirovki: ";
    vyvestiMassiv(massivPorazryadnyi);

    std::cout << "Posle bystroi sortirovki: ";
    vyvestiMassiv(massivBystryi);

    return 0;
}