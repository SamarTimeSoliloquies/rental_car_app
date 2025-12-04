#include "person.h"

Person::Person()
{
    id = 0;
    name = "";
}

Person::Person(int personId, const string& personName)
{
    id = personId;
    name = personName;
}

Person::~Person()
{

}

int Person::getId() const
{
    return id;
}

const string& Person::getName() const
{
    return name;
}