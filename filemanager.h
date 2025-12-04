#ifndef filemanager_h
#define filemanager_h
#include <vector>
#include <string>
using namespace std;

class Vehicle;
class RentalRecord;

class FileManager {
public:
    static vector<Vehicle*> loadVehicles();
    static void saveVehicles(const std::vector<Vehicle*>& vehicles);
    static vector<RentalRecord> loadRentalRecords();
    static void saveRentalRecords(const std::vector<RentalRecord>& records);
    static void logRental(const std::string& message);
};
#endif