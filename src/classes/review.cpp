#include "review.h"

review::review()
{
    title = body = tstamp = "";
    likes = dislikes = 0;
    userName = "";
}

review::review(std::string title, std::string body, std::string userName)
{
    tstamp = nowTime();
    likes = dislikes = 0;
    this->userName = userName;
    this->title = title;
    this->body = body;
}

review::review(const review &p)
{
    title = p.title;
    body = p.body;
    tstamp = p.tstamp;
    likes = p.likes;
    dislikes = p.dislikes;
    userName = p.userName;
}

review &review::operator=(const review &p)
{
    if (this != &p)
    {
        title = p.title;
        body = p.body;
        tstamp = p.tstamp;
        likes = p.likes;
        dislikes = p.dislikes;
        userName = p.userName;
    }
    return *this;
}

void review::displayRev()
{
    std::cout << "WrittenBy: " << userName << " on " << tstamp << std::endl;
    std::cout << title << std::endl;
    std::cout << body << std::endl;
    std::cout << "Likes: " << likes << "  Dislikes: " << dislikes << std::endl;
    std::cout << "*************************************************" << std::endl;
}

void review::LikeDislike(bool b)
{
    if (b)
        likes++;
    else
        dislikes++;
}

void review::takeReview(std::string name)
{
    std::cout << "Enter your Title for review: ";
    userName = name;
    std::string str;
    getline(std::cin, str);
    title = str;
    tstamp = nowTime();
    std::cout << "Enter a descriptive detail: ";
    getline(std::cin, str);
    body = str;
    likes = dislikes = 0;
}

std::ostream &operator<<(std::ostream &out, const review &p)
{
    out << "Name: " << p.userName << std::endl;
    out << "Time: " << p.tstamp << std::endl;
    out << "Title: " << p.title << std::endl;
    out << "Body: " << p.body << std::endl;
    out << "Likes: " << p.likes << "  Dislikes: " << p.dislikes;
    return out;
}

std::istream &operator>>(std::istream &in, review &p)
{
    std::string str;
    getline(in, str);
    std::stringstream ss(str);
    ss >> str >> p.userName;
    while (ss >> str)
        p.userName += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.tstamp;
    while (ss >> str)
        p.tstamp += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.title;
    while (ss >> str)
        p.title += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.body;
    while (ss >> str)
        p.body += " " + str;
    getline(in, str);
    ss.str("");
    ss.clear();
    ss << str;
    ss >> str >> p.likes >> str >> p.dislikes;
    return in;
}
