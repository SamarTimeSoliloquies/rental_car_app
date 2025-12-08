#ifndef customer_h
#define customer_h
#include "person.h"
#include <string>
#include <vector>+
using namespace std;


class Customer : public Person {
private:
    int customerId;
    static int nextCustomerId;

public:
    Customer(const string& name = "", int age = 0,const string& cnic = "", const string& phone = "",const string& email = "");

    int getCustomerId() const { return customerId; }
    void viewProfile() const;
    void viewRentedVehicles() const;

    static void loadNextId();
    static void saveNextId();
};

#endif