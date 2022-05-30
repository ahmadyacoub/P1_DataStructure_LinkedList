
// Ahmad Jaghama 1202450 sec #1
// line 611 added else statement just copied from above it that deletes a passenger when we didn't assign
// also line 157
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct passenger { // declaring the passenger structure
    int travelerId;
    int travellingDate;
    char travellingTime[200];
    char from[200];
    char to[200];
    struct passenger *link;
} passenger;
typedef struct Bus {// declaring the bus structure
    int busNumber;
    int date;
    char departureTime[200];
    char from[200];
    char to[200];
    int price;
    int capacity;
    passenger *pass; // this pointer is to add passengers in the bus
    struct Bus *link;
} Bus;

// find node function used to find a specific passenger node using the id from linked list
passenger *findPassenger(passenger *head, int i) {
    passenger *result = head;
    while (result != NULL && result->travelerId != i) {
        result = result->link;
    }
    return result;
}

// find node function used to find a specific bus node using the bus number from linked list
Bus *findBus(Bus *head, int i) {
    Bus *result = head;
    while (result != NULL && result->busNumber != i) {
        result = result->link;
    }
    return result;
}

// to find the node that is previous from the needed node used in delete node
passenger *find_prevPassenger(passenger *head, int data) {
    passenger *ptr = head;
    while (ptr->link != NULL && ptr->link->travelerId != data)
        ptr = ptr->link;
    return ptr;

}

// to find the node that is previous from the needed node used in delete node
Bus *find_prevBus(Bus *head, int data) {
    Bus *ptr = head;
    while (ptr->link != NULL && ptr->link->busNumber != data)
        ptr = ptr->link;
    return ptr;

}

// a function to delete a specific passenger node used in assigning function
void deletePasseneger(passenger *head, int data) {

    passenger *temp = findPassenger(head, data)->link;
    findPassenger(head, data)->link = NULL;
    find_prevPassenger(head, data)->link = temp;

}

// a function to delete a specific Bus node used in assigning function
void deleteBus(Bus *head, int data) {

    Bus *temp = findBus(head, data)->link;
    findBus(head, data)->link = NULL;
    find_prevBus(head, data)->link = temp;
}

// a function to delete a full linked list
void deleteList(passenger *head) {
    passenger *ptr;
    passenger *temp;
    ptr = head->link;
    head->link = NULL;
    while (ptr != NULL) {
        temp = ptr->link;
        free(ptr);
        ptr = temp;
    }

}

// a function to append a passenger node after last node in linkedlist
void appendPassenger(passenger *head, char travelerId[200], char travellingDate[200], char travellingTime[200],
                     char from[200], char to[200]) {
    passenger *new = (passenger *) malloc(sizeof(passenger)); // declare the head of Linked
    new->link = NULL;
    new->travelerId = atoi(travelerId);
    new->travellingDate = atoi(travellingDate);
    strcpy(new->travellingTime, travellingTime); // str cpy is used to copy strings
    strcpy(new->from, from);
    strcpy(new->to, to);
    passenger *ptr = head;
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }
    ptr->link = new;


}

//  same as before but this is more fast and accurate  after getting the data from files
void appendPassengerToBus(passenger *head, int travelerId, int travellingDate, char travellingTime[], char from[],
                          char to[]) {
    passenger *new = (passenger *) malloc(sizeof(passenger));
    new->link = NULL;
    new->travelerId = travelerId;
    new->travellingDate = travellingDate;
    strcpy(new->travellingTime, travellingTime);
    strcpy(new->from, from);
    strcpy(new->to, to);
    passenger *ptr = head;
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }
    ptr->link = new;
}

// a function to append busses from files  busses.txt
void appendBus(Bus *head, char busNumber[200], char date[200], char departureTime[200], char from[200], char to[200],
               char price[200], char capacity[200]) {
    Bus *new = (Bus *) malloc(sizeof(Bus));
    new->link = NULL;
    new->busNumber = atoi(busNumber);
    new->date = atoi(date);
    strcpy(new->departureTime, departureTime);

    strcpy(new->from, from);
    strcpy(new->to, to);
    new->price = atoi(price);
    new->capacity = atoi(capacity);
    Bus *ptr = head;
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }
    ptr->link = new;
}

