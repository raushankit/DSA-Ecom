#include "order.h"

order::order(){
    isDelivered = false;
    log.clear();
}

order::order(const order &p){
    isDelivered = p.isDelivered;
    log = p.log;
    ad = p.ad;
}

order& order::operator=(const order &p){
    if(this!=&p){
        isDelivered = p.isDelivered;
        log = p.log;
        ad = p.ad;
    }
    return *this;
}

void order::changeStat(){
    isDelivered = true;
}

ostream& operator<<(ostream &out, const order &p){
    out << "Delivered: " << p.isDelivered << endl;
    out << p.ad << endl;
    out << "Logsize: " << p.log.size() << endl;
    for(auto i:p.log) out << i << endl;
    return out;
}

istream& operator>>(istream &in, order &p){
    string str;
    getline(in,str);
    stringstream ss(str);
    ss >> str >> p.isDelivered;
    int n;
    in >> p.ad;
    getline(in, str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> n;
    for(int i = 0;i < n;i++){
        tracklog temp;
        in >> temp;
        p.log.push_back(temp);
    }
    return in;
}

void order::addlog(string s){
    log.push_back(tracklog(s));
}
