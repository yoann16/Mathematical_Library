#include <iostream>
#include <cassert>
#include <array>
#include "TemplateArray.h"

using namespace Mathematical_library;

template<typename T, std::size_t Size>
void compareArrays(const std::array<T, Size>& stdArr, const Array<T, Size>& myArr) {
    // Comparaison de taille
    assert(stdArr.size() == myArr.size());

    // Comparaison des éléments
    for (std::size_t i = 0; i < Size; ++i) {
        assert(stdArr[i] == myArr[i]);
    }
}

int main() {
    // 1. Test construction et initialisation
    {
        std::array<int, 4> stdArr1 = { 0, 0, 0, 0 };
        Array<int, 4> myArr1;
        compareArrays(stdArr1, myArr1);

        std::array<int, 4> stdArr2 = { 1, 2, 3, 4 };
        Array<int, 4> myArr2 = { 1, 2, 3, 4 };
        compareArrays(stdArr2, myArr2);
    }

    // 2. Test accès aux éléments
    {
        std::array<int, 4> stdArr = { 1, 2, 3, 4 };
        Array<int, 4> myArr = { 1, 2, 3, 4 };

        // Test opérateur []
        for (std::size_t i = 0; i < stdArr.size(); ++i) {
            assert(stdArr[i] == myArr[i]);
        }

        // Test at()
        for (std::size_t i = 0; i < stdArr.size(); ++i) {
            assert(stdArr.at(i) == myArr.at(i));
        }

        // Test front() et back()
        assert(stdArr.front() == myArr.front());
        assert(stdArr.back() == myArr.back());

        // Test data()
        assert(*stdArr.data() == *myArr.data());
    }

    // 3. Test itérateurs
    {
        std::array<int, 4> stdArr = { 1, 2, 3, 4 };
        Array<int, 4> myArr = { 1, 2, 3, 4 };

        // Test begin() et end()
        {
            auto stdIt = stdArr.begin();
            auto myIt = myArr.begin();
            while (stdIt != stdArr.end()) {
                assert(*stdIt == *myIt);
                ++stdIt;
                ++myIt;
            }
        }

        // Test rbegin() et rend()
        {
            auto stdRit = stdArr.rbegin();
            auto myRit = myArr.rbegin();
            while (stdRit != stdArr.rend()) {
                assert(*stdRit == *myRit);
                ++stdRit;
                ++myRit;
            }
        }
    }

    // 4. Test modifications
    {
        // Test fill()
        {
            std::array<int, 4> stdArr;
            Array<int, 4> myArr;

            stdArr.fill(42);
            myArr.fill(42);
            compareArrays(stdArr, myArr);
        }

        // Test swap()
        {
            std::array<int, 4> stdArr1 = { 1, 2, 3, 4 };
            std::array<int, 4> stdArr2 = { 5, 6, 7, 8 };
            Array<int, 4> myArr1 = { 1, 2, 3, 4 };
            Array<int, 4> myArr2 = { 5, 6, 7, 8 };

            stdArr1.swap(stdArr2);
            myArr1.swap(myArr2);

            compareArrays(stdArr1, myArr1);
            compareArrays(stdArr2, myArr2);
        }
    }

    // 5. Test exceptions
    {
        std::array<int, 4> stdArr = { 1, 2, 3, 4 };
        Array<int, 4> myArr = { 1, 2, 3, 4 };

        // Test out of bounds
        try {
            stdArr.at(10);
            assert(false); // Ne devrait pas arriver
        }
        catch (const std::out_of_range&) {
            try {
                myArr.at(10);
                assert(false); // Ne devrait pas arriver
            }
            catch (const std::runtime_error&) {
                // Ok, exception capturée
                std::cout << "Test out of bounds reussi" << std::endl;
            }
        }
    }

    // 6. Test propriétés supplémentaires
    {
        std::array<int, 4> stdArr = { 1, 2, 3, 4 };
        Array<int, 4> myArr = { 1, 2, 3, 4 };

        assert(stdArr.size() == myArr.size());
        assert(stdArr.max_size() == myArr.max_size());
        assert(stdArr.empty() == myArr.empty());
    }

    std::cout << "Tous les tests ont réussi !" << std::endl;
    return 0;
}