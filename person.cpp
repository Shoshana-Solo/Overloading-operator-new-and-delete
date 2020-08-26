#include <stddef.h>
#include <exception>
#include "person.h"

static const int heapSize = 50;

char Person::s_pool[sizeof(Person) * heapSize];
void* Person::s_firstFree = initAllFree(s_pool);


/*--------------------Auxiliary Functions--------------------*/

void* getPrevFreeBlock(void* ptr , void* personToDelete)
{
    while (*reinterpret_cast<Person**>(ptr) < (Person*)personToDelete)
    {
        ptr = *reinterpret_cast<Person**>(ptr);
    }

    return ptr;
}

/*-----------------------------------------------------------*/


/*-----------------------API Functions-----------------------*/

void* initAllFree(void* firstFree)
{
    Person* ptr = (Person*)firstFree;

    for (size_t i = 0; i < heapSize - 1; ++i) {
        *reinterpret_cast<Person**>(ptr) = ptr + 1;
        ptr += 1;
    }

    *reinterpret_cast<Person**>(ptr) = NULL;

    return firstFree;
}



void* Person::operator new(size_t size)
{
    if(!s_firstFree)
    {
        throw std::bad_alloc();
    }
    void* ptr = s_firstFree;
    s_firstFree = *reinterpret_cast<Person**>(s_firstFree);
    *(Person*)ptr = Person();
    return ptr;
}


void Person::operator delete(void* personToDelete)
{
    void* ptr = s_firstFree;
    ptr = getPrevFreeBlock(ptr , personToDelete);
    Person* tmp = *(Person**)ptr;
    *reinterpret_cast<Person**>(ptr) = (Person*)personToDelete;
    *reinterpret_cast<Person**>(personToDelete) = tmp;
}

/*-----------------------------------------------------------*/