// a function used to print passengers linked lists
void printPassenger(passenger *head) {
    passenger *ptr = head->link;
    int c = 0;
    if (ptr == NULL) {
        printf("\t\t\t\t\t\t  Bus  is Empty "); // Changed the output -> from "node %d is Null" to  "Bus id Empty"
    } else {
        while (ptr != NULL) {
            if (ptr->link == NULL) {
                printf("\n\t LAST Passenger # %d id === %d , Date :  %d ,Time : %s, from : %s , to : %s", c + 1,
                       ptr->travelerId, ptr->travellingDate, ptr->travellingTime, ptr->from, ptr->to);
                break;
            } else {
                printf("\n\t Passenger # %d id === %d , Date : %d ,Time : %s, from : %s , to : %s", c + 1,
                       ptr->travelerId,
                       ptr->travellingDate, ptr->travellingTime, ptr->from, ptr->to);
                c++;
                ptr = ptr->link;
            }
        }
    }
}

void printBus(Bus *head) { // to print all busses information
    Bus *ptr = head->link;
    int c = 0;
    if (ptr == NULL) {
        printf("\n\t  %d node is Null ", c);

    } else {
        while (ptr != NULL) {
            if (ptr->link == NULL) {
                printf("\n\t LAST node # %d id === %d , Date :  %d ,Time : %s, from : %s , to : %s , price : %d , capacity : %d",
                       c + 1, ptr->busNumber, ptr->date, ptr->departureTime, ptr->from, ptr->to, ptr->price,
                       ptr->capacity);

                break;
            } else {
                printf("\n\t node # %d id === %d , Date :  %d ,Time : %s, from : %s , to : %s , price : %d , capacity : %d",
                       c + 1, ptr->busNumber, ptr->date, ptr->departureTime, ptr->from, ptr->to, ptr->price,
                       ptr->capacity);
/*
                printf("\n-------------its passengers in integers  are --------------\n");

                printPassenger(ptr->pass);



                printf("---------------------------\n");
*/
                c++;
                ptr = ptr->link;
            }
        }
    }
}

void assignPassengers(Bus *busHead, passenger *Passengers, passenger *ON_Passengers, passenger *UN_Passengers) {
    deleteList(UN_Passengers); // to avoid repetition
    deleteList(ON_Passengers);// to avoid repetition
    passenger *passenger1 = Passengers->link;
    passenger *tempPass;
    int a;
    while (passenger1 != NULL) {
        tempPass = findPassenger(Passengers, passenger1->travelerId)->link;
        a = 0;
        Bus *bus = busHead->link;
        while (bus != NULL) {
            if (strcmp(passenger1->travellingTime, bus->departureTime) == 0 &&
                passenger1->travellingDate == bus->date &&
                strcmp(passenger1->from, bus->from) == 0 &&
                (strcmp(passenger1->to, bus->to) == 0 ||
                 (strcmp(passenger1->to, bus->to) == 10 && (passenger1->to[0] == bus->to[0])))
                && bus->capacity > 0) {
                // 10 because of that <<fgets>> does not remove new line and by ascii code the difference is 10 OR there was problem in strcmp
                appendPassengerToBus(bus->pass, passenger1->travelerId,
                                     passenger1->travellingDate, passenger1->travellingTime,
                                     passenger1->from, passenger1->to);
                appendPassengerToBus(ON_Passengers, passenger1->travelerId,
                                     passenger1->travellingDate, passenger1->travellingTime,
                                     passenger1->from, passenger1->to); // to check in deletion

                int temp = (bus->capacity) - 1; // to not have passengers more than seats
                bus->capacity = temp;
                a++;
            }
            bus = bus->link;
        }
        if (a == 0) {

            appendPassengerToBus(UN_Passengers, passenger1->travelerId, passenger1->travellingDate,
                                 passenger1->travellingTime,
                                 passenger1->from, passenger1->to); // to check when we want to delete a passenger
        }
        passenger1 = tempPass;
    }
}

// this function is used to scan an integer from console better than scanf that is not efficient
int scanInt() {
    char temp[10];
    fgets(temp, 10, stdin);
    int len = strlen(temp);
    if (len > 0 && temp[len - 1] == '\n')
        temp[len - 1] = '\0';
    return atoi(temp);
}

