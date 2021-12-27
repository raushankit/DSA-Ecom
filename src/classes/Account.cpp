#include "Account.h"

Account::Account(){
    username = password = name = "";
}

Account::Account(string userName, string PassWord, string Name){
    username = userName;
    password = PassWord;
    name = Name;
    addresses.clear();
    reviews.clear();
    ratings.clear();
    wish.clear();
    orders.clear();
}

Account::Account(const Account &p){
    username = p.username;
    password = p.password;
    name = p.name;
    wish = p.wish;
    orders = p.orders;
    addresses = p.addresses;
    reviews = p.reviews;
    ratings = p.ratings;
}

Account& Account::operator=(const Account &p){
    if(this!=&p){
        username = p.username;
        password = p.password;
        name = p.name;
        wish = p.wish;
        orders = p.orders;
        addresses = p.addresses;
        reviews = p.reviews;
        ratings = p.ratings;
    }
    return *this;
}

ostream& operator<<(ostream &out, const Account &p){
    out << "username: " << p.username << endl;
    out << "password: " << p.password << endl;
    out << "name: " << p.name << endl;
    out << "AddressSize: " << p.addresses.size() << endl;
    for(auto i:p.addresses){
        out << i << endl;
    }
    out << "CartSize: " << p.wish.size() << endl;
    for(auto i:p.wish){
        out << i.first << " " << i.second << endl;
    }
    out << "OrderSize: " << p.orders.size() << endl;
    for(auto i:p.orders){
        out << "ProductID: " << i.first << endl;
        out << i.second;
    }
    out << "ReviewSize: " << p.reviews.size() << endl;
    for(auto i:p.reviews){
        out << i << endl;
    }
    out << "RatingSize: " << p.ratings.size() << endl;
    for(auto i:p.ratings){
        out << i << endl;
    }
    return out;
}

istream& operator>>(istream &in, Account &p){
    string str;
    getline(in,str);
    stringstream ss(str);
    ss >> str >> p.username;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.password;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.name;
    while(ss >> str) p.name += " "+str;
    int n;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        address temp;
        in >> temp;
        p.addresses.push_back(temp);
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        unsigned int flag;
        string prodID;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> prodID >> str >> flag;
        p.wish[prodID+" "+str] = flag;
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        string prodid;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> prodid >> str;
        prodid += " "+str;
        order temp;
        in >> temp;
        p.orders[prodid] = temp;
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        getline(in,str);
        p.reviews.push_back(str);
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        getline(in,str);
        p.ratings.push_back(str);
    }
    return in;
}

bool Account::verifyID(string un,string pw){
    if(un!=username){
        cout << "Invalid username" << endl;
        return false;
    }
    if(pw!=password){
        cout << "Invalid password" << endl;
        return false;
    }
    return true;
}

string Account::getName(){
    return name;
}

void Account::setUp(string u,string p){
    username = u;
    password = p;
}

string Account::newAccount(){
    cout << "Enter name: ";
    getline(cin,name);
    cout << "Enter username: ";
    getline(cin,username);
    cout << "Enter Password: ";
    getline(cin,password);
    cout << "Do you want to enter an address[y/n]? ";
    if(getResponse('y')){
        address ad;
        ad.addAddress();
        addresses.push_back(ad);
    }
    return name;
}

void Account::addAddress(){
    address ad;
    ad.addAddress();
    addresses.push_back(ad);
}

