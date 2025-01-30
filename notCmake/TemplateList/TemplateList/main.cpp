#include <iostream>
#include <string>

#include "TemplateList.h"


int main()
{
    List<int> toto;
    toto.push_back(12);
    std::cout << toto.back() << std::endl;
    toto.push_back(42);
    std::cout << toto.back() << std::endl;
    toto.pop_back();
    std::cout << toto.size() << std::endl;
    std::cout << toto.back() << std::endl;
    toto.pop_back();
    std::cout << toto.size() << std::endl;

    std::cout << "\n\n";

    toto.push_front(36);
    toto.push_front(24);
    std::cout << toto.size() << std::endl;
    std::cout << toto.front() << std::endl;
    toto.pop_front();
    std::cout << toto.size() << std::endl;
    std::cout << toto.front() << std::endl;
    toto.pop_front();
    std::cout << toto.size() << std::endl;
}
