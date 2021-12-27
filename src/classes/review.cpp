#include "review.h"

review::review(){
    title = body = tstamp = "";
    likes = dislikes = 0;
    userName = "";
}

review::review(string title, string body, string userName){
    tstamp = nowTime();
    likes = dislikes = 0;
    this->userName = userName;
    this->title = title;
    this->body = body;
}

review::review(const review &p){
    title = p.title;
    body = p.body;
    tstamp = p.tstamp;
    likes = p.likes;
    dislikes = p.dislikes;
    userName = p.userName;
}

review& review::operator=(const review &p){
    if(this != &p){
        title = p.title;
        body = p.body;
        tstamp = p.tstamp;
        likes = p.likes;
        dislikes = p.dislikes;
        userName = p.userName;
    }
    return *this;
}

void review::displayRev(){
    cout << "WrittenBy: " << userName << " on " << tstamp << endl;
    cout << title << endl;
    cout << body << endl;
    cout << "Likes: " << likes << "  Dislikes: " << dislikes << endl;
    cout << "*************************************************" << endl;
}

void review::LikeDislike(bool b){
    if(b) likes++;
    else dislikes++;
}

void review::takeReview(string name){
    cout << "Enter your Title for review: ";
    userName = name;
    string str;
    getline(cin,str);
    title = str;
    tstamp = nowTime();
    cout << "Enter a descriptive detail: ";
    getline(cin,str);
    body = str;
    likes = dislikes = 0;
}

ostream& operator<< (ostream &out, const review &p){
    out << "Name: " << p.userName << endl;
    out << "Time: " << p.tstamp << endl;
    out << "Title: " << p.title << endl;
    out << "Body: " << p.body << endl;
    out << "Likes: " << p.likes << "  Dislikes: " << p.dislikes;
    return out;
}

istream& operator>> (istream &in, review &p){
    string str;
    getline(in, str);
    stringstream ss(str);
    ss >> str >> p.userName;
    while(ss >> str) p.userName += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.tstamp;
    while(ss >> str) p.tstamp += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.title;
    while(ss >> str) p.title += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.body;
    while(ss >> str) p.body += " "+str;
    getline(in,str);
    ss.str("");ss.clear();ss << str;
    ss >> str >> p.likes >> str >> p.dislikes;
    return in;
}
