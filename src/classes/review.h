#ifndef __REV__
#define __REV__

#include "tstamp.h"
#include <sstream>

class Kart;

class review
{
public:
    review();
    review(std::string, std::string, std::string);
    review(const review &);
    void takeReview(std::string);
    review &operator=(const review &);
    void displayRev();
    void LikeDislike(bool); // true for like vice versa
    friend std::ostream &operator<<(std::ostream &, const review &);
    friend std::istream &operator>>(std::istream &, review &);

private:
    std::string title, body, tstamp;
    int likes, dislikes;
    std::string userName;

    friend class Kart;
};

#endif
