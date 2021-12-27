#ifndef __ORDER__
#define __ORDER__

#include "address.h"
#include "tracklog.h"
#include <vector>

class order
{
public:
    order();
    order(const order &);
    order &operator=(const order &);
    void changeStat();
    void addlog(std::string);
    friend std::ostream &operator<<(std::ostream &, const order &);
    friend std::istream &operator>>(std::istream &, order &);

private:
    bool isDelivered;
    address ad;
    std::vector<tracklog> log;

    friend class Kart;
};

#endif
