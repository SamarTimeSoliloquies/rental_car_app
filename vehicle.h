#ifndef vehicle_h
#define veicle_h
#include<iostream>
#include <string>
#include <fstream>
using namespace std;
class FileManager;
class Vehicle {
private:
    int vehicleId;
    string type;
    string brand;
    string model;
    float rentPerDay;
    bool isAvailable;
    static int nextId;
    friend class FileManager;
public:
    Vehicle();
    Vehicle(const string& t, const string& b, const string& m, float r);
    virtual ~Vehicle() = default;

    int getVehicleId() const;
    const string& getType() const;
    const string& getBrand() const;
    const string& getModel() const;
    float getRentPerDay() const;
    bool getAvailability() const;
    void setAvailability(bool status);
    static int generateNextId();
    void setVehicleId(int id);

    virtual void saveSpecific(ostream& os) const = 0;
    static int getNextId() { return nextId++; }
};
#endif