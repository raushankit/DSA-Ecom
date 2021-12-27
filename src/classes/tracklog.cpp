#include "tracklog.h"

tracklog::tracklog() : time(""),info("") {}

tracklog::tracklog(const tracklog &p){
    time = p.time;
    info = p.info;
}

tracklog::tracklog(string s){
    time = nowTime();
    info = s;
}

tracklog& tracklog::operator=(const tracklog &p){
    if(this!=&p){
        time = p.time;
        info = p.info;
    }
    return *this;
}

ostream& operator<<(ostream &out, const tracklog &p){
    out << p.time << " :: " << p.info;
    return out;
}

istream& operator>>(istream &in, tracklog &p){
    string str;
    getline(in,str);
    stringstream ss(str);
    ss >> p.time >> str;
    p.time += " "+str;
    ss >> str >> p.info;
    while(ss >> str) p.info += " "+str;
    return in;
}

