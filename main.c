#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>

#define ANIME_TIME 0

COORD coord = {0,0};

void gotoxy(int x, int y);

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

void squire();

void fastSquire();

void checkFoldersOfApp();

void login();

void Register();

int checkUserExists(char* cartCNI);

void welcomeApp(char* cartCNI);

int countryList();

void morocco(char* cartCNI);

void france(char* cartCNI);

void spain(char* cartCNI);

Hotel* readHotelData(char* cityWithExt, int* size);

Date setDays();

void showOrderInfo(Order order);

void userHaveOrder(char* cartCNI);

void showOrders(char* userFileExt);

void showUserOrder(Order order);

void APP();

void writeUserIntoFile(char* userFileWithExt, Order order);

int main()
{
    checkFoldersOfApp();
    APP();
    return 0;
}

void checkFoldersOfApp(){
    const char* foldername = "userOrders";
    DIR* dir = opendir(foldername);
    if (dir) {
        closedir(dir);
    } else {
        system("mkdir userOrders");
    }
}

void login(){
    system("cls");
    char cartCNI[30];
    fastSquire();
    gotoxy(25, 4);
    printf("---Login---");
    gotoxy(30,5);
    printf("Cart CNI: ");
    scanf("%s", cartCNI);
    if(!checkUserExists(cartCNI)){
        gotoxy(31,6);
        printf("error, user is not regesterd\n");
        gotoxy(34, 7);
        printf("please Register");
        getch();
        return;
    }
    userHaveOrder(cartCNI);
}

void Register(){
    system("cls");
    char cartCNI[30];
    char phoneNumber[30];
    fastSquire();
    gotoxy(25, 4);
    printf("---Register---");
    gotoxy(30,5);
    printf("Cart CNI: ");
    scanf("%s", cartCNI);
    gotoxy(30,6);
    printf("Phone Number: ");
    scanf("%s", phoneNumber);
    FILE* usersFile = fopen("users.txt", "a");
    if(usersFile==NULL){
        usersFile = fopen("users.txt", "w");
        gotoxy(30,7);
        fprintf(usersFile, "%s %s\n", cartCNI, phoneNumber);
    }else{
        char *data;
        char line[200];
        if(checkUserExists(cartCNI)){
            gotoxy(35,10);
            printf("error, this User Already Regestered\n");
            getch();
            return;
        }
        fprintf(usersFile, "%s %s\n", cartCNI, phoneNumber);
        fclose(usersFile);
        system("cls");
        fastSquire();
        gotoxy(35,10);
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
            spain(cartCNI);
            break;
            //France:
        case 3:
            france(cartCNI);
            break;
    }

}

int countryList(){
    int choice;
    do{
    fastSquire();
    gotoxy(30,5);
    printf("1-Morroco");
    gotoxy(30,6);
    printf("2-Spain");
    gotoxy(30,7);
    printf("3-France");
    gotoxy(30,8);
    scanf("%d", &choice);
    }while(choice<1 || choice > 3);
    return choice;
}


void morocco(char* cartCNI){
    UP:
    system("cls");
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "Morocco");
    system("cls");
    fastSquire();
    gotoxy(30,5);
    printf("1-Kenitra\n");
    gotoxy(30,6);
    printf("2-tanger\n");
    gotoxy(30,7);
    printf("3-marrakech\n");
    gotoxy(30,8);
    printf("4-agadir\n");
    gotoxy(45,5);
    printf("5-rabat\n");
    gotoxy(45,6);
    printf("6-cassablanca\n");
    gotoxy(45,10);
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
        case 5:
            strcpy(city, "rabat");
            break;
        case 6:
            strcpy(city, "cassablanca");
            break;
    }
    strcpy(order.city, city);
    char cityWithExt[200];
    strcpy(cityWithExt, "morocco/");
    strcat(cityWithExt, city);
    strcat(cityWithExt, ".csv");
    int size;
    system("cls");
    Hotel* hotelList = readHotelData(cityWithExt,&size);
    if(hotelList==NULL){
        return;
    }
    do{
        printf("Hotel Number: ");
        scanf("%d", &hotelChoice);
    }while(hotelChoice<1 || hotelChoice>=size);
    order.hotel = hotelList[hotelChoice-1];
    system("cls");
    fastSquire();
    gotoxy(30,5);
    printf("Persons: ");
    scanf("%d", &order.persons);
    system("cls");
    order.date = setDays();
    system("cls");
    int confirm;
    do{
        showOrderInfo(order);
        gotoxy(42,13);
        printf("1-Accept");
        gotoxy(42,14);
        printf("2-edit");
        gotoxy(42,15);
        printf("3-cancle");
        gotoxy(42,16);
        scanf("%d", &confirm);
        system("cls");
    }while(confirm<1 || confirm>3);
    switch(confirm){
        case 1:
            break;
        case 2:
            goto UP;
            break;
        case 3:
            return;
            break;
    }
    fastSquire();
    gotoxy(30,5);
    printf("add more Orders");
    gotoxy(33,6);
    printf("1-yes");
    gotoxy(33,7);
    printf("2-no");
    gotoxy(33, 8);
    do{
        scanf("%d", &YESNO);
    }while(YESNO<1 || YESNO>2);
    switch(YESNO){
        case 2:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            writeUserIntoFile(userFileWithExt, order);
            break;
            }
        case 1:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            writeUserIntoFile(userFileWithExt, order);
            break;
            }
        default:
            printf("error in choice");
            getch();
            break;
    }
}

