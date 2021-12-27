#include "page.h"

void ProfilePage(Kart &p, bool firstTime, std::string uid, std::string name)
{
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    std::cout << "PROFILE PAGE" << std::endl;
    if (firstTime)
        ProfilePageCodes();
    std::cout << "Enter Code: ";
    std::string r;
    getline(std::cin, r);
    if (r == "C" || r == "c")
    {
        cartPage(p, name, uid, true);
    }
    else if (r == "W" || r == "w")
    {
        std::cout << "==============================" << std::endl;
        std::cout << "   M   \tMove items to cart" << std::endl;
        std::cout << "   R   \tRemove Items" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Enter Code: ";
        getline(std::cin, r);
        if (r != "m" && r != "M" && r != "R" && r != "r")
        {
            std::cout << "Invalid Input" << std::endl;
            ProfilePage(p, false, uid, name);
        }
        p.WishlistPage(uid, (r == "m" || r == "M"));
        ProfilePage(p, false, uid, name);
    }
    else if (r == "O" || r == "o")
    {
        p.orderPage(uid);
        ProfilePage(p, false, uid, name);
    }
    else if (r == "B" || r == "b")
    {
        // back to front page
        frontPage(p, false, name, uid);
    }
    else if (r == "S" || r == "s")
    {
        // search product
        grp<unsigned int, std::string> pro = p.searchResult();
        if (pro.a == 0)
            ProfilePage(p, false, uid, name);
        std::vector<std::string> rev;
        ProductPage(p, true, pro.a, pro.b, uid, name, rev);
    }
    else if (r == "A" || r == "a")
    {
        p.AddAddress(uid);
        ProfilePage(p, false, uid, name);
    }
    else if (r == "E" || r == "e")
    {
        p.saveData();
        std::cout << "DATA SAVED SUCCESSFULLY" << std::endl;
    }
    else
    {
        std::cout << "Invalid Code" << std::endl;
        ProfilePage(p, false, uid, name);
    }
}

