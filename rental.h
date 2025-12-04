#ifndef rental_h
#define rental_h
#include <string>
#include<iostream>
#include <vector>
class FileManager;

class RentalRecord {
    friend class FileManager;

private:
    int recordId = 0;
    int customerId;
    int vehicleId;
    int rentDays;
    float totalAmount;
    std::string status = "Rented";
    static int nextRecordId;

public:
    static int generateNextRecordId();

    RentalRecord(int customerId, int vehicleId, int days, float totalAmount);

    int getRecordId() const;
    int getCustomerId() const;
    int getVehicleId() const;
    int getRentDays() const;
    float getTotalAmount() const;
    const std::string& getStatus() const;

    void updateStatus(const std::string& newStatus);
    void getRecordDetails() const;
    void setRecordId(int id) { recordId = id; }
};
#endif