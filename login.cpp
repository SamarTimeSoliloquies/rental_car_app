#include "login.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;


// LoginSystem.cpp (ONLY this function needs to be fixed)
int LoginSystem::validateCredentials(const std::string& username, const std::string& password)
{
    std::ifstream file("admins.txt");

    // If file doesn't exist → create default admin and auto-login if credentials match
    if (!file.is_open())
    {
        std::ofstream out("admins.txt");
        out << "1,admin,admin\n";
        out.close();

        if (username == "admin" && password == "admin")
        {
            loggedInAdminId = 1;
            return 1;
        }
        loggedInAdminId = -1;
        return -1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string idStr, storedUser, storedPass;

        // Correct order:
        std::getline(iss, idStr, ',');      // adminId
        std::getline(iss, storedUser, ','); // username
        std::getline(iss, storedPass);      // password (rest of line)

        if (storedUser == username && storedPass == password)
        {
            loggedInAdminId = std::stoi(idStr);
            return loggedInAdminId;
        }
    }

    loggedInAdminId = -1;
    return -1;
}
int LoginSystem::getLoggedInAdminId() const
{
    return loggedInAdminId;
}