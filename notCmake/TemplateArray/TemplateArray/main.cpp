// TemplateArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <array>


#include "TemplateArray.h"
using namespace Mathematical_library;
namespace Mathematical_library
{
    /*Array& concat(auto& tab1, auto& tab2)
    {
        for (int i = tab1.begin();i != tab.end();++i)
        {

        }
    }*/
}


int main()
{
    // 1. Test construction et initialisation
    std::cout << "=== Test construction et initialisation ===\n";
    Array<int, 4> arr1;  // Constructeur par défaut
    std::cout << "arr1 (default): " << arr1 << "\n";

    Array<int, 4> arr2 = { 1, 2, 3, 4 };  // Initializer list
    std::cout << "arr2 (init list): " << arr2 << "\n";

    Array<int, 4> arr3(arr2);  // Constructeur de copie
    std::cout << "arr3 (copy of arr2): " << arr3 << "\n";

    // 2. Test accès aux éléments
    std::cout << "\n=== Test accès aux éléments ===\n";
    std::cout << "arr2[0]: " << arr2[0] << "\n";
    std::cout << "arr2.at(1): " << arr2.at(1) << "\n";
    std::cout << "arr2.front(): " << arr2.front() << "\n";
    std::cout << "arr2.back(): " << arr2.back() << "\n";

    // 3. Test itérateurs
    std::cout << "\n=== Test itérateurs ===\n";
    std::cout << "Normal iterator: ";
    for (auto it = arr2.begin(); it != arr2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "Reverse iterator: ";
    for (auto it = arr2.rbegin(); it != arr2.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // 4. Test modifications
    std::cout << "\n=== Test modifications ===\n";
    arr1.fill(42);
    std::cout << "arr1 after fill(42): " << arr1 << "\n";

    arr1.assign(10);
    std::cout << "arr1 after assign(10): " << arr1 << "\n";

    std::cout << "Before swap:\n";
    std::cout << "arr1: " << arr1 << "\n";
    std::cout << "arr2: " << arr2 << "\n";

    arr1.swap(arr2);

    std::cout << "After swap:\n";
    std::cout << "arr1: " << arr1 << "\n";
    std::cout << "arr2: " << arr2 << "\n";

    // 5. Test avec des exceptions
    std::cout << "\n=== Test exceptions ===\n";
    try {
        arr1.at(10);  // Devrait lancer une exception
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}

