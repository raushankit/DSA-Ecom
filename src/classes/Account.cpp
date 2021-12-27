#include "Account.h"

Account::Account()
{
    username = password = name = "";
}

Account::Account(std::string userName, std::string PassWord, std::string Name)
{
    username = userName;
    password = PassWord;
    name = Name;
    addresses.clear();
    reviews.clear();
    ratings.clear();
    wish.clear();
    orders.clear();
}

Account::Account(const Account &p)
{
    username = p.username;
    password = p.password;
    name = p.name;
    wish = p.wish;
    orders = p.orders;
    addresses = p.addresses;
    reviews = p.reviews;
    ratings = p.ratings;
}

Account &Account::operator=(const Account &p)
{
    if (this != &p)
    {
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

std::ostream &operator<<(std::ostream &out, const Account &p)
{
    out << "username: " << p.username << std::endl;
    out << "password: " << p.password << std::endl;
    out << "name: " << p.name << std::endl;
    out << "AddressSize: " << p.addresses.size() << std::endl;
    for (auto i : p.addresses)
    {
        out << i << std::endl;
    }
    out << "CartSize: " << p.wish.size() << std::endl;
    for (auto i : p.wish)
    {
        out << i.first << " " << i.second << std::endl;
    }
    out << "OrderSize: " << p.orders.size() << std::endl;
    for (auto i : p.orders)
    {
        out << "ProductID: " << i.first << std::endl;
        out << i.second;
    }
    out << "ReviewSize: " << p.reviews.size() << std::endl;
    for (auto i : p.reviews)
    {
        out << i << std::endl;
    }
    out << "RatingSize: " << p.ratings.size() << std::endl;
    for (auto i : p.ratings)
    {
        out << i << std::endl;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Account &p)
{
    std::string str;
    getline(in, str);
    std::stringstream ss(str);
    ss >> str >> p.username;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.password;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.name;
    while (ss >> str)
        p.name += " " + str;
    int n;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        address temp;
        in >> temp;
        p.addresses.push_back(temp);
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        unsigned int flag;
        std::string prodID;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> prodID >> str >> flag;
        p.wish[prodID + " " + str] = flag;
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        std::string prodid;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> prodid >> str;
        prodid += " " + str;
        order temp;
        in >> temp;
        p.orders[prodid] = temp;
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        getline(in, str);
        p.reviews.push_back(str);
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        getline(in, str);
        p.ratings.push_back(str);
    }
    return in;
}

bool Account::verifyID(std::string un, std::string pw)
{
    if (un != username)
    {
        std::cout << "Invalid username" << std::endl;
        return false;
    }
    if (pw != password)
    {
        std::cout << "Invalid password" << std::endl;
        return false;
    }
    return true;
}

std::string Account::getName()
{
    return name;
}

void Account::setUp(std::string u, std::string p)
{
    username = u;
    password = p;
}

std::string Account::newAccount()
{
    std::cout << "Enter name: ";
    getline(std::cin, name);
    std::cout << "Enter username: ";
    getline(std::cin, username);
    std::cout << "Enter Password: ";
    getline(std::cin, password);
    std::cout << "Do you want to enter an address[y/n]? ";
    if (getResponse('y'))
    {
        address ad;
        ad.addAddress();
        addresses.push_back(ad);
    }
    return name;
}

void Account::addAddress()
{
    address ad;
    ad.addAddress();
    addresses.push_back(ad);
}
