#ifndef __ORDER__
#define __ORDER__

#include "address.h"
#include "tracklog.h"
#include <vector>

class order{
    bool isDelivered;
    address ad;
    vector<tracklog> log;

    friend class Kart;
    public:
    order();
    order(const order&);
    order& operator=(const order&);
    void changeStat();
    void addlog(string);
    friend ostream& operator<<(ostream&, const order&);
    friend istream& operator>>(istream&, order&);
};


#endif
