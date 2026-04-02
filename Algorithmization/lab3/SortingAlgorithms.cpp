#include "SortingAlgorithms.h"
#include <algorithm>
#include <stdexcept>

namespace SortingAlgorithms
{
    void sortirovkaVstavkami(std::vector<int>& massiv)
    {
        for (int i = 1; i < static_cast<int>(massiv.size()); ++i)
        {
            int tekushchii = massiv[i];
            int j = i - 1;

            while (j >= 0 && massiv[j] > tekushchii)
            {
                massiv[j + 1] = massiv[j];
                --j;
            }

            massiv[j + 1] = tekushchii;
        }
    }

    void sortirovatPoRazryadu(std::vector<int>& massiv, int razryad)
    {
        std::vector<std::vector<int>> korziny(10);

        for (int chislo : massiv)
        {
            if (chislo < 0)
            {
                throw std::invalid_argument("Podderzhivaet tolko neotritsatelnye chisla");
            }

            int indeksKorziny = (chislo / razryad) % 10;
            korziny[indeksKorziny].push_back(chislo);
        }

        std::vector<int> obedinennyiMassiv;
        obedinennyiMassiv.reserve(massiv.size());

        for (const auto& korzina : korziny)
        {
            obedinennyiMassiv.insert(obedinennyiMassiv.end(), korzina.begin(), korzina.end());
        }

        massiv = obedinennyiMassiv;
    }

    void porazryadnayaSortirovka(std::vector<int>& massiv)
    {
        if (massiv.empty())
        {
            return;
        }

        int maksimalnoeChislo = *std::max_element(massiv.begin(), massiv.end());
        int razryad = 1;

        while (maksimalnoeChislo / razryad > 0)
        {
            sortirovatPoRazryadu(massiv, razryad);
            razryad *= 10;
        }
    }

    int razdelit(std::vector<int>& massiv, int niz, int vysokii)
    {
        int opornyi = massiv[vysokii];
        int i = niz - 1;

        for (int j = niz; j <= vysokii - 1; ++j)
        {
            if (massiv[j] <= opornyi)
            {
                ++i;
                std::swap(massiv[i], massiv[j]);
            }
        }

        std::swap(massiv[i + 1], massiv[vysokii]);
        return i + 1;
    }

    void bystrayaSortirovka(std::vector<int>& massiv, int niz, int vysokii)
    {
        if (niz < vysokii)
        {
            int opornyiIndeks = razdelit(massiv, niz, vysokii);

            bystrayaSortirovka(massiv, niz, opornyiIndeks - 1);
            bystrayaSortirovka(massiv, opornyiIndeks + 1, vysokii);
        }
    }

    void bystrayaSortirovka(std::vector<int>& massiv)
    {
        if (massiv.empty())
        {
            return;
        }

        bystrayaSortirovka(massiv, 0, static_cast<int>(massiv.size()) - 1);
    }
}