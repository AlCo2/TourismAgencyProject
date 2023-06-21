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

void showOrders(char* cartCNI);

Date setDays();

void showOrderInfo(Order order);

int main()
{
    int appRunning = 1;
    int appChoice;

    while(appRunning){
        system("cls");
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
                getch();
                break;
        }
    }
    return 0;
}

void login(){
    system("cls");
    char cartCNI[30];
    printf("Cart CNI: ");
    scanf("%s", cartCNI);
    if(!checkUserExists(cartCNI)){
        printf("error, user is not regesterd\n");
        getch();
        return;
    }
    welcomeApp(cartCNI);
}

void Register(){
    system("cls");
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
            getch();
            return;
        }
        fprintf(usersFile, "%s %s\n", cartCNI, phoneNumber);
        fclose(usersFile);
        system("cls");
        printf("User Regestered Sussecful\n");
        getch();
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
    system("cls");
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
    up:
    system("cls");
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "Morocco");
    Hotel hotelList[1000];
    system("cls");
    printf("1-Kenitra\n");
    printf("2-tanger\n");
    printf("3-marrakech\n");
    printf("4-agadir\n");
    scanf("%d", &cityChoice);
    switch(cityChoice){
        case 1:
            strcpy(city, "kenitra");
            break;
        case 2:
            strcpy(city, "tanger");
            break;
        case 3:
            strcpy(city, "marrakech");
            break;
        case 4:
            strcpy(city, "agadir");
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
        getch();
        return;
    }
    int size;
    system("cls");
    readHotelData(cityFile, hotelList,&size);
    do{
        printf("Hotel Number: ");
        scanf("%d", &hotelChoice);
    }while(hotelChoice<1 || hotelChoice>=size);
    order.hotel = hotelList[hotelChoice-1];
    system("cls");
    printf("Persons: ");
    scanf("%d", &order.persons);
    system("cls");
    order.date = setDays();
    system("cls");

    int confirm;
    do{
        showOrderInfo(order);
        printf("1-Accept\n2-edit\n3-cancle\n");
        scanf("%d", &confirm);
        system("cls");
    }while(confirm<1 || confirm>3);
    switch(confirm){
        case 1:
            break;
        case 2:
            goto up;
            break;
        case 3:
            return;
            break;
    }
    printf("add more Orders\n 1-yes 2-no \n");
    do{
        scanf("%d", &YESNO);
    }while(YESNO<1 || YESNO>2);
    int days = order.date.lastDay-order.date.firstDay;
    switch(YESNO){
        case 2:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            FILE* userFile = fopen(userFileWithExt, "a");
            if(userFile==NULL){
                userFile = fopen(userFileWithExt, "w");
                fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d $\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
                break;
            }
            fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d $\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
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
                fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d$\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
                break;
            }

            fprintf(userFile, "%s %s %s from %d to %d persons:%d price: %d$\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
            welcomeApp(cartCNI);
            break;
            }
        default:
            printf("error in choice");
            getch();
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
            printf(" ");
        printf("____________________________________________________________________________________________________________\n");
            i++;
        }else{
            printf("-------------------------------------------------------------------------------------------------\n");
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
                char price[10];
                strcpy(price, token);
                price[size-1] = '\0';
                hotelList[i-2].price = atoi(price);
            }
            j++;
            printf("|");
            printf("%-14s", token);
            token = strtok(NULL, ",");
        }
    }
    printf("____________________________________________________________________________________________________________\n");
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
    }while(date.firstDay>date.lastDay || date.lastDay==date.firstDay);
    return date;
}

void showOrderInfo(Order order){
    printf("Country: %s\n", order.country);
    printf("City: %s\n", order.city);
    printf("Hotel: %s\n", order.hotel.hotelName);
    printf("Days: %d from %d to %d\n", order.date.lastDay-order.date.firstDay, order.date.firstDay, order.date.lastDay);
    printf("Person: %d\n", order.persons);
    int days = order.date.lastDay-order.date.firstDay;
    printf("price: %d$\n", order.hotel.price*order.persons*days);
}

void showOrders(char* cartCNI){
    char userFileWithExt[200];
    strcpy(userFileWithExt, "userOrders/");
    strcat(userFileWithExt, ".txt");
    FILE* userFile = fopen(userFileWithExt, "r");
}
