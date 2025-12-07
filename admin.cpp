// Admin.cpp
#include "Admin.h"
#include "Rental.h"   // ← This was missing → caused "identifier RentalManager undefined"
#include "FileManager.h"     // needed for loadVehicles()
#include "Car.h"             // needed for dynamic_cast / specific info (optional but nice)
#include "Van.h"
#include "Bike.h"
#include "loginmanager.h"
#include <iostream>
#include <fstream>
#include <sstream>

Admin::Admin(int id, const std::string& u, const std::string& p,
    const std::string& n, int a, const std::string& c,
    const std::string& ph, const std::string& e)
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
    std::cout << "\n=== ALL REGISTERED CUSTOMERS ===\n";
    std::ifstream file("customers.txt");
    if (!file.is_open() || file.peek() == EOF) {
        std::cout << "No customers registered yet.\n";
        return;
    }

    std::cout << "ID\tName\t\tAge\tCNIC\t\tPhone\t\tEmail\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> parts;

        while (std::getline(iss, token, ',')) {
            parts.push_back(token);
        }

        if (parts.size() >= 6) {
            std::cout << parts[0] << "\t"
                << parts[1].substr(0, 15) << "\t"
                << parts[2] << "\t"
                << parts[3] << "\t"
                << parts[4] << "\t"
                << parts[5] << "\n";
        }
    }
    std::cout << "--------------------------------------------------------------------------------\n";
}

void Admin::viewCustomerProfile(int customerId) const {
    std::ifstream file("customers.txt");
    std::string line;
    bool found = false;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string idStr;
        std::getline(iss, idStr, ',');
        if (std::stoi(idStr) == customerId) {
            found = true;

            std::cout << "\n=== CUSTOMER PROFILE ===\n";
            std::cout << "ID    : " << idStr << "\n";
            std::cout << line.substr(line.find(',') + 1) << "\n";  // rest of the data

            // Show customer's current rentals
            auto records = FileManager::loadRentalRecords();
            bool hasRental = false;
            for (const auto& r : records) {
                if (r.getCustomerId() == customerId && r.getStatus() == "Rented") {
                    if (!hasRental) {
                        std::cout << "\nCurrently Rented Vehicles:\n";
                        hasRental = true;
                    }
                    auto vehicles = FileManager::loadVehicles();
                    for (const auto v : vehicles) {
                        if (v->getVehicleId() == r.getVehicleId()) {
                            std::cout << "- " << v->getType() << " " << v->getBrand() << " " << v->getModel()
                                << " | Days: " << r.getRentDays()
                                << " | Total: Rs." << r.getTotalAmount() << "\n";
                            break;
                        }
                    }
                    for (auto v : vehicles) delete v;
                }
            }
            if (!hasRental) std::cout << "\nNo active rentals.\n";
            break;
        }
    }

    if (!found) std::cout << "Customer with ID " << customerId << " not found!\n";
}

void Admin::viewAllVehicles() const {
    auto vehicles = FileManager::loadVehicles();
    std::cout << "\n=== ALL VEHICLES IN SYSTEM ===\n";
    std::cout << "ID\tType\tBrand\t\tModel\t\tRent/Day\tStatus\n";
    std::cout << "-------------------------------------------------------------------------\n";

    for (const auto v : vehicles) {
        std::cout << v->getVehicleId() << "\t"
            << v->getType() << "\t"
            << v->getBrand() << "\t\t"
            << v->getModel() << "\t\t"
            << v->getRentPerDay() << "\t\t"
            << (v->getAvailability() ? "Available" : "Rented") << "\n";
    }

    std::cout << "-------------------------------------------------------------------------\n";
    for (auto v : vehicles) delete v;
}

void Admin::addNewVehicle() {
    RentalManager rm;  // we use RentalManager's add methods

    int choice;
    std::string brand, model, typeBike;
    float rent, cargo;
    int doors, seats, cc;

    std::cout << "\n=== ADD NEW VEHICLE ===\n";
    std::cout << "1. Car\n2. Van\n3. Bike\nChoice: ";
    std::cin >> choice;
    std::cin.ignore();

    std::cout << "Brand: ";
    std::getline(std::cin, brand);
    std::cout << "Model: ";
    std::getline(std::cin, model);
    std::cout << "Rent per day (Rs): ";
    std::cin >> rent;
    std::cin.ignore();

    if (choice == 1) {
        std::cout << "Number of doors: ";
        std::cin >> doors;
        std::cout << "Seating capacity: ";
        std::cin >> seats;
        rm.addCar(brand, model, rent, doors, seats);
    }
    else if (choice == 2) {
        std::cout << "Cargo capacity (kg): ";
        std::cin >> cargo;
        std::cout << "Seating capacity: ";
        std::cin >> seats;
        rm.addVan(brand, model, rent, cargo, seats);
    }
    else if (choice == 3) {
        std::cout << "Engine CC: ";
        std::cin >> cc;
        std::cout << "Type (Sport/Cruiser/etc): ";
        std::cin.ignore();
        std::getline(std::cin, typeBike);
        rm.addBike(brand, model, rent, cc, typeBike);
    }
    else {
        std::cout << "Invalid choice!\n";
        return;
    }

    std::cout << "Vehicle added successfully!\n";
}