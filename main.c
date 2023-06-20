#include <stdio.h>
#include <stdlib.h>



typedef struct Date{
    int firstDay;
    int lastDay;
}Date;
typedef struct Hotel{
    int id;
    char hotelName[100];
    int price;
}Hotel;


typedef struct Order{
    char cartCNI[30];
    char country[50];
    char city[100];
    Hotel hotel;
    int persons;
    Date date;
}Order;

void login();

void Register();

int checkUserExists(char* cartCNI);

void welcomeApp(char* cartCNI);

int countryList();

void morocco(char* cartCNI);

void readHotelData(FILE* data, Hotel* hotelList, int* size);

Date setDays();

int main()
{
    int appRunning = 1;
    int appChoice;

    while(appRunning){
        printf("1-Login\n");
        printf("2-Register\n");
        printf("3-Stop App\n");
        scanf("%d", &appChoice);
        switch(appChoice){
            case 1:
                login();
                break;
            case 2:
                Register();
                break;
            case 3:
                appRunning = 0;
                break;
            default:
                printf("Error in choice\n");
        }
    }
    return 0;
}

void login(){
    char cartCNI[30];
    printf("Cart CNI: ");
    scanf("%s", cartCNI);
    if(!checkUserExists(cartCNI)){
        printf("error, user is not regesterd\n");
        return;
    }
    welcomeApp(cartCNI);
}

void Register(){
    char cartCNI[30];
    char phoneNumber[30];
    printf("Cart CNI: ");
    scanf("%s", cartCNI);
    printf("Phone Number: ");
    scanf("%s", phoneNumber);
    FILE* usersFile = fopen("users.txt", "a");
    if(usersFile==NULL){
        usersFile = fopen("users.txt", "w");
        fprintf(usersFile, "%s %s\n", cartCNI, phoneNumber);
    }else{
        char *data;
        char line[200];
        if(checkUserExists(cartCNI)){
            printf("error, this User Already Regestered\n");
            return;
        }
        fprintf(usersFile, "%s %s\n", cartCNI, phoneNumber);
        fclose(usersFile);
    }
}

int checkUserExists(char* cartCNI){
    FILE* file = fopen("users.txt", "r");
    if(file==NULL){
        return;
    }
    char *data;
    char line[200];
    while(fgets(line, sizeof(line), file)){
        data = strtok(line, " ");
        while(data!=NULL){
            if(strcmp(data, cartCNI)==0){
                fclose(file);
                return 1;
            }
            data = strtok(NULL, " ");
            break;
        }
    }
    fclose(file);
    return 0;
}

void welcomeApp(char* cartCNI){
    int countryChoice;
    countryChoice = countryList();
    switch(countryChoice){
        //morocco:
        case 1:
            morocco(cartCNI);
            break;
            //Spain:
        case 2:
            printf("Spain");
            break;
            //France:
        case 3:
            printf("France");
            break;
    }

}

int countryList(){
    int choice;
    do{
    printf("1-Morroco\n");
    printf("2-Spain\n");
    printf("3-France\n");
    scanf("%d", &choice);
    }while(choice<1 || choice > 3);
    return choice;
}


void morocco(char* cartCNI){
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "Morocco");
    Hotel hotelList[1000];
    printf("1-Kenitra\n");
    scanf("%d", &cityChoice);
    switch(cityChoice){
        case 1:
            strcpy(city, "kenitra");
            break;
    }
    strcpy(order.city, city);
    char cityWithExt[200];
    strcpy(cityWithExt, "morocco/");
    strcat(cityWithExt, city);
    strcat(cityWithExt, ".csv");
    FILE* cityFile = fopen(cityWithExt, "r");
    if(cityFile == NULL){
        printf("city Is not Available Right Now\n");
        return;
    }
    int size;
    readHotelData(cityFile, hotelList,&size);
    do{
        scanf("%d", &hotelChoice);
    }while(hotelChoice<1 || hotelChoice>=size);
    order.hotel = hotelList[hotelChoice-1];
    printf("Persons: ");
    scanf("%d", &order.persons);
    order.date = setDays();
    printf("add more Orders\n 1-yes 2-no \n");
    scanf("%d", &YESNO);
    switch(YESNO){
        case 2:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            FILE* userFile = fopen(userFileWithExt, "a");
            if(userFile==NULL){
                userFile = fopen(userFileWithExt, "w");
                fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d $\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons);
                break;
            }
            fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d $\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons);
            break;
            }
        case 1:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            FILE* userFile = fopen(userFileWithExt, "a");
            if(userFile==NULL){
                userFile = fopen(userFileWithExt, "w");
                fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d $\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons);
                break;
            }
            fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d $\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons);
            welcomeApp(cartCNI);
            break;
            }
        default:
            printf("error in choice");
            break;
    }
}

void readHotelData(FILE* data,Hotel* hotelList, int* size){
    int i = 0;
    int j=0;
    char *token;
    char line[200];
    while(fgets(line, sizeof(line), data)){
        token = strtok(line, ",");

        if(i==0){
            i++;
        }else{
            printf("_______________________\n");
            hotelList[i-1].id = i;
            printf("%d", i);

        }
        j = 0;
        while(token!=NULL){
            if(hotelList[i-1].id == i){
                strcpy(hotelList[i-1].hotelName, token);
                i++;
            }
            if(j==2){
                int size = strlen(token);
                token[size-1] = '\0';
                hotelList[i-2].price = atoi(token);
            }
            j++;
            printf("|");
            printf("%-14s ", token);
            printf("|");
            token = strtok(NULL, ",");
        }
        printf("_______________________\n");
    }
    *size = i;
}

Date setDays(){
    Date date;
    for(int i=0;i<30;i++){
        if(i==10 || i==20)
            printf("\n");
        printf("%-4d", i+1);
    }
    printf("\n");
    printf("firstDay: ");
    scanf("%d", &date.firstDay);
    do{
        printf("lastDay: ");
        scanf("%d", &date.lastDay);
    }while(date.firstDay>date.lastDay);
    return date;
}
