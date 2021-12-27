#ifndef __KART__
#define __KART__

#include "tstamp.h"
#include "Account.h"
#include "Product.h"
#include "search.h"
#include "grp.h"
#include <fstream>

class Kart
{
public:
    Kart(std::string);
    void addProduct();
    void saveData();
    void loadData();
    void processOrders();
    grp<unsigned int, std::string> searchResult();
    friend std::ostream &operator<<(std::ostream &, const Kart &);
    friend std::istream &operator>>(std::istream &, Kart &);
    std::string verifyID(std::string, std::string, std::string);
    bool recoverAndSet(std::string, std::string);
    std::vector<std::string> showProduct(unsigned int, std::string);
    grp<std::string, std::string> createAccount();
    void AddAddress(std::string);
    std::string getProductName(std::string);
    std::vector<grp<std::string, unsigned int>> getCart(std::string);
    void checkout(std::string, std::vector<grp<std::string, unsigned int>>);
    void removeFromCart(std::string, std::vector<std::string>);
    void rateProd(std::string, unsigned int, std::string);
    void reviewProd(std::string, unsigned int, std::string);
    void lordreview(unsigned int, std::string, std::string, bool);
    void orderPage(std::string);
    void WishlistPage(std::string, bool);
    void AddWishlistORcart(std::string, unsigned int, std::string, bool);
    void BuyNow(std::string, unsigned int, std::string);

private:
    std::string passcode;
    std::unordered_map<std::string, Account> users;
    std::vector<std::string> categ;
    std::unordered_map<unsigned int, std::unordered_map<std::string, Product>> prod;
    std::unordered_map<std::string, std::vector<std::string>> orders;
    searchList search;
};

#endif
