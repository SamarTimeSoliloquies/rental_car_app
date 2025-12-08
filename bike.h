// Bike.h
#pragma once
#include "Vehicle.h"

class Bike : public Vehicle {
private:
    int engineCC;
    std::string typeOfBike;

public:
    Bike(const std::string& brand, const std::string& model, float rentPerDay,
        int cc, const std::string& t);

    int getEngineCC() const { return engineCC; }
    const std::string& getTypeOfBike() const { return typeOfBike; }

    void saveSpecific(std::ostream& os) const override;
};