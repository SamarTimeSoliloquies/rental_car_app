// Bike.cpp
#include "Bike.h"

Bike::Bike(const std::string& brand, const std::string& model, float rentPerDay,
    int cc, const std::string& t)
    : Vehicle("Bike", brand, model, rentPerDay),
    engineCC(cc), typeOfBike(t)
{
}

void Bike::saveSpecific(std::ostream& os) const
{
    os << engineCC << '\n' << typeOfBike << '\n';
}