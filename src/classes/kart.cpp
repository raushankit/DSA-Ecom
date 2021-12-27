#include "kart.h"

Kart::Kart(std::string pw)
{
    passcode = pw;
    users.clear();
    categ.clear();
    prod.clear();
    orders.clear();
}

void Kart::addProduct()
{
    std::string name, desc;
    unsigned int am, qu, cat;
    std::cout << "Name of the product(Only Alphabets): ";
    getline(std::cin, name);
    std::cout << "Description: ";
    getline(std::cin, desc);
    std::cout << "Enter price of the product: ";
    std::cin >> am;
    std::cout << "Enter quantity: ";
    std::cin >> qu;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (categ.empty())
    {
        std::cout << "Add the product's category" << std::endl;
        std::cout << "Enter Category name: ";
        std::string s;
        getline(std::cin, s);
        cat = 1;
        categ.push_back(s);
    }
    else
    {
        std::cout << "Choose category of the product......." << std::endl;
        for (unsigned int i = 0; i < categ.size(); i++)
        {
            std::cout << i + 1 << ". " << categ[i] << std::endl;
        }
        std::cout << "If Product is of another category proceed to add category(TYPE 0)" << std::endl;
        std::cout << "Else choose the category number" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> cat;
        if (cat == 0)
        {
            std::cout << "Enter Category name: ";
            std::string s;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, s);
            cat = categ.size() + 1;
            categ.push_back(s);
        }
        if (cat > categ.size())
        {
            std::cout << "Invalid choice." << std::endl;
            while (cat > categ.size())
            {
                std::cout << "Choose Valid category: ";
                std::cin >> cat;
            }
        }
    }
    std::string tstamp = "PROD" + Timestamp();
    prod[cat][tstamp] = Product(name, desc, am, qu, cat);
    search.insert(tstamp, cat, name);
}

void Kart::saveData()
{
    char *file = (char *)"Kartdata.txt";
    std::ofstream fout;
    fout.open(file, std::ofstream::out | std::ofstream::trunc);
    fout << "BACKUP DATA" << std::endl;
    fout << "//////////////////////////////////////" << std::endl;
    fout << *this << std::endl;
}

void Kart::loadData()
{
    std::ifstream fin("Kartdata.txt");
    std::string str = "";
    getline(fin, str);
    getline(fin, str);
    fin >> *this;
}

void Kart::processOrders()
{
    for (auto i : orders)
    {
        std::string prodid;
        unsigned int cat;
        std::stringstream ss(i.first);
        ss >> cat >> prodid;
        std::cout << "********************************************" << std::endl;
        for (auto j : i.second)
        {
            users[j].orders[i.first].log.push_back(tracklog("Order Delivered"));
            users[j].orders[i.first].isDelivered = true;
            std::cout << users[j].getName() << "'s oder delivered" << std::endl;
            std::cout << "********************************************" << std::endl;
        }
        i.second.clear();
    }
    orders.clear();
}

grp<unsigned int, std::string> Kart::searchResult()
{
    std::string key;
    std::cout << "Enter the name of the product to search: ";
    getline(std::cin, key);
    std::vector<grp<unsigned int, std::string>> results = search.getList(key);
    if (results.empty())
    {
        std::cout << "No results found. " << std::endl;
        return grp<unsigned int, std::string>(0, "");
    }
    for (unsigned int i = 0; i < results.size(); i++)
    {
        std::cout << i + 1 << ". ";
        std::cout << prod[results[i].a][results[i].b].getName() << std::endl;
    }
    std::cout << "Choose the Product number: ";
    unsigned int response;
    std::cin >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (response < 1 || response > results.size())
    {
        std::cout << "Invalid input " << std::endl;
        return grp<unsigned int, std::string>(0, "");
    }
    return results[response - 1];
}

