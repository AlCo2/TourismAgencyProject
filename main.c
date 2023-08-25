#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define ANIME_TIME 0

COORD coord = {0,0};

void gotoxy(int x, int y);

typedef struct Date{
    int firstDay;
    int firstMonth;
    int lastDay;
    int lastMonth;
    int year;
    int days;
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

typedef struct User{
    char cartCNI[30];
    char firstName[50];
    char lastName[50];
    char phoneNumber[20];
}User;
User user;

int mainMenu();

void squire();

void fastSquire();

void checkFoldersOfApp();

void login();

void Register();

int checkUserExists(char* cartCNI);

void welcomeApp(char* cartCNI);

int countryList();

void newTourismeOrder(char* cartCNI, char* country);

Hotel* readHotelData(char* cityWithExt, int* size);

Date setDays();

void showOrderInfo(Order order);

void userHaveOrder(char* cartCNI);

int showOrders(char* userFileExt);

void showUserOrder(Order order, int id);

void APP();

void writeUserIntoFile(char* userFileWithExt, Order order);

char* moroccoCityChoice();
char* franceCityChoice();
char* italyCityChoice();
char* spainCityChoice();

Order createOrder(char* country, char* cartCNI);

Hotel getHotelChoice(char* cityWithExt);

char* createCityWithExt(char* country, char* city);

char* createUserFileWithExt(char* cartCNI);

int getHowManyPerson();

void manageOrders(char* userFileWithExt);

void editUserOrder(char* userFileWithExt);

void deleteUserOrder(char* userFileWithExt);

Order findTheOrder(int id, char* userFileWithExt);

Order editOrder(Order order, int id);

void renewOrder(int id, Order order,char* userFileExt);

void deleteOrder(int id, char* userFileExt);

void showOrderInfoToDelete(Order order);

void arrowHere(int realPosition, int arrowPosition);

Date setUserDate();

int manageUser();

int manageUserMenu();

void changeUserInfo(int choice, int userLine);

int getUserIdLine();

int deleteUserAccount();
int confirmDeleteAccountMenu();
void deleteAccount(int userLine);
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
    gotoxy(25, 7);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
    printf("+-----Login--------------------+");
    gotoxy(25,8);
    printf("|                              |");
    gotoxy(25,10);
    printf("|                              |");
    gotoxy(25,11);
    printf("+------------------------------+");
    gotoxy(25,9);
    SetConsoleTextAttribute(hConsole, 2);
    printf("|");
    SetConsoleTextAttribute(hConsole, 3);
    printf("  Cart CNI:                   ");
    SetConsoleTextAttribute(hConsole, 2);
    printf("|");
    SetConsoleTextAttribute(hConsole, 7);
    gotoxy(38, 9);
    scanf("%s", cartCNI);
    if(!checkUserExists(cartCNI)){
        gotoxy(27,10);
        SetConsoleTextAttribute(hConsole, 4);
        printf("error, user is not regesterd\n");
        getch();
        return;
    }
    userHaveOrder(cartCNI);
}

