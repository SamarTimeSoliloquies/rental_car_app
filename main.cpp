#include <iostream>
#include "admin.h"
#include "customer.h"
#include "login.h"
#include "loginmanager.h"
using namespace std;

int main()
{
    RentalManager rentalManager;

    cout << "Welcome to Vehicle Rental System\n";
    cout << "1. Admin\n";
    cout << "2. Customer\n";
    cout << "Enter choice: ";
    int userType;
    cin >> userType;

    if (userType == 1)
    {
        LoginSystem loginSystem;
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        int adminId = loginSystem.validateCredentials(username, password);
        if (adminId == -1)
        {
            cout << "Invalid credentials\n";
            return 0;
        }

        cout << "Login successful\n";
        cout << "1. Add Car\n";
        cout << "2. Add Van\n";
        cout << "3. Add Bike\n";
        cout << "Enter choice: ";
        int adminChoice;
        cin >> adminChoice;

        if (adminChoice == 1)
        {
            string brand, model;
            float rentPerDay;
            int numDoors, seatingCapacity;
            cout << "Enter brand: ";
            cin >> brand;
            cout << "Enter model: ";
            cin >> model;
            cout << "Enter rent per day: ";
            cin >> rentPerDay;
            cout << "Enter number of doors: ";
            cin >> numDoors;
            cout << "Enter seating capacity: ";
            cin >> seatingCapacity;
            rentalManager.addCar(brand, model, rentPerDay, numDoors, seatingCapacity);
            cout << "Car added successfully\n";
        }
        else if (adminChoice == 2)
        {
            string brand, model;
            float rentPerDay, cargoCapacity;
            int seatingCapacity;
            cout << "Enter brand: ";
            cin >> brand;
            cout << "Enter model: ";
            cin >> model;
            cout << "Enter rent per day: ";
            cin >> rentPerDay;
            cout << "Enter cargo capacity: ";
            cin >> cargoCapacity;
            cout << "Enter seating capacity: ";
            cin >> seatingCapacity;
            rentalManager.addVan(brand, model, rentPerDay, cargoCapacity, seatingCapacity);
            cout << "Van added successfully\n";
        }
        else if (adminChoice == 3)
        {
            string brand, model, typeOfBike;
            float rentPerDay;
            int engineCC;
            cout << "Enter brand: ";
            cin >> brand;
            cout << "Enter model: ";
            cin >> model;
            cout << "Enter rent per day: ";
            cin >> rentPerDay;
            cout << "Enter engine CC: ";
            cin >> engineCC;
            cout << "Enter type of bike: ";
            cin >> typeOfBike;
            rentalManager.addBike(brand, model, rentPerDay, engineCC, typeOfBike);
            cout << "Bike added successfully\n";
        }
    }
    else if (userType == 2)
    {
        string cnic;
        cout << "Enter CNIC: ";
        cin >> cnic;

        int customerId = -1;
        if (!Customer::cnicExists(cnic))
        {
            cout << "CNIC not found. Register first.\n";
            string name, password;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter password: ";
            cin >> password;
            customerId = Customer::registerCustomer(name, cnic, password);
            if (customerId == -1)
            {
                cout << "Registration failed\n";
                return 0;
            }
            cout << "Registration successful\n";
        }
        else
        {
            string password;
            cout << "Enter password: ";
            cin >> password;
            customerId = Customer::loginCustomer(cnic, password);
            if (customerId == -1)
            {
                cout << "Invalid password\n";
                return 0;
            }
            cout << "Login successful\n";
        }

        cout << "1. Rent Vehicle\n";
        cout << "2. Return Vehicle\n";
        cout << "Enter choice: ";
        int customerChoice;
        cin >> customerChoice;

        if (customerChoice == 1)
        {
            string type, brand, model;
            int days;
            cout << "Enter vehicle type: ";
            cin >> type;
            cout << "Enter brand: ";
            cin >> brand;
            cout << "Enter model: ";
            cin >> model;
            cout << "Enter number of days: ";
            cin >> days;

            int vehicleId = rentalManager.findAvailableVehicle(type, brand, model);
            if (vehicleId == -1)
            {
                cout << "Vehicle not available\n";
                return 0;
            }

            float bill = rentalManager.calculateBill(vehicleId, days);
            cout << "Total bill: " << bill << "\n";

            rentalManager.rentVehicle(customerId, vehicleId, days);
            cout << "Vehicle rented successfully\n";
        }
        else if (customerChoice == 2)
        {
            int vehicleId;
            cout << "Enter vehicle ID: ";
            cin >> vehicleId;
            rentalManager.returnVehicle(vehicleId);
            cout << "Vehicle returned successfully\n";
        }
    }

    return 0;
}