void ProductPage(Kart &p, bool firstTime, unsigned int cat, std::string prodid, std::string uID, std::string Name, std::vector<std::string> &reveids)
{
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    std::cout << "PRODUCT PAGE" << std::endl;
    if (firstTime)
    {
        ProductPageCodes();
        reveids = p.showProduct(cat, prodid);
    }
    std::string r;
    std::cout << "Enter Code: ";
    getline(std::cin, r);
    if (r == "P" || r == "p")
    {
        p.BuyNow(uID, cat, prodid);
        frontPage(p, true, Name, uID);
    }
    else if (r == "W" || r == "w")
    {
        p.AddWishlistORcart(uID, cat, prodid, true);
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r == "A" || r == "a")
    {
        p.AddWishlistORcart(uID, cat, prodid, false);
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r == "b" || r == "B")
    {
        frontPage(p, true, Name, uID);
    }
    else if (r == "O" || r == "o")
    {
        p.orderPage(uID);
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r == "R" || r == "r")
    {
        p.rateProd(uID, cat, prodid);
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r == "V" || r == "v")
    {
        p.reviewProd(uID, cat, prodid);
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r == "S" || r == "s")
    {
        grp<unsigned int, std::string> pro = p.searchResult();
        if (pro.a == 0)
            frontPage(p, true, Name, uID);
        ProductPage(p, true, pro.a, pro.b, uID, Name, reveids);
    }
    else if (r[0] == 'l' || r[0] == 'L')
    {
        if (reveids.empty())
        {
            std::cout << "No reviews" << std::endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        unsigned int n;
        std::stringstream ss(r);
        ss >> r;
        if (ss >> n)
        {
            if (n < 1 || n > reveids.size())
            {
                std::cout << "Input out of bound" << std::endl;
                ProductPage(p, false, cat, prodid, uID, Name, reveids);
            }
            p.lordreview(cat, prodid, reveids[n - 1], true);
        }
        else
        {
            std::cout << "Invalid input" << std::endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r[0] == 'D' || r[0] == 'd')
    {
        if (reveids.empty())
        {
            std::cout << "No reviews" << std::endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        unsigned int n;
        std::stringstream ss(r);
        ss >> r;
        if (ss >> n)
        {
            if (n < 1 || n > reveids.size())
            {
                std::cout << "Input out of bound" << std::endl;
                ProductPage(p, false, cat, prodid, uID, Name, reveids);
            }
            p.lordreview(cat, prodid, reveids[n - 1], false);
        }
        else
        {
            std::cout << "Invalid input" << std::endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r == "E" || r == "e")
    {
        p.saveData();
        std::cout << "DATA SAVED SUCCESSFULLY" << std::endl;
    }
    else
    {
        std::cout << "Invalid Code" << std::endl;
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
}

std::string loginActivity(Kart &p, std::string uID)
{
    std::string uName, Pword;
    std::cout << "Enter Username: ";
    getline(std::cin, uName);
    std::cout << "Enter Password: ";
    getline(std::cin, Pword);
    uName = p.verifyID(uID, uName, Pword);
    if (uName != "")
        return uName;
    if (uName == "")
        std::cout << "Forgot password?[y/n] ";
    getline(std::cin, uName);
    if (uName == "Y" || uName == "y")
    {
        std::cout << "Enter your name: ";
        getline(std::cin, Pword);
        if (p.recoverAndSet(uID, Pword))
        {
            return Pword;
        }
    }
    else
    {
        if (uName != "N" && uName != "n")
            std::cout << "Invalid response" << std::endl;
    }
    return "";
}
grp<std::string, std::string> frontPageOperation(Kart &p, std::string uID)
{
    std::string name, userID = uID;
    if (userID == "")
    {
        std::cout << "Create an Account" << std::endl;
        return p.createAccount();
    }
    else
    {
        std::cout << "Login with your Credentials" << std::endl;
        name = loginActivity(p, userID);
    }
    return grp<std::string, std::string>(userID, name);
}

void frontPage(Kart &p, bool firstTime, std::string name, std::string uid)
{
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    std::cout << "MAIN PAGE" << std::endl;
    std::string userID, Name;
    if (firstTime && name == "")
    {
        frontPageCodes();
        grp<std::string, std::string> data = frontPageOperation(p, uid);
        userID = data.a;
        Name = data.b;
        if (Name == "")
        {
            std::cout << "Login Failed" << std::endl;
            return;
        }
        std::cout << "Logged in as: " << Name << std::endl;
    }
    else
    {
        userID = uid;
        Name = name;
    }
    std::cout << "Hi! " << Name << std::endl;
    std::cout << "Enter the operation code: ";
    std::string r;
    getline(std::cin, r);
    if (r == "S" || r == "s")
    {
        grp<unsigned int, std::string> pro = p.searchResult();
        if (pro.a == 0)
            frontPage(p, false, Name, userID);
        std::vector<std::string> rev;
        ProductPage(p, true, pro.a, pro.b, userID, Name, rev);
    }
    else if (r == "P" || r == "p")
    {
        ProfilePage(p, true, userID, Name);
    }
    else if (r == "C" || r == "c")
    {
        cartPage(p, Name, userID, true);
    }
    else if (r == "W" || r == "w")
    {
        std::cout << "==============================" << std::endl;
        std::cout << "   M   \tMove items to cart" << std::endl;
        std::cout << "   R   \tRemove Items" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Enter Code: ";
        getline(std::cin, r);
        if (r != "m" && r != "M" && r != "R" && r != "r")
        {
            std::cout << "Invalid Input" << std::endl;
            ProfilePage(p, false, uid, name);
        }
        p.WishlistPage(uid, (r == "m" || r == "M"));
        frontPage(p, false, Name, userID);
    }
    else if (r == "O" || r == "o")
    {
        // go to order page
        p.orderPage(uid);
        frontPage(p, false, Name, userID);
    }
    else if (r == "E" || r == "e")
    {
        p.saveData();
        std::cout << "DATA SAVED SUCCESSFULLY" << std::endl;
    }
    else
    {
        std::cout << "Invalid Code" << std::endl;
        frontPage(p, false, Name, userID);
    }
}

void cartPage(Kart &p, std::string name, std::string uID, bool FirstTime)
{
    std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl;
    std::cout << "CART PAGE" << std::endl;
    auto cprod = p.getCart(uID);
    if (cprod.empty())
    {
        std::cout << "No items in Cart" << std::endl;
        frontPage(p, false, name, uID);
        return;
    }
    if (FirstTime)
    {
        cartPageCodes();
        for (unsigned int i = 0; i < cprod.size(); i++)
        {
            std::cout << i + 1 << " :: " << p.getProductName(cprod[i].a) << " quantity: " << cprod[i].b << std::endl;
        }
    }
    std::string res;
    std::cout << "Choose Operation: ";
    getline(std::cin, res);
    if (res == "S" || res == "s")
    {
        grp<unsigned int, std::string> pro = p.searchResult();
        if (pro.a == 0)
            cartPage(p, name, uID, false);
        std::vector<std::string> rev;
        ProductPage(p, true, pro.a, pro.b, uID, name, rev);
    }
    else if (res == "P" || res == "p")
    {
        ProfilePage(p, true, uID, name);
    }
    else if (res == "C" || res == "c")
    {
        std::string str;
        std::cout << "Choose the products to checkout" << std::endl;
        std::cout << "Enter the number/(s) seperated by spaces: ";
        getline(std::cin, str);
        std::stringstream ss(str);
        std::vector<grp<std::string, unsigned int>> tp;
        int tmp, tsz = cprod.size();
        bool tmb = false;
        while (ss >> tmp)
        {
            if (tmp > tsz)
            {
                tmb = true;
                break;
            }
            tp.push_back(cprod[tmp - 1]);
        }
        if (tp.empty() || tmb)
        {
            std::cout << "Invalid Input" << std::endl;
            cartPage(p, name, uID, false);
        }
        p.checkout(uID, tp);
        cartPage(p, name, uID, false);
    }
    else if (res == "R" || res == "r")
    {
        std::string str;
        std::cout << "Choose the products to checkout" << std::endl;
        std::cout << "Enter the number/(s) seperated by spaces: ";
        getline(std::cin, str);
        std::stringstream ss(str);
        std::vector<std::string> tp;
        int tmp, tsz = cprod.size();
        bool tmb = false;
        while (ss >> tmp)
        {
            if (tmp > tsz)
            {
                tmb = true;
                break;
            }
            tp.push_back(cprod[tmp - 1].a);
        }
        if (tp.empty() || tmb)
        {
            std::cout << "Invalid Input" << std::endl;
            cartPage(p, name, uID, false);
        }
        p.removeFromCart(uID, tp);
        cartPage(p, name, uID, false);
    }
    else if (res == "W" || res == "w")
    {
        std::cout << "==============================" << std::endl;
        std::cout << "   M   \tMove items to cart" << std::endl;
        std::cout << "   R   \tRemove Items" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << "Enter Code: ";
        std::string r;
        getline(std::cin, r);
        if (r != "m" && r != "M" && r != "R" && r != "r")
        {
            std::cout << "Invalid Input" << std::endl;
            ProfilePage(p, false, uID, name);
        }
        p.WishlistPage(uID, (r == "m" || r == "M"));
        cartPage(p, name, uID, false);
    }
    else if (res == "O" || res == "o")
    {
        p.orderPage(uID);
        cartPage(p, name, uID, false);
    }
    else if (res == "B" || res == "b")
    {
        frontPage(p, true, name, uID);
    }
    else if (res == "E" || res == "e")
    {
        p.saveData();
        std::cout << "DATA SAVED SUCCESSFULLY" << std::endl;
    }
    else
    {
        std::cout << "Invalid Code" << std::endl;
        cartPage(p, name, uID, false);
    }
}
