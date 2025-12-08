#pragma once
#include "Person.h"
#include <string>
class RentalManager;
using namespace std;

class Admin : public Person {
private:
    int adminId;
    string username;
    string password;

public:
    Admin(int id = 0, const string& username = "", const string& password = "",
        const string& name = "", int age = 0,
        const string& cnic = "", const string& phone = "", const string& email = "");

    int getAdminId() const { return adminId; }
    const string& getUsername() const { return username; }

    void rentVehicle(int customerId, int vehicleId, int days);
    void returnVehicle(int vehicleId);
    void viewCustomers() const;
    void viewCustomerProfile(int customerId) const;
    void viewAllVehicles() const;
    void addNewVehicle();
};