#include "address.h"

address::address()
{
    name = phoneNo = city = state = country = landmark = "";
    homeAddress = false;
    pincode = 0;
}

address::address(const address &p)
{
    name = p.name;
    phoneNo = p.phoneNo;
    pincode = p.pincode;
    city = p.city;
    state = p.state;
    country = p.country;
    landmark = p.landmark;
    homeAddress = p.homeAddress;
}

address &address::operator=(const address &p)
{
    if (this != &p)
    {
        name = p.name;
        phoneNo = p.phoneNo;
        pincode = p.pincode;
        city = p.city;
        state = p.state;
        country = p.country;
        landmark = p.landmark;
        homeAddress = p.homeAddress;
    }
    return *this;
}

bool address::checkPin(std::string s)
{
    if (s.length() != 6)
        return false;
    for (char c : s)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

void address::displayAddress()
{
    std::cout << name << ", PhoneNo.: " << phoneNo << std::endl;
    std::cout << city << ", " << state << ", " << country << ", " << pincode << std::endl;
}

void address::addAddress()
{
    std::cout << "===ADDRESS===\nName: ";
    getline(std::cin, name);
    std::cout << "Phone Number: ";
    getline(std::cin, phoneNo);
    std::cout << "PINCODE: ";
    std::string PinCode;
    getline(std::cin, PinCode);
    while (!checkPin(PinCode))
    {
        std::cout << "Enter a valid PINCODE: ";
        getline(std::cin, PinCode);
    }
    pincode = stoi(PinCode);
    std::cout << "City: ";
    getline(std::cin, city);
    std::cout << "State: ";
    getline(std::cin, state);
    std::cout << "Country: ";
    getline(std::cin, country);
    std::cout << "Do want to add any landmark[y/n]? ";
    getline(std::cin, PinCode);
    if (PinCode == "y" || PinCode == "Y")
    {
        std::cout << "Landmark: ";
        getline(std::cin, landmark);
    }
    else
    {
        if (PinCode != "N" && PinCode != "n")
            std::cout << "Invalid response" << std::endl;
    }
    std::cout << "Is this a home address[y/n]? ";
    getline(std::cin, PinCode);
    if (PinCode == "y" || PinCode == "Y")
    {
        homeAddress = true;
    }
    else
    {
        if (PinCode != "N" && PinCode != "n")
            std::cout << "Invalid response" << std::endl;
    }
}

std::ostream &operator<<(std::ostream &out, const address &p)
{
    out << "Name: " << p.name << std::endl;
    out << "Phoneno: " << p.phoneNo << std::endl;
    out << "city: " << p.city << std::endl;
    out << "state: " << p.state << std::endl;
    out << "country: " << p.country << std::endl;
    out << "PINCODE: " << p.pincode << std::endl;
    out << "Landmark: " << p.landmark << std::endl;
    out << "isHomeAddress: " << p.homeAddress;
    return out;
}

std::istream &operator>>(std::istream &in, address &p)
{
    std::string str;
    getline(in, str);
    std::stringstream ss(str);
    ss >> str >> p.name;
    while (ss >> str)
        p.name += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.phoneNo;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.city;
    while (ss >> str)
        p.city += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.state;
    while (ss >> str)
        p.state += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.country;
    while (ss >> str)
        p.country += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.pincode;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.landmark;
    while (ss >> str)
        p.landmark += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.homeAddress;
    return in;
}
