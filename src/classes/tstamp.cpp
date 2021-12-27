#include "tstamp.h"

bool getResponse(char small){
    string res;
    char big = (char)(small-'a'+'A');
    cout << "Enter your response: ";
    getline(cin,res);
    return (res[0]==small||res[0]==big);
}

string nowTime(){
    time_t now = time(0);
    tm *z = localtime(&now);
    string t = "";
    if(z->tm_mday < 10) t+="0";
    t+=to_string(z->tm_mday)+"/";
    if(z->tm_mon < 9) t+="0";
    t+=to_string(z->tm_mon+1)+"/"+to_string(1900+z->tm_year)+" ";
    int hour = (z->tm_hour+11)%12 + 1;
    if(hour<10)t+="0";
    t += to_string(hour)+":";
    if(z->tm_min<10)t+="0";
    t += to_string(z->tm_min)+":";
    if(z->tm_sec<10)t+="0";
    t += to_string(z->tm_sec)+":";
    t += (z->tm_hour>=12)?"PM":"AM";
    return t;
}

string Timestamp(){
    unsigned long long int now =       std::chrono::seconds(std::chrono::seconds(std::time(NULL))).count();
    return to_string(now);
}
