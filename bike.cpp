#include "bike.h"
#include <fstream>

Bike::Bike() {
    engineCC = 0;
    typeOfBike = "";
}
Bike::Bike(const string& brand, const string& model, float rentPerDay,int engineCC, const string& typeOfBike) : Vehicle("Bike", brand, model, rentPerDay),engineCC(engineCC), typeOfBike(typeOfBike) {

}

int Bike::getEngineCC() const { 
    return engineCC; 
}
const string& Bike::getTypeOfBike() const { 
    return typeOfBike;
}

void Bike::saveSpecific(ostream& os) const {
    os << engineCC << '\n' << typeOfBike << '\n';
}