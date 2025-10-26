#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define size 12

int registercandidate();
int isValidName(char name[]);
int isValidNIC(char nic[]);
int isValidParty(char party[]);
void clearBuffer();
int isregistered(char nic[]);
int getNextCandidateID();

int main() {

registercandidate();
return 0;


}

int registercandidate() {
FILE *fptr = fopen("candidates.txt", "a+");
if (!fptr) {
printf("File could not be opened!\n");
return 0;
}

char name[100], nic[size+1], password[13], party[30];
int age;
int found;

printf("\n-----Registration-----\n");

int id = getNextCandidateID();
char username[20];
sprintf(username, "candi%04d", id);

while (1) {
    printf("Enter Full Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    if (strlen(name) == 0) {
        printf("Name cannot be empty!\n");
        continue;
    }
    if (!isValidName(name)) {
        printf("Name must contain English letters only!\n");
        continue;
    }
    break;
    
}

while (1) {
    printf("Enter NIC Number: ");
    scanf("%12s",nic);

     if(strlen(nic) > size){
    continue;
   }
   
    if (strlen(nic) == 0) {
        printf("NIC cannot be empty!\n");
        continue;
    }
     if (strlen(nic) != size) {
            printf("NIC must contain exactly 12 digits!\n");
            continue;
        }

    if (!isValidNIC(nic)) {
        printf("Please enter valid NIC number (12 digits)!\n");
        continue;
    }
    
    if(isregistered(nic)){
    printf(".....You All ready Registered......");
    return 0;
    fclose(fptr);
    }


while (1) {
    printf("Enter Age: ");
    if (scanf("%d", &age) != 1) {
        printf("Please enter a valid number.\n");
        clearBuffer();
        continue;
    }
    clearBuffer();
    if (age < 18) {
        printf("Age must be at least 18 to register.\n");
        return 0;
    }
    break;
}

while (1) {
    printf("--Party Type--\n\tParty A\n\tParty B\n\tParty C\n\tParty D\nEnter Party Name: ");
    scanf("%s", party);
    clearBuffer();
    if (!isValidParty(party)) {
        printf("\nInvalid Party! Please choose from Party A, Party B, Party C, Party D.\n");
        continue;
    }
    break;
}

strcpy(password, nic);
fprintf(fptr, "%s %s %s %s %d\n", nic, name,username,party,age);
fclose(fptr);

printf("\nRegistration Successful!\n");


return 0;

}
}
int isValidName(char name[]) {
for (int i = 0; name[i] != '\0'; i++) {
if (name[i] == '\n') break;
if (name[i] == ' ') continue;
if (!isalpha(name[i])) return 0;
}
return 1;
}

int isValidNIC(char nic[]) {
int len = strlen(nic);
for (int i = 0; i < len; i++) {
if (!isdigit(nic[i])) return 0;
}
return 1;
}

int isValidParty(char party[]) {
if (strcmp(party, "A") == 0 || strcmp(party, "B") == 0 ||
strcmp(party, "C") == 0 || strcmp(party, "D") == 0) {
return 1;
}
return 0;
}

void clearBuffer() {
int c;
while ((c = getchar()) != '\n' && c != EOF) { }
}


int isregistered(char nic[]) {
FILE *fptr = fopen("candidates.txt", "r");
if (fptr == NULL) {
    return 0;
}


char id[20];

while (fscanf(fptr,"%s", id) == 1) {
    if (strcmp(id, nic) == 0) {
        fclose(fptr);
        return 1;
        
    }
    fscanf(fptr, "%*[^\n]");
}
fclose(fptr);
return 0;

}

int getNextCandidateID() {
FILE *fptr = fopen("candidates.txt", "r");
if (!fptr) return 1;


char line[256];
int count = 0;
while (fgets(line, sizeof(line), fptr)) {
    count++;
}
fclose(fptr);
return count + 1;


}