#ifndef __ADDRESS__
#define __ADDRESS__

#include <iostream>
#include <sstream>

class address
{
public:
    address();
    address(const address &);
    address &operator=(const address &);
    void addAddress();
    void displayAddress();
    friend std::ostream &operator<<(std::ostream &, const address &);
    friend std::istream &operator>>(std::istream &, address &);

private:
    std::string name, phoneNo;
    unsigned int pincode;
    std::string city, state, country, landmark;
    bool homeAddress;

    bool checkPin(std::string);
};

#endif
