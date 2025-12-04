#include "loginmanager.h"
#include "Vehicle.h"
#include "Car.h"
#include "Van.h"
#include "Bike.h"
#include "rental.h"
#include "FileManager.h"
#include <iostream>

void RentalManager::addCar(const string& brand, const string& model, float rentPerDay,
    int numDoors, int seatingCapacity) {
    auto vehicles = FileManager::loadVehicles();
    Vehicle* newV = new Car(brand, model, rentPerDay, numDoors, seatingCapacity);
    newV->setVehicleId(Vehicle::generateNextId());
    vehicles.push_back(newV);
    FileManager::saveVehicles(vehicles);
    for (auto v : vehicles) delete v;  // clean up including the new one (data is already saved)
}

void RentalManager::addVan(const string& brand, const string& model, float rentPerDay,
    float cargoCapacity, int seatingCapacity) {
    auto vehicles = FileManager::loadVehicles();
    Vehicle* newV = new Van(brand, model, rentPerDay, cargoCapacity, seatingCapacity);
    newV->setVehicleId(Vehicle::generateNextId());
    vehicles.push_back(newV);
    FileManager::saveVehicles(vehicles);
    for (auto v : vehicles) delete v;
}

void RentalManager::addBike(const std::string& brand, const std::string& model, float rentPerDay,
    int engineCC, const std::string& typeOfBike) {
    auto vehicles = FileManager::loadVehicles();
    Vehicle* newV = new Bike(brand, model, rentPerDay, engineCC, typeOfBike);
    newV->setVehicleId(Vehicle::generateNextId());
    vehicles.push_back(newV);
    FileManager::saveVehicles(vehicles);
    for (auto v : vehicles) delete v;
}

bool RentalManager::checkAvailability(int vehicleId) {
    auto vehicles = FileManager::loadVehicles();
    for (const auto v : vehicles) {
        if (v->getVehicleId() == vehicleId) {
            bool avail = v->getAvailability();
            for (auto ptr : vehicles) delete ptr;
            return avail;
        }
    }
    for (auto ptr : vehicles) delete ptr;
    return false;
}

int RentalManager::findAvailableVehicle(const std::string& type, const std::string& brand, const std::string& model) {
    auto vehicles = FileManager::loadVehicles();
    for (const auto v : vehicles) {
        if (v->getAvailability() && v->getType() == type &&
            v->getBrand() == brand && v->getModel() == model) {
            int id = v->getVehicleId();
            for (auto ptr : vehicles) delete ptr;
            return id;
        }
    }
    for (auto ptr : vehicles) delete ptr;
    return -1;
}

float RentalManager::calculateBill(int vehicleId, int days) {
    auto vehicles = FileManager::loadVehicles();
    for (const auto v : vehicles) {
        if (v->getVehicleId() == vehicleId) {
            float bill = v->getRentPerDay() * days;
            for (auto ptr : vehicles) delete ptr;
            return bill;
        }
    }
    for (auto ptr : vehicles) delete ptr;
    return 0.0f;
}

RentalRecord RentalManager::createRentalRecord(int customerId, int vehicleId, int days) {
    float bill = calculateBill(vehicleId, days);
    return RentalRecord(customerId, vehicleId, days, bill);
}

void RentalManager::rentVehicle(int customerId, int vehicleId, int days) {
    auto vehicles = FileManager::loadVehicles();

    Vehicle* target = nullptr;
    for (auto v : vehicles) {
        if (v->getVehicleId() == vehicleId) {
            target = v;
            break;
        }
    }

    if (!target || !target->getAvailability()) {
        std::cout << "Vehicle not available or not found.\n";
        for (auto v : vehicles) delete v;
        return;
    }

    target->setAvailability(false);
    FileManager::saveVehicles(vehicles);
    for (auto v : vehicles) delete v;  // cleanup

    RentalRecord newRecord(customerId, vehicleId, days, target->getRentPerDay() * days);
    newRecord.setRecordId(RentalRecord::generateNextRecordId());

    auto records = FileManager::loadRentalRecords();
    records.push_back(newRecord);
    FileManager::saveRentalRecords(records);

    std::string msg = "Customer " + std::to_string(customerId) +
        " rented " + target->getType() + " " + target->getBrand() + " " + target->getModel() +
        " (ID: " + std::to_string(vehicleId) + ") for " + std::to_string(days) +
        " days. Total: " + std::to_string(newRecord.getTotalAmount());
    FileManager::logRental(msg);
}

void RentalManager::returnVehicle(int vehicleId) {
    auto vehicles = FileManager::loadVehicles();
    Vehicle* target = nullptr;
    for (auto v : vehicles) {
        if (v->getVehicleId() == vehicleId) {
            target = v;
            break;
        }
    }
    if (target) target->setAvailability(true);
    FileManager::saveVehicles(vehicles);
    for (auto v : vehicles) delete v;

    auto records = FileManager::loadRentalRecords();
    for (auto& r : records) {
        if (r.getVehicleId() == vehicleId && r.getStatus() == "Rented") {
            r.updateStatus("Returned");
            FileManager::logRental("Customer " + std::to_string(r.getCustomerId()) +
                " returned vehicle " + std::to_string(vehicleId));
            FileManager::saveRentalRecords(records);
            return;
        }
    }
    std::cout << "No active rental found for vehicle " << vehicleId << "\n";
}
void RentalManager::getVehicleDetails(int vehicleId) {
    auto vehicles = FileManager::loadVehicles();
    for (const auto v : vehicles) {
        if (v->getVehicleId() == vehicleId) {
            std::cout << "Vehicle ID: " << v->getVehicleId() << "\n";
            std::cout << "Type: " << v->getType() << "\n";
            std::cout << "Brand: " << v->getBrand() << "\n";
            std::cout << "Model: " << v->getModel() << "\n";
            std::cout << "Rent per Day: " << v->getRentPerDay() << "\n";
            std::cout << "Availability: " << (v->getAvailability() ? "Available" : "Rented") << "\n";
            for (auto ptr : vehicles) delete ptr;
            return;
        }
    }
    std::cout << "Vehicle with ID " << vehicleId << " not found.\n";
    for (auto ptr : vehicles) delete ptr;
}