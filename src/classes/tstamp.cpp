#include "tstamp.h"

bool getResponse(char small)
{
    std::string res;
    char big = (char)(small - 'a' + 'A');
    std::cout << "Enter your response: ";
    getline(std::cin, res);
    return (res[0] == small || res[0] == big);
}

std::string nowTime()
{
    time_t now = time(0);
    tm *z = localtime(&now);
    std::string t = "";
    if (z->tm_mday < 10)
        t += "0";
    t += std::to_string(z->tm_mday) + "/";
    if (z->tm_mon < 9)
        t += "0";
    t += std::to_string(z->tm_mon + 1) + "/" + std::to_string(1900 + z->tm_year) + " ";
    int hour = (z->tm_hour + 11) % 12 + 1;
    if (hour < 10)
        t += "0";
    t += std::to_string(hour) + ":";
    if (z->tm_min < 10)
        t += "0";
    t += std::to_string(z->tm_min) + ":";
    if (z->tm_sec < 10)
        t += "0";
    t += std::to_string(z->tm_sec) + ":";
    t += (z->tm_hour >= 12) ? "PM" : "AM";
    return t;
}

std::string Timestamp()
{
    unsigned long long int now = std::chrono::seconds(std::chrono::seconds(std::time(NULL))).count();
    return std::to_string(now);
}
