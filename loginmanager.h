#ifndef loginmanager_h
#define loginmanager_h
#include <string>
#include <vector>
using namespace std;

class Vehicle;
class RentalRecord;

class RentalManager {
public:
    RentalManager() = default;

    void addCar(const string& brand, const string& model, float rentPerDay, int numDoors, int seatingCapacity);
    void addVan(const string& brand, const string& model, float rentPerDay, float cargoCapacity, int seatingCapacity);
    void addBike(const string& brand, const string& model, float rentPerDay, int engineCC, const string& typeOfBike);

    bool checkAvailability(int vehicleId);
    int findAvailableVehicle(const string& type, const string& brand, const string& model);
    void rentVehicle(int customerId, int vehicleId, int days);
    void returnVehicle(int vehicleId);
    float calculateBill(int vehicleId, int days);
    RentalRecord createRentalRecord(int customerId, int vehicleId, int days);

    void getVehicleDetails(int vehicleId);
};
#endif
