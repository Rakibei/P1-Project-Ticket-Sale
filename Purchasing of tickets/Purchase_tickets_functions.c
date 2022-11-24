//
// Created by Louis Poblocki on 24/11/2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "Purchase_tickets_functions.h"
//#include "profile_data_storage.c/profile_data_storage.h"

#define NORMAL_PRICE 100 // DELETE LATER USED FOR TESTING
#define VIP_PRICE 200 // DELETE LATER USED FOR TESTING

int main(void){
    int choice;
    int amount_choice,number_of_tickets;
    int ticket_type,ticket_choice;
    int extras_type,extras_choice;
    int total;
    int checkout_choice;
    int balance = 500; // DELETE LATER USED FOR TESTING

    run_purchase_tickets(choice,  number_of_tickets,  amount_choice,  ticket_type,  ticket_choice,  total,  checkout_choice,  balance);

}
/**
 * Asks the user if he wants to purchase tickets
 * @param choice decides if to return to ticket info or continue
 * @return returns choice which decides what happens
 */
int purchase_tickets(int *choice){
    printf("Press 1 to purchase the ticket(s). Press 2 to go back.\n");
    scanf("%d", choice);
    return *choice;
}
/**
 * Asks the user the amount of tickets
 * @param number_of_tickets is the number or tickets to be purchased
 * @param amount_choice decides if the user wants to continue or go back
 * @return returns amount_choice which decides what happens now
 */

int amount_of_tickets(int *number_of_tickets, int *amount_choice){
    printf("How many ticket(s) would you like?\n");
    scanf("%d", number_of_tickets);

    printf("You have chosen %d ticket(s). Press 1 to continue or press 2 to go back\n",*number_of_tickets);
    scanf("%d", amount_choice);
    return *amount_choice;

}

/**
 * Asks the user which type of ticket is desired
 * @param ticket_type Normal or VIP ticket choice
 * @param ticket_choice decides to continue or to go back
 * @param total total price which gets updated after choosing the ticket-type
 * @param number_of_tickets pointer from "amount_of_tickets", is the amount of tickets
 * @return returns ticket choice which decides to continue or go back
 */
int type_of_ticket(int *ticket_type, int *ticket_choice,int *total, int *number_of_tickets){
    printf("Choose your type of ticket(s).\n");
    printf("Press 1 for normal ticket(s) or press 2 for VIP ticket(s)\n");
    scanf("%d", ticket_type);
    if(*ticket_type == 1){
        printf("You have chosen %d normal ticket(s). Press 1 to continue or press 2 to go back\n",*number_of_tickets);
        *total = *number_of_tickets * NORMAL_PRICE;
    }
    else if (*ticket_type == 2){
        printf("You have chosen %d VIP ticket(s). Press 1 to continue or press 2 to go back\n",*number_of_tickets);
        *total = *number_of_tickets * VIP_PRICE;
    }
    scanf("%d",ticket_choice);

    return *ticket_choice;
}

void extras(int *extras_type, int *extras_choice,int *total){
    // NOT SURE IF GOING TO BE USED
}


/**
 * Asks the user for payment, updates balance, ticket amount and profile with the tickets if purchased
 * @param total Is the total cost of the basket
 * @param checkout_choice decides whether to finalise payment or go back
 * @param balance shows users balance
 * @return returns checkout choice which decides whether to finalise or go back
 */
int payment(int *total, int *checkout_choice, int balance){
    printf("Your total is = %d\n",*total);
    printf("Your balance is = %d\n", balance);
    printf("Press 1 to complete purchase or press 2 to go back\n");
    scanf("%d", checkout_choice);

    if (*checkout_choice == 1){
        if(balance >= *total){
            balance = balance - *total;
            printf("Payment successful\n");
            printf("New balance is = %d\n",balance);
            printf("You can now access your ticket(s) in the profile menu, enjoy your event.\n");

            // UPDATE NUMBER OF TICKETS HERE


            // UPDATE PROFILE WITH TICKETS FUNCTION HERE
            // update_profile(ticket_struct new_ticket, profile_struct my_profile, prize);
            // deallocate_ticket_list(ticket_list* list);


        }
        else if(balance < *total){
            printf("Not enough funds for purchase, refill and try again\n");
            exit(EXIT_FAILURE);
        }
    }
    return *checkout_choice;
}

/**
 * Runs program in a loop until payment is finalised or until user goes back all the way to ticket info
 * @param choice pointer from before
 * @param number_of_tickets pointer from before
 * @param amount_choice pointer from before
 * @param ticket_type pointer from before
 * @param ticket_choice pointer from before
 * @param total pointer from before
 * @param checkout_choice pointer from before
 * @param balance pointer from before
 */
void run_purchase_tickets (int choice, int number_of_tickets, int amount_choice, int ticket_type, int ticket_choice, int total, int checkout_choice, int balance ){
    if(purchase_tickets(&choice) == 1){
        while (choice == 1){
            if (amount_of_tickets(&number_of_tickets, &amount_choice) == 1) {
                if (type_of_ticket( &ticket_type,  &ticket_choice, &total, &number_of_tickets) ==1){
                    if(payment(&total, &checkout_choice, balance)==1){
                        exit(EXIT_SUCCESS);
                    }
                }
            }
            else if (amount_choice != 1) {
                purchase_tickets(&choice);
            }
            else if (ticket_choice != 1) {
                amount_of_tickets(&number_of_tickets, &amount_choice);
            }
            else if (checkout_choice != 1) {
                type_of_ticket(&ticket_type, &ticket_choice, &total, &number_of_tickets);
            }
        }
    }
    else {
        // GO BACK TO TICKET INFO HERE
    }
}