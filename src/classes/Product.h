#ifndef __PRODUCT__
#define __PRODUCT__

#include "review.h"
#include <unordered_map>
#include <vector>

class Product
{
public:
    Product();
    Product(std::string, std::string, unsigned int, unsigned int, unsigned int);
    Product(const Product &);
    Product &operator=(const Product &);
    void addRating(std::string, unsigned int);
    void addReview(std::string, review);
    std::string getName();
    std::vector<std::string> displayProduct();
    friend std::ostream &operator<<(std::ostream &, const Product &);
    friend std::istream &operator>>(std::istream &, Product &);

private:
    std::string name, description;
    unsigned int amount, quantity, category;
    double rating;
    std::unordered_map<std::string, review> redata; // std::string is the userID
    std::unordered_map<std::string, unsigned int> ratdata;

    friend class Kart;
};

#endif
