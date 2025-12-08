// Car.cpp
#include "Car.h"

Car::Car(const std::string& brand, const std::string& model, float rentPerDay,
    int doors, int seats)
    : Vehicle("Car", brand, model, rentPerDay),
    numDoors(doors), seatingCapacity(seats)
{
}

void Car::saveSpecific(std::ostream& os) const
{
    os << numDoors << '\n' << seatingCapacity << '\n';
}