void Register(){
    system("cls");
    char cartCNI[30];
    char phoneNumber[30];
    char firstName[50];
    char lastName[50];

    fastSquire();
    gotoxy(25, 5);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
    printf("+------Register-------------------+");
    gotoxy(25,6);
    printf("|                                 |");
    gotoxy(25,7);
    printf("|   ");
    SetConsoleTextAttribute(hConsole, 3);
    printf("Cart CNI: ");
    SetConsoleTextAttribute(hConsole, 2);
    printf("                    |");
    gotoxy(25,8);
    printf("|   ");
    SetConsoleTextAttribute(hConsole, 3);
    printf("FirstName: ");
    SetConsoleTextAttribute(hConsole, 2);
    printf("                   |");
    gotoxy(25,9);
    printf("|   ");
    SetConsoleTextAttribute(hConsole, 3);
    printf("LastName: ");
    SetConsoleTextAttribute(hConsole, 2);
    printf("                    |");
    gotoxy(25,10);
    printf("|   ");
    SetConsoleTextAttribute(hConsole, 3);
    printf("PhoneNumber: ");
    SetConsoleTextAttribute(hConsole, 2);
    printf("                 |");
    gotoxy(25,11);
    printf("|                                 |");
    gotoxy(25,12);
    printf("+---------------------------------+");
    SetConsoleTextAttribute(hConsole, 7);
    gotoxy(42,7);
    scanf("%s", cartCNI);
    gotoxy(42,8);
    scanf("%s", firstName);
    gotoxy(42,9);
    scanf("%s", lastName);
    gotoxy(42,10);
    scanf("%s", phoneNumber);
    FILE* usersFile = fopen("users.txt", "a");
    char *data;
    char line[200];
    if(checkUserExists(cartCNI)){
        gotoxy(35,14);
        SetConsoleTextAttribute(hConsole, 4);
        printf("error, this User Already Regestered\n");
        getch();
        fclose(usersFile);
        return;
    }
    //check cartNational
    if(isdigit(cartCNI[0])){
        gotoxy(35,14);
        SetConsoleTextAttribute(hConsole, 4);
        printf("error, this cartCNI is not valid");
        gotoxy(35,15);
        printf("(cartCNI doesn't start with a number)");
        getch();
        return;
    }
    for(int i=0;firstName[i]!='\0';i++){
        if(isdigit(firstName[i])){
            gotoxy(35,14);
            SetConsoleTextAttribute(hConsole, 4);
            printf("error, there is a number in your firstName");
            getch();
            return;
        }
    }
    for(int i=0;lastName[i]!='\0';i++){
        if(isdigit(lastName[i])){
            gotoxy(35,14);
            SetConsoleTextAttribute(hConsole, 4);
            printf("error, there is a number in your lastName");
            getch();
            return;
        }
    }
    //check user phone Number is Valid:
    for(int i=0;phoneNumber[i]!='\0';i++){
        if (!isdigit(phoneNumber[i])) {
            gotoxy(35,14);
            SetConsoleTextAttribute(hConsole, 4);
            printf("error, phone number can't be a char");
            getch();
            return;
        }
    }
    if(strlen(phoneNumber)!=10){
        gotoxy(35,14);
        SetConsoleTextAttribute(hConsole, 4);
        printf("error, phone number have to be 10 Numbers");
        getch();
        return;
    }
    fprintf(usersFile, "%s %s %s %s\n", cartCNI, firstName, lastName, phoneNumber);
    fclose(usersFile);
    system("cls");
    fastSquire();
    gotoxy(35,14);
    SetConsoleTextAttribute(hConsole, 2);
    printf("User Regestered Sussecful\n");
    getch();
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
                strcpy(user.cartCNI, cartCNI);
                data = strtok(NULL, " ");
                strcpy(user.firstName, data);
                data = strtok(NULL, " ");
                strcpy(user.lastName, data);
                data = strtok(NULL, " ");
                strcpy(user.phoneNumber, data);
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
            newTourismeOrder(cartCNI, "Morocco");
            break;
        case 2:
            newTourismeOrder(cartCNI, "Spain");
            break;
        case 3:
            newTourismeOrder(cartCNI, "France");
            break;
        case 4:
            newTourismeOrder(cartCNI, "Italy");
    }

}

int countryList(){
    int position = 1;
    int key = 0;
    fastSquire();
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(30, 10);
        arrowHere(1, position);printf(" Morroco");
        gotoxy(30, 11);
        arrowHere(2, position);printf(" Spain");
        gotoxy(30, 12);
        arrowHere(3, position);printf(" France");
        gotoxy(30,13);
        arrowHere(4, position);printf(" Italy");
        key = getch();
        if(key == 80 && position!=4){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;

}


void newTourismeOrder(char* cartCNI, char* country){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    UP:
    system("cls");
    Order order;
    int YESNO, confirm;
    order = createOrder(country,cartCNI);
    confirm = confirmOrderMenu(order);
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
    system("cls");
    YESNO = confirmAddOrderMenu();
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
            goto UP;
            break;
            }
        default:
            SetConsoleTextAttribute(hConsole, 4);
            printf("error in choice");
            getch();
            break;
    }
}

