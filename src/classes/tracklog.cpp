#include "tracklog.h"

tracklog::tracklog() : time(""), info("") {}

tracklog::tracklog(const tracklog &p)
{
    time = p.time;
    info = p.info;
}

tracklog::tracklog(std::string s)
{
    time = nowTime();
    info = s;
}

tracklog &tracklog::operator=(const tracklog &p)
{
    if (this != &p)
    {
        time = p.time;
        info = p.info;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const tracklog &p)
{
    out << p.time << " :: " << p.info;
    return out;
}

std::istream &operator>>(std::istream &in, tracklog &p)
{
    std::string str;
    getline(in, str);
    std::stringstream ss(str);
    ss >> p.time >> str;
    p.time += " " + str;
    ss >> str >> p.info;
    while (ss >> str)
        p.info += " " + str;
    return in;
}
