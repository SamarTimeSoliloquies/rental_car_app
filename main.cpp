#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>

#include "login.h"
#include "loginmanager.h"
#include "Customer.h"
#include "Admin.h"
#include "Vehicle.h"
#include "Car.h"
#include "Van.h"
#include "Bike.h"
#include "Rental.h"
#include "FileManager.h"

using namespace std;

void adminMenu(int adminId);
void customerMenu(int customerId);
void registerNewCustomer();
void displayAvailableVehicles();
void displayAllVehicles();

int main()
{
    Customer::loadNextId();

    system("cls");
    cout << "=====================================\n";
    cout << "   CAR RENTAL MANAGEMENT SYSTEM\n";
    cout << "=====================================\n\n";

    while (true)
    {
        cout << "1. Admin Login\n";
        cout << "2. Customer Menu (Login / Register)\n";
        cout << "3. Exit\n\n";
        cout << "Enter choice: ";

        char choice;
        cin >> choice;
        cin.ignore();

        if (choice == '3') break;

        if (choice == '1')
        {
            string username, password;
            cout << "\n--- Admin Login ---\n";
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            LoginSystem login;
            int adminId = login.validateCredentials(username, password);

            if (adminId != -1)
            {
                cout << "\nLogin successful! Welcome Admin ID: " << adminId << "\n";
                (void)_getch();
                adminMenu(adminId);
            }
            else
            {
                cout << "\nInvalid username or password!\n";
                _getch();
            }
        }
        else if (choice == '2')
        {
            cout << "\nEnter Customer ID (or 0 to register): ";
            int custId;
            cin >> custId;
            cin.ignore();

            if (custId == 0)
            {
                registerNewCustomer();
            }
            else
            {
                ifstream file("customers.txt");
                bool found = false;
                string line;
                while (getline(file, line))
                {
                    stringstream ss(line);
                    string idStr;
                    getline(ss, idStr, ',');
                    if (stoi(idStr) == custId)
                    {
                        found = true;
                        break;
                    }
                }
                file.close();

                if (found)
                    customerMenu(custId);
                else
                {
                    cout << "\nCustomer ID not found!\n";
                    _getch();
                }
            }
        }

        system("cls");
    }

    cout << "\nThank you for using the system!\n";
    return 0;
}

void registerNewCustomer()
{
    system("cls");
    cout << "=== Register New Customer ===\n\n";

    string name, cnic, phone, email;
    int age;

    cout << "Full Name     : ";
    getline(cin, name);
    cout << "Age           : ";
    cin >> age;
    cin.ignore();
    cout << "CNIC          : ";
    getline(cin, cnic);
    cout << "Phone Number  : ";
    getline(cin, phone);
    cout << "Email         : ";
    getline(cin, email);

    Customer newCustomer(name, age, cnic, phone, email);

    ofstream out("customers.txt", ios::app);
    out << newCustomer.getCustomerId() << ","
        << name << "," << age << "," << cnic << "," << phone << "," << email << "\n";
    out.close();

    cout << "\n*** Registration Successful! ***\n";
    cout << "Your Customer ID is: " << newCustomer.getCustomerId() << "\n";
    cout << "Please remember it for login.\n";
    _getch();
}

void displayAvailableVehicles()
{
    auto vehicles = FileManager::loadVehicles();

    cout << "\n=== AVAILABLE VEHICLES ===\n";
    cout << "ID\tType\tBrand\t\tModel\t\tRent/Day\tSpecs\n";
    cout << "-------------------------------------------------------------------------\n";

    bool hasAvailable = false;
    for (const auto v : vehicles)
    {
        if (v->getAvailability())
        {
            hasAvailable = true;
            cout << v->getVehicleId() << "\t"
                << v->getType() << "\t"
                << v->getBrand() << "\t\t"
                << v->getModel() << "\t\t"
                << v->getRentPerDay() << "\t\t";

            if (v->getType() == "Car")
            {
                auto car = dynamic_cast<Car*>(v);
                cout << "Doors: " << car->getNumDoors() << ", Seats: " << car->getSeatingCapacity();
            }
            else if (v->getType() == "Van")
            {
                auto van = dynamic_cast<Van*>(v);
                cout << "Cargo: " << van->getCargoCapacity() << "kg, Seats: " << van->getSeatingCapacity();
            }
            else if (v->getType() == "Bike")
            {
                auto bike = dynamic_cast<Bike*>(v);
                cout << bike->getEngineCC() << "cc, " << bike->getTypeOfBike();
            }
            cout << "\n";
        }
    }

    if (!hasAvailable)
        cout << "No vehicles available at the moment.\n";

    cout << "-------------------------------------------------------------------------\n";

    for (auto v : vehicles) delete v;
    _getch();
}

void displayAllVehicles()
{
    auto vehicles = FileManager::loadVehicles();

    cout << "\n=== ALL VEHICLES ===\n";
    cout << "ID\tType\tBrand\t\tModel\t\tRent/Day\tStatus\n";
    cout << "-------------------------------------------------------------------------\n";

    for (const auto v : vehicles)
    {
        cout << v->getVehicleId() << "\t"
            << v->getType() << "\t"
            << v->getBrand() << "\t\t"
            << v->getModel() << "\t\t"
            << v->getRentPerDay() << "\t\t"
            << (v->getAvailability() ? "Available" : "Rented") << "\n";
    }

    cout << "-------------------------------------------------------------------------\n";
    for (auto v : vehicles) delete v;
    _getch();
}

