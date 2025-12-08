#include "Person.h"
#include <iostream>

Person::Person(const string& name, int age, const string& cnic, const string& phone,const string& email): name(name), age(age), cnic(cnic), phone(phone), email(email) {
}

void Person::displayInfo() const {
    cout << "Name   : " << name << endl;
    cout << "Age    : " << age << endl;
    cout << "CNIC   : " << cnic << endl;
    cout << "Phone  : " << phone << endl;
    cout << "Email  : " << email << endl;
}