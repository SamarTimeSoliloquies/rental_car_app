#pragma once
#include "Person.h"
#include <string>
class RentalManager;

class Admin : public Person {
private:
    int adminId;
    std::string username;
    std::string password;

public:
    Admin(int id = 0, const std::string& username = "", const std::string& password = "",
        const std::string& name = "", int age = 0,
        const std::string& cnic = "", const std::string& phone = "", const std::string& email = "");

    int getAdminId() const { return adminId; }
    const std::string& getUsername() const { return username; }

    void rentVehicle(int customerId, int vehicleId, int days);
    void returnVehicle(int vehicleId);
    void viewCustomers() const;
    void viewCustomerProfile(int customerId) const;
    void viewAllVehicles() const;
    void addNewVehicle();
};