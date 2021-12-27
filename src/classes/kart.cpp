#include "kart.h"

Kart::Kart(string pw){
    passcode = pw;
    users.clear();
    categ.clear();
    prod.clear();
    orders.clear();
}

void Kart::addProduct(){
    string name,desc;
    unsigned int am,qu,cat;
    cout << "Name of the product(Only Alphabets): ";
    getline(cin,name);
    cout << "Description: ";
    getline(cin, desc);
    cout << "Enter price of the product: ";
    cin >> am;
    cout << "Enter quantity: ";
    cin >> qu;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(categ.empty()){
        cout << "Add the product's category" << endl;
        cout << "Enter Category name: ";
        string s;
        getline(cin,s);
        cat = 1;
        categ.push_back(s);
    }
    else{
        cout << "Choose category of the product......." << endl;
        for(unsigned int i = 0;i < categ.size();i++){
            cout << i+1 << ". " << categ[i] << endl;
        }
        cout << "If Product is of another category proceed to add category(TYPE 0)" << endl;
        cout << "Else choose the category number" << endl;
        cout << "Enter your choice: ";
        cin >> cat;
        if(cat==0){
            cout << "Enter Category name: ";
            string s;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(cin,s);
            cat = categ.size() +1;
            categ.push_back(s);
        }
        if(cat > categ.size()){
            cout << "Invalid choice." << endl;
            while(cat > categ.size()){
                cout << "Choose Valid category: ";
                cin >> cat;
            }
        }
    }
    string tstamp = "PROD" + Timestamp();
    prod[cat][tstamp] = Product(name,desc,am,qu,cat);
    search.insert(tstamp,cat,name);
}

void Kart::saveData(){
    char *file = (char*)"Kartdata.txt";
    ofstream fout;
    fout.open(file, ofstream::out | ofstream::trunc);
    fout << "BACKUP DATA" << endl;
    fout << "//////////////////////////////////////" << endl;
    fout << *this << endl;
}

void Kart::loadData(){
    ifstream fin("Kartdata.txt");
    string str="";
    getline(fin,str);getline(fin,str);
    fin >> *this;
}

void Kart::processOrders(){
    for(auto i:orders){
        string prodid;
        unsigned int cat;
        stringstream ss(i.first);
        ss >> cat >> prodid;
        cout << "********************************************" << endl;
        for(auto j:i.second){
            users[j].orders[i.first].log.push_back(tracklog("Order Delivered"));
            users[j].orders[i.first].isDelivered = true;
            cout << users[j].getName() << "'s oder delivered" << endl;
            cout << "********************************************" << endl;
        }
        i.second.clear();
    }
    orders.clear();
}

grp<unsigned int, string> Kart::searchResult(){
    string key;
    cout << "Enter the name of the product to search: ";
    getline(cin,key);
    vector<grp<unsigned int, string>> results = search.getList(key);
    if(results.empty()){
        cout << "No results found. " << endl;
        return grp<unsigned int, string>(0,"");
    }
    for(unsigned int i = 0;i < results.size(); i++){
        cout << i+1 << ". ";
        cout << prod[results[i].a][results[i].b].getName() << endl; 
    }
    cout << "Choose the Product number: ";
    unsigned int response;
    cin >> response;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(response<1||response>results.size()){
        cout << "Invalid input " << endl;
        return grp<unsigned int, string>(0,"");
    }
    return results[response-1];
}

ostream& operator<<(ostream &out, const Kart &p){
    out << "UserSize: " << p.users.size() << endl;
    for(auto i:p.users){
        out << "userID: " << i.first << endl;
        out << i.second << endl;
    }
    out << "CategorySize: " << p.categ.size() << endl;
    for(unsigned int i = 0;i < p.categ.size();i++){
        out << i+1 << ". " << p.categ[i] << endl;
    }
    out << "categorySize: " << p.prod.size() << endl;
    for(auto i:p.prod){
        out << "categoryNumber: " << i.first << endl;
        out << "categoryProductSize: " << i.second.size() << endl;
        for(auto j:i.second){
            out << "ProductID: " << j.first << endl;
            out << j.second << endl;
        }
    }
    out << "OrderSize: " << p.orders.size() << endl;
    for(auto i:p.orders){
        out << "ProdID: " << i.first << endl;
        out << "ProductOrderSize: " << i.second.size() << endl;
        for(auto j:i.second) out << j << endl;
    }
    return out;
}

istream& operator>>(istream &in, Kart &p){
    string str;
    getline(in,str);
    stringstream ss(str);
    int n;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> str;
        Account temp;
        in >> temp;
        p.users[str] = temp;
        getline(in,str);
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    p.categ.resize(n);
    for(int i = 0;i < n;i++){
        unsigned int temp_in;
        string temp_str;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> temp_in >> str >> temp_str;
        while(ss >> str) temp_str += " "+str;
        p.categ[temp_in-1] = temp_str;
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        unsigned int categNo;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> categNo;
        int m;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> m;
        for(int j = 0;j < m;j++){
            Product temp;
            string prodID;
            getline(in,str);
            ss.str("");ss.clear();ss << str;
            ss >> str >> prodID;
            in >> temp;
            p.prod[categNo][prodID] = temp;
            p.search.insert(prodID,categNo,temp.getName());
            getline(in,str);
        }
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        string prodID;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> prodID >> str;
        prodID += " "+str;
        int m;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> m;
        for(int j = 0;j < m;j++){
            getline(in,str);
            p.orders[prodID].push_back(str);
        }
    }
    return in;
}

