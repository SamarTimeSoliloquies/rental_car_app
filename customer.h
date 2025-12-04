#ifndef customer_h
#define customer_h
#include "person.h"
#include <string>
using namespace std;

class Customer : public Person
{
private:
    string cnic;
    string password;

public:
    Customer();
    Customer(int customerId, const string& customerName, const string& customerCnic, const string& customerPassword);

    const string& getCnic() const;
    const string& getPassword() const;

    static int registerCustomer(const string& name, const string& cnic, const string& password);
    static int loginCustomer(const string& cnic, const string& password);
    static bool cnicExists(const string& cnic);
};

#endif