//
// Created by alexa on 21/11/2022.
//

#ifndef P1_PROJECT_PROFILE_DATA_STORAGE_H
#define P1_PROJECT_PROFILE_DATA_STORAGE_H

#endif //P1_PROJECT_PROFILE_DATA_STORAGE_H

typedef struct{
    char location[30];
    int time;
} ticket_struct;

typedef struct ticket_node{
    ticket_struct ticket;
    struct ticket_node* next;
} ticket_node;

typedef struct{
    ticket_node* head;
} ticket_list;

typedef struct{
    char username[30];
    ticket_list my_tickets;
} profile_struct;

void update_profile(ticket_struct new_ticket, profile_struct my_profile, int prize);
void deallocate_ticket_list(ticket_list* list);