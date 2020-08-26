#ifndef __PERSON_H__
#define __PERSON_H__
#include <cstring>
class Person
{
public:
    Person(){};
    Person(char* , unsigned int , unsigned char);
    ~Person(){};
    void* getFirstFree() { return s_firstFree; }
    void* getPool() { return s_pool; }
    void* operator new(size_t);
    void operator delete(void*);


private:
    static char s_pool[];
    static void* s_firstFree;
    char m_fullname[32];
    unsigned int m_id;
    unsigned char m_age;
    void* operator new[](size_t) {return NULL;};
    void operator delete[](void*) {};
};

inline Person::Person(char* fullname, unsigned int id , unsigned char age)
:m_fullname{}
,m_id(id)
,m_age(age)
{
    strcpy(m_fullname , fullname);
}


void* initAllFree(void* firstFree);

#endif //__PERSON_H__