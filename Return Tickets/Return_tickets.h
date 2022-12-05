//
// Created by Louis Poblocki on 05/12/2022.
//

#ifndef P1_PROJECT_RETURN_TICKETS_H
#define P1_PROJECT_RETURN_TICKETS_H

#endif //P1_PROJECT_RETURN_TICKETS_H

/**
 * Ticket struct, takes ticket info, later to be placed in an array of structs
 */
typedef struct {
    char category[20];
    char genre[20];
    char performing[20];
    char opponent[20];
    char type[20];
    char price[20];
}ticket_return;

/**
 * Array of structs, number indicates max amount of tickets possible to be ran by program
 */
ticket_return all_tickets[10];

void fill_tickets_struct(int *tickets_in_profile);

void return_function(int *tickets_in_profile);

void run_return_tickets(int *tickets_in_profile);
