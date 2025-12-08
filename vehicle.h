// Vehicle.h
#pragma once
#include <string>
#include <ostream>

class Vehicle {
private:
    int vehicleId = 0;
    std::string type;
    std::string brand;
    std::string model;
    float rentPerDay = 0.0f;
    bool isAvailable = true;
    static int nextId;

    friend class FileManager;  // needed for nextId access

public:
    static int generateNextId();  // returns nextId and increments

    Vehicle(const std::string& t, const std::string& b, const std::string& m, float r);
    virtual ~Vehicle() = default;

    // Getters
    int getVehicleId() const { return vehicleId; }
    const std::string& getType() const { return type; }
    const std::string& getBrand() const { return brand; }
    const std::string& getModel() const { return model; }
    float getRentPerDay() const { return rentPerDay; }
    bool getAvailability() const { return isAvailable; }

    // Setters
    void setVehicleId(int id) { vehicleId = id; }
    void setAvailability(bool status) { isAvailable = status; }

    // Pure virtual - forces override in derived classes
    virtual void saveSpecific(std::ostream& os) const = 0;
};