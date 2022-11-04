#include "Login Code/login_functions.h"
#include "Menu Code/menu_functions.h"

struct Account;

int main() {
    int success = 0;
    success = s_option(success);
    printf("%i",success);
    if (success == 1) {
        menu();
    }
    return 0;
}