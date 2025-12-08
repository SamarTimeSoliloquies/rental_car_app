#include "Customer.h"
#include "FileManager.h"
#include "Vehicle.h"
#include "rental.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int Customer::nextCustomerId = 1;


Customer::Customer(const string& name, int age,
    const string& cnic, const string& phone,
    const string& email)
    : Person(name, age, cnic, phone, email)
{
    customerId = nextCustomerId++;
    saveNextId();
}


void Customer::loadNextId()
{
    ifstream in("next_customer_id.txt");
    if (in.is_open())
    {
        in >> nextCustomerId;
        in.close();
       
        if (nextCustomerId < 1) nextCustomerId = 1;
    }
   
}

void Customer::saveNextId()
{
    ofstream out("next_customer_id.txt");
    if (out.is_open())
    {
        out << nextCustomerId;
        out.close();
    }
}


void Customer::viewProfile() const
{
    cout << "\n=== CUSTOMER PROFILE ===\n";
    cout << "Customer ID : " << customerId << "\n";
    displayInfo();   
    cout << "\n";
}


void Customer::viewRentedVehicles() const
{
    auto records = FileManager::loadRentalRecords();
    auto vehicles = FileManager::loadVehicles();  

    bool foundAny = false;

    cout << "\n=== CURRENTLY RENTED VEHICLES\n";
    cout << "------------------------------------------------------------\n";

    for (const auto& r : records)
    {
        if (r.getCustomerId() == customerId && r.getStatus() == "Rented")
        {
            foundAny = true;

            bool vehicleFound = false;
            for (const auto v : vehicles)
            {
                if (v->getVehicleId() == r.getVehicleId())
                {
                   cout << v->getType() << " "
                        << v->getBrand() << " "
                        << v->getModel() << " | "
                        << r.getRentDays() << " days | "
                        << "Total: Rs." << r.getTotalAmount() << "\n";
                    vehicleFound = true;
                    break;
                }
            }

            if (!vehicleFound)
                cout << "Vehicle ID " << r.getVehicleId() << " (record exists but vehicle data missing)\n";
        }
    }

    if (!foundAny)
          cout << "No vehicles currently rented.\n";

          cout << "------------------------------------------------------------\n";

    for (auto v : vehicles)
        delete v;
}