string Kart::verifyID(string uid,string u,string p){
    string nam = users[uid].getName();
    if(nam==""){
        cout << "Critical Error!" << endl;
        cout << "Invalid user" << endl;
        return "";
    }
    if(users[uid].verifyID(u,p)){
        return nam;
    }    
    else return "";
}

bool Kart::recoverAndSet(string uid,string name){
    if(users[uid].getName()!=name){
        cout << "username incorrect" << endl;
        return false;
    }
    cout << "Enter your new credentials" << endl;
    string uName,Pword;
    cout << "Enter Username: ";
    getline(cin,uName);
    cout << "Enter Password: ";
    getline(cin,Pword);
    users[uid].setUp(uName,Pword);
    return true;
}

grp<string,string> Kart::createAccount(){
    grp<string,string> p("USER","");
    Account temp;
    p.b = temp.newAccount();
    p.a += Timestamp();
    users[p.a] = temp;
    return p;
}

vector<string> Kart::showProduct(unsigned int cat, string prodID){
    return prod[cat][prodID].displayProduct();
}

void Kart::AddAddress(string uid){
    users[uid].addAddress();
}

vector<grp<string,unsigned int>> Kart::getCart(string uid){
    vector<grp<string,unsigned int>> tmp;
    for(auto i:users[uid].wish){
        if(i.second==0)continue;
        tmp.push_back(grp<string,unsigned int>(i.first,i.second));
    }
    return tmp;
}

string Kart::getProductName(string uprid){
    stringstream ss(uprid);
    unsigned int categ;
    string prodID;
    ss >> categ >> prodID;
    return prod[categ][prodID].name;
}

void Kart::rateProd(string uid,unsigned int cat,string prodid){
    cout << "Rate the Product from (1-10): ";
    unsigned int n;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(n < 1||n > 10){
        cout << "Invalid rating" << endl;
        return;
    }
    prod[cat][prodid].rating = (1.0*prod[cat][prodid].ratdata.size()*prod[cat][prodid].rating + n)/(prod[cat][prodid].ratdata.size()+1);
    prod[cat][prodid].ratdata[uid] = n;
    users[uid].ratings.push_back(to_string(cat)+" "+prodid);
}

void Kart::removeFromCart(string uid, vector<string> prodids){
    for(auto i:prodids){
        users[uid].wish.erase(i);
    }
    cout << "Selected items removed from cart" << endl;
}

void Kart::reviewProd(string uid,unsigned int cat,string prodid){
    review tmr;
    tmr.takeReview(users[uid].getName());
    users[uid].reviews.push_back(to_string(cat)+" "+prodid);
    prod[cat][prodid].redata[uid] = tmr;
}

void Kart::lordreview(unsigned int cat,string prodid,string rid,bool b){
    if(b) prod[cat][prodid].redata[rid].likes++;
    else prod[cat][prodid].redata[rid].dislikes++;
}

void Kart::checkout(string uid, vector<grp<string,unsigned int>> prods){
    cout << "Choose a Address to Deliver(Enter 0 to add new Address)" << endl;
    int j = 1;
    for(auto i:users[uid].addresses){
        cout << j << " :: ";
        i.displayAddress();
        j++;
    }
    int choose;
    cout << "Choose the address number: ";
    cin >> choose;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(choose==0){
        users[uid].addAddress();
        choose = j+1;
    }
    if(choose<1||choose>j){
        cout << "Invalid Address Chosen. " << endl;
        cout << "------------------------------------" << endl;
        cout << "order checkout failed" << endl;
        cout << "------------------------------------" << endl;
        return;
    }
    unsigned int amount = 0;
    stringstream ss;
    cout << "Order Placed of the following products: " << endl;
    j =1;
    for(auto i:prods){
        orders[i.a].push_back(uid);
        unsigned int ct;
        ss.str("");ss.clear();ss << i.a;
        string prodID;
        ss >> ct >> prodID;
        amount += i.b*prod[ct][prodID].amount;
        order tord;
        tord.ad = users[uid].addresses[choose-1];
        tord.isDelivered = false;
        cout << j << " :: " << prod[ct][prodID].name << endl;
        tord.log.push_back(tracklog("Order of Product "+prod[ct][prodID].name + " placed."));
        tord.log.push_back(tracklog("Quantity: " + to_string(i.b)));
        tord.log.push_back(tracklog("Order shipped from the nearest courier facility"));
        users[uid].wish.erase(i.a);
        users[uid].orders[to_string(i.b) + " " + i.a] = tord;
    }
    cout << "Total Amount: " << amount << endl;
}