std::ostream &operator<<(std::ostream &out, const Kart &p)
{
    out << "UserSize: " << p.users.size() << std::endl;
    for (auto i : p.users)
    {
        out << "userID: " << i.first << std::endl;
        out << i.second << std::endl;
    }
    out << "CategorySize: " << p.categ.size() << std::endl;
    for (unsigned int i = 0; i < p.categ.size(); i++)
    {
        out << i + 1 << ". " << p.categ[i] << std::endl;
    }
    out << "categorySize: " << p.prod.size() << std::endl;
    for (auto i : p.prod)
    {
        out << "categoryNumber: " << i.first << std::endl;
        out << "categoryProductSize: " << i.second.size() << std::endl;
        for (auto j : i.second)
        {
            out << "ProductID: " << j.first << std::endl;
            out << j.second << std::endl;
        }
    }
    out << "OrderSize: " << p.orders.size() << std::endl;
    for (auto i : p.orders)
    {
        out << "ProdID: " << i.first << std::endl;
        out << "ProductOrderSize: " << i.second.size() << std::endl;
        for (auto j : i.second)
            out << j << std::endl;
    }
    return out;
}

std::istream &operator>>(std::istream &in, Kart &p)
{
    std::string str;
    getline(in, str);
    std::stringstream ss(str);
    int n;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> str;
        Account temp;
        in >> temp;
        p.users[str] = temp;
        getline(in, str);
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    p.categ.resize(n);
    for (int i = 0; i < n; i++)
    {
        unsigned int temp_in;
        std::string temp_str;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> temp_in >> str >> temp_str;
        while (ss >> str)
            temp_str += " " + str;
        p.categ[temp_in - 1] = temp_str;
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        unsigned int categNo;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> categNo;
        int m;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> m;
        for (int j = 0; j < m; j++)
        {
            Product temp;
            std::string prodID;
            getline(in, str);
            ss.str("");
            ss.clear();
            ss << str;
            ss >> str >> prodID;
            in >> temp;
            p.prod[categNo][prodID] = temp;
            p.search.insert(prodID, categNo, temp.getName());
            getline(in, str);
        }
    }
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        std::string prodID;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> prodID >> str;
        prodID += " " + str;
        int m;
        getline(in, str);
        ss.str("");
        ss.clear();
        ss << str;
        ss >> str >> m;
        for (int j = 0; j < m; j++)
        {
            getline(in, str);
            p.orders[prodID].push_back(str);
        }
    }
    return in;
}

std::string Kart::verifyID(std::string uid, std::string u, std::string p)
{
    std::string nam = users[uid].getName();
    if (nam == "")
    {
        std::cout << "Critical Error!" << std::endl;
        std::cout << "Invalid user" << std::endl;
        return "";
    }
    if (users[uid].verifyID(u, p))
    {
        return nam;
    }
    else
        return "";
}

bool Kart::recoverAndSet(std::string uid, std::string name)
{
    if (users[uid].getName() != name)
    {
        std::cout << "username incorrect" << std::endl;
        return false;
    }
    std::cout << "Enter your new credentials" << std::endl;
    std::string uName, Pword;
    std::cout << "Enter Username: ";
    getline(std::cin, uName);
    std::cout << "Enter Password: ";
    getline(std::cin, Pword);
    users[uid].setUp(uName, Pword);
    return true;
}

grp<std::string, std::string> Kart::createAccount()
{
    grp<std::string, std::string> p("USER", "");
    Account temp;
    p.b = temp.newAccount();
    p.a += Timestamp();
    users[p.a] = temp;
    return p;
}

std::vector<std::string> Kart::showProduct(unsigned int cat, std::string prodID)
{
    return prod[cat][prodID].displayProduct();
}

void Kart::AddAddress(std::string uid)
{
    users[uid].addAddress();
}

std::vector<grp<std::string, unsigned int>> Kart::getCart(std::string uid)
{
    std::vector<grp<std::string, unsigned int>> tmp;
    for (auto i : users[uid].wish)
    {
        if (i.second == 0)
            continue;
        tmp.push_back(grp<std::string, unsigned int>(i.first, i.second));
    }
    return tmp;
}

std::string Kart::getProductName(std::string uprid)
{
    std::stringstream ss(uprid);
    unsigned int categ;
    std::string prodID;
    ss >> categ >> prodID;
    return prod[categ][prodID].name;
}

void Kart::rateProd(std::string uid, unsigned int cat, std::string prodid)
{
    std::cout << "Rate the Product from (1-10): ";
    unsigned int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (n < 1 || n > 10)
    {
        std::cout << "Invalid rating" << std::endl;
        return;
    }
    prod[cat][prodid].rating = (1.0 * prod[cat][prodid].ratdata.size() * prod[cat][prodid].rating + n) / (prod[cat][prodid].ratdata.size() + 1);
    prod[cat][prodid].ratdata[uid] = n;
    users[uid].ratings.push_back(std::to_string(cat) + " " + prodid);
}