void france(char* cartCNI){
    UP:
    system("cls");
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "France");
    system("cls");

    scanf("%d", &cityChoice);
    switch(cityChoice){

    }
    strcpy(order.city, city);
    char cityWithExt[200];
    strcpy(cityWithExt, "france/");
    strcat(cityWithExt, city);
    strcat(cityWithExt, ".csv");
    int size;
    system("cls");
    Hotel* hotelList = readHotelData(cityWithExt,&size);
    if(hotelList==NULL){
        return;
    }
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
            goto UP;
            break;
        case 3:
            return;
            break;
    }
    printf("add more Orders\n 1-yes 2-no \n");
    do{
        scanf("%d", &YESNO);
    }while(YESNO<1 || YESNO>2);
    switch(YESNO){
        case 2:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            writeUserIntoFile(userFileWithExt, order);
            break;
            }
        case 1:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            writeUserIntoFile(userFileWithExt, order);
            break;
            }
        default:
            printf("error in choice");
            getch();
            break;
    }
}

void spain(char* cartCNI){
    UP:
    system("cls");
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "Spain");
    system("cls");
    scanf("%d", &cityChoice);
    switch(cityChoice){
        //spain city
    }
    strcpy(order.city, city);
    char cityWithExt[200];
    strcpy(cityWithExt, "spain/");
    strcat(cityWithExt, city);
    strcat(cityWithExt, ".csv");
    int size;
    system("cls");
    Hotel* hotelList = readHotelData(cityWithExt,&size);
    if(hotelList==NULL){
        return;
    }
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
            goto UP;
            break;
        case 3:
            return;
            break;
    }
    printf("add more Orders\n 1-yes 2-no \n");
    do{
        scanf("%d", &YESNO);
    }while(YESNO<1 || YESNO>2);
    switch(YESNO){
        case 2:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            writeUserIntoFile(userFileWithExt, order);
            break;
            }
        case 1:{
            char userFileWithExt[200];
            strcpy(userFileWithExt, "userOrders/");
            strcat(userFileWithExt, order.cartCNI);
            strcat(userFileWithExt, ".txt");
            writeUserIntoFile(userFileWithExt, order);
            break;
            }
        default:
            printf("error in choice");
            getch();
            break;
    }
}

Hotel* readHotelData(char* cityWithExt, int* size){
   FILE* data = fopen(cityWithExt, "r");
    if(data == NULL){
        printf("city Is not Available Right Now\n");
        getch();
        return NULL;
    }
    Hotel hotelList[1000];
    Hotel* ptr = hotelList;
    int i = 0;
    int j = 0;
    char *token;
    char line[200];
    while(fgets(line, sizeof(line), data)){
        token = strtok(line, ",");
        if(i==0){
            printf("+----------------------------------------------------------------------------------------------------------+\n|  ");
            while(token!=NULL){
                printf("%-20s|", token);
                token = strtok(NULL, ",");
            }
            i++;
            gotoxy(0,2);
            printf("+----------------------------------------------------------------------------------------------------------+\n");
        }else{
            j = 0;
            printf("|%d-", i);
            while(token!=NULL){
                switch(j){
                    case 0:
                        strcpy(hotelList[i-1].hotelName, token);
                        printf("%-20s|",token);
                        break;
                    case 1:
                        printf("%-20s|", token);
                        break;
                    case 2:
                        {
                        printf("%-20s\n", token);
                        int SIZE = strlen(token);
                        char price[10];
                        strcpy(price, token);
                        price[SIZE-1] = '\0';
                        hotelList[i-1].price = atoi(price);
                        break;
                        }
                    case 3:
                        printf("| %s", token);
                        printf("+----------------------------------------------------------------------------------------------------------+\n");
                        break;
                }
                j++;
                token = strtok(NULL, ",");
            }
            i++;
        }
    }
    fclose(data);
    *size = i;
    return ptr;
}

Date setDays(){
    Date date;
    int x = 30;
    int y = 5;
    fastSquire();
    for(int i=0;i<30;i++){
        gotoxy(x, y);
        if(i==10 || i==20){
            x = 27;
            y++;
        }
        printf("%-3d", i+1);
        x+=4;
    }
    gotoxy(40,10);
    printf("firstDay: ");
    scanf("%d", &date.firstDay);
    do{
        gotoxy(40,11);
        printf("lastDay: ");
        scanf("%d", &date.lastDay);
    }while(date.firstDay>date.lastDay || date.lastDay==date.firstDay);
    return date;
}

