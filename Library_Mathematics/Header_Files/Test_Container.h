#pragma once
#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include "Vector.h"
#include "Array.h"
#include "List.h"

using namespace Mathematical_library;

class VectorTests : public testing::Test {
protected:
    std::vector<int> stdVec;
    Vector<int> customVec;
    void SetUp() override {
        stdVec = { 1, 2, 3, 4, 5 };
        customVec = { 1, 2, 3, 4, 5 };
    }
};

// Test des constructeurs
TEST_F(VectorTests, Constructors) {
    // Default constructor
    std::vector<int> sv1;
    Vector<int> cv1;
    EXPECT_EQ(sv1.size(), cv1.size());
    EXPECT_TRUE(cv1.empty());

    // Size constructor
    std::vector<int> sv2(3);
    Vector<int> cv2(3);
    EXPECT_EQ(sv2.size(), cv2.size());

    // Size and value constructor
    std::vector<int> sv3(3, 42);
    Vector<int> cv3(3, 42);
    EXPECT_EQ(sv3.size(), cv3.size());
    EXPECT_EQ(sv3[0], cv3[0]);

    // Initializer list constructor
    std::vector<int> sv4 = { 1, 2, 3 };
    Vector<int> cv4 = { 1, 2, 3 };
    EXPECT_EQ(sv4.size(), cv4.size());
    for (size_t i = 0; i < sv4.size(); ++i) {
        EXPECT_EQ(sv4[i], cv4[i]);
    }

    // Copy constructor
    Vector<int> cv5(cv4);
    EXPECT_EQ(cv4.size(), cv5.size());
    for (size_t i = 0; i < cv4.size(); ++i) {
        EXPECT_EQ(cv4[i], cv5[i]);
    }

    // Move constructor
    Vector<int> cv6(std::move(cv5));
    EXPECT_EQ(cv4.size(), cv6.size());
    EXPECT_EQ(cv5.size(), 0);  // cv5 devrait être vide après le move
}

// Test des opérateurs d'affectation
TEST_F(VectorTests, AssignmentOperators) {
    // Copy assignment
    Vector<int> cv1;
    cv1 = customVec;
    EXPECT_EQ(customVec.size(), cv1.size());
    for (size_t i = 0; i < cv1.size(); ++i) {
        EXPECT_EQ(customVec[i], cv1[i]);
    }

    // Move assignment
    Vector<int> cv2;
    Vector<int> temp = customVec;
    cv2 = std::move(temp);
    EXPECT_EQ(customVec.size(), cv2.size());
    EXPECT_EQ(temp.size(), 0);  // temp devrait être vide après le move
}

// Test des accesseurs et des modificateurs d'éléments
TEST_F(VectorTests, ElementAccess) {
    // operator[]
    EXPECT_EQ(stdVec[0], customVec[0]);
    EXPECT_EQ(stdVec[stdVec.size() - 1], customVec[customVec.size() - 1]);

    // at()
    EXPECT_EQ(stdVec.at(0), customVec.at(0));
    EXPECT_THROW(customVec.at(customVec.size()), std::out_of_range);

    // front()
    EXPECT_EQ(stdVec.front(), customVec.front());

    // back()
    EXPECT_EQ(stdVec.back(), customVec.back());

    // data()
    EXPECT_NE(customVec.data(), nullptr);
    EXPECT_EQ(*customVec.data(), customVec.front());
}

// Test des itérateurs
TEST_F(VectorTests, Iterators) {
    // begin/end
    auto stdIt = stdVec.begin();
    auto customIt = customVec.begin();
    EXPECT_EQ(*stdIt, *customIt);

    // const begin/end
    const Vector<int>& constCustomVec = customVec;
    auto constIt = constCustomVec.begin();
    EXPECT_EQ(*constIt, customVec.front());

    // reverse iterators
    auto stdRIt = stdVec.rbegin();
    auto customRIt = customVec.rbegin();
    EXPECT_EQ(*stdRIt, *customRIt);

    // Itération complète
    int sum1 = 0, sum2 = 0;
    for (const auto& val : customVec) sum1 += val;
    for (const auto& val : stdVec) sum2 += val;
    EXPECT_EQ(sum1, sum2);
}

// Test des fonctions de capacité
TEST_F(VectorTests, Capacity) {
    EXPECT_EQ(stdVec.empty(), customVec.empty());
    EXPECT_EQ(stdVec.size(), customVec.size());

    // reserve
    size_t newCap = customVec.capacity() * 2;
    customVec.reserve(newCap);
    EXPECT_GE(customVec.capacity(), newCap);

    // Test que reserve ne modifie pas la taille
    EXPECT_EQ(customVec.size(), stdVec.size());
}

// Test des modificateurs
TEST_F(VectorTests, Modifiers) {
    // clear
    customVec.clear();
    EXPECT_TRUE(customVec.empty());
    EXPECT_EQ(customVec.size(), 0);

    // push_back
    customVec.push_back(1);
    EXPECT_EQ(customVec.size(), 1);
    EXPECT_EQ(customVec.back(), 1);

    // pop_back
    customVec.pop_back();
    EXPECT_TRUE(customVec.empty());

    // resize plus grand
    size_t newSize = 10;
    customVec.resize(newSize);
    EXPECT_EQ(customVec.size(), newSize);

    // resize plus petit
    newSize = 5;
    customVec.resize(newSize);
    EXPECT_EQ(customVec.size(), newSize);

    // swap
    Vector<int> other = { 10, 20, 30 };
    size_t thisSize = customVec.size();
    size_t otherSize = other.size();
    customVec.swap(other);
    EXPECT_EQ(customVec.size(), otherSize);
    EXPECT_EQ(other.size(), thisSize);
}

