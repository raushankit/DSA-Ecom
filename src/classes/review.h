#ifndef __REV__
#define __REV__

#include "tstamp.h"
#include <sstream>

class Kart;

class review{
    string title, body, tstamp;
    int likes,dislikes;
    string userName;

    friend class Kart;
    public:
    review();
    review(string, string, string);
    review(const review&);
    void takeReview(string);
    review& operator=(const review&);
    void displayRev();
    void LikeDislike(bool);// true for like vice versa
    friend ostream& operator<< (ostream&, const review&);
    friend istream& operator>>(istream&, review&);
};

#endif
