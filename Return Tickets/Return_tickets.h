//
// Created by Louis Poblocki on 05/12/2022.
//

#ifndef P1_PROJECT_RETURN_TICKETS_H
#define P1_PROJECT_RETURN_TICKETS_H

#endif //P1_PROJECT_RETURN_TICKETS_H


typedef struct {
    char category[20];
    char genre[20];
    char performing[20];
    char opponent[20];
}ticket_return;

ticket_return all_tickets[10];

void fill_tickets_struct(int *tickets_in_profile);

void return_function(int *tickets_in_profile);

void run_return_tickets(int *tickets_in_profile);