void customerMenu(int customerId)
{
    RentalManager rm;

    while (true)
    {
        system("cls");
        cout << "=== CUSTOMER MENU - ID: " << customerId << " ===\n\n";
        cout << "1. View My Profile\n";
        cout << "2. View Available Vehicles\n";
        cout << "3. Rent a Vehicle\n";
        cout << "4. View My Current Rentals\n";
        cout << "5. Return a Vehicle\n";
        cout << "6. Logout\n\n";
        cout << "Choice: ";

        char ch;
        cin >> ch;
        cin.ignore();

        if (ch == '6') break;

        switch (ch)
        {
        case '1':
        {
            ifstream file("customers.txt");
            string line;
            while (getline(file, line))
            {
                stringstream ss(line);
                string idStr;
                getline(ss, idStr, ',');
                if (stoi(idStr) == customerId)
                {
                    cout << "\n--- Your Profile ---\n";
                    cout << line.substr(line.find(',') + 1) << "\n\n";
                    break;
                }
            }
            file.close();
            _getch();
            break;
        }

        case '2':
            displayAvailableVehicles();
            break;

        case '3':
        {
            displayAvailableVehicles();

            int vid, days;
            cout << "\nEnter Vehicle ID to rent: ";
            if (!(cin >> vid))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nInvalid Vehicle ID!\n";
                _getch();
                break;
            }

            cout << "Number of days: ";
            if (!(cin >> days) || days <= 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "\nInvalid number of days! Must be a positive number.\n";
                _getch();
                break;
            }

            if (rm.checkAvailability(vid))
            {
                rm.rentVehicle(customerId, vid, days);
                cout << "\nVehicle rented successfully!\n";
            }
            else
            {
                cout << "\nVehicle not available or invalid ID!\n";
            }
            _getch();
            break;
        }

        case '4':
        {
            auto records = FileManager::loadRentalRecords();
            auto vehicles = FileManager::loadVehicles();

            cout << "\nYour Current Rentals:\n";
            bool found = false;

            for (const auto& r : records)
            {
                if (r.getCustomerId() == customerId && r.getStatus() == "Rented")
                {
                    found = true;
                    for (const auto v : vehicles)
                    {
                        if (v->getVehicleId() == r.getVehicleId())
                        {
                            cout << v->getBrand() << " " << v->getModel()
                                << " | Days: " << r.getRentDays()
                                << " | Total: Rs." << r.getTotalAmount() << "\n";
                            break;
                        }
                    }
                }
            }

            if (!found) cout << "No active rentals.\n";
            cout << "\n";

            for (auto v : vehicles) delete v;
            _getch();
            break;
        }

        case '5':
        {
            cout << "Enter Vehicle ID to return: ";
            int vid;
            cin >> vid;
            rm.returnVehicle(vid);
            _getch();
            break;
        }
        }
    }
}

void adminMenu(int adminId)
{
    Admin admin(adminId, "", "", "", 0, "", "", "");
    RentalManager rm;

    while (true)
    {
        system("cls");
        cout << "=== ADMIN PANEL - ID: " << adminId << " ===\n\n";
        cout << "1. Add New Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. View Available Vehicles\n";
        cout << "4. View All Customers\n";
        cout << "5. Rent Vehicle for Customer\n";
        cout << "6. Return Vehicle\n";
        cout << "7. View Rental Logs\n";
        cout << "8. Logout\n\n";
        cout << "Choice: ";

        char ch;
        cin >> ch;
        cin.ignore();

        if (ch == '8') break;

        int cid, vid, days;

        switch (ch)
        {
        case '1':
            admin.addNewVehicle();
            break;

        case '2':
            displayAllVehicles();
            break;

        case '3':
            displayAvailableVehicles();
            break;

        case '4':
        {
            cout << "\nAll Registered Customers:\n";
            ifstream file("customers.txt");
            string line;
            bool hasData = false;
            while (getline(file, line))
            {
                if (!hasData) hasData = true;
                cout << line << "\n";
            }
            file.close();
            if (!hasData) cout << "No customers yet.\n";
            _getch();
            break;
        }

        case '5':
            cout << "Customer ID: ";
            if (!(cin >> cid) || cid <= 0) {
                cout << "Invalid Customer ID!\n"; _getch(); break;
            }
            cout << "Vehicle ID : ";
            if (!(cin >> vid) || vid <= 0) {
                cout << "Invalid Vehicle ID!\n"; _getch(); break;
            }
            cout << "Days       : ";
            if (!(cin >> days) || days <= 0) {
                cout << "Invalid number of days!\n"; _getch(); break;
            }
            rm.rentVehicle(cid, vid, days);
            cout << "\nRented successfully!\n";
            _getch();
            break;

        case '6':
            cout << "Vehicle ID to return: ";
            cin >> vid;
            rm.returnVehicle(vid);
            _getch();
            break;

        case '7':
            system("type rental_logs.txt");
            cout << "\n\nPress any key to continue...";
            _getch();
            break;
        }
    }
}
