#include "Admin.h"
#include "Rental.h"   
#include "FileManager.h"     
#include "Car.h"             
#include "Van.h"
#include "Bike.h"
#include "loginmanager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Admin::Admin(int id, const string& u, const string& p,
    const string& n, int a, const string& c,
    const string& ph, const string& e)
    : Person(n, a, c, ph, e), adminId(id), username(u), password(p) {
}

void Admin::rentVehicle(int customerId, int vehicleId, int days) {
    RentalManager rm;
    rm.rentVehicle(customerId, vehicleId, days);
}

void Admin::returnVehicle(int vehicleId) {
    RentalManager rm;
    rm.returnVehicle(vehicleId);
}

void Admin::viewCustomers() const {
    cout << "\n=== ALL REGISTERED CUSTOMERS ===\n";
    ifstream file("customers.txt");
    if (!file.is_open() || file.peek() == EOF) {
        cout << "No customers registered yet.\n";
        return;
    }

    cout << "ID\tName\t\tAge\tCNIC\t\tPhone\t\tEmail\n";
    cout << "--------------------------------------------------------------------------------\n";

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        vector<string> parts;

        while (getline(iss, token, ',')) {
            parts.push_back(token);
        }

        if (parts.size() >= 6) {
           cout << parts[0] << "\t"
                << parts[1].substr(0, 15) << "\t"
                << parts[2] << "\t"
                << parts[3] << "\t"
                << parts[4] << "\t"
                << parts[5] << "\n";
        }
    }
    cout << "--------------------------------------------------------------------------------\n";
}

void Admin::viewCustomerProfile(int customerId) const {
    ifstream file("customers.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        istringstream iss(line);
        string idStr;
        getline(iss, idStr, ',');
        if (stoi(idStr) == customerId) {
            found = true;

            cout << "\n=== CUSTOMER PROFILE ===\n";
            cout << "ID    : " << idStr << "\n";
            cout << line.substr(line.find(',') + 1) << "\n";  

            
            auto records = FileManager::loadRentalRecords();
            bool hasRental = false;
            for (const auto& r : records) {
                if (r.getCustomerId() == customerId && r.getStatus() == "Rented") {
                    if (!hasRental) {
                        cout << "\nCurrently Rented Vehicles:\n";
                        hasRental = true;
                    }
                    auto vehicles = FileManager::loadVehicles();
                    for (const auto v : vehicles) {
                        if (v->getVehicleId() == r.getVehicleId()) {
                           cout << "- " << v->getType() << " " << v->getBrand() << " " << v->getModel()
                                << " | Days: " << r.getRentDays()
                                << " | Total: Rs." << r.getTotalAmount() << "\n";
                            break;
                        }
                    }
                    for (auto v : vehicles) delete v;
                }
            }
            if (!hasRental) cout << "\nNo active rentals.\n";
            break;
        }
    }

    if (!found) cout << "Customer with ID " << customerId << " not found!\n";
}

void Admin::viewAllVehicles() const {
    auto vehicles = FileManager::loadVehicles();
    cout << "\n=== ALL VEHICLES IN SYSTEM ===\n";
    cout << "ID\tType\tBrand\t\tModel\t\tRent/Day\tStatus\n";
    cout << "-------------------------------------------------------------------------\n";

    for (const auto v : vehicles) {
       cout << v->getVehicleId() << "\t"
            << v->getType() << "\t"
            << v->getBrand() << "\t\t"
            << v->getModel() << "\t\t"
            << v->getRentPerDay() << "\t\t"
            << (v->getAvailability() ? "Available" : "Rented") << "\n";
    }

    cout << "-------------------------------------------------------------------------\n";
    for (auto v : vehicles) delete v;
}

void Admin::addNewVehicle() {
    RentalManager rm;  

    int choice;
    string brand, model, typeBike;
    float rent, cargo;
    int doors, seats, cc;

    cout << "\n=== ADD NEW VEHICLE ===\n";
    cout << "1. Car\n2. Van\n3. Bike\nChoice: ";
    cin >> choice;
    cin.ignore();

    cout << "Brand: ";
    getline(cin, brand);
    cout << "Model: ";
    getline(cin, model);
    cout << "Rent per day (Rs): ";
    cin >> rent;
    cin.ignore();

    if (choice == 1) {
        cout << "Number of doors: ";
        cin >> doors;
        cout << "Seating capacity: ";
        cin >> seats;
        rm.addCar(brand, model, rent, doors, seats);
    }
    else if (choice == 2) {
        cout << "Cargo capacity (kg): ";
        cin >> cargo;
        cout << "Seating capacity: ";
        cin >> seats;
        rm.addVan(brand, model, rent, cargo, seats);
    }
    else if (choice == 3) {
        cout << "Engine CC: ";
        cin >> cc;
        cout << "Type (Sport/Cruiser/etc): ";
        cin.ignore();
        getline(cin, typeBike);
        rm.addBike(brand, model, rent, cc, typeBike);
    }
    else {
        cout << "Invalid choice!\n";
        return;
    }

    cout << "Vehicle added successfully!\n";
}