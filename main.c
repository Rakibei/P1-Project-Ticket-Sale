#include "Login Code/login_functions.h"
#include "Menu Code/menu_functions.h"

struct Account;

int main() {
    int success = 0;
    s_option(success);

    menu(success);

    return 0;
}