Hotel* readHotelData(char* cityWithExt, int* size){
    FILE* data = fopen(cityWithExt, "r");
    system("cls");
    if(data == NULL){
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while(fgets(line, sizeof(line), data)){
        token = strtok(line, ",");
        if(i==0){
            SetConsoleTextAttribute(hConsole, 3);
            printf("+----------------------+--------------------+--------------------+-----------------------------------------+\n|  ");
            while(token!=NULL){
                int end = 0;
                if(token[strlen(token)-1]=='\n'){
                    token[strlen(token)-1] = '\0';
                    end = 1;
                }
                if(!end){
                    SetConsoleTextAttribute(hConsole, 2);
                    printf("%-20s", token);
                    SetConsoleTextAttribute(hConsole, 3);
                    printf("|");
                }else{
                    SetConsoleTextAttribute(hConsole, 2);
                    printf("%-41s", token);
                    SetConsoleTextAttribute(hConsole, 3);
                    printf("|");
                }
                token = strtok(NULL, ",");
            }
            i++;
            gotoxy(0,2);
            printf("+----------------------+--------------------+--------------------+-----------------------------------------+\n");
        }else{
            j = 0;
            SetConsoleTextAttribute(hConsole, 3);
            printf("|");
            SetConsoleTextAttribute(hConsole, 7);
            printf("%d-", i);
            while(token!=NULL){
                switch(j){
                    case 0:
                        strcpy(hotelList[i-1].hotelName, token);
                        SetConsoleTextAttribute(hConsole, 7);
                        printf("%-20s",token);
                        SetConsoleTextAttribute(hConsole, 3);
                        printf("|");
                        break;
                    case 1:
                        SetConsoleTextAttribute(hConsole, 7);
                        printf("%-20s",token);
                        SetConsoleTextAttribute(hConsole, 3);
                        printf("|");
                        break;
                    case 2:
                        {
                        SetConsoleTextAttribute(hConsole, 7);
                        printf("%-62s", token);
                        SetConsoleTextAttribute(hConsole, 3);
                        printf("|\n");
                        int SIZE = strlen(token);
                        char price[10];
                        strcpy(price, token);
                        price[SIZE-1] = '\0';
                        hotelList[i-1].price = atoi(price);
                        break;
                        }
                    case 3:
                        token[strlen(token)-1] = '\0';
                        SetConsoleTextAttribute(hConsole, 3);
                        printf("|");
                        SetConsoleTextAttribute(hConsole, 7);
                        printf(" %-105s", token);
                        SetConsoleTextAttribute(hConsole, 3);
                        printf("|\n");
                        printf("+----------------------+--------------------+--------------------+-----------------------------------------+\n");
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

    do{
        system("cls");
        gotoxy(40,10);
        printf("firstDay: ");
        scanf("%d", &date.firstDay);
    }while(date.firstDay < 1 || date.firstDay > 31);
    do{
        system("cls");
        gotoxy(40,11);
        printf("lastDay: ");
        scanf("%d", &date.lastDay);
    }while( date.firstDay>date.lastDay || date.lastDay==date.firstDay || date.lastDay > 31);
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
    printf("Days: %d from %d/%d to %d/%d\n", order.date.days, order.date.firstDay,order.date.firstMonth, order.date.lastDay, order.date.lastMonth);
    gotoxy(40,9);
    printf("Person: %d\n", order.persons);
    int days = order.date.days;
    gotoxy(40,10);
    printf("price: %d$\n", order.hotel.price*order.persons*days);
}

void showOrderInfoToDelete(Order order){
    fastSquire();
    gotoxy(40,5);
    printf("Country: %s\n", order.country);
    gotoxy(40,6);
    printf("City: %s\n", order.city);
    gotoxy(40,7);
    printf("Hotel: %s\n", order.hotel.hotelName);
    gotoxy(40,8);
    printf("Days: %d from %d/%d to %d/%d\n", order.date.days, order.date.firstMonth,order.date.firstDay, order.date.lastMonth, order.date.lastDay);
    gotoxy(40,9);
    printf("Person: %d\n", order.persons);
    int days = order.date.lastDay-order.date.firstDay;
    gotoxy(40,10);
    printf("price: %d$\n", order.hotel.price);
}

void showUserOrder(Order order, int id){
    printf("+------------------------+\n");
    printf("| id: %-4d               |\n", id);
    printf("| Country: %-14s|\n", order.country);
    printf("| City: %-17s|\n", order.city);
    printf("| Hotel: %-16s|\n", order.hotel.hotelName);
    printf("| Days:%-2d %-2d/%-2d to %-2d/%-2d |\n", order.date.days, order.date.firstMonth,order.date.firstDay, order.date.lastMonth, order.date.lastDay);
    printf("| Person: %-15d|\n", order.persons);
    int days = order.date.lastDay-order.date.firstDay;
    printf("| price: %-6d$         |\n", order.hotel.price);
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
        fclose(userFile);
        welcomeApp(cartCNI);
    }else{
        int n;
        int isDeleted = 0;
        fclose(userFile);
        do{
            n = userMainMenu();
            switch(n){
                case 1:
                    welcomeApp(cartCNI);
                    break;
                case 2:
                    system("cls");
                    int MaxId = showOrders(userFileWithExt);
                    if(MaxId==0){
                        fastSquire();
                        gotoxy(30,5);
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 4);
                        printf("Error, there is no Active Order");
                    }
                    getch();
                    break;
                case 3:
                    manageOrders(userFileWithExt);
                    break;
                case 4:
                    isDeleted = manageUser();
                    break;
            }
        }while(n!=5 && !isDeleted);
    }
}

int showOrders(char* userFileExt){
    FILE* userFile = fopen(userFileExt, "r");
    char *token;
    char line[200];
    Order order;
    int i;
    int id = 0;
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
                    order.date.year = atoi(token);
                    break;
                case 4:
                    order.date.firstMonth = atoi(token);
                    break;
                case 5:
                    order.date.firstDay = atoi(token);
                    break;
                case 6:
                    order.date.lastMonth = atoi(token);
                    break;
                case 7:
                    order.date.lastDay = atoi(token);
                    break;
                case 8:
                    order.date.days = atoi(token);
                    break;
                case 9:
                    order.persons = atoi(token);
                    break;
                case 10:
                    order.hotel.price = atoi(token);
                    break;
            }
            i++;
            token = strtok(NULL, ",");
        }
        id++;
        showUserOrder(order, id);
    }
    fclose(userFile);
    return id;
}

void APP(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int appRunning = 1;
    int appChoice;
    while(appRunning){
        system("cls");
        appChoice = mainMenu();
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
                SetConsoleTextAttribute(hConsole, 4);
                printf("Error in choice\n");
                getch();
                break;
        }
    }
};

void writeUserIntoFile(char* userFileWithExt, Order order){
    int days = order.date.days;
    int total = order.hotel.price*order.persons*days;
    FILE* userFile = fopen(userFileWithExt, "a");
    fprintf(userFile, "%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n", order.country, order.city, order.hotel.hotelName,order.date.year,order.date.firstMonth,order.date.firstDay, order.date.lastMonth,order.date.lastDay,order.date.days,order.persons, total);
    fclose(userFile);
}

