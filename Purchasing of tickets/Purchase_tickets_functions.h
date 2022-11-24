//
// Created by Louis Poblocki on 22/11/2022.
//

#ifndef PURCHASING_OF_TICKETS_PURCHASING_OF_TICKETS_H
#define PURCHASING_OF_TICKETS_PURCHASING_OF_TICKETS_H

#endif //PURCHASING_OF_TICKETS_PURCHASING_OF_TICKETS_H


int purchase_tickets(int *choice);

int amount_of_tickets(int *number_of_tickets, int *amount_choice);

int type_of_ticket(int *ticket_type, int *ticket_choice,int *total,int *number_of_tickets);

void extras(int *extras_type, int *extras_choice,int *total);

int payment(int *total, int *checkout_choice, int balance);

void run_purchase_tickets(int choice, int number_of_tickets, int amount_choice, int ticket_type, int ticket_choice, int total, int checkout_choice, int balance);