void Kart::orderPage(string uid){
    cout << "************************************" << endl;
    if(users[uid].orders.empty()){
        cout << "You haven't placed any orders" << endl;
        cout << "************************************" << endl;
        return;
    }
    cout << "Your orders are" << endl;
    int j =1;
    vector<grp<string,string>> tmp;
    for(auto i:users[uid].orders){
        cout << "------------------------------------" << endl;
        stringstream ss(i.first);
        unsigned int cat;
        string prodid;
        ss >> cat >> prodid;
        tmp.push_back(grp<string,string>(prod[cat][prodid].name,i.first));
        cout << j << " :: name: " << prod[cat][prodid].name;
        if(i.second.isDelivered) cout << " DELIVERED" << endl;
        else cout << " ON THE WAY" << endl;
        j++; 
    }
    cout << "************************************" << endl;
    int n;
    cout << "Choose the Product Number: ";
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "************************************" << endl;
    if(n < 1 || n > j){
        cout << "Invalid Product Number" << endl;
        cout << "************************************" << endl;
        return;
    }
    cout << "Name: " << tmp[n-1].a << endl;
    cout << "Previous Logs are: " << endl;
    for(auto i:users[uid].orders[tmp[n-1].b].log){
        cout << i.time << " :: " << i.info << endl;
        cout << "------------------------------------" << endl;
    }
    cout << "************************************" << endl;
}

void Kart::WishlistPage(string uid, bool b){
    vector<grp<unsigned int,string>> wishlist;
    for(auto i:users[uid].wish){
        if(i.second==0){
            stringstream ss(i.first);
            grp<unsigned int,string> tmg(0,"");
            ss >> tmg.a >> tmg.b;
            wishlist.push_back(tmg);
        }
    }
    cout << "************************************" << endl;
    if(wishlist.empty()){
        cout << "Your Wishlist is empty" << endl;
        cout << "************************************" << endl;
        return;
    }
    int j = 1;
    for(auto i:wishlist){
        cout << j << " :: name: " << prod[i.a][i.b].name << endl;
        cout << "------------------------------------" << endl;
    }
    cout << "************************************" << endl;
    string str;
    vector<int> a;
    cout << "Choose the products to checkout" << endl;
    cout << "Enter the number/(s) seperated by spaces: ";
    getline(cin,str);
    stringstream ss(str);
    int tmn;
    while(ss >> tmn){
        if(tmn < 1 || tmn > j){
            cout << "Invalid Product Number" << endl;
            cout << "************************************" << endl;
            return;
        }
        a.push_back(tmn);
    }
    if(a.empty()){
        cout <<" No products chosen" << endl;
        cout << "************************************" << endl;
        return;
    }
    cout << "************************************" << endl;
    if(b){
        for(auto i:a){
            int pmn;
            cout << "Choose quantity for Product " << i << " :";
            cin >> pmn;
            if(pmn<=0){
                cout <<"Quantity must be  positive" << endl;
                cout << "************************************" << endl;
                return;
            }
            users[uid].wish[to_string(wishlist[i-1].a) + " " + wishlist[i-1].b] = pmn;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else{
        for(auto i:a){
            users[uid].wish.erase(to_string(wishlist[i-1].a) + " " + wishlist[i-1].b);
        }
    }
    cout << "************************************" << endl;
}

void Kart::AddWishlistORcart(string uid ,unsigned int cat ,string prodid ,bool b){
    if(b){
        users[uid].wish[to_string(cat)+" "+prodid] = 0;
        cout << "Added To Your Wishlist" << endl;
        return;
    }
    cout << "Choose the quantity of the Product: ";
    int n;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(n <= 0){
        cout << "Quantity cannot be negative" <<endl;
        return;
    }
    users[uid].wish[to_string(cat)+" "+prodid] = n;
}

void Kart::BuyNow(string uid,unsigned int cat,string prodid){
    cout << "Choose the quantity of the Product: ";
    int n;
    cin >> n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(n <= 0){
        cout << "Quantity must be negative" <<endl;
        return;
    }
    cout << "Choose a Address to Deliver(Enter 0 to add new Address)" << endl;
    int j = 1;
    for(auto i:users[uid].addresses){
        cout << j << " :: ";
        i.displayAddress();
        j++;
    }
    int choose;
    cout << "Choose the address number: ";
    cin >> choose;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(choose==0){
        users[uid].addAddress();
        choose = j+1;
    }
    else if(choose<1||choose>j){
        cout << "Invalid Address Chosen. " << endl;
        cout << "------------------------------------" << endl;
        cout << "order checkout failed" << endl;
        cout << "------------------------------------" << endl;
        return;
    }
    order tord;
    tord.ad = users[uid].addresses[choose-1];
    tord.isDelivered = false;
    tord.log.push_back(tracklog("Order of Product "+prod[cat][prodid].name + " placed."));
    tord.log.push_back(tracklog("Quantity: " + to_string(n)));
    tord.log.push_back(tracklog("Order shipped from the nearest courier facility"));
    users[uid].orders[to_string(cat)+" "+prodid] = tord;
    cout << "Ordersize: " << users[uid].orders.size() << endl;
    orders[to_string(cat)+" "+prodid].push_back(uid);
    cout << "Amount: " << prod[cat][prodid].amount << endl;
}

