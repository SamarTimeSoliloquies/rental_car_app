#include "rental.h"
#include <iostream>
using namespace std;

int RentalRecord::nextRecordId = 1;

int RentalRecord::generateNextRecordId() {
    return nextRecordId++;
}

RentalRecord::RentalRecord(int customerId, int vehicleId, int days, float totalAmount) : customerId(customerId), vehicleId(vehicleId), rentDays(days), totalAmount(totalAmount) {

}

int RentalRecord::getRecordId() const { 
    return recordId;
}
int RentalRecord::getCustomerId() const { 
    return customerId;
}
int RentalRecord::getVehicleId() const {
    return vehicleId;
}
int RentalRecord::getRentDays() const { 
    return rentDays;
}
float RentalRecord::getTotalAmount() const {
    return totalAmount;
}
const std::string& RentalRecord::getStatus() const { 
    return status; 
}

void RentalRecord::updateStatus(const string& newStatus) {
    status = newStatus;
}

void RentalRecord::getRecordDetails() const {
    cout << "Record ID: " << recordId << endl;
    cout << "Customer ID: " << customerId << endl;
    cout << "Vehicle ID: " << vehicleId << endl;
    cout << "Rent Days: " << rentDays << endl;
    cout << "Total Amount: " << totalAmount << endl;
    cout << "Status: " << status << endl;
}