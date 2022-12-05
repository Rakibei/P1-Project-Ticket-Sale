//
// Created by Louis Poblocki on 05/12/2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "Return_tickets.h"

void fill_tickets_struct(int *tickets_in_profile){
    int ch;
    int j=0;
    FILE* tickets_temp = fopen("Tickets.txt","r");
    if (tickets_temp == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    while((ch = getc(tickets_temp))!= EOF){
        ungetc(ch,tickets_temp);
        fscanf(tickets_temp, "%s %s %s %s", all_tickets[j].category, all_tickets[j].genre, all_tickets[j].performing, all_tickets[j].opponent);
        ++j;
    }
    *tickets_in_profile = j;

    fclose(tickets_temp);

}

void return_function(int *tickets_in_profile){
    printf("%d\n",*tickets_in_profile);
    int tickets_to_be_returned;
    int ticket_number;
    printf("How many tickets would you like to return?\n");
    scanf("%d", &tickets_to_be_returned);

    FILE* tickets_returned = fopen("Tickets.txt","w");
    if (tickets_returned == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    if(tickets_to_be_returned == 1){
        printf("Which ticket(s) would you like to return?\n");
        for (int i = 0;  i < *tickets_in_profile; ++i ){
            printf("%d) %s\n %s\n %s\n %s\n",i,all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
        }
        scanf("%d",&ticket_number);

        for (int i = 0;  i < *tickets_in_profile; ++i ){
            if(i != ticket_number){
                if(*tickets_in_profile - ticket_number != 1){
                    if(*tickets_in_profile - i != 1){
                        fprintf(tickets_returned,"%s %s %s %s\n",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                    else if(*tickets_in_profile - i == 1){
                        fprintf(tickets_returned,"%s %s %s %s",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                }
                else if(*tickets_in_profile - ticket_number == 1){
                    if(*tickets_in_profile - i != 2){
                        fprintf(tickets_returned,"%s %s %s %s\n",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                    else if(*tickets_in_profile - i == 2){
                        fprintf(tickets_returned,"%s %s %s %s",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                }
            }
        }
    }

    else if(tickets_to_be_returned > 1){
        printf("Which tickets would you like to return?\n");
        for (int i = 0;  i < *tickets_in_profile; ++i ){
            printf("%d) %s\n %s\n %s\n %s\n",i,all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
        }
        scanf("%d",&ticket_number);

        for (int i = 0;  i < *tickets_in_profile; ++i ){
            if(i != ticket_number){
                if(*tickets_in_profile - ticket_number != 1){
                    if(*tickets_in_profile - i != 1){
                        fprintf(tickets_returned,"%s %s %s %s\n",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                    else if(*tickets_in_profile - i == 1){
                        fprintf(tickets_returned,"%s %s %s %s",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                }
                else if(*tickets_in_profile - ticket_number == 1){
                    if(*tickets_in_profile - i != 2){
                        fprintf(tickets_returned,"%s %s %s %s\n",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                    else if(*tickets_in_profile - i == 2){
                        fprintf(tickets_returned,"%s %s %s %s",all_tickets[i].category, all_tickets[i].genre, all_tickets[i].performing, all_tickets[i].opponent);
                    }
                }
            }
        }
    }

    fclose(tickets_returned);

}

void run_return_tickets(int *tickets_in_profile){
    fill_tickets_struct(tickets_in_profile);
    return_function(tickets_in_profile);


    exit(EXIT_SUCCESS);
}