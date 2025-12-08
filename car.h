// Car.h
#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
private:
    int numDoors;
    int seatingCapacity;

public:
    Car(const std::string& brand, const std::string& model, float rentPerDay,
        int doors, int seats);

    int getNumDoors() const { return numDoors; }
    int getSeatingCapacity() const { return seatingCapacity; }

    void saveSpecific(std::ostream& os) const override;  // ← override keyword correct
};