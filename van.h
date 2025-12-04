#ifndef van_h
#define van_h
#include "vehicle.h"

class Van : public Vehicle {
private:
    float cargoCapacity;
    int seatingCapacity;

public:
    Van();
    Van(const string& brand, const string& model, float rentPerDay,float cargoCapacity, int seatingCapacity);

    float getCargoCapacity() const;
    int getSeatingCapacity() const;

    void saveSpecific(ostream& os) const override;
};
#endif