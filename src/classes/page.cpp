#include "page.h"

void ProfilePage(Kart &p, bool firstTime, string uid, string name)
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "PROFILE PAGE" << endl;
    if (firstTime)
        ProfilePageCodes();
    cout << "Enter Code: ";
    string r;
    getline(cin, r);
    if (r == "C" || r == "c")
    {
        cartPage(p, name, uid, true);
    }
    else if (r == "W" || r == "w")
    {
        cout << "==============================" << endl;
        cout << "   M   \tMove items to cart" << endl;
        cout << "   R   \tRemove Items" << endl;
        cout << "==============================" << endl;
        cout << "Enter Code: ";
        getline(cin, r);
        if (r != "m" && r != "M" && r != "R" && r != "r")
        {
            cout << "Invalid Input" << endl;
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
        grp<unsigned int, string> pro = p.searchResult();
        if (pro.a == 0)
            ProfilePage(p, false, uid, name);
        vector<string> rev;
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
        cout << "DATA SAVED SUCCESSFULLY" << endl;
    }
    else
    {
        cout << "Invalid Code" << endl;
        ProfilePage(p, false, uid, name);
    }
}

void ProductPage(Kart &p, bool firstTime, unsigned int cat, string prodid, string uID, string Name, vector<string> &reveids)
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "PRODUCT PAGE" << endl;
    if (firstTime)
    {
        ProductPageCodes();
        reveids = p.showProduct(cat, prodid);
    }
    string r;
    cout << "Enter Code: ";
    getline(cin, r);
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
        grp<unsigned int, string> pro = p.searchResult();
        if (pro.a == 0)
            frontPage(p, true, Name, uID);
        ProductPage(p, true, pro.a, pro.b, uID, Name, reveids);
    }
    else if (r[0] == 'l' || r[0] == 'L')
    {
        if (reveids.empty())
        {
            cout << "No reviews" << endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        unsigned int n;
        stringstream ss(r);
        ss >> r;
        if (ss >> n)
        {
            if (n < 1 || n > reveids.size())
            {
                cout << "Input out of bound" << endl;
                ProductPage(p, false, cat, prodid, uID, Name, reveids);
            }
            p.lordreview(cat, prodid, reveids[n - 1], true);
        }
        else
        {
            cout << "Invalid input" << endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r[0] == 'D' || r[0] == 'd')
    {
        if (reveids.empty())
        {
            cout << "No reviews" << endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        unsigned int n;
        stringstream ss(r);
        ss >> r;
        if (ss >> n)
        {
            if (n < 1 || n > reveids.size())
            {
                cout << "Input out of bound" << endl;
                ProductPage(p, false, cat, prodid, uID, Name, reveids);
            }
            p.lordreview(cat, prodid, reveids[n - 1], false);
        }
        else
        {
            cout << "Invalid input" << endl;
            ProductPage(p, false, cat, prodid, uID, Name, reveids);
        }
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
    else if (r == "E" || r == "e")
    {
        p.saveData();
        cout << "DATA SAVED SUCCESSFULLY" << endl;
    }
    else
    {
        cout << "Invalid Code" << endl;
        ProductPage(p, false, cat, prodid, uID, Name, reveids);
    }
}

string loginActivity(Kart &p, string uID)
{
    string uName, Pword;
    cout << "Enter Username: ";
    getline(cin, uName);
    cout << "Enter Password: ";
    getline(cin, Pword);
    uName = p.verifyID(uID, uName, Pword);
    if (uName != "")
        return uName;
    if (uName == "")
        cout << "Forgot password?[y/n] ";
    getline(cin, uName);
    if (uName == "Y" || uName == "y")
    {
        cout << "Enter your name: ";
        getline(cin, Pword);
        if (p.recoverAndSet(uID, Pword))
        {
            return Pword;
        }
    }
    else
    {
        if (uName != "N" && uName != "n")
            cout << "Invalid response" << endl;
    }
    return "";
}
grp<string, string> frontPageOperation(Kart &p, string uID)
{
    string name, userID = uID;
    if (userID == "")
    {
        cout << "Create an Account" << endl;
        return p.createAccount();
    }
    else
    {
        cout << "Login with your Credentials" << endl;
        name = loginActivity(p, userID);
    }
    return grp<string, string>(userID, name);
}

void frontPage(Kart &p, bool firstTime, string name, string uid)
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "MAIN PAGE" << endl;
    string userID, Name;
    if (firstTime && name == "")
    {
        frontPageCodes();
        grp<string, string> data = frontPageOperation(p, uid);
        userID = data.a;
        Name = data.b;
        if (Name == "")
        {
            cout << "Login Failed" << endl;
            return;
        }
        cout << "Logged in as: " << Name << endl;
    }
    else
    {
        userID = uid;
        Name = name;
    }
    cout << "Hi! " << Name << endl;
    cout << "Enter the operation code: ";
    string r;
    getline(cin, r);
    if (r == "S" || r == "s")
    {
        grp<unsigned int, string> pro = p.searchResult();
        if (pro.a == 0)
            frontPage(p, false, Name, userID);
        vector<string> rev;
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
        cout << "==============================" << endl;
        cout << "   M   \tMove items to cart" << endl;
        cout << "   R   \tRemove Items" << endl;
        cout << "==============================" << endl;
        cout << "Enter Code: ";
        getline(cin, r);
        if (r != "m" && r != "M" && r != "R" && r != "r")
        {
            cout << "Invalid Input" << endl;
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
        cout << "DATA SAVED SUCCESSFULLY" << endl;
    }
    else
    {
        cout << "Invalid Code" << endl;
        frontPage(p, false, Name, userID);
    }
}

void cartPage(Kart &p, string name, string uID, bool FirstTime)
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "CART PAGE" << endl;
    auto cprod = p.getCart(uID);
    if (cprod.empty())
    {
        cout << "No items in Cart" << endl;
        frontPage(p, false, name, uID);
        return;
    }
    if (FirstTime)
    {
        cartPageCodes();
        for (unsigned int i = 0; i < cprod.size(); i++)
        {
            cout << i + 1 << " :: " << p.getProductName(cprod[i].a) << " quantity: " << cprod[i].b << endl;
        }
    }
    string res;
    cout << "Choose Operation: ";
    getline(cin, res);
    if (res == "S" || res == "s")
    {
        grp<unsigned int, string> pro = p.searchResult();
        if (pro.a == 0)
            cartPage(p, name, uID, false);
        vector<string> rev;
        ProductPage(p, true, pro.a, pro.b, uID, name, rev);
    }
    else if (res == "P" || res == "p")
    {
        ProfilePage(p, true, uID, name);
    }
    else if (res == "C" || res == "c")
    {
        string str;
        cout << "Choose the products to checkout" << endl;
        cout << "Enter the number/(s) seperated by spaces: ";
        getline(cin, str);
        stringstream ss(str);
        vector<grp<string, unsigned int>> tp;
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
            cout << "Invalid Input" << endl;
            cartPage(p, name, uID, false);
        }
        p.checkout(uID, tp);
        cartPage(p, name, uID, false);
    }
    else if (res == "R" || res == "r")
    {
        string str;
        cout << "Choose the products to checkout" << endl;
        cout << "Enter the number/(s) seperated by spaces: ";
        getline(cin, str);
        stringstream ss(str);
        vector<string> tp;
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
            cout << "Invalid Input" << endl;
            cartPage(p, name, uID, false);
        }
        p.removeFromCart(uID, tp);
        cartPage(p, name, uID, false);
    }
    else if (res == "W" || res == "w")
    {
        cout << "==============================" << endl;
        cout << "   M   \tMove items to cart" << endl;
        cout << "   R   \tRemove Items" << endl;
        cout << "==============================" << endl;
        cout << "Enter Code: ";
        string r;
        getline(cin, r);
        if (r != "m" && r != "M" && r != "R" && r != "r")
        {
            cout << "Invalid Input" << endl;
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
        cout << "DATA SAVED SUCCESSFULLY" << endl;
    }
    else
    {
        cout << "Invalid Code" << endl;
        cartPage(p, name, uID, false);
    }
}
