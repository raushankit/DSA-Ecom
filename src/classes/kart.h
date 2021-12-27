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
    Kart(string);
    void addProduct();
    void saveData();
    void loadData();
    void processOrders();
    grp<unsigned int, string> searchResult();
    friend ostream &operator<<(ostream &, const Kart &);
    friend istream &operator>>(istream &, Kart &);
    string verifyID(string, string, string);
    bool recoverAndSet(string, string);
    vector<string> showProduct(unsigned int, string);
    grp<string, string> createAccount();
    void AddAddress(string);
    string getProductName(string);
    vector<grp<string, unsigned int>> getCart(string);
    void checkout(string, vector<grp<string, unsigned int>>);
    void removeFromCart(string, vector<string>);
    void rateProd(string, unsigned int, string);
    void reviewProd(string, unsigned int, string);
    void lordreview(unsigned int, string, string, bool);
    void orderPage(string);
    void WishlistPage(string, bool);
    void AddWishlistORcart(string, unsigned int, string, bool);
    void BuyNow(string, unsigned int, string);

private:
    string passcode;
    unordered_map<string, Account> users;
    vector<string> categ;
    unordered_map<unsigned int, unordered_map<string, Product>> prod;
    unordered_map<string, vector<string>> orders;
    searchList search;
};

#endif
