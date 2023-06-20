#include <stdio.h>
#include <stdlib.h>


void login();

void Register();

int checkUserExists(char* cartCNI);

void welcomeApp();

int countryList();


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
                welcomeApp();
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
            printf("Morocco\n");
            break;
            //Spain:
        case 2:
            printf("Spain\n");
            break;
            //France:
        case 3:
            printf("France\n");
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
    }while(choice!=1 || choice!=2 || choice!=3);
    return choice;
}
