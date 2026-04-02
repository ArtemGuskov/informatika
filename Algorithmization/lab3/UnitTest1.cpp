#include "pch.h"
#include "CppUnitTest.h"
#include "../dz_prak3/SortingAlgorithms.h"
#include <vector>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortingAlgorithmsTests
{
    void assertEqual(const std::vector<int>& expected, const std::vector<int>& actual)
    {
        Assert::AreEqual(static_cast<int>(expected.size()), static_cast<int>(actual.size()), L"Razmer massivov ne sovpadaet.");

        for (size_t i = 0; i < expected.size(); ++i)
        {
            Assert::AreEqual(expected[i], actual[i], L"Elementy massivov ne sovpadayut.");
        }
    }

    TEST_CLASS(SortingAlgorithmsUnitTests)
    {
    public:
        TEST_METHOD(SortirovkaVstavkami_UporyadochivaetNeotsortirovannyiMassiv)
        {
            std::vector<int> massiv = { 5, 2, 4, 6, 1, 3 };
            std::vector<int> expected = { 1, 2, 3, 4, 5, 6 };

            SortingAlgorithms::sortirovkaVstavkami(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }

        TEST_METHOD(SortirovkaVstavkami_KorrektnoRabotaetSDublikatami)
        {
            std::vector<int> massiv = { 4, 2, 4, 1, 2, 3 };
            std::vector<int> expected = { 1, 2, 2, 3, 4, 4 };

            SortingAlgorithms::sortirovkaVstavkami(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }

        TEST_METHOD(SortirovkaVstavkami_NeMenyayetUzheOtsortirovannyiMassiv)
        {
            std::vector<int> massiv = { 1, 2, 3, 4, 5 };
            std::vector<int> expected = { 1, 2, 3, 4, 5 };

            SortingAlgorithms::sortirovkaVstavkami(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }

        TEST_METHOD(PorazryadnayaSortirovka_UporyadochivaetNeotsortirovannyiMassiv)
        {
            std::vector<int> massiv = { 170, 45, 75, 90, 802, 24, 2, 66 };
            std::vector<int> expected = { 2, 24, 45, 66, 75, 90, 170, 802 };

            SortingAlgorithms::porazryadnayaSortirovka(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }

        TEST_METHOD(PorazryadnayaSortirovka_KorrektnoRabotaetSPovtorami)
        {
            std::vector<int> massiv = { 10, 1, 10, 100, 2, 2, 11 };
            std::vector<int> expected = { 1, 2, 2, 10, 10, 11, 100 };

            SortingAlgorithms::porazryadnayaSortirovka(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }

        TEST_METHOD(PorazryadnayaSortirovka_KorrektnoRabotaetSPustymMassivom)
        {
            std::vector<int> massiv;
            std::vector<int> expected;

            SortingAlgorithms::porazryadnayaSortirovka(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(massiv.empty());
        }

        TEST_METHOD(BystrayaSortirovka_UporyadochivaetNeotsortirovannyiMassiv)
        {
            std::vector<int> massiv = { 10, 7, 8, 9, 1, 5 };
            std::vector<int> expected = { 1, 5, 7, 8, 9, 10 };

            SortingAlgorithms::bystrayaSortirovka(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }

        TEST_METHOD(BystrayaSortirovka_KorrektnoRabotaetSOdinakovymiElementami)
        {
            std::vector<int> massiv = { 3, 3, 3, 3, 3 };
            std::vector<int> expected = { 3, 3, 3, 3, 3 };

            SortingAlgorithms::bystrayaSortirovka(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }

        TEST_METHOD(BystrayaSortirovka_KorrektnoRabotaetSChastichnoOtsortirovannymMassivom)
        {
            std::vector<int> massiv = { 1, 2, 3, 7, 5, 6, 4 };
            std::vector<int> expected = { 1, 2, 3, 4, 5, 6, 7 };

            SortingAlgorithms::bystrayaSortirovka(massiv);

            assertEqual(expected, massiv);
            Assert::IsTrue(std::is_sorted(massiv.begin(), massiv.end()));
        }
    };
}