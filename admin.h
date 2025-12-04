#ifndef admin_h
#define admin_h
#include "person.h"
#include <string>
using namespace std;

class Admin : public Person
{
private:
    string username;
    string password;

public:
    Admin();
    Admin(int adminId, const string& adminName, const string& adminUsername, const string& adminPassword);

    const string& getUsername() const;
    const string& getPassword() const;
};

#endif#pragma once
