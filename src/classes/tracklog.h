#ifndef __TRACK__
#define __TRACK__

#include "tstamp.h"
#include <sstream>

class Kart;

class tracklog
{
    std::string time, info;

    friend class Kart;

public:
    tracklog();
    tracklog(const tracklog &);
    tracklog &operator=(const tracklog &);
    tracklog(std::string);
    friend std::ostream &operator<<(std::ostream &, const tracklog &);
    friend std::istream &operator>>(std::istream &, tracklog &);
};

#endif
