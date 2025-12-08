// Van.cpp
#include "Van.h"

Van::Van(const std::string& brand, const std::string& model, float rentPerDay,
    float cargo, int seats)
    : Vehicle("Van", brand, model, rentPerDay),
    cargoCapacity(cargo), seatingCapacity(seats)
{
}

void Van::saveSpecific(std::ostream& os) const
{
    os << cargoCapacity << '\n' << seatingCapacity << '\n';
}