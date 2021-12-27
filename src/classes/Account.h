#ifndef __ACCOUNT__
#define __ACCOUNT__

#include "order.h"
#include "tstamp.h"
#include <unordered_map>

class Account
{
public:
    Account();
    Account(std::string, std::string, std::string);
    Account(const Account &);
    Account &operator=(const Account &);
    friend std::ostream &operator<<(std::ostream &, const Account &);
    friend std::istream &operator>>(std::istream &, Account &);
    bool verifyID(std::string, std::string);
    std::string getName();
    void setUp(std::string, std::string);
    std::string newAccount();
    void addAddress();

private:
    std::string username, password, name;
    std::vector<address> addresses;
    std::unordered_map<std::string, unsigned int> wish; // holds quantity
    std::unordered_map<std::string, order> orders;      // std::string prodID
    std::vector<std::string> reviews, ratings;          // here std::string will store the product ID

    friend class Kart;
};

#endif
