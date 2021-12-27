#include "page.h"

int main()
{
    Kart k("Ankit");
    k.loadData();
    k.processOrders();
    frontPage(k, true, "", "USER1615814063");
    // username is a
    // password is 9
    return 0;
}
