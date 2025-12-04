#include "filemanager.h"
#include "vehicle.h"
#include "car.h"
#include "van.h"
#include "bike.h"
#include "rental.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

vector<Vehicle*> FileManager::loadVehicles() {
    vector<Vehicle*> vehicles;
    ifstream file("vehicles.txt");
    if (!file.is_open()) {
        Vehicle::nextId = 1;
        return vehicles;
    }

    int maxId = 0;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        string vehType = line;

        getline(file, line); int id = stoi(line);
        if (id > maxId) maxId = id;

        getline(file, line); string brand = line;
        getline(file, line); string model = line;
        getline(file, line); float rentPerDay = stof(line);
        getline(file, line); bool isAvailable = (line == "true");

        string spec1, spec2;
        getline(file, spec1);
        getline(file, spec2);

        Vehicle* v = nullptr;

        if (vehType == "Car") {
            v = new Car(brand, model, rentPerDay, stoi(spec1), stoi(spec2));
        }
        else if (vehType == "Van") {
            v = new Van(brand, model, rentPerDay, stof(spec1), stoi(spec2));
        }
        else if (vehType == "Bike") {
            v = new Bike(brand, model, rentPerDay, stoi(spec1), spec2);
        }

        if (v) {
            v->setVehicleId(id);
            v->setAvailability(isAvailable);
            vehicles.push_back(v);
        }
    }

    Vehicle::nextId = maxId + 1;
    return vehicles;
}

void FileManager::saveVehicles(const std::vector<Vehicle*>& vehicles) {
    ofstream file("vehicles.txt");
    if (!file) {
        cerr << "Cannot open vehicles.txt for writing!\n";
        return;
    }
    for (const auto v : vehicles) {
        file << v->getType() << endl;
        file << v->getVehicleId() << endl;
        file << v->getBrand() << endl;
        file << v->getModel() << endl;
        file << v->getRentPerDay() << endl;
        file << (v->getAvailability() ? "true" : "false") << endl;
        v->saveSpecific(file);
    }
}

vector<RentalRecord> FileManager::loadRentalRecords() {
    vector<RentalRecord> records;
    ifstream file("rental_records.txt");
    if (!file) {
        RentalRecord::nextRecordId = 1;
        return records;
    }

    int maxId = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        string token;

        getline(iss, token, ','); int recordId = stoi(token);
        if (recordId > maxId) maxId = recordId;
        getline(iss, token, ','); int customerId = stoi(token);
        getline(iss, token, ','); int vehicleId = stoi(token);
        getline(iss, token, ','); int rentDays = stoi(token);
        getline(iss, token, ','); float totalAmount = stof(token);
        getline(iss, token); 
        string status = token;

        RentalRecord r(customerId, vehicleId, rentDays, totalAmount);
        r.setRecordId(recordId);
        r.updateStatus(status);
        records.push_back(r);
    }

    RentalRecord::nextRecordId = maxId + 1;
    return records;
}

void FileManager::saveRentalRecords(const std::vector<RentalRecord>& records) {
    ofstream file("rental_records.txt");
    if (!file) {
        cerr << "Cannot open rental_records.txt for writing!\n";
        return;
    }
    for (const auto& r : records) {
        file << r.getRecordId() << ',' << r.getCustomerId() << ','<< r.getVehicleId() << ',' << r.getRentDays() << ','<< r.getTotalAmount() << ',' << r.getStatus() << '\n';
    }
}

void FileManager::logRental(const string& message) {
    ofstream log("rental_logs.txt", ios::app);
    if (log) {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        log << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " : " << message << '\n';
    }
}