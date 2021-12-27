#include "address.h"

address::address(){
    name = phoneNo = city = state = country = landmark = "";
    homeAddress = false;
    pincode = 0;
}

address::address(const address &p){
    name = p.name;
    phoneNo = p.phoneNo;
    pincode = p.pincode;
    city = p.city;
    state = p.state;
    country = p.country;
    landmark = p.landmark;
    homeAddress = p.homeAddress;
}

address& address::operator=(const address &p){
    if(this != &p){
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

bool address::checkPin(string s){
    if(s.length()!=6) return false;
    for(char c:s){
        if(c<'0'||c>'9') return false;
    }
    return true;
}

void address::displayAddress(){
    cout << name << ", PhoneNo.: " << phoneNo << endl;
    cout << city <<", "<<state<<", "<<country<<", "<<pincode<< endl;
}

void address::addAddress(){
    cout << "===ADDRESS===\nName: ";
    getline(cin,name);
    cout << "Phone Number: ";
    getline(cin, phoneNo);
    cout << "PINCODE: ";
    string PinCode;
    getline(cin, PinCode);
    while(!checkPin(PinCode)){
        cout << "Enter a valid PINCODE: ";
        getline(cin, PinCode);
    }
    pincode = stoi(PinCode);
    cout << "City: ";
    getline(cin, city);
    cout << "State: ";
    getline(cin, state);
    cout << "Country: ";
    getline(cin, country);
    cout << "Do want to add any landmark[y/n]? ";
    getline(cin, PinCode);
    if(PinCode=="y"||PinCode=="Y"){
        cout << "Landmark: ";
        getline(cin, landmark);
    }
    else{
        if(PinCode!="N"&&PinCode!="n") cout << "Invalid response" << endl;
    }
    cout << "Is this a home address[y/n]? ";
    getline(cin, PinCode);
    if(PinCode=="y"||PinCode=="Y"){
        homeAddress = true;
    }
    else{
        if(PinCode!="N"&&PinCode!="n") cout << "Invalid response" << endl;
    }
}

ostream& operator<< (ostream &out, const address &p){
    out << "Name: " << p.name << endl;
    out << "Phoneno: " << p.phoneNo << endl;
    out << "city: " << p.city << endl;
    out << "state: " << p.state << endl;
    out << "country: " << p.country << endl;
    out << "PINCODE: " << p.pincode << endl;
    out << "Landmark: " << p.landmark << endl;
    out << "isHomeAddress: " << p.homeAddress;
    return out;
}

istream& operator>>(istream &in, address &p){
    string str;
    getline(in, str);
    stringstream ss(str);
    ss >> str >> p.name;
    while(ss >> str) p.name += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.phoneNo;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.city;
    while(ss >> str) p.city += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.state;
    while(ss >> str) p.state += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.country;
    while(ss >> str) p.country += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.pincode;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.landmark;
    while(ss >> str) p.landmark += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.homeAddress;
    return in;
}
