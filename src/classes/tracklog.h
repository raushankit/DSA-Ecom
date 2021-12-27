#ifndef __TRACK__
#define __TRACK__

#include "tstamp.h"
#include <sstream>

class Kart;

class tracklog{
    string time, info;

    friend class Kart;
    public:
    tracklog();
    tracklog(const tracklog&);
    tracklog& operator=(const tracklog&);
    tracklog(string);
    friend ostream& operator<<(ostream&, const tracklog&);
    friend istream& operator>>(istream&, tracklog&);
};

#endif
