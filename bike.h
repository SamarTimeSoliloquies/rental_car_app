#ifndef bike_h
#define bike_h
#include "vehicle.h"

class Bike : public Vehicle {
private:
    int engineCC;
    string typeOfBike;

public:
    Bike();
    Bike(const string& brand, const string& model, float rentPerDay,int engineCC, const string& typeOfBike);

    int getEngineCC() const;
    const string& getTypeOfBike() const;

    void saveSpecific(ostream& os) const override;
};
#endif