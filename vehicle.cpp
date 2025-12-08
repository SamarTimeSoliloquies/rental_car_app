// Vehicle.cpp
#include "Vehicle.h"

int Vehicle::nextId = 1;

int Vehicle::generateNextId()
{
    return nextId++;
}

Vehicle::Vehicle(const std::string& t, const std::string& b, const std::string& m, float r)
    : type(t), brand(b), model(m), rentPerDay(r)
{
    // DO NOT assign ID here → done only when adding new vehicle or loading
}