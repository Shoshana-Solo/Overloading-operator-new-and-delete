#include <iostream>
#include "person.h"


int main()
{
    Person* p = new Person();

    std::cout << p->getFirstFree();
    return 1;
}