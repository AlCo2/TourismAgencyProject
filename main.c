#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <windows.h>

#define ANIME_TIME 1

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
    char firstName[50];
    char lastName[50];

    fastSquire();
    gotoxy(25, 4);
    printf("---Register---");
    gotoxy(30,5);
    printf("Cart CNI: ");
    scanf("%s", cartCNI);
    gotoxy(30,6);
    printf("firstName: ");
    scanf("%s", firstName);
    gotoxy(30,7);
    printf("lastName: ");
    scanf("%s", lastName);
    gotoxy(30,8);
    printf("Phone Number: ");
    scanf("%s", phoneNumber);
    FILE* usersFile = fopen("users.txt", "a");
    if(usersFile==NULL){
        usersFile = fopen("users.txt", "w");
        gotoxy(30,9);
        fprintf(usersFile, "%s %s %s %s\n", cartCNI, firstName, lastName, phoneNumber);
        fclose(usersFile);
    }else{
        char *data;
        char line[200];
        if(checkUserExists(cartCNI)){
            gotoxy(35,10);
            printf("error, this User Already Regestered\n");
            getch();
            fclose(usersFile);
            return;
        }
        fprintf(usersFile, "%s %s %s %s\n", cartCNI, firstName, lastName, phoneNumber);
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
    printf("4-Italy");
    gotoxy(30,9);
    scanf("%d", &choice);
    }while(choice<1 || choice > 4);
    return choice;
}


void newTourismeOrder(char* cartCNI, char* country){
    UP:
    system("cls");
    Order order;
    int YESNO, confirm;
    order = createOrder(country,cartCNI);
    do{
        system("cls");
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
            goto UP;
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
    system("cls");
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

void showOrderInfoToDelete(Order order){
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
    printf("price: %d$\n", order.hotel.price);
}

void showUserOrder(Order order, int id){
    printf("+------------------------+\n");
    printf("| id: %-4d               |\n", id);
    printf("| Country: %-14s|\n", order.country);
    printf("| City: %-17s|\n", order.city);
    printf("| Hotel: %-16s|\n", order.hotel.hotelName);
    printf("| Days: %-2d from %-2d to %-2d |\n", order.date.lastDay-order.date.firstDay, order.date.firstDay, order.date.lastDay);
    printf("| Person: %-15d|\n", order.persons);
    int days = order.date.lastDay-order.date.firstDay;
    printf("| price: %-4d$           |\n", order.hotel.price);
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
        fclose(userFile);
        do{
            system("cls");
            fastSquire();
            gotoxy(30,5);
            printf("1-add Order");
            gotoxy(30,6);
            printf("2-show Orders");
            gotoxy(30,7);
            printf("3-manage Orders");
            gotoxy(30,8);
            printf("4-Logout");
            gotoxy(30,9);
            scanf("%d", &n);
            switch(n){
                case 1:
                    welcomeApp(cartCNI);
                    break;
                case 2:
                    system("cls");
                    showOrders(userFileWithExt);
                    getch();
                    break;
                case 3:
                    manageOrders(userFileWithExt);
                    break;
            }
        }while(n!=4);
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
        id++;
        showUserOrder(order, id);
    }
    fclose(userFile);
    return id;
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
    gotoxy(43,2);
    printf("Tourisme Agency");
}

char* moroccoCityChoice(){
    int cityChoice;
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
    int cityChoice;
    fastSquire();
    gotoxy(30,5);
    printf("1-marcial\n");
    gotoxy(30,6);
    printf("2-paris\n");
    gotoxy(30,7);
    printf("3-tollosse\n");
    gotoxy(45,8);
    scanf("%d", &cityChoice);
    switch(cityChoice){
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
    int cityChoice;
    fastSquire();
    gotoxy(30,5);
    printf("1-madrid\n");
    gotoxy(30,6);
    printf("2-barcallona\n");
    gotoxy(30,7);
    printf("3-sevilla\n");
    gotoxy(45,8);
    scanf("%d", &cityChoice);
    switch(cityChoice){
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
    int cityChoice;
    fastSquire();
    gotoxy(30,5);
    printf("1-mellano\n");
    gotoxy(30,6);
    printf("2-nappoli\n");
    gotoxy(30,7);
    printf("3-torino\n");
    gotoxy(45,8);
    scanf("%d", &cityChoice);
    switch(cityChoice){
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
    int size;
    int hotelChoice;
    Hotel* hotelList = readHotelData(cityWithExt,&size);
    if(hotelList==NULL){
        return;
    }
    do{
        printf("Hotel Number: ");
        scanf("%d", &hotelChoice);
    }while(hotelChoice<1 || hotelChoice>=size);
    return hotelList[hotelChoice-1];
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
    order.date = setDays();
    return order;
}

int getHowManyPerson(){
    int n;
    do{
        system("cls");
        fastSquire();
        gotoxy(30,5);
        printf("Persons: ");
        scanf("%d", &n);
    }while(n<1);
    return n;
}

void manageOrders(char* userFileWithExt){
    int choice;
    do{
    system("cls");
    fastSquire();
    gotoxy(30, 10);
    printf("1-edit Order");
    gotoxy(30, 11);
    printf("2-delete Order");
    gotoxy(30, 12);
    printf("3-back");
    gotoxy(30,13);
    scanf("%d", &choice);
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
        printf("Error, there is no Active Order");
        getch();
        return;
    }
    system("cls");
    do{
        showOrders(userFileWithExt);
        printf("Order id: ");
        scanf("%d", &id);
    }while(id<1 || id>MaxId);
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
        days = order.date.lastDay-order.date.firstDay;
        showUserOrder(order, id);
        printf("1-change City\n");
        printf("2-change Hotel\n");
        printf("3-change Person Number\n");
        printf("4-change date\n");
        printf("5-Confirme 6-cancle\n");
        scanf("%d", &choice);
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
                order.date = setDays();
                days = order.date.lastDay-order.date.firstDay;
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
            fprintf(tempFile, "%s,%s,%s,%d,%d,%d,%d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price);
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
        printf("Error, there is no Active Order");
        getch();
        return;
    }
    system("cls");
    do{
        showOrders(userFileWithExt);
        printf("Order id: ");
        scanf("%d", &id);
    }while(id<1 || id>MaxId);
    system("cls");
    order = findTheOrder(id-1, userFileWithExt);
    do{
        system("cls");
        showOrderInfoToDelete(order);
        gotoxy(40,15);
        printf("1-Delete 2-cancle");
        gotoxy(40,16);
        scanf("%d", &choix);
    }while(choix<1 || choix>2);
    if(choix==1){
        if(MaxId==1){
            remove(userFileWithExt);
            return;
        }
        deleteOrder(id-1, userFileWithExt);
    }
}
