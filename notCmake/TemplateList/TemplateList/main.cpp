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
    assert(myList.back() == stdList.back() && "push_back: premi�re valeur diff�rente");
    assert(myList.size() == stdList.size() && "push_back: taille diff�rente apr�s premi�re insertion");

    myList.push_back(2);
    stdList.push_back(2);
    assert(myList.back() == stdList.back() && "push_back: deuxi�me valeur diff�rente");
    assert(myList.size() == stdList.size() && "push_back: taille diff�rente apr�s deuxi�me insertion");

    myList.push_back(3);
    stdList.push_back(3);
    assert(myList.back() == stdList.back() && "push_back: troisi�me valeur diff�rente");
    assert(myList.size() == stdList.size() && "push_back: taille diff�rente apr�s troisi�me insertion");

    std::cout << "Test push_back: OK" << std::endl;
}

void testPushFront() {
    List<int> myList;
    std::list<int> stdList;

    // Test push_front avec plusieurs valeurs
    myList.push_front(1);
    stdList.push_front(1);
    assert(myList.front() == stdList.front() && "push_front: premi�re valeur diff�rente");
    assert(myList.size() == stdList.size() && "push_front: taille diff�rente apr�s premi�re insertion");

    myList.push_front(2);
    stdList.push_front(2);
    assert(myList.front() == stdList.front() && "push_front: deuxi�me valeur diff�rente");
    assert(myList.size() == stdList.size() && "push_front: taille diff�rente apr�s deuxi�me insertion");

    myList.push_front(3);
    stdList.push_front(3);
    assert(myList.front() == stdList.front() && "push_front: troisi�me valeur diff�rente");
    assert(myList.size() == stdList.size() && "push_front: taille diff�rente apr�s troisi�me insertion");

    std::cout << "Test push_front: OK" << std::endl;
}

void testPopBack() {
    List<int> myList;
    std::list<int> stdList;

    // Pr�paration des listes
    for (int i = 1; i <= 3; i++) {
        myList.push_back(i);
        stdList.push_back(i);
    }

    // Test pop_back
    myList.pop_back();
    stdList.pop_back();
    assert(myList.back() == stdList.back() && "pop_back: valeur diff�rente apr�s premier pop");
    assert(myList.size() == stdList.size() && "pop_back: taille diff�rente apr�s premier pop");

    myList.pop_back();
    stdList.pop_back();
    assert(myList.back() == stdList.back() && "pop_back: valeur diff�rente apr�s deuxi�me pop");
    assert(myList.size() == stdList.size() && "pop_back: taille diff�rente apr�s deuxi�me pop");

    std::cout << "Test pop_back: OK" << std::endl;
}

void testPopFront() {
    List<int> myList;
    std::list<int> stdList;

    // Pr�paration des listes
    for (int i = 1; i <= 3; i++) {
        myList.push_back(i);
        stdList.push_back(i);
    }

    // Test pop_front
    myList.pop_front();
    stdList.pop_front();
    assert(myList.front() == stdList.front() && "pop_front: valeur diff�rente apr�s premier pop");
    assert(myList.size() == stdList.size() && "pop_front: taille diff�rente apr�s premier pop");

    myList.pop_front();
    stdList.pop_front();
    assert(myList.front() == stdList.front() && "pop_front: valeur diff�rente apr�s deuxi�me pop");
    assert(myList.size() == stdList.size() && "pop_front: taille diff�rente apr�s deuxi�me pop");

    std::cout << "Test pop_front: OK" << std::endl;
}

void testMixedOperations() {
    List<int> myList;
    std::list<int> stdList;

    // Test combinaison d'op�rations
    myList.push_back(1);
    stdList.push_back(1);
    myList.push_front(2);
    stdList.push_front(2);
    myList.push_back(3);
    stdList.push_back(3);

    assert(myList.front() == stdList.front() && "Mixed: front diff�rent");
    assert(myList.back() == stdList.back() && "Mixed: back diff�rent");
    assert(myList.size() == stdList.size() && "Mixed: taille diff�rente");

    myList.pop_front();
    stdList.pop_front();
    myList.pop_back();
    stdList.pop_back();

    assert(myList.front() == stdList.front() && "Mixed: front diff�rent apr�s pop");
    assert(myList.back() == stdList.back() && "Mixed: back diff�rent apr�s pop");
    assert(myList.size() == stdList.size() && "Mixed: taille diff�rente apr�s pop");

    std::cout << "Test op�rations mixtes: OK" << std::endl;
}

int main() {
    try {
        std::cout << "D�but des tests..." << std::endl;

        testPushBack();
        testPushFront();
        testPopBack();
        testPopFront();
        testMixedOperations();

        std::cout << "Tous les tests ont r�ussi!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Une erreur s'est produite: " << e.what() << std::endl;
        return 1;
    }
    std::list<int> test;
    
    return 0;
}