void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void squire(){
    system("color 3");
    gotoxy(19, 0);
    printf("+");
    for(int i=0;i<60;i++){
        printf("-");
        Sleep(ANIME_TIME);
    }
    printf("+");
    printf("\n");
    for(int i=1;i<24;i++){
        gotoxy(19,i);
        printf("|");
        Sleep(ANIME_TIME);
    }
    gotoxy(19, 24);
    printf("+");
    for(int i=0;i<60;i++){
        printf("-");
        Sleep(ANIME_TIME);
    }
    printf("+");
    printf("\n");
    for(int i=23;i>0;i--){
        gotoxy(80,i);
        printf("|");
        Sleep(ANIME_TIME);
    }
    gotoxy(43,2);
    printf("Tourisme Agency");
}

void fastSquire(){
 system("color 3");
    gotoxy(19, 0);
    printf("+");
    for(int i=0;i<60;i++){
        printf("-");
    }
    printf("+");
    printf("\n");
    for(int i=1;i<24;i++){
        gotoxy(19,i);
        printf("|");
    }
    gotoxy(19, 24);
    printf("+");
    for(int i=0;i<60;i++){
        printf("-");
    }
    printf("+");
    printf("\n");
    for(int i=23;i>0;i--){
        gotoxy(80,i);
        printf("|");
    }
    gotoxy(41,2);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3);
    printf("+-----------------+");
    gotoxy(41,3);
    printf("| Tourisme Agency |");
    gotoxy(41,4);
    printf("+-----------------+");
    SetConsoleTextAttribute(hConsole, 7);
}

