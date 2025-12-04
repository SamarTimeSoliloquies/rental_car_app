#include "vehicle.h"

int Vehicle::nextId = 1;
Vehicle::Vehicle() {
    type = "";
    brand = "";
    model = "";
    rentPerDay = 0.0;
    isAvailable = true;
    vehicleId = getNextId();    
}

Vehicle::Vehicle(const string& t, const string& b, const string& m, float r) {
    type = t;
    brand = b;
    model = m;
    rentPerDay = r;
    vehicleId = generateNextId();
}

void Vehicle::setVehicleId(int id) {
    this->vehicleId = id;
}

int Vehicle::getVehicleId() const {
    return vehicleId; 
}
const string& Vehicle::getType() const { 
    return type; }
const string& Vehicle::getBrand() const { 
    return brand; 
}
const string& Vehicle::getModel() const { 
    return model;
}
float Vehicle::getRentPerDay() const { 
    return rentPerDay; 
}
bool Vehicle::getAvailability() const { 
    return isAvailable;
}
void Vehicle::setAvailability(bool status) { 
    isAvailable = status; 

}
int Vehicle::generateNextId() {
    return nextId++;
}