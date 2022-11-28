#include "Login Code/login_functions.h"
#include "Purchasing of tickets/Purchase_tickets_functions.h"

struct Account;

int main() {
    /*
    int success = 0;
    success = s_option(success);
    printf("%i",success);
    if (success == 1) {
        menu();
    }
    return 0;
    */
    int choice = 1;
    int balance = 1000;

    profile_struct user = {"Test", balance, NULL};
    run_purchase_tickets(choice, &user);
    deallocate_ticket_list(&user.list_of_tickets);

    return 0;
}