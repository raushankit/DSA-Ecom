#ifndef __ADDRESS__
#define __ADDRESS__

#include <iostream>
#include <sstream>
using namespace std;

class address{
    string name,phoneNo;
    unsigned int pincode;
    string city,state,country,landmark;
    bool homeAddress;

    bool checkPin(string);

    public:
    address();
    address(const address&);
    address& operator=(const address&);
    void addAddress();
    void displayAddress();
    friend ostream& operator<<(ostream&, const address&);
    friend istream& operator>>(istream& , address&);
};

#endif
