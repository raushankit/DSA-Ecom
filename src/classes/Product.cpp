#include "Product.h"

Product::Product(){
    name = description = "";
    amount = quantity = category = 0;
    rating = 0;
    redata.clear();
    ratdata.clear();
}

Product::Product(string n,string d, unsigned int am,unsigned int q, unsigned int cat){
    name = n;description = d;
    amount = am;quantity = q;category = cat;
    rating = 0;
    redata.clear();
    ratdata.clear();
}

Product::Product(const Product &p){
    name = p.name;
    description = p.description;
    amount = p.amount;
    quantity = p.quantity;
    category = p.category;
    rating = p.rating;
    redata = p.redata;
    ratdata = p.ratdata;
}

Product& Product::operator=(const Product &p){
    if(this!=&p){
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

void Product::addRating(string userId, unsigned int n){
    ratdata[userId] = n;
    unsigned int m = ratdata.size();
    rating = (rating*(m-1)+n)/(1.0*m);
}

void Product::addReview(string userId, review p){
    redata[userId] = p;
}

string Product::getName(){
    return name;
}

ostream& operator<<(ostream &out, const Product &p){
    out << "Name: " << p.name << endl;
    out << "Description: " << p.description << endl;
    out << "Price: " << p.amount << endl;
    out << "Quantity: " << p.quantity << endl;
    out << "Category: " << p.category << endl;
    out << "Rating: " << p.rating << endl;
    out << "ReviewSize: " << p.redata.size() << endl;
    for(auto i:p.redata){
        out << "WrittenBy: " << i.first << endl;
        out << i.second << endl;
    }
    out << "RatingSize: " << p.ratdata.size() << endl;
    for(auto i:p.ratdata){
        out << "WrittenBy: " << i.first << " " << i.second << endl;
    }
    return out;
}

vector<string> Product::displayProduct(){
    vector<string> revids;
    if(quantity==0)cout << "out of stock" << endl;
    cout << "Name: " << name << endl;
    cout << description << endl;
    cout << "Price  = " << amount << endl;
    if(ratdata.empty()) cout << "No Ratings yet" << endl;
    else cout << "rated " << rating << " star" << endl;
    int j = 1;
    if(redata.empty()) cout << "No reviews yet" << endl;
    for(auto i:redata){
        revids.push_back(i.first);
        cout << "*************************************************" << endl;
        cout << j << " :: ";
        j++;
        i.second.displayRev();
    }
    return revids;
}

istream& operator>>(istream &in, Product &p){
    string str;
    getline(in,str);
    stringstream ss(str);
    ss >> str >> p.name;
    while(ss >> str) p.name += " "+str; 
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.description;
    while(ss >> str) p.description += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.amount;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.quantity;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.category;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.rating;
    int n;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> str;
        review temp;
        in >> temp;
        p.redata[str] = temp;
    }
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        unsigned int temp;
        getline(in,str);
        ss.str("");ss.clear();ss << str;
        ss >> str >> str >> temp;
        p.ratdata[str] = temp;
    }
    return in;
}

