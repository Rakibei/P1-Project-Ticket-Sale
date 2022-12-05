//
// Created by Louis Poblocki on 05/12/2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "Return_tickets.h"

/**
 * Function fills struct with information while character in file is not EOF, also opens FILE with tickets in read mode
 * @param tickets_in_profile shows how many tickets are in profile
 * closes tickets FILE
 */
void fill_tickets_struct(int *tickets_in_profile){
    int character;
    int j=0;
    FILE* tickets_temp = fopen("Tickets.txt","r"); // NAME OF FINAL TICKET TEXT FILE HERE
    if (tickets_temp == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    while((character = getc(tickets_temp))!= EOF){
        ungetc(character,tickets_temp);
        fscanf(tickets_temp, "%s %s %s %s %s %s", all_tickets[j].category, all_tickets[j].genre
               ,all_tickets[j].performing, all_tickets[j].opponent,all_tickets[j].type, all_tickets[j].price);
        ++j;
    }
    *tickets_in_profile = j;

    fclose(tickets_temp);

}

/**
 * Function that returns the tickets(deletes from text FILE), return balance to user and ups the number of available
 * tickets.
 * Function opens tickets FILE in write mode
 * Function shows all tickets with assigned numbers and asks user which are to be returned
 * Function runs through all ticket numbers and DOES NOT print the ticket(struct) which the user wanted returned
 * Function prints the rest of the tickets neatly in text FILE
 * Function returns balance spent on buying to user and ups amount of tickets returned to available tickets
 * @param tickets_in_profile
 */
void return_function(int *tickets_in_profile){
    int ticket_number;


    FILE* tickets_returned = fopen("Tickets.txt","w");// NAME OF FINAL TICKET TEXT FILE HERE
    if (tickets_returned == NULL){
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    printf("Which ticket would you like to return?\n");
    for (int i = 0;  i < *tickets_in_profile; ++i ){
        printf("%d) %s\n%s\n%s\n%s\n%s\n%s\n",i,all_tickets[i].category, all_tickets[i].genre
               ,all_tickets[i].performing, all_tickets[i].opponent,all_tickets[i].type,all_tickets[i].price);
        printf("\n");
    }
    scanf("%d",&ticket_number);


    for (int i = 0;  i < *tickets_in_profile; ++i ){
        if(i != ticket_number){
            /*CHECKS IF THIS TICKET IS THE LAST, IF IT IS NO NEWLINE CHARACTER IS PRINTED, IF IT ALWAYS PRINTED NEWLINE
            TEXT FILE WOULD HAVE AN EXTRA EMPTY TICKET */

            //THIS IF IS FOR THE USER CHOOSING EVERY TICKET OTHER THAN THE LAST TO BE RETURNED
            if(*tickets_in_profile - ticket_number != 1){
                if(*tickets_in_profile - i != 1){
                    fprintf(tickets_returned,"%s %s %s %s %s %s\n",all_tickets[i].category, all_tickets[i].genre
                            ,all_tickets[i].performing, all_tickets[i].opponent,all_tickets[i].type
                            ,all_tickets[i].price);
                }
                else if(*tickets_in_profile - i == 1){
                    fprintf(tickets_returned,"%s %s %s %s %s %s",all_tickets[i].category, all_tickets[i].genre
                            ,all_tickets[i].performing, all_tickets[i].opponent,all_tickets[i].type
                            ,all_tickets[i].price);
                }
            }
            /* THIS ELSE IF IS FOR RETURNING THE LAST TICKET. TICKET NUMBER FOR LAST TICKET IS ALWAYS 1 LOWER THAN
             * TICKETS_IN_PROFILE THEREFORE == 1*/
            else if(*tickets_in_profile - ticket_number == 1){
                if(*tickets_in_profile - i != 2){
                    fprintf(tickets_returned,"%s %s %s %s %s %s\n",all_tickets[i].category, all_tickets[i].genre
                            ,all_tickets[i].performing, all_tickets[i].opponent,all_tickets[i].type
                            ,all_tickets[i].price);
                }
                // IF WE WANT TO RETURN THE LAST TICKET LETS SAY NUMBER 5 OUT OF 5, IT WOULD BE CHOICE 4 BECAUSE
                // 0 ALSO IS A PART OF THE STRUCT, THE NUMBER 4 WON'T ENTER THIS PART OF THE FUNCTION
                // BECAUSE OF THE FIRST IF "if(i != ticket_number)", THEREFORE THE TICKET BEFORE 4 WILL BE THE LAST = 3.
                // 5 (TICKETS) - 3(i, THE LAST 'i' BEFORE FUNCTION END) = 2, THEREFORE NO NEWLINE CHARACTER IN THIS ONE
                else if(*tickets_in_profile - i == 2){
                    fprintf(tickets_returned,"%s %s %s %s %s %s",all_tickets[i].category, all_tickets[i].genre
                            ,all_tickets[i].performing, all_tickets[i].opponent,all_tickets[i].type
                            ,all_tickets[i].price);
                }
            }
        }
    }
    printf("The ticket has been returned! Your new balance will be shown below.\n");

    // BALANCE GOES UP, PRICES NEEDED, IDENTIFIER OF TICKET TYPE IN TEXT FILE NEEDED

    int balance = 0; // DELETE LATER USED FOR TESTING

    balance = balance + atoi(all_tickets[ticket_number].price);
    printf("YOUR NEW BALANCE IS = %d\n",balance);


    // NUMBER OF TICKETS GOES UP HERE


    fclose(tickets_returned);
}

/**
 * Runs all the functions.
 * To be used in final program.
 * @param tickets_in_profile
 */
void run_return_tickets(int *tickets_in_profile){
    fill_tickets_struct(tickets_in_profile);
    return_function(tickets_in_profile);

    exit(EXIT_SUCCESS); // DELETE LATER, USED FOR TESTING
}