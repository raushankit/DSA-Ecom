#include "Product.h"

Product::Product()
{
    name = description = "";
    amount = quantity = category = 0;
    rating = 0;
    redata.clear();
    ratdata.clear();
}

Product::Product(std::string n, std::string d, unsigned int am, unsigned int q, unsigned int cat)
{
    name = n;
    description = d;
    amount = am;
    quantity = q;
    category = cat;
    rating = 0;
    redata.clear();
    ratdata.clear();
}

Product::Product(const Product &p)
{
    name = p.name;
    description = p.description;
    amount = p.amount;
    quantity = p.quantity;
    category = p.category;
    rating = p.rating;
    redata = p.redata;
    ratdata = p.ratdata;
}

Product &Product::operator=(const Product &p)
{
    if (this != &p)
    {
        name = p.name;
        description = p.description;
        amount = p.amount;
        quantity = p.quantity;
        category = p.category;
        rating = p.rating;
        redata = p.redata;
        ratdata = p.ratdata;
    }
    return *this;
}

void Product::addRating(std::string userId, unsigned int n)
{
    ratdata[userId] = n;
    unsigned int m = ratdata.size();
    rating = (rating * (m - 1) + n) / (1.0 * m);
}

void Product::addReview(std::string userId, review p)
{
    redata[userId] = p;
}

std::string Product::getName()
{
    return name;
}

std::ostream &operator<<(std::ostream &out, const Product &p)
{
    out << "Name: " << p.name << std::endl;
    out << "Description: " << p.description << std::endl;
    out << "Price: " << p.amount << std::endl;
    out << "Quantity: " << p.quantity << std::endl;
    out << "Category: " << p.category << std::endl;
    out << "Rating: " << p.rating << std::endl;
    out << "ReviewSize: " << p.redata.size() << std::endl;
    for (auto i : p.redata)
    {
        out << "WrittenBy: " << i.first << std::endl;
        out << i.second << std::endl;
    }
    out << "RatingSize: " << p.ratdata.size() << std::endl;
    for (auto i : p.ratdata)
    {
        out << "WrittenBy: " << i.first << " " << i.second << std::endl;
    }
    return out;
}

std::vector<std::string> Product::displayProduct()
{
    std::vector<std::string> revids;
    if (quantity == 0)
        std::cout << "out of stock" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << description << std::endl;
    std::cout << "Price  = " << amount << std::endl;
    if (ratdata.empty())
        std::cout << "No Ratings yet" << std::endl;
    else
        std::cout << "rated " << rating << " star" << std::endl;
    int j = 1;
    if (redata.empty())
        std::cout << "No reviews yet" << std::endl;
    for (auto i : redata)
    {
        revids.push_back(i.first);
        std::cout << "*************************************************" << std::endl;
        std::cout << j << " :: ";
        j++;
        i.second.displayRev();
    }
    return revids;
}

std::istream &operator>>(std::istream &in, Product &p)
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
    ss >> str >> p.description;
    while (ss >> str)
        p.description += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.amount;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.quantity;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.category;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.rating;
    int n;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> str;
        review temp;
        in >> temp;
        p.redata[str] = temp;
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        unsigned int temp;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> str >> temp;
        p.ratdata[str] = temp;
    }
    return in;
}
