#include "order.h"

order::order()
{
    isDelivered = false;
    log.clear();
}

order::order(const order &p)
{
    isDelivered = p.isDelivered;
    log = p.log;
    ad = p.ad;
}

order &order::operator=(const order &p)
{
    if (this != &p)
    {
        isDelivered = p.isDelivered;
        log = p.log;
        ad = p.ad;
    }
    return *this;
}

void order::changeStat()
{
    isDelivered = true;
}

std::ostream &operator<<(std::ostream &out, const order &p)
{
    out << "Delivered: " << p.isDelivered << std::endl;
    out << p.ad << std::endl;
    out << "Logsize: " << p.log.size() << std::endl;
    for (auto i : p.log)
        out << i << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, order &p)
{
    std::string str;
    getline(in, str);
    std::stringstream ss(str);
    ss >> str >> p.isDelivered;
    int n;
    in >> p.ad;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> n;
    for (int i = 0; i < n; i++)
    {
        tracklog temp;
        in >> temp;
        p.log.push_back(temp);
    }
    return in;
}

void order::addlog(std::string s)
{
    log.push_back(tracklog(s));
}
