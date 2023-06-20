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

void welcomeApp();

int countryList();

void morocco(Order order);

void readHotelData(FILE* data, Hotel* hotelList, int* size);



int main()
{
    int appRunning = 1;
    int appChoice;
    Order order;
    while(appRunning){
        printf("1-Login\n");
        printf("2-Register\n");
        printf("3-Stop App\n");
        scanf("%d", &appChoice);
        switch(appChoice){
            case 1:
                morocco(order);
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

void welcomeApp(){
    int countryChoice;
    countryChoice = countryList();
    switch(countryChoice){
        //morocco:
        case 1:

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


morocco(Order order){
    int cityChoice, hotelChoice;
    char city[100];
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
