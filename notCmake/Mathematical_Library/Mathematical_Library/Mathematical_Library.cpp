#include "Array.h"
#include <iostream>
#include <gtest/gtest.h>
#include <array>
#include <algorithm>
namespace Mathematical_library
{
    
    class ArrayFixture : public testing::Test
    {
    protected:
        std::array<int, 5> arr1;
        Mathematical_library::Array<int, 5> arr2;

        void SetUp() override
        {
            arr1 = { 1,2,3,4,5 };
            arr2 = { 1,2,3,4,5 };
        }

        void TearDown() override
        {
            std::cout << "Test Array Finish" << std::endl;

        }
    };

    
    TEST_F(ArrayFixture, HasCorrectSize)
    {
        EXPECT_EQ(arr1.size(), 5);
    }

    TEST_F(ArrayFixture, TestElements)
    {
        EXPECT_EQ(arr1[0], arr2[0]);
        EXPECT_EQ(arr1.at(1), arr2.at(1));
        EXPECT_THROW(arr2.at(10), std::runtime_error);
        EXPECT_EQ(arr1.front(), arr2.front());
        EXPECT_EQ(arr1.back(), arr2.back());
    }
    TEST_F(ArrayFixture, TestCopyConstructor)
    {
        Mathematical_library::Array<int, 5> arr3(arr2);
        for (size_t i = 0; i < 5; ++i) {
            EXPECT_EQ(arr3[i], arr2[i]);
        }
    }

    TEST_F(ArrayFixture, TestAssignmentOperator)
    {
        Mathematical_library::Array<int, 5> arr3;
        arr3 = arr2;
        for (size_t i = 0; i < 5; ++i) {
            EXPECT_EQ(arr3[i], arr2[i]);
        }
    }

    TEST_F(ArrayFixture, TestEmpty)
    {
        EXPECT_FALSE(arr2.empty());
        Mathematical_library::Array<int, 0> emptyArr;
        EXPECT_TRUE(emptyArr.empty());
    }

    TEST_F(ArrayFixture, TestIterators)
    {
        int expected = 1;
        for (auto it = arr2.begin(); it != arr2.end(); ++it) {
            EXPECT_EQ(*it, expected++);
        }
    }

    TEST_F(ArrayFixture, TestReverseIterators)
    {
        int expected = 5;
        for (auto it = arr2.rbegin(); it != arr2.rend(); ++it) {
            EXPECT_EQ(*it, expected--);
        }
    }

    TEST_F(ArrayFixture, TestFill)
    {
        arr2.fill(42);
        for (size_t i = 0; i < arr2.size(); ++i) {
            EXPECT_EQ(arr2[i], 42);
        }
    }

    TEST_F(ArrayFixture, TestSwap)
    {
        Mathematical_library::Array<int, 5> arr3 = { 5, 4, 3, 2, 1 };
        Mathematical_library::Array<int, 5> expected = arr2;
        arr2.swap(arr3);

        for (size_t i = 0; i < 5; ++i) {
            EXPECT_EQ(arr3[i], expected[i]);
            EXPECT_EQ(arr2[i], 5 - i);
        }
    }

    TEST_F(ArrayFixture, TestData)
    {
        const int* data = arr2.data();
        for (size_t i = 0; i < arr2.size(); ++i) {
            EXPECT_EQ(data[i], i + 1);
        }
    }

    TEST_F(ArrayFixture, TestConstIterators)
    {
        const Mathematical_library::Array<int, 5>& constArr = arr2;
        int expected = 1;
        for (auto it = constArr.cbegin(); it != constArr.cend(); ++it) {
            EXPECT_EQ(*it, expected++);
        }
    }

    TEST_F(ArrayFixture, TestInitializerListConstructor)
    {
        auto createSmallArray = []() { Array<int, 3> arr({ 1,2,3,4,5 }); };
        auto createGoodArray = []() { Array<int, 5> arr({ 1,2,3,4,5 }); };

        EXPECT_THROW(createSmallArray(), std::runtime_error);
        EXPECT_NO_THROW(createGoodArray());
    }
}


int main(int argc, char** argv) 
{
    /*Mathematical_library::Array<int, 3> arr4;
    std::vector<int> vec(10);
    std::cout << vec[0] << std::endl;
    std::cout << arr4[0] << std::endl;
    std::fill(vec.begin(), vec.end(), 5);
    std::fill(arr4.rbegin(), arr4.rend(), 5);
    std::cout << vec[0] << std::endl;
    std::cout << arr4[0] << std::endl;*/
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//TEST(NomDuGroupe, NomDuTest) {
//    // Votre code de test
//    EXPECT_TRUE(condition);
//    EXPECT_EQ(valeur1, valeur2);
//}
//
//class MaFixture : public testing::Test {
//protected:
//    // Variables membres
//    void SetUp() override {
//        // Initialisation avant chaque test
//    }
//};
//
//TEST_F(MaFixture, MonTest) {
//    // Utilise les variables de la fixture
//}
//
//EXPECT_TRUE(condition);    // Vérifie si vrai
//EXPECT_FALSE(condition);   // Vérifie si faux
//EXPECT_EQ(val1, val2);    // Vérifie si égal
//EXPECT_NE(val1, val2);    // Vérifie si non égal
//EXPECT_LT(val1, val2);    // Vérifie si inférieur
//EXPECT_GT(val1, val2);    // Vérifie si supérieur
//
//// Test de votre conteneur
//TEST(MonConteneur, TestDeBase) 
//{
//    MonConteneur<int> cont;
//
//    EXPECT_TRUE(cont.empty());
//
//    cont.ajouter(42);
//    EXPECT_FALSE(cont.empty());
//    EXPECT_EQ(cont.taille(), 1);
//}