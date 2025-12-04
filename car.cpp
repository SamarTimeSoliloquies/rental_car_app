#include "car.h"
#include <fstream>

Car::Car() {
    numDoors = 0;
    seatingCapacity = 0;
}
Car::Car(const string& brand, const string& model, float rentPerDay,int numDoors, int seatingCapacity): Vehicle("Car", brand, model, rentPerDay),numDoors(numDoors), seatingCapacity(seatingCapacity) {
}

int Car::getNumDoors() const { 
    return numDoors;
}
int Car::getSeatingCapacity() const { 
    return seatingCapacity;
}

void Car::saveSpecific(ostream& os) const {
    os << numDoors << '\n' << seatingCapacity << '\n';
}