void Kart::removeFromCart(std::string uid, std::vector<std::string> prodids)
{
    for (auto i : prodids)
    {
        users[uid].wish.erase(i);
    }
    std::cout << "Selected items removed from cart" << std::endl;
}

void Kart::reviewProd(std::string uid, unsigned int cat, std::string prodid)
{
    review tmr;
    tmr.takeReview(users[uid].getName());
    users[uid].reviews.push_back(std::to_string(cat) + " " + prodid);
    prod[cat][prodid].redata[uid] = tmr;
}

void Kart::lordreview(unsigned int cat, std::string prodid, std::string rid, bool b)
{
    if (b)
        prod[cat][prodid].redata[rid].likes++;
    else
        prod[cat][prodid].redata[rid].dislikes++;
}

void Kart::checkout(std::string uid, std::vector<grp<std::string, unsigned int>> prods)
{
    std::cout << "Choose a Address to Deliver(Enter 0 to add new Address)" << std::endl;
    int j = 1;
    for (auto i : users[uid].addresses)
    {
        std::cout << j << " :: ";
        i.displayAddress();
        j++;
    }
    int choose;
    std::cout << "Choose the address number: ";
    std::cin >> choose;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choose == 0)
    {
        users[uid].addAddress();
        choose = j + 1;
    }
    if (choose < 1 || choose > j)
    {
        std::cout << "Invalid Address Chosen. " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "order checkout failed" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        return;
    }
    unsigned int amount = 0;
    std::stringstream ss;
    std::cout << "Order Placed of the following products: " << std::endl;
    j = 1;
    for (auto i : prods)
    {
        orders[i.a].push_back(uid);
        unsigned int ct;
        ss.str("");
        ss.clear();
        ss << i.a;
        std::string prodID;
        ss >> ct >> prodID;
        amount += i.b * prod[ct][prodID].amount;
        order tord;
        tord.ad = users[uid].addresses[choose - 1];
        tord.isDelivered = false;
        std::cout << j << " :: " << prod[ct][prodID].name << std::endl;
        tord.log.push_back(tracklog("Order of Product " + prod[ct][prodID].name + " placed."));
        tord.log.push_back(tracklog("Quantity: " + std::to_string(i.b)));
        tord.log.push_back(tracklog("Order shipped from the nearest courier facility"));
        users[uid].wish.erase(i.a);
        users[uid].orders[std::to_string(i.b) + " " + i.a] = tord;
    }
    std::cout << "Total Amount: " << amount << std::endl;
}