void showOrderInfo(Order order){
    fastSquire();
    gotoxy(40,5);
    printf("Country: %s\n", order.country);
    gotoxy(40,6);
    printf("City: %s\n", order.city);
    gotoxy(40,7);
    printf("Hotel: %s\n", order.hotel.hotelName);
    gotoxy(40,8);
    printf("Days: %d from %d to %d\n", order.date.lastDay-order.date.firstDay, order.date.firstDay, order.date.lastDay);
    gotoxy(40,9);
    printf("Person: %d\n", order.persons);
    int days = order.date.lastDay-order.date.firstDay;
    gotoxy(40,10);
    printf("price: %d$\n", order.hotel.price*order.persons*days);
}

void showUserOrder(Order order){
    printf("+------------------------+\n");
    printf("| Country: %-14s|\n", order.country);
    printf("| City: %-17s|\n", order.city);
    printf("| Hotel: %-16s|\n", order.hotel.hotelName);
    printf("| Days: %d from %d to %-5d|\n", order.date.lastDay-order.date.firstDay, order.date.firstDay, order.date.lastDay);
    printf("| Person: %-15d|\n", order.persons);
    int days = order.date.lastDay-order.date.firstDay;
    printf("| price: %d$            |\n", order.hotel.price);
    printf("+------------------------+\n");
}

void userHaveOrder(char* cartCNI){
    system("cls");
    char userFileWithExt[200];
    strcpy(userFileWithExt, "userOrders/");
    strcat(userFileWithExt, cartCNI);
    strcat(userFileWithExt, ".txt");
    FILE* userFile = fopen(userFileWithExt, "r");
    if(userFile==NULL){
        welcomeApp(cartCNI);
    }else{
        int n;
        do{
            system("cls");
            fastSquire();
            gotoxy(30,5);
            printf("1-add Order");
            gotoxy(30,6);
            printf("2-show Orders");
            gotoxy(30,7);
            printf("3-Logout");
            gotoxy(30,8);
            scanf("%d", &n);
            if(n==1){
                welcomeApp(cartCNI);
            }else if(n==2){
                system("cls");
                fclose(userFile);
                showOrders(userFileWithExt);
                getch();
            }
        }while(n!=3);
    }
}

void showOrders(char* userFileExt){
    FILE* userFile = fopen(userFileExt, "r");
    char *token;
    char line[200];
    Order order;
    int i;
    while(fgets(line, sizeof(line), userFile)){
        i = 0;
        token = strtok(line, ",");
        while(token!=NULL){
            switch(i){
                case 0:
                    strcpy(order.country, token);
                    break;
                case 1:
                    strcpy(order.city, token);
                    break;
                case 2:
                    strcpy(order.hotel.hotelName, token);
                    break;
                case 3:
                    order.date.firstDay = atoi(token);
                    break;
                case 4:
                    order.date.lastDay = atoi(token);
                    break;
                case 5:
                    order.persons = atoi(token);
                    break;
                case 6:
                    order.hotel.price = atoi(token);
                    break;
            }
            i++;
            token = strtok(NULL, ",");
        }
        showUserOrder(order);
    }
    fclose(userFile);
}

void APP(){
    int appRunning = 1;
    int appChoice;
    while(appRunning){
        system("cls");
        squire();
        gotoxy(30, 10);
        printf("1-Login");
        gotoxy(30, 11);
        printf("2-Register");
        gotoxy(30, 12);
        printf("3-Stop App");
        gotoxy(30,13);
        scanf("%d", &appChoice);
        switch(appChoice){
            case 1:
                login();
                break;
            case 2:
                Register();
                break;
            case 3:
                gotoxy(0,25);
                appRunning = 0;
                break;
            default:
                printf("Error in choice\n");
                getch();
                break;
        }
    }
};

void writeUserIntoFile(char* userFileWithExt, Order order){
    int days = order.date.lastDay-order.date.firstDay;
    int total = order.hotel.price*order.persons*days;
    FILE* userFile = fopen(userFileWithExt, "a");
    fprintf(userFile, "%s,%s,%s,%d,%d,%d,%d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, total);
    fclose(userFile);
}

void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void squire(){
    system("color 3");
    gotoxy(20, 0);
    for(int i=0;i<60;i++){
        printf("_");
        Sleep(ANIME_TIME);
    }
    printf("\n");
    for(int i=1;i<25;i++){
        gotoxy(19,i);
        printf("|");
        Sleep(ANIME_TIME);
    }
    for(int i=0;i<60;i++){
        printf("_");
        Sleep(ANIME_TIME);
    }
    printf("\n");
    for(int i=24;i>0;i--){
        gotoxy(80,i);
        printf("|");
        Sleep(ANIME_TIME);
    }
    gotoxy(43,2);
    printf("Tourisme Agency");
}

void fastSquire(){
    system("color 3");
    gotoxy(20, 0);
    for(int i=0;i<60;i++){
        printf("_");
    }
    printf("\n");
    for(int i=1;i<25;i++){
        gotoxy(19,i);
        printf("|");
    }
    for(int i=0;i<60;i++){
        printf("_");
    }
    printf("\n");
    for(int i=24;i>0;i--){
        gotoxy(80,i);
        printf("|");
    }
    gotoxy(43,2);
    printf("Tourisme Agency");
}
