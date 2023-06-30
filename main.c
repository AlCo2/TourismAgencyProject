#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


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
    printf("Cart CNI: ");
    scanf("%s", cartCNI);
    if(!checkUserExists(cartCNI)){
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
    printf("1-Morroco\n");
    printf("2-Spain\n");
    printf("3-France\n");
    scanf("%d", &choice);
    }while(choice<1 || choice > 3);
    return choice;
}


void morocco(char* cartCNI){
    system("cls");
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "Morocco");
    system("cls");
    printf("1-Kenitra\n");
    printf("2-tanger\n");
    printf("3-marrakech\n");
    printf("4-agadir\n");
    printf("5-rabat\n");
    printf("6-cassablanca\n");
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
            break;
        case 3:
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

void france(char* cartCNI){
    up:
    system("cls");
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "France");
    Hotel hotelList[1000];
    system("cls");

    scanf("%d", &cityChoice);
    switch(cityChoice){
        //france city
    }
    strcpy(order.city, city);
    char cityWithExt[200];
    strcpy(cityWithExt, "france/");
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
    readHotelData(cityFile,&size);
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
            welcomeApp(cartCNI);
            return;
            break;
        case 3:
            welcomeApp(cartCNI);
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
                fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
                fclose(userFile);
                break;
            }
            fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
            fclose(userFile);
            userHaveOrder(cartCNI);
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
                fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
                fclose(userFile);
                break;
            }

            fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
            fclose(userFile);
            welcomeApp(cartCNI);
            break;
            }
        default:
            printf("error in choice");
            getch();
            break;
    }
}

void spain(char* cartCNI){
    up:
    system("cls");
    Order order;
    strcpy(order.cartCNI, cartCNI);
    int YESNO;
    int cityChoice, hotelChoice;
    char city[100];
    strcpy(order.country, "Spain");
    Hotel hotelList[1000];
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
    FILE* cityFile = fopen(cityWithExt, "r");
    if(cityFile == NULL){
        printf("city Is not Available Right Now\n");
        getch();
        return;
    }
    int size;
    system("cls");
    readHotelData(cityFile,&size);
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
            welcomeApp(cartCNI);
            return;
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
                fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
                fclose(userFile);
                break;
            }
            fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
            fclose(userFile);
            userHaveOrder(cartCNI);
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
                fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
                fclose(userFile);
                break;
            }

            fprintf(userFile, "%s %s %s %d %d %d %d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
            fclose(userFile);
            welcomeApp(cartCNI);
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
            printf(" ");
            printf("____________________________________________________________________________________________________________\n");
            while(token!=NULL){
                printf("|");
                printf("%-14s", token);
                token = strtok(NULL, ",");
            }
            i++;
        }else{
            printf("------------------------------------------------------------------------------------------------------------\n");
            j = 0;
            printf("%d", i);
            while(token!=NULL){
                switch(j){
                    case 0:
                        strcpy(hotelList[i-1].hotelName, token);
                        break;
                    case 2:
                        {
                        int SIZE = strlen(token);
                        char price[10];
                        strcpy(price, token);
                        price[SIZE-1] = '\0';
                        hotelList[i-2].price = atoi(price);
                        break;
                        }
                }
                j++;
                printf("|");
                printf("%-14s", token);
                token = strtok(NULL, ",");
            }
            i++;
        }
    }
    printf("____________________________________________________________________________________________________________\n");
    fclose(data);
    *size = i;
    return ptr;
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

void showUserOrder(Order order){
    printf("Country: %s\n", order.country);
    printf("City: %s\n", order.city);
    printf("Hotel: %s\n", order.hotel.hotelName);
    printf("Days: %d from %d to %d\n", order.date.lastDay-order.date.firstDay, order.date.firstDay, order.date.lastDay);
    printf("Person: %d\n", order.persons);
    int days = order.date.lastDay-order.date.firstDay;
    printf("price: %d$\n", order.hotel.price);
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
            printf("1-add Order\n2-show Orders\n3-Logout\n");
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
        printf("-------------------------\n");
    }
    fclose(userFile);
}

void APP(){
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
};

void writeUserIntoFile(char* userFileWithExt, Order order){
    int days = order.date.lastDay-order.date.firstDay;
    FILE* userFile = fopen(userFileWithExt, "a");
    fprintf(userFile, "%s,%s,%s,%d,%d,%d,%d\n", order.country, order.city, order.hotel.hotelName,order.date.firstDay, order.date.lastDay,order.persons, order.hotel.price*order.persons*days);
    fclose(userFile);
}
