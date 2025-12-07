#ifndef person_h
#define person_h
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;
    string cnic;
    string phone;
    string email;

public:
    Person(const string& name = "", int age = 0,
        const string& cnic = "", const string& phone = "",
        const string& email = "");

    const string& getName() const { return name; }
    int getAge() const { return age; }
    const string& getCnic() const { return cnic; }
    const string& getPhone() const { return phone; }
    const string& getEmail() const { return email; }

    void setName(const string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setCnic(const string& c) { cnic = c; }
    void setPhone(const string& p) { phone = p; }
    void setEmail(const string& e) { email = e; }

    void displayInfo() const;
};

#endif