// Test des opérateurs de comparaison
TEST_F(VectorTests, ComparisonOperators) {
    Vector<int> vec1 = { 1, 2, 3 };
    Vector<int> vec2 = { 1, 2, 3 };
    Vector<int> vec3 = { 1, 2, 4 };
    Vector<int> vec4 = { 1, 2 };

    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 == vec3);
    EXPECT_TRUE(vec1 != vec3);
    EXPECT_TRUE(vec1 > vec4);
    EXPECT_TRUE(vec4 < vec1);
    EXPECT_TRUE(vec1 >= vec2);
    EXPECT_TRUE(vec1 <= vec2);
}

// Test des cas spéciaux et des cas limites
TEST_F(VectorTests, EdgeCases) {
    // Vecteur vide
    Vector<int> empty;
    EXPECT_THROW(empty.front(), std::out_of_range);
    EXPECT_THROW(empty.back(), std::out_of_range);
    EXPECT_THROW(empty.pop_back(), std::runtime_error);

    // Grande capacité
    Vector<int> large;
    large.reserve(1000000);
    EXPECT_GE(large.capacity(), 1000000);

    // Beaucoup d'insertions
    Vector<int> growing;
    for (int i = 0; i < 1000; ++i) {
        growing.push_back(i);
    }
    EXPECT_EQ(growing.size(), 1000);
    EXPECT_EQ(growing[999], 999);
}

// Tests pour Array personnalisé
class ArrayTests : public testing::Test {
protected:
    std::array<int, 5> stdArr;
    Mathematical_library::Array<int, 5> customArr;

    void SetUp() override {
        stdArr = { 1, 2, 3, 4, 5 };
        customArr = { 1, 2, 3, 4, 5 };
    }
};

TEST_F(ArrayTests, Constructors) {
    // Default constructor
    std::array<int, 3> sa1;
    Mathematical_library::Array<int, 3> ca1;
    EXPECT_EQ(sa1.size(), ca1.size());

    // Initializer list constructor
    std::array<int, 3> sa2 = { 1, 2, 3 };
    Mathematical_library::Array<int, 3> ca2 = { 1, 2, 3 };
    for (size_t i = 0; i < sa2.size(); ++i) {
        EXPECT_EQ(sa2[i], ca2[i]);
    }
}

TEST_F(ArrayTests, ElementAccess) {
    EXPECT_EQ(stdArr[0], customArr[0]);
    EXPECT_EQ(stdArr.front(), customArr.front());
    EXPECT_EQ(stdArr.back(), customArr.back());

    EXPECT_THROW(customArr.at(10), std::runtime_error);
}

TEST_F(ArrayTests, Iterators) {
    auto stdIt = stdArr.begin();
    auto customIt = customArr.begin();
    EXPECT_EQ(*stdIt, *customIt);

    stdIt = stdArr.end() - 1;
    customIt = customArr.end() - 1;
    EXPECT_EQ(*stdIt, *customIt);
}
TEST_F(ArrayTests, SuiteArrayTests) {
    // Teste les opérateurs de comparaison
    Mathematical_library::Array<int, 5> arr1 = { 1, 2, 3, 4, 5 };
    Mathematical_library::Array<int, 5> arr2 = { 1, 2, 3, 4, 5 };
    Mathematical_library::Array<int, 5> arr3 = { 1, 2, 3, 4, 6 };

    EXPECT_TRUE(arr1 == arr2);
    EXPECT_FALSE(arr1 == arr3);
    EXPECT_TRUE(arr1 != arr3);
    EXPECT_TRUE(arr1 < arr3);
    EXPECT_TRUE(arr3 > arr1);

    // Teste size(), max_size(), empty()
    EXPECT_EQ(customArr.size(), 5);
    EXPECT_EQ(customArr.max_size(), 5);
    EXPECT_FALSE(customArr.empty());

    // Teste data()
    EXPECT_EQ(*customArr.data(), customArr.front());

    // Teste les itérateurs inverses
    auto rIt = customArr.rbegin();
    EXPECT_EQ(*rIt, customArr.back());

    // Teste assign() et fill()
    Mathematical_library::Array<int, 5> assignArr;
    assignArr.assign(42);
    for (int val : assignArr) {
        EXPECT_EQ(val, 42);
    }

    // Teste swap()
    Mathematical_library::Array<int, 5> swapArr = { 6, 7, 8, 9, 10 };
    arr1.swap(swapArr);
    EXPECT_EQ(arr1[0], 6);
    EXPECT_EQ(swapArr[0], 1);

    // Teste constructeur de copie
    Mathematical_library::Array<int, 5> copyArr(customArr);
    EXPECT_EQ(copyArr, customArr);

    // Teste opérateur d'affectation
    Mathematical_library::Array<int, 5> assignmentArr;
    assignmentArr = customArr;
    EXPECT_EQ(assignmentArr, customArr);
}