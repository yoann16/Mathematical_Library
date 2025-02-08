#include <iostream>
#include <string>
#include <list>
#include <cassert>
#include "TemplateList.h"

void testPushBack() {
    List<int> myList;
    std::list<int> stdList;

    // Test push_back avec plusieurs valeurs
    myList.push_back(1);
    stdList.push_back(1);
    assert(myList.back() == stdList.back() && "push_back: première valeur différente");
    assert(myList.size() == stdList.size() && "push_back: taille différente après première insertion");

    myList.push_back(2);
    stdList.push_back(2);
    assert(myList.back() == stdList.back() && "push_back: deuxième valeur différente");
    assert(myList.size() == stdList.size() && "push_back: taille différente après deuxième insertion");

    myList.push_back(3);
    stdList.push_back(3);
    assert(myList.back() == stdList.back() && "push_back: troisième valeur différente");
    assert(myList.size() == stdList.size() && "push_back: taille différente après troisième insertion");

    std::cout << "Test push_back: OK" << std::endl;
}

void testPushFront() {
    List<int> myList;
    std::list<int> stdList;

    // Test push_front avec plusieurs valeurs
    myList.push_front(1);
    stdList.push_front(1);
    assert(myList.front() == stdList.front() && "push_front: première valeur différente");
    assert(myList.size() == stdList.size() && "push_front: taille différente après première insertion");

    myList.push_front(2);
    stdList.push_front(2);
    assert(myList.front() == stdList.front() && "push_front: deuxième valeur différente");
    assert(myList.size() == stdList.size() && "push_front: taille différente après deuxième insertion");

    myList.push_front(3);
    stdList.push_front(3);
    assert(myList.front() == stdList.front() && "push_front: troisième valeur différente");
    assert(myList.size() == stdList.size() && "push_front: taille différente après troisième insertion");

    std::cout << "Test push_front: OK" << std::endl;
}

void testPopBack() {
    List<int> myList;
    std::list<int> stdList;

    // Préparation des listes
    for (int i = 1; i <= 3; i++) {
        myList.push_back(i);
        stdList.push_back(i);
    }

    // Test pop_back
    myList.pop_back();
    stdList.pop_back();
    assert(myList.back() == stdList.back() && "pop_back: valeur différente après premier pop");
    assert(myList.size() == stdList.size() && "pop_back: taille différente après premier pop");

    myList.pop_back();
    stdList.pop_back();
    assert(myList.back() == stdList.back() && "pop_back: valeur différente après deuxième pop");
    assert(myList.size() == stdList.size() && "pop_back: taille différente après deuxième pop");

    std::cout << "Test pop_back: OK" << std::endl;
}

void testPopFront() {
    List<int> myList;
    std::list<int> stdList;

    // Préparation des listes
    for (int i = 1; i <= 3; i++) {
        myList.push_back(i);
        stdList.push_back(i);
    }

    // Test pop_front
    myList.pop_front();
    stdList.pop_front();
    assert(myList.front() == stdList.front() && "pop_front: valeur différente après premier pop");
    assert(myList.size() == stdList.size() && "pop_front: taille différente après premier pop");

    myList.pop_front();
    stdList.pop_front();
    assert(myList.front() == stdList.front() && "pop_front: valeur différente après deuxième pop");
    assert(myList.size() == stdList.size() && "pop_front: taille différente après deuxième pop");

    std::cout << "Test pop_front: OK" << std::endl;
}

void testMixedOperations() {
    List<int> myList;
    std::list<int> stdList;

    // Test combinaison d'opérations
    myList.push_back(1);
    stdList.push_back(1);
    myList.push_front(2);
    stdList.push_front(2);
    myList.push_back(3);
    stdList.push_back(3);

    assert(myList.front() == stdList.front() && "Mixed: front différent");
    assert(myList.back() == stdList.back() && "Mixed: back différent");
    assert(myList.size() == stdList.size() && "Mixed: taille différente");

    myList.pop_front();
    stdList.pop_front();
    myList.pop_back();
    stdList.pop_back();

    assert(myList.front() == stdList.front() && "Mixed: front différent après pop");
    assert(myList.back() == stdList.back() && "Mixed: back différent après pop");
    assert(myList.size() == stdList.size() && "Mixed: taille différente après pop");

    std::cout << "Test opérations mixtes: OK" << std::endl;
}

int main() {
    try {
        std::cout << "Début des tests..." << std::endl;

        testPushBack();
        testPushFront();
        testPopBack();
        testPopFront();
        testMixedOperations();

        std::cout << "Tous les tests ont réussi!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Une erreur s'est produite: " << e.what() << std::endl;
        return 1;
    }
    std::list<int> test;
    
    return 0;
}