// this function is used to scan a char from console better than scanf that is not efficient used once
char scanChar() {
    char temp[10];
    fgets(temp, 10, stdin);
    int len = strlen(temp);
    if (len > 0 && temp[len - 1] == '\n')
        temp[len - 1] = '\0';
    return temp[0];
}

int main() {

    // -------------------------------------------declaring heads of linked lists and some variables--------------------------------------
    passenger *passengersHead = (passenger *) malloc(sizeof(passenger));

    passengersHead->link = NULL;

    passenger *ONB_Passengers = (passenger *) malloc(sizeof(passenger));//ON BUS PASSENGERS ARRAY LIST

    ONB_Passengers->link = NULL;

    passenger *UN_Passengers = (passenger *) malloc(sizeof(passenger)); // UNMATCHED

    UN_Passengers->link = NULL;

    Bus *busHead = (Bus *) malloc(sizeof(Bus));

    busHead->link = NULL;


    char *tok;
    char *passID[200];
    char *travellingDate[200];
    char *travellingTime[200];
    char *from[200];
    char *to[200];
    char array[1000][255];
    char line[255];
    int c;
    int a;
    int loadBusLimit = 0;
    int loadPassLimit = 0;

    int num = 0; // to get the user input choice

    int idDel;
    char switchLine[10];


    //  ----------------------------------------------------------------------------------------------------------------

    // -------------------------------------------files declaring for loading data--------------------------------------
//    FILE *passFile = fopen("passengers.txt", "r");
//
//    FILE *BusFile = fopen("busses.txt", "r");
    // this is u attached but in my computer it needs a Full Path like
    //  Users/ahmadyacoub/CLionProjects/P1_1202450_AhmadJaghama_1.c/passengers.txt

    FILE *passFile = fopen("/Users/ahmadyacoub/CLionProjects/P1_1202450_AhmadJaghama_1.c/passengers.txt", "r");

    FILE *BusFile = fopen("/Users/ahmadyacoub/CLionProjects/P1_1202450_AhmadJaghama_1.c/busses.txt", "r");
    //  ----------------------------------------------------------------------------------------------------------------


    while (1) { // a while loop for program menu
        printf("\n------------------------------------------------------------------------------------------------\n");
        printf("1-Load the busses information file\n");
        printf("2-Load the passengers information file\n");
        printf("3-Assign passengers and print assignment information of all busses \n");
        printf("4-Print a specific bus information along with its passengers information (names and IDs) \n");
        printf("5-Print unmatched passengers \n");
        printf("6-Add new passenger \n");

        printf("7-Delete passenger \n");
        printf("8-Delete bus number\n");
        printf("9- EXIT\n");
        printf(" ENTER YOUR CHOICE :\t");
        fgets(switchLine, 10, stdin);
        int len = strlen(switchLine);
        if (len > 0 && switchLine[len - 1] == '\n')
            switchLine[len - 1] = '\0';

        while ((atoi(switchLine) > 'a' && atoi(switchLine) < 'z')) { // to avoid wrong inputs

            printf("\n!!!!!wrong number re enter !!!!\n");
            break;

        }

        num = atoi(switchLine);


        printf("\n------------------------------------------------------------------------------------------------\n");
        switch (num) {


            case 1:

                if (loadBusLimit == 0) { // this condition to avoid repetition
                    a = 0;

                    char *price[200];
                    char *capacity[200];
                    while (!feof(BusFile)) {
                        fgets(line, 255, BusFile);
                        strcpy(array[a], line);
                        a++;
                    }
                    c = 1;
                    for (int i = 0; i < a; ++i) {
                        tok = strtok(array[i], "#");
                        while (tok != NULL) {

                            switch (c) {

                                case 1:
                                    //     passID = tok;
                                    strcpy(passID, tok);
                                    break;
                                case 2:
                                    strcpy(travellingDate, tok);
                                    break;
                                case 3:
                                    strcpy(travellingTime, tok);

                                case 4:
                                    strcpy(from, tok);
                                    break;
                                case 5:
                                    strcpy(to, tok);
                                    break;
                                case 6:
                                    strcpy(price, tok);
                                    break;
                                case 7:
                                    strcpy(capacity, tok);
                                    break;
                                default:
                                    printf("wrong input for Bus data");
                                    break;
                            }
                            c++;

                            tok = strtok(NULL, "#");
                        }
                        int len = strlen(capacity);
                        if (len > 0 && capacity[len - 1] == '\n')
                            capacity[len - 1] = '\0';
                        appendBus(busHead, passID, travellingDate, travellingTime, from, to, price, capacity);
                        int id = atoi(passID);
                        findBus(busHead, id)->pass = (passenger *) malloc(sizeof(passenger));
                        findBus(busHead, id)->pass->link = NULL;

                        c = 1;
                    }
                    printf("\nBusses Information LOADED \n");
                    loadBusLimit++;
                    break;
                } else printf("\nBusses Already Loaded :)\n");

                break;
            case 2:

                if (loadPassLimit == 0) { // this condition to avoid repetition
                    a = 0;
                    while (!feof(passFile)) {
                        fgets(line, 255, passFile);
                        strcpy(array[a], line);
                        a++;
                    }
                    c = 1;
                    for (int i = 0; i < a; ++i) {
                        tok = strtok(array[i], "#");
                        while (tok != NULL) {
                            switch (c) {

                                case 1:

                                    strcpy(passID, tok);
                                    break;
                                case 2:
                                    strcpy(travellingDate, tok);
                                    break;
                                case 3:
                                    strcpy(travellingTime, tok);

                                case 4:
                                    strcpy(from, tok);
                                    break;
                                case 5:
                                    strcpy(to, tok);
                                    break;
                                default:
                                    printf("wrong input for passenger data");
                                    break;


                            }
                            c++;

                            tok = strtok(NULL, "#");
                        }
                        int len = strlen(to);
                        if (len > 0 && to[len - 1] == '\n')
                            to[len - 1] = '\0';

                        appendPassenger(passengersHead, passID, travellingDate, travellingTime, from, to);
                        c = 1;
                    }
                    printf("\nPassengers Information LOADED\n");
                    loadPassLimit++;
                    break;

                } else
                    printf("\nPassengers Information Already Loaded\n");

                break;
            case 3:
                if (busHead->link == NULL || passengersHead->link == NULL) {
                    printf("there is no data in neither passenger linked list nor busses list");
                    break;
                } else {
                    assignPassengers(busHead, passengersHead, ONB_Passengers, UN_Passengers);
                    printf("\npassengers and busses are assigned\n");

                }

                break;
            case 4:

                printBus(busHead);
                printf("\nEnter Bus Number :  ");
                int busNum;

                busNum = scanInt();

                if ((findBus(busHead, busNum) != NULL)) {
                    Bus *ptr = (findBus(busHead, busNum));
                    printf("\n\t Bus id === %d , Date :  %d ,Time : %s, from : %s , to : %s , price : %d , capacity : %d",
                           ptr->busNumber, ptr->date, ptr->departureTime, ptr->from, ptr->to, ptr->price,
                           ptr->capacity);

                    printf("\n******************************** Its Passengers ***********************************************\n");


                    printPassenger(ptr->pass);

                    printf("\n*************************************************************************************************");

                    break;
                } else
                    printf("Bus Not Found");

                break;
            case 5:
                printf(" \n Unmatched passengers are  :  \n");
                if (UN_Passengers->link == NULL) {
                    printf("Please assign program first ");
                    break;
                }

                printPassenger(UN_Passengers);

                break;
            case 6:
                printf("\n please enter passenger id <id>:\t ");

                int id, temp;
                id = scanInt();


                if (findPassenger(passengersHead, id) != NULL) {
                    passenger *ptr = findPassenger(passengersHead, id);
                    printf("\n\tpassenger is  already exist in the linked list whereas its information : "); // when user enters charecters or string also print this
                    printf("\n\t  id === %d , Date : %d ,Time : %s, from : %s , to : %s",
                           ptr->travelerId,
                           ptr->travellingDate, ptr->travellingTime, ptr->from, ptr->to);
                    break;

                } else {

                    if (busHead->link == NULL) {
                        printf("\n\t!!!!!!!!!please add a bus to program!!!!!!!!!!!\n");
                        break;
                    }
                    printBus(busHead);
                    printf("\n In which Bus ? \t");
                    temp = scanInt();

                    if (findBus(busHead, temp) == NULL) {
                        printf("\n\tNO Bus Found !! :( \n");
                        break;
                    }
                    if (findBus(busHead, temp)->capacity <= 0) {
                        printf("\n\tThere is no enough seats on bus  !! :( \n");
                        break;
                    } else {
                        Bus *ptr = findBus(busHead, temp);
                        appendPassengerToBus(passengersHead, id, ptr->date, ptr->departureTime, ptr->from, ptr->to);
                        assignPassengers(busHead, passengersHead, ONB_Passengers, UN_Passengers);
                        printf("passenger added successfully");
                    }
                }


                break;
            case 7:

                printf(" ENTER passenger id to remove :\n");


                idDel = scanInt();

                if (findPassenger(passengersHead, idDel) == NULL) {
                    printf("No Passenger Found thank you :)");
                    break;
                } else if (findPassenger(UN_Passengers, idDel) != NULL) {
                    printf("the Passenger Is not on any Bus do you want to peremantly delete it ? <y/n> \n");
                    if (scanChar() == 'y') {

                        deletePasseneger(UN_Passengers, idDel);
                        deletePasseneger(passengersHead, idDel);
                        printf("\npassenger with id == %d , was deleted from  list \n", idDel);

                        break;
                    } else {
                        printf(" passenger No :%d  , NOT deleted  Thank you :)", idDel);
                        break;
                    }
                } else if (findPassenger(ONB_Passengers, idDel) != NULL) {
                    passenger *passenger1 = findPassenger(ONB_Passengers, idDel);
                    printf("the Passenger Is  on a Bus if you want to peremantly delete it  ---> Enter the bus Number to remove it ?  \t");
                    busNum = scanInt();
                    if ((findPassenger(findBus(busHead, busNum)->pass, idDel)) != NULL) {
                        findBus(busHead, busNum)->capacity++;
                        appendPassengerToBus(passengersHead, passenger1->travelerId, passenger1->travellingDate,
                                             passenger1->travellingTime, passenger1->from, passenger1->to);
                        deletePasseneger(findBus(busHead, busNum)->pass, idDel);
                        deletePasseneger(ONB_Passengers, idDel);

                        printf("\npassenger with id == %d , was deleted from Bus No <#%d>  \n", idDel,
                               findBus(busHead, busNum)->busNumber);
                        break;


                    } else {
                        printf("The Passenger is Not on Bus No <#%d>", busNum);
                        break;
                    }

                } else { // fixes that when we delete a passenger when we didn't assign the program
                    printf("the Passenger Is not on any Bus do you want to peremantly delete it ? <y/n> \n");
                    if (scanChar() == 'y') {
                        deletePasseneger(passengersHead, idDel);
                        printf("\npassenger with id == %d , was deleted from  list \n", idDel);

                        break;
                    } else {
                        printf(" passenger No :%d  , NOT deleted  Thank you :)", idDel);
                        break;
                    }
                }


            case 8:
                printf(" ENTER Bus Number to remove :\n");
                busNum = scanInt();
                Bus *bus = findBus(busHead, busNum);
                if (bus == NULL) {
                    printf("Bus Not Found & Not Deleted thank you :)");
                    break;
                } else {
                    if (bus->pass->link == NULL) {
                        deleteBus(busHead, busNum);
                        printf("The Bus No <#%d> Has Been Deleted :)", busNum);
                        break;

                    } else {
                        passenger *temp = bus->pass->link;
                        while (temp != NULL) {
                            appendPassenger(UN_Passengers, temp->travelerId,temp->travellingDate,temp->travellingTime,temp->from,temp->to);
                            deletePasseneger(bus->pass, temp->travelerId); // this is useless I think
                            deletePasseneger(ONB_Passengers, temp->travelerId);


                            temp = temp->link;
                        }
                        deleteBus(busHead, bus->busNumber);
                        assignPassengers(busHead, passengersHead, ONB_Passengers, UN_Passengers);
                        printf(" The Bus Deleted Successfully");
                        break;
                    }
                }


                break;
            case 9:
                printf("exiiiiittt");
                exit(0);
            default:
                printf("\n Wrong Number Re Enter \n ");

                break;


        }


    }


    return 0; // not important while we are using switch and exit(0);
}
//