#ifndef __ACCOUNT__
#define __ACCOUNT__

#include "order.h"
#include "tstamp.h"
#include <unordered_map>

class Account{
    string username, password,name;
    vector<address> addresses;
    unordered_map<string, unsigned int> wish;//holds quantity
    unordered_map<string, order> orders;// string prodID
    vector<string> reviews, ratings;// here string will store the product ID

    friend class Kart;
    public:
    Account();
    Account(string, string, string);
    Account(const Account&);
    Account& operator=(const Account&);
    friend ostream& operator<<(ostream&, const Account&);
    friend istream& operator>>(istream&, Account&);
    bool verifyID(string,string);
    string getName();
    void setUp(string,string);
    string newAccount();
    void addAddress();
};

#endif
