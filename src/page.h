#ifndef __PAGE__
#define __PAGE__

#include "classes/pageCode.h"
#include "classes/grp.h"
#include "classes/kart.h"

void ProfilePage(Kart &, bool, std::string, std::string);

std::string loginActivity(Kart &, std::string);

grp<std::string, std::string> frontPageOperation(Kart &, std::string);

void frontPage(Kart &, bool, std::string, std::string);

void ProductPage(Kart &, bool, unsigned int, std::string, std::string, std::string, std::vector<std::string> &);

void cartPage(Kart &, std::string, std::string, bool);

#endif
