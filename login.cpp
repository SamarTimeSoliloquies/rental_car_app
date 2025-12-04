#include "login.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;


int LoginSystem::validateCredentials(const string& username, const string& password)
{
    ifstream file("admins.txt");

    if (!file.is_open())
    {
        ofstream out("admins.txt");
        if (out.is_open())
        {
            out << "1,admin,admin\n";  // adminId=1, username=admin, password=admin
            out.close();

            if (username == "admin" && password == "admin")
            {
                loggedInAdminId = 1;
                return 1;
            }
        }
        loggedInAdminId = -1;
        return -1;
    }

    string line;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        istringstream iss(line);
        string token;

        // Format: adminId,username,password
        if (!getline(iss, token, ',')) continue;
        int id = std::stoi(token);

        if (getline(iss, token, ',')) continue;
        string storedUsername = token;

        if (getline(iss, token)) continue;
        string storedPassword = token;

        if (storedUsername == username && storedPassword == password)
        {
            loggedInAdminId = id;
            return id;
        }
    }

    loggedInAdminId = -1;
    return -1;
}

int LoginSystem::getLoggedInAdminId() const
{
    return loggedInAdminId;
}