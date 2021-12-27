#ifndef __PRODUCT__
#define __PRODUCT__

#include "review.h"
#include <unordered_map>
#include <vector>

class Product{
    string name, description;
    unsigned int amount, quantity, category;
    double rating;
    unordered_map<string, review> redata;// string is the userID
    unordered_map<string, unsigned int> ratdata;

    friend class Kart;
    public:
    Product();
    Product(string,string,unsigned int,unsigned int,unsigned int);
    Product(const Product&);
    Product& operator=(const Product&);
    void addRating(string, unsigned int);
    void addReview(string, review);
    string getName();
    vector<string> displayProduct();
    friend ostream& operator<<(ostream&, const Product&);
    friend istream& operator>>(istream&, Product&);
};

#endif
