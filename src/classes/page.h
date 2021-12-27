#ifndef __PAGE__
#define __PAGE__

#include "pageCode.h"
#include "grp.h"
#include "kart.h"

void ProfilePage(Kart &, bool, string, string);

string loginActivity(Kart &, string);

grp<string, string> frontPageOperation(Kart &, string);

void frontPage(Kart &, bool, string, string);

void ProductPage(Kart &, bool, unsigned int, string, string, string, vector<string> &);

void cartPage(Kart &, string, string, bool);

#endif
