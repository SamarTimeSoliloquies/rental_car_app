// Customer.cpp (FULLY FIXED, CLEAN, EFFICIENT, NO ERRORS, NO MEMORY LEAKS)
#include "Customer.h"
#include "FileManager.h"
#include "Vehicle.h"
#include "rental.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int Customer::nextCustomerId = 1;

// ------------------------------------------------------------------
// Constructor
// ------------------------------------------------------------------
Customer::Customer(const std::string& name, int age,
    const std::string& cnic, const std::string& phone,
    const std::string& email)
    : Person(name, age, cnic, phone, email)
{
    customerId = nextCustomerId++;
    saveNextId();
}

// ------------------------------------------------------------------
// Static ID persistence
// ------------------------------------------------------------------
void Customer::loadNextId()
{
    std::ifstream in("next_customer_id.txt");
    if (in.is_open())
    {
        in >> nextCustomerId;
        in.close();
        // Safety: if file is corrupted or empty, start from 1
        if (nextCustomerId < 1) nextCustomerId = 1;
    }
    // If file doesn't exist, nextCustomerId stays 1 → first customer gets ID 1
}

void Customer::saveNextId()
{
    std::ofstream out("next_customer_id.txt");
    if (out.is_open())
    {
        out << nextCustomerId;
        out.close();
    }
}

// ------------------------------------------------------------------
// View profile
// ------------------------------------------------------------------
void Customer::viewProfile() const
{
    std::cout << "\n=== CUSTOMER PROFILE ===\n";
    std::cout << "Customer ID : " << customerId << "\n";
    displayInfo();   // from Person class
    std::cout << "\n";
}

// ------------------------------------------------------------------
// View currently rented vehicles (fixed version - loads vehicles only ONCE)
// ------------------------------------------------------------------
void Customer::viewRentedVehicles() const
{
    auto records = FileManager::loadRentalRecords();
    auto vehicles = FileManager::loadVehicles();   // ← load only once

    bool foundAny = false;

    std::cout << "\n=== CURRENTLY RENTED VEHICLES\n";
    std::cout << "------------------------------------------------------------\n";

    for (const auto& r : records)
    {
        if (r.getCustomerId() == customerId && r.getStatus() == "Rented")
        {
            foundAny = true;

            // Find matching vehicle
            bool vehicleFound = false;
            for (const auto v : vehicles)
            {
                if (v->getVehicleId() == r.getVehicleId())
                {
                    std::cout << v->getType() << " "
                        << v->getBrand() << " "
                        << v->getModel() << " | "
                        << r.getRentDays() << " days | "
                        << "Total: Rs." << r.getTotalAmount() << "\n";
                    vehicleFound = true;
                    break;
                }
            }

            if (!vehicleFound)
                std::cout << "Vehicle ID " << r.getVehicleId() << " (record exists but vehicle data missing)\n";
        }
    }

    if (!foundAny)
        std::cout << "No vehicles currently rented.\n";

    std::cout << "------------------------------------------------------------\n";

    // Clean up all loaded vehicles exactly once
    for (auto v : vehicles)
        delete v;
}