// Van.h
#pragma once
#include "Vehicle.h"

class Van : public Vehicle {
private:
    float cargoCapacity;
    int seatingCapacity;

public:
    Van(const std::string& brand, const std::string& model, float rentPerDay,
        float cargo, int seats);

    float getCargoCapacity() const { return cargoCapacity; }
    int getSeatingCapacity() const { return seatingCapacity; }

    void saveSpecific(std::ostream& os) const override;
};