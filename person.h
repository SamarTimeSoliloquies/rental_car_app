#ifndef person_h
#define person_h
#include <string>
using namespace std;

class Person
{
protected:
    int id;
    string name;

public:
    Person();
    Person(int personId, const string& personName);
    virtual ~Person();

    int getId() const;
    const string& getName() const;
};

#endif