char* moroccoCityChoice(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(30,5);
        arrowHere(1, position);printf(" Kenitra");
        gotoxy(30, 6);
        arrowHere(2, position);printf(" Tanger");
        gotoxy(30, 7);
        arrowHere(3, position);printf(" marrakech");
        gotoxy(30, 8);
        arrowHere(4, position);printf(" agadir");
        gotoxy(30, 9);
        arrowHere(5, position);printf(" rabat");
        gotoxy(30, 10);
        arrowHere(6, position);printf(" cassablanca");
        key = getch();
        if(key == 80 && position!=6){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    switch(position){
        case 1:
            return "Kenitra";
            break;
        case 2:
            return "Tanger";
            break;
        case 3:
            return "marrakech";
            break;
        case 4:
            return "agadir";
            break;
        case 5:
            return "rabat";
            break;
        case 6:
            return "cassablanca";
            break;
    }
}

char* franceCityChoice(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(30,5);
        arrowHere(1, position);printf(" marcial");
        gotoxy(30, 6);
        arrowHere(2, position);printf(" paris");
        gotoxy(30, 7);
        arrowHere(3, position);printf(" tollosse");
        key = getch();
        if(key == 80 && position!=3){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    switch(position){
        case 1:
            return "marcial";
            break;
        case 2:
            return "paris";
            break;
        case 3:
            return "tollosse";
            break;
    }

}

char* spainCityChoice(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(30,5);
        arrowHere(1, position);printf(" madrid");
        gotoxy(30, 6);
        arrowHere(2, position);printf(" barcallona");
        gotoxy(30, 7);
        arrowHere(3, position);printf(" sevilla");
        key = getch();
        if(key == 80 && position!=3){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    switch(position){
        case 1:
            return "madrid";
            break;
        case 2:
            return "barcallona";
            break;
        case 3:
            return "sevilla";
            break;
    }

}

char* italyCityChoice(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(30,5);
        arrowHere(1, position);printf(" mellano");
        gotoxy(30, 6);
        arrowHere(2, position);printf(" nappoli");
        gotoxy(30, 7);
        arrowHere(3, position);printf(" torino");
        key = getch();
        if(key == 80 && position!=3){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    switch(position){
        case 1:
            return "mellano";
            break;
        case 2:
            return "nappoli";
            break;
        case 3:
            return "torino";
            break;
    }

}

Hotel getHotelChoice(char* cityWithExt){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Hotel* hotelList;
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        int size;
        hotelList = readHotelData(cityWithExt,&size);
        if(hotelList==NULL){
            return;
        }
        printf("Hotel Choice: \n");
        SetConsoleTextAttribute(hConsole, 7);
        for(int i=0;i<size-1;i++){
            arrowHere(i+1, position);printf(" %s\n", hotelList[i].hotelName);
        }
        key = getch();
        if(key == 80 && position!=size-1){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return hotelList[position-1];
}

Order createOrder(char* country, char* cartCNI){
    Order order;
    char cityWithExt[200];
    strcpy(order.cartCNI, cartCNI);
    strcpy(order.country, country);
    if(strcmp(country, "Morocco")==0){
        strcpy(order.city,moroccoCityChoice());
    }else if(strcmp(country, "France")==0){
        strcpy(order.city, franceCityChoice());
    }else if(strcmp(country, "Spain")==0){
        strcpy(order.city, spainCityChoice());
    }else if(strcmp(country, "Italy")==0){
        strcpy(order.city, italyCityChoice());
    }
    strcpy(cityWithExt, order.country);
    strcat(cityWithExt, "/");
    strcat(cityWithExt, order.city);
    strcat(cityWithExt, ".csv");
    order.hotel = getHotelChoice(cityWithExt);
    order.persons = getHowManyPerson();
    gotoxy(30,5);
    system("cls");
    order.date = setUserDate();
    return order;
}

int getHowManyPerson(){
    int n;
    do{
        int result;
        do{
            system("cls");
            fastSquire();
            gotoxy(30,5);
            printf("Persons: ");
            result = scanf("%d", &n);
            if(result!=1){
                while (getchar() != '\n');
            }
        }while(result!=1);
    }while(n<1);
    return n;
}

void manageOrders(char* userFileWithExt){
    int choice;
    do{
    choice = manageOrderMenu();
    switch(choice){
        case 1:
            editUserOrder(userFileWithExt);
            break;
        case 2:
            deleteUserOrder(userFileWithExt);
            break;
    }

    }while(choice!=3);
}

void editUserOrder(char* userFileWithExt){
    Order order;
    int id;
    system("cls");
    int MaxId = showOrders(userFileWithExt);
    if(MaxId==0){
        fastSquire();
        gotoxy(30,5);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        printf("Error, there is no Active Order");
        getch();
        return;
    }
    system("cls");
    do{
        int result;
        do{
            system("cls");
            showOrders(userFileWithExt);
            printf("0 to go back\n");
            printf("Order id: ");
            result = scanf("%d", &id);
            if(result!=1){
                while (getchar() != '\n');
            }
        }while(result!=1);
        if(id==0){
            return;
        }
    }while(id<0 || id>MaxId);
    system("cls");
    order = findTheOrder(id-1, userFileWithExt);
    order = editOrder(order, id);
    renewOrder(id-1, order, userFileWithExt);
}
Order findTheOrder(int id, char* userFileWithExt){
    FILE* userFile = fopen(userFileWithExt, "r");
    char *token;
    char line[200];
    Order order;
    int i;
    int order_id = 0;
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
                    order.date.year = atoi(token);
                    break;
                case 4:
                    order.date.firstMonth = atoi(token);
                    break;
                case 5:
                    order.date.firstDay = atoi(token);
                    break;
                case 6:
                    order.date.lastMonth = atoi(token);
                    break;
                case 7:
                    order.date.lastDay = atoi(token);
                    break;
                case 8:
                    order.date.days = atoi(token);
                    break;
                case 9:
                    order.persons = atoi(token);
                    break;
                case 10:
                    order.hotel.price = atoi(token);
                    break;
            }
            i++;
            token = strtok(NULL, ",");
        }
        if(order_id==id){
            break;
        }
        order_id++;
    }
    fclose(userFile);
    return order;
}

Order editOrder(Order order,int id){
    Order temp = order;
    int choice;
    int days, total;
    total = order.hotel.price;
    char cityWithExt[200];
    do{
        system("cls");
        days = order.date.days;
        choice = editOrderMenu(order, id);
        switch(choice){
            case 1:
                system("cls");
                if(strcmp(order.country, "Morocco")==0){
                    strcpy(order.city,moroccoCityChoice());
                }else if(strcmp(order.country, "France")==0){
                    strcpy(order.city, franceCityChoice());
                }else if(strcmp(order.country, "Spain")==0){
                    strcpy(order.city, spainCityChoice());
                }else if(strcmp(order.country, "Italy")==0){
                    strcpy(order.city, italyCityChoice());
                }
                strcpy(cityWithExt, order.country);
                strcat(cityWithExt,"/");
                strcat(cityWithExt, order.city);
                strcat(cityWithExt, ".csv");
                order.hotel = getHotelChoice(cityWithExt);
                order.hotel.price *= days * order.persons;
                break;
            case 2:
                system("cls");
                strcpy(cityWithExt, order.country);
                strcat(cityWithExt,"/");
                strcat(cityWithExt, order.city);
                strcat(cityWithExt, ".csv");
                order.hotel = getHotelChoice(cityWithExt);
                order.hotel.price *= days * order.persons;
                break;
            case 3:
                system("cls");
                order.hotel.price/=order.persons;
                order.persons = getHowManyPerson();
                order.hotel.price*=order.persons;
                break;
            case 4:
                system("cls");
                order.hotel.price/=days;
                order.date = setUserDate();
                days = order.date.days;
                order.hotel.price*=days;
                break;
        }
        if(choice==5){
            return order;
        }else if(choice==6){
            return temp;
        }
    }while(choice!=6);
}

void renewOrder(int id, Order order, char* userFileExt){
    int i = 0;
    char tempFileExt[] = "userOrders/temp.txt";
    FILE* userFile = fopen(userFileExt, "r");
    FILE* tempFile = fopen(tempFileExt, "w");
    char line[200];
    while(fgets(line, sizeof(line), userFile)){
        if(id==i){
            fprintf(tempFile, "%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n", order.country, order.city, order.hotel.hotelName,order.date.year,order.date.firstMonth,order.date.firstDay, order.date.lastMonth,order.date.lastDay,order.date.days,order.persons, order.hotel.price);
        }else{
            fprintf(tempFile,"%s", line);
        }
        i++;
    }
    fclose(userFile);
    fclose(tempFile);
    remove(userFileExt);
    rename(tempFileExt, userFileExt);
}

void deleteOrder(int id, char* userFileExt){
    int i = 0;
    char tempFileExt[] = "userOrders/temp.txt";
    FILE* userFile = fopen(userFileExt, "r");
    FILE* tempFile = fopen(tempFileExt, "w");
    char line[200];
    while(fgets(line, sizeof(line), userFile)){
        if(id!=i){
            fprintf(tempFile,"%s", line);
        }
        i++;
    }
    fclose(userFile);
    fclose(tempFile);
    remove(userFileExt);
    rename(tempFileExt, userFileExt);
}

void deleteUserOrder(char* userFileWithExt){
    Order order;
    int choix;
    int id;
    system("cls");
    int MaxId = showOrders(userFileWithExt);
    if(MaxId==0){
        fastSquire();
        gotoxy(30,5);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        printf("Error, there is no Active Order");
        getch();
        return;
    }
    do{
        int result;
        do{
            system("cls");
            showOrders(userFileWithExt);
            printf("0 to go back\n");
            printf("Order id: ");
            result = scanf("%d", &id);
            if(result!=1){
                while (getchar() != '\n');
            }
        }while(result!=1);
        if(id==0){
            return;
        }
    }while(id<1 || id>MaxId);
    system("cls");
    order = findTheOrder(id-1, userFileWithExt);
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        showOrderInfoToDelete(order);
        gotoxy(40,15);
        arrowHere(1, position);printf(" Delete");
        gotoxy(40,16);
        arrowHere(2, position);printf(" Cancle");
        key = getch();
        if(key == 80 && position!=2){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    if(position==1){
        if(MaxId==1){
            remove(userFileWithExt);
            return;
        }else{
            deleteOrder(id-1, userFileWithExt);
        }

    }
}

void arrowHere(int realPosition, int arrowPosition){
    if(arrowPosition==realPosition){
        printf("  -->");
    }else{
        printf("     ");
    }
}

int mainMenu(){
    int position = 1;
    int key = 0;
    squire();
    while(key!=13){
        system("cls");
        fastSquire();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
        gotoxy(30, 10);
        arrowHere(1, position);printf(" Login");
        gotoxy(30, 11);
        arrowHere(2, position);printf(" Register");
        gotoxy(30, 12);
        arrowHere(3, position);printf(" Stop App");
        key = getch();
        if(key == 80 && position!=3){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}

int userMainMenu(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(30,10);
        arrowHere(1, position);printf(" add Order");
        gotoxy(30, 11);
        arrowHere(2, position);printf(" show Orders");
        gotoxy(30, 12);
        arrowHere(3, position);printf(" manage Orders");
        gotoxy(30, 13);
        arrowHere(4, position);printf(" user Info");
        gotoxy(30, 14);
        arrowHere(5, position);printf(" Logout");
        key = getch();
        if(key == 80 && position!=5){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}

int manageOrderMenu(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(30,10);
        arrowHere(1, position);printf(" edit Order");
        gotoxy(30, 11);
        arrowHere(2, position);printf(" delete Order");
        gotoxy(30, 12);
        arrowHere(3, position);printf(" back");
        key = getch();
        if(key == 80 && position!=3){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}

int confirmOrderMenu(Order order){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        showOrderInfo(order);
        gotoxy(42,13);
        arrowHere(1, position);printf(" Accept\n");
        gotoxy(42,14);
        arrowHere(2, position);printf(" Edit\n");
        gotoxy(42,15);
        arrowHere(3, position);printf(" Cancle\n");
        key = getch();
        if(key == 80 && position!=3){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}
int confirmAddOrderMenu(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");

        fastSquire();
        gotoxy(30,12);
        printf("add more Orders");
        gotoxy(42,13);
        arrowHere(1, position);printf(" Yes\n");
        gotoxy(42,14);
        arrowHere(2, position);printf(" No\n");
        key = getch();
        if(key == 80 && position!=2){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}
int confirmDeleteAccountMenu(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");

        fastSquire();
        gotoxy(30,12);
        printf("Are You Sure You Want To Delete Your Account");
        gotoxy(42,13);
        arrowHere(1, position);printf(" Yes\n");
        gotoxy(42,14);
        arrowHere(2, position);printf(" No\n");
        key = getch();
        if(key == 80 && position!=2){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}

int editOrderMenu(Order order, int id){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        showUserOrder(order, id);
        arrowHere(1, position);printf(" change City\n");
        arrowHere(2, position);printf(" change Hotel\n");
        arrowHere(3, position);printf(" change Person Number\n");
        arrowHere(4, position);printf(" change date\n");
        arrowHere(5, position);printf(" Confirme\n");
        arrowHere(6, position);printf(" cancle");
        key = getch();
        if(key == 80 && position!=6){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}


Date setUserDate(){
    Date date;
    time_t t = time(NULL);
    struct tm *currentTime = localtime(&t);
    struct tm finishedDate = {0};
    struct tm startedDate = {0};

    startedDate.tm_year = currentTime->tm_year;
    startedDate.tm_mon = currentTime->tm_mon;
    startedDate.tm_mday = currentTime->tm_mday;
    startedDate.tm_hour = finishedDate.tm_min = finishedDate.tm_sec = 0;
    startedDate.tm_isdst = -1;

    finishedDate.tm_year = currentTime->tm_year;
    finishedDate.tm_mon = currentTime->tm_mon;
    finishedDate.tm_mday = currentTime->tm_mday;
    finishedDate.tm_hour = finishedDate.tm_min = finishedDate.tm_sec = 0;
    finishedDate.tm_isdst = -1;
    int monthChoice;
    int result;
    do{
        do{
            system("cls");
            showMonth(currentTime->tm_year, currentTime->tm_mon);
            gotoxy(50, 4);
            printf("start Month: ");
            result = scanf("%d", &monthChoice);
            if(result!=1){
                while (getchar() != '\n');
            }

        }while(result!=1);
        startedDate.tm_mon = monthChoice-1;
    }while(startedDate.tm_mon<currentTime->tm_mon || startedDate.tm_mon>11);

    do{
        do{
            system("cls");
            if(currentTime->tm_mon==startedDate.tm_mon){
                showDays(startedDate.tm_mon+1, currentTime->tm_mday-1);
            }else{
                showDays(startedDate.tm_mon, 0);
            }
            gotoxy(50,8);
            printf("start day: ");
            result = scanf("%d", &startedDate.tm_mday);
            if(result!=1){
                while (getchar() != '\n');
            }

        }while(result!=1);
    }while(currentTime->tm_mon==startedDate.tm_mon && startedDate.tm_mday<currentTime->tm_mday || startedDate.tm_mday>30);

    do{
        do{
            system("cls");
            if(startedDate.tm_mday==30 && finishedDate.tm_mon==startedDate.tm_mon){
                showMonth(currentTime->tm_year, startedDate.tm_mon+1);
            }else{
                showMonth(currentTime->tm_year, startedDate.tm_mon);
            }

            gotoxy(50, 4);
            printf("end Month: ");
            result = scanf("%d", &monthChoice);;
            if(result!=1){
                while (getchar() != '\n');
            }

        }while(result!=1);
        finishedDate.tm_mon = monthChoice-1;
    }while(finishedDate.tm_mon<startedDate.tm_mon || finishedDate.tm_mon>11 || (startedDate.tm_mday==30 && finishedDate.tm_mon==startedDate.tm_mon));

    do{
        do{
            system("cls");
            if(startedDate.tm_mon==finishedDate.tm_mon){
                showDays(startedDate.tm_mon+1, startedDate.tm_mday);
            }else{
                showDays(finishedDate, 0);
            }
            gotoxy(50,8);
            printf("end day: ");
            result = scanf("%d", &finishedDate.tm_mday);
            if(result!=1){
                while (getchar() != '\n');
            }

        }while(result!=1);
    }while(startedDate.tm_mon==finishedDate.tm_mon && finishedDate.tm_mday<=startedDate.tm_mday || finishedDate.tm_mday>31);

    time_t t1 = mktime(&finishedDate);
    time_t t2 = mktime(&startedDate);

    double dt = difftime(t1, t2);
    int days = round(dt / 86400);

    date.days = days;
    date.firstDay = startedDate.tm_mday;
    date.firstMonth = startedDate.tm_mon+1;
    date.lastDay = finishedDate.tm_mday;
    date.lastMonth = finishedDate.tm_mon+1;
    date.year = currentTime->tm_year+1900;
    return date;
}


void showMonth(int year, int start){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    gotoxy(50, 2);
    SetConsoleTextAttribute(hConsole, 7);
    printf("==== YEAR: %d ====\n", year+1900);
    gotoxy(50, 3);
    for(int i=0;i<12;i++){
        if(i<start){
            SetConsoleTextAttribute(hConsole, 4);
        }else{
            SetConsoleTextAttribute(hConsole, 2);
        }
        printf("%-3d", i+1);
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void showDays(int month,int start){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = 50;
    int y = 4;
    gotoxy(50,2);
    SetConsoleTextAttribute(hConsole, 7);
    printf("==== MONTH: %d ====", month);
    gotoxy(50,3);
    for(int i=0;i<30;i++){
        if(i<start){
            SetConsoleTextAttribute(hConsole, 4);
        }else{
            SetConsoleTextAttribute(hConsole, 2);
        }
        gotoxy(x, y);
        if(i==10 || i==20){
            x = 27;
            y++;
        }
        printf("%-3d", i+1);
        x+=4;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

int manageUser(){
    int choice;
    int line;
    int isDeleted = 0;
    line = getUserIdLine();
    do{
    choice = manageUserMenu();
    switch(choice){
        case 1:
            changeUserInfo(1, line);
            break;
        case 2:
            changeUserInfo(2, line);
            break;
        case 3:
            changeUserInfo(3, line);
            break;
        case 4:
            isDeleted = deleteUserAccount(line);
            break;
    }
    }while(choice!=5 && !isDeleted);
    return isDeleted;
}

int manageUserMenu(){
    int position = 1;
    int key = 0;
    while(key!=13){
        system("cls");
        fastSquire();
        gotoxy(25, 6);
        printf("CartCNI: %s", user.cartCNI);
        gotoxy(25, 7);
        printf("FirstName: %s", user.firstName);
        gotoxy(25, 8);
        printf("LastName: %s", user.lastName);
        gotoxy(25, 9);
        printf("PhoneNumber: %s", user.phoneNumber);
        gotoxy(30,12);
        arrowHere(1, position);printf(" change FirstName");
        gotoxy(30, 13);
        arrowHere(2, position);printf(" change LastName");
        gotoxy(30, 14);
        arrowHere(3, position);printf(" change PhoneNumber");
        gotoxy(30, 15);
        arrowHere(4, position);printf(" delete Account");
        gotoxy(30, 16);
        arrowHere(5, position);printf(" Back");
        key = getch();
        if(key == 80 && position!=5){
            position++;
        }else if(key == 72 && position!=1){
            position--;
        }else{
            position = position;
        }
    }
    return position;
}

int getUserIdLine(){
    FILE* file = fopen("users.txt", "r");
    if(file==NULL){
        return;
    }
    char *data;
    char line[200];
    int i = 0;
    while(fgets(line, sizeof(line), file)){
        data = strtok(line, " ");
        while(data!=NULL){
            if(strcmp(data, user.cartCNI)==0){
                fclose(file);
                return i;
            }
            data = strtok(NULL, " ");
            break;
        }
        i++;
    }
    fclose(file);
}

void changeUserInfo(int choice, int userLine){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char temp[50];
    switch(choice){
        case 1:
            system("cls");
            printf("New FirstName: ");
            scanf("%s", temp);
            break;
        case 2:
            system("cls");
            printf("New LastName: ");
            scanf("%s", temp);
            break;
        case 3:
            system("cls");
            printf("New phoneNumber: ");
            scanf("%s", temp);
            break;
    }
    if(choice==1){
        for(int i=0;temp[i]!='\0';i++){
            if(isdigit(temp[i])){
                gotoxy(35,10);
                SetConsoleTextAttribute(hConsole, 4);
                printf("error, there is a number in your firstName");
                getch();
                return;
            }
        }
    }
    if(choice==2){
         for(int i=0;temp[i]!='\0';i++){
            if(isdigit(temp[i])){
                gotoxy(35,10);
                SetConsoleTextAttribute(hConsole, 4);
                printf("error, there is a number in your lastName");
                getch();
                return;
            }
        }
    }
    if(choice==3){
        //check user phone Number is Valid:
        for(int i=0;temp[i]!='\0';i++){
            if (!isdigit(temp[i])) {
                gotoxy(35,10);
                SetConsoleTextAttribute(hConsole, 4);
                printf("error, phone number can't be a char");
                getch();
                return;
            }
        }
        if(strlen(temp)!=10){
            gotoxy(35,10);
            SetConsoleTextAttribute(hConsole, 4);
            printf("error, phone number have to be 10 Numbers");
            getch();
            return;
        }
    }
    int i = 0;
    FILE* userFile = fopen("users.txt", "r");
    FILE* tempFile = fopen("tempUser.txt", "w");
    char line[200];
    while(fgets(line, sizeof(line), userFile)){
        if(userLine==i){
            switch(choice){
                case 1:
                    fprintf(tempFile, "%s %s %s %s", user.cartCNI, temp, user.lastName, user.phoneNumber);
                    strcpy(user.firstName, temp);
                    break;
                case 2:
                    fprintf(tempFile, "%s %s %s %s", user.cartCNI, user.firstName, temp, user.phoneNumber);
                    strcpy(user.lastName, temp);
                    break;
                case 3:
                    fprintf(tempFile, "%s %s %s %s", user.cartCNI, user.firstName, user.lastName, temp);
                    strcpy(user.phoneNumber, temp);
                    break;
            }
        }else{
            fprintf(tempFile,"%s", line);
        }
        i++;
    }
    fclose(userFile);
    fclose(tempFile);
    remove("users.txt");
    rename("tempUser.txt", "users.txt");
}
void deleteAccount(int userLine){
    int i = 0;
    FILE* userFile = fopen("users.txt", "r");
    FILE* tempFile = fopen("tempUser.txt", "w");
    char line[200];
    while(fgets(line, sizeof(line), userFile)){
        if(userLine!=i){
            fprintf(tempFile,"%s", line);
        }
        i++;
    }
    fclose(userFile);
    fclose(tempFile);
    remove("users.txt");
    rename("tempUser.txt", "users.txt");
}

int deleteUserAccount(int userLine){
    int choice = confirmDeleteAccountMenu();
    if(choice==1){
        deleteAccount(userLine);
        return 1;
    }
    return 0;
}
