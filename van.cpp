#include "van.h"
#include <fstream>
Van::Van() {
    cargoCapacity = 0.0;
    seatingCapacity = 0;
}

Van::Van(const std::string& brand, const std::string& model, float rentPerDay,float cargoCapacity, int seatingCapacity): Vehicle("Van", brand, model, rentPerDay),cargoCapacity(cargoCapacity), seatingCapacity(seatingCapacity) {
}

float Van::getCargoCapacity() const { 
    return cargoCapacity;
}
int Van::getSeatingCapacity() const {
    return seatingCapacity;
}

void Van::saveSpecific(ostream& os) const {
    os << cargoCapacity << '\n' << seatingCapacity << '\n';
}