void Kart::orderPage(std::string uid)
{
    std::cout << "************************************" << std::endl;
    if (users[uid].orders.empty())
    {
        std::cout << "You haven't placed any orders" << std::endl;
        std::cout << "************************************" << std::endl;
        return;
    }
    std::cout << "Your orders are" << std::endl;
    int j = 1;
    std::vector<grp<std::string, std::string>> tmp;
    for (auto i : users[uid].orders)
    {
        std::cout << "------------------------------------" << std::endl;
        std::stringstream ss(i.first);
        unsigned int cat;
        std::string prodid;
        ss >> cat >> prodid;
        tmp.push_back(grp<std::string, std::string>(prod[cat][prodid].name, i.first));
        std::cout << j << " :: name: " << prod[cat][prodid].name;
        if (i.second.isDelivered)
            std::cout << " DELIVERED" << std::endl;
        else
            std::cout << " ON THE WAY" << std::endl;
        j++;
    }
    std::cout << "************************************" << std::endl;
    int n;
    std::cout << "Choose the Product Number: ";
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "************************************" << std::endl;
    if (n < 1 || n > j)
    {
        std::cout << "Invalid Product Number" << std::endl;
        std::cout << "************************************" << std::endl;
        return;
    }
    std::cout << "Name: " << tmp[n - 1].a << std::endl;
    std::cout << "Previous Logs are: " << std::endl;
    for (auto i : users[uid].orders[tmp[n - 1].b].log)
    {
        std::cout << i.time << " :: " << i.info << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
    std::cout << "************************************" << std::endl;
}

void Kart::WishlistPage(std::string uid, bool b)
{
    std::vector<grp<unsigned int, std::string>> wishlist;
    for (auto i : users[uid].wish)
    {
        if (i.second == 0)
        {
            std::stringstream ss(i.first);
            grp<unsigned int, std::string> tmg(0, "");
            ss >> tmg.a >> tmg.b;
            wishlist.push_back(tmg);
        }
    }
    std::cout << "************************************" << std::endl;
    if (wishlist.empty())
    {
        std::cout << "Your Wishlist is empty" << std::endl;
        std::cout << "************************************" << std::endl;
        return;
    }
    int j = 1;
    for (auto i : wishlist)
    {
        std::cout << j << " :: name: " << prod[i.a][i.b].name << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
    std::cout << "************************************" << std::endl;
    std::string str;
    std::vector<int> a;
    std::cout << "Choose the products to checkout" << std::endl;
    std::cout << "Enter the number/(s) seperated by spaces: ";
    getline(std::cin, str);
    std::stringstream ss(str);
    int tmn;
    while (ss >> tmn)
    {
        if (tmn < 1 || tmn > j)
        {
            std::cout << "Invalid Product Number" << std::endl;
            std::cout << "************************************" << std::endl;
            return;
        }
        a.push_back(tmn);
    }
    if (a.empty())
    {
        std::cout << " No products chosen" << std::endl;
        std::cout << "************************************" << std::endl;
        return;
    }
    std::cout << "************************************" << std::endl;
    if (b)
    {
        for (auto i : a)
        {
            int pmn;
            std::cout << "Choose quantity for Product " << i << " :";
            std::cin >> pmn;
            if (pmn <= 0)
            {
                std::cout << "Quantity must be  positive" << std::endl;
                std::cout << "************************************" << std::endl;
                return;
            }
            users[uid].wish[std::to_string(wishlist[i - 1].a) + " " + wishlist[i - 1].b] = pmn;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
        for (auto i : a)
        {
            users[uid].wish.erase(std::to_string(wishlist[i - 1].a) + " " + wishlist[i - 1].b);
        }
    }
    std::cout << "************************************" << std::endl;
}

void Kart::AddWishlistORcart(std::string uid, unsigned int cat, std::string prodid, bool b)
{
    if (b)
    {
        users[uid].wish[std::to_string(cat) + " " + prodid] = 0;
        std::cout << "Added To Your Wishlist" << std::endl;
        return;
    }
    std::cout << "Choose the quantity of the Product: ";
    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (n <= 0)
    {
        std::cout << "Quantity cannot be negative" << std::endl;
        return;
    }
    users[uid].wish[std::to_string(cat) + " " + prodid] = n;
}

void Kart::BuyNow(std::string uid, unsigned int cat, std::string prodid)
{
    std::cout << "Choose the quantity of the Product: ";
    int n;
    std::cin >> n;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (n <= 0)
    {
        std::cout << "Quantity must be negative" << std::endl;
        return;
    }
    std::cout << "Choose a Address to Deliver(Enter 0 to add new Address)" << std::endl;
    int j = 1;
    for (auto i : users[uid].addresses)
    {
        std::cout << j << " :: ";
        i.displayAddress();
        j++;
    }
    int choose;
    std::cout << "Choose the address number: ";
    std::cin >> choose;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choose == 0)
    {
        users[uid].addAddress();
        choose = j + 1;
    }
    else if (choose < 1 || choose > j)
    {
        std::cout << "Invalid Address Chosen. " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::cout << "order checkout failed" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        return;
    }
    order tord;
    tord.ad = users[uid].addresses[choose - 1];
    tord.isDelivered = false;
    tord.log.push_back(tracklog("Order of Product " + prod[cat][prodid].name + " placed."));
    tord.log.push_back(tracklog("Quantity: " + std::to_string(n)));
    tord.log.push_back(tracklog("Order shipped from the nearest courier facility"));
    users[uid].orders[std::to_string(cat) + " " + prodid] = tord;
    std::cout << "Ordersize: " << users[uid].orders.size() << std::endl;
    orders[std::to_string(cat) + " " + prodid].push_back(uid);
    std::cout << "Amount: " << prod[cat][prodid].amount << std::endl;
}
