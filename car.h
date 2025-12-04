#ifndef car_h
#define car_h
#include<string>

class Car : public Vehicle {
private:
    int numDoors;
    int seatingCapacity;

public:
    Car();
    Car(const string& brand, const string& model, float rentPerDay,int numDoors, int seatingCapacity);

    int getNumDoors() const;
    int getSeatingCapacity() const;

    void saveSpecific(ostream& os) const override;
};
#endif