#include "customer.h"
#include <fstream>
#include <iostream>

Customer::Customer()
{
    cnic = "";
    password = "";
}

Customer::Customer(int customerId, const string& customerName, const string& customerCnic, const string& customerPassword) : Person(customerId, customerName)
{
    cnic = customerCnic;
    password = customerPassword;
}

const string& Customer::getCnic() const
{
    return cnic;
}

const string& Customer::getPassword() const
{
    return password;
}

bool Customer::cnicExists(const string& cnic)
{
    ifstream file("customers.txt");
    if (!file.is_open())
    {
        return false;
    }

    int tempId;
    string tempName, fileCnic, tempPassword;
    while (file >> tempId >> tempName >> fileCnic >> tempPassword)
    {
        if (fileCnic == cnic)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

int Customer::registerCustomer(const string& name, const string& cnic, const string& password)
{
    if (cnicExists(cnic))
    {
        return -1;
    }

    ifstream inFile("customers.txt");
    int maxId = 0;
    int tempId;
    string tempName, tempCnic, tempPassword;
    while (inFile >> tempId >> tempName >> tempCnic >> tempPassword)
    {
        if (tempId > maxId)
        {
            maxId = tempId;
        }
    }
    inFile.close();

    int newId = maxId + 1;
    ofstream file("customers.txt", ios::app);
    if (!file.is_open())
    {
        return -1;
    }

    file << newId << " " << name << " " << cnic << " " << password << "\n";
    file.close();
    return newId;
}

int Customer::loginCustomer(const string& cnic, const string& password)
{
    ifstream file("customers.txt");
    if (!file.is_open())
    {
        return -1;
    }

    int customerId;
    string customerName, fileCnic, filePassword;
    while (file >> customerId >> customerName >> fileCnic >> filePassword)
    {
        if (fileCnic == cnic && filePassword == password)
        {
            file.close();
            return customerId;
        }
    }

    file.close();
    return -1;
}