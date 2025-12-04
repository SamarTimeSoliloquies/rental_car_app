#include "admin.h"

Admin::Admin()
{
    username = "";
    password = "";
}

Admin::Admin(int adminId, const string& adminName, const string& adminUsername, const string& adminPassword) : Person(adminId, adminName)
{
    username = adminUsername;
    password = adminPassword;
}

const string& Admin::getUsername() const
{
    return username;
}

const string& Admin::getPassword() const
{
    return password;
}