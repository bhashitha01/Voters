#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>


#define size 12

#define MAX_USERS 100
#define MAX_CANDIDATES 20
#define MAX_LENGTH 100

#define CANDIDATES 100

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

typedef struct {
    char name[MAX_LENGTH];
    char party[MAX_LENGTH];
} Candidate;

typedef struct {
    char username[MAX_LENGTH];
    int vote1, vote2, vote3;
} Vote;

User existingUsers[MAX_USERS], newUsers[MAX_USERS];
Candidate candidates[MAX_CANDIDATES];
Vote votes[MAX_USERS];
int existingUserCount = 0, newUserCount = 0, candidateCount = 0, voteCount = 0;




void Registration(int age);  //Voter
int check(const char* prompt);
int isValidName(char name[]);
int checkid();


int registercandidate();   //Candidate
int isValidNIC(char nic[]);  
int isValidParty(char party[]);
void clearBuffer();
int isregistered(char nic[]);
int getNextCandidateID();

void loadData(const char* filename, void* array, int* count, int type); //voting
int authenticateUser(char* currentUser);
void displayCandidates();
void voteProcess(const char* username);
int isValidID(const char* password);
int hasAlreadyVoted(const char* username);
int voting();


int votecalculate();// votecalculate

int main(){
int num,age,choice;


do{
    printf("\n\n______Main Menu_______\n\n"); //Main Menu
    printf("1.Voters Registration\n");
    printf("2.Candidate Registration\n");
    printf("3.Votting\n");
    printf("4.Result View\n");
    printf("0.Exit\n");
    num=check("\nEnter Your Choice:");
    

switch(num){
          case 0:
          printf("Exitting the Programme"); //Voter Registration
          return 0;
          break;
          
          case 1:
          Registration(age);//Candidate Regisstertion
          break;
          
          case 2:
          registercandidate();// Voting
          break;
          
          case 3:
          voting(); // Result viwe
          break;

          case 4:
          votecalculate(); //vote calculating
          break;
          
        
}         
} while (1);


return 0;
}

void Registration(int age){
char character;
 int id,choice;
    printf("\n\n_______Voters Registration________\n\n"); //Age Checking 18+
    age=check("Enter The Age: ");
    while(getchar() != '\n'); 
    if(age>=18){
    checkid();
    
    
   
    

    }
    else{
    printf("\n\nYour Age is Equal to 18 or 18 Than\n\n");}
   
   
    }
    
int check(const char* prompt){   //Coreect User input Choice Check
      printf("%s",prompt);
      int choice;
      while (scanf("%d",&choice) !=1){
          printf("please Valid %s\n\n",prompt);//Buffer remove
          while(getchar() != '\n');
          printf("%s",prompt);
        }
        return choice;

}

int isValidName(char name[]) {       // User characters validation
    for (int i = 0; name[i] != '\0'; i++) { 
        if (name[i] == '\n') break;      // User input characters validation  A to Z and a to z  
        if (name[i] == ' ') continue;    //Check use libray fountion isalpha
        if (!isalpha(name[i])) {         
            return 0;             
        }
    }
    return 1;
}


int checkid(){   //Id checking fountion
char id[size+2];
char idr[size+2];
char name[50];
int found=0;
int x=0;


while(1){
  int checkbit=1;
  printf("Enter the Id number: ");
  scanf("%13s",id);

  if(strlen(id) != size){
  printf("enter the 12 characters\n");//Id length checking
  continue;
  }
  if(strlen(id) > size){
  printf("enter the only 12 characters\n");//Id over length Checking
   continue;
  }
  
  for(int i=0;i<size;i++){
   if(!isdigit(id[i])){        //User enter the Only Digits check fountion
    printf("Enter the only characters\n");
      checkbit=0;                        //Use the Libray funtion isdigit
      break;
   }
 
  }
   if(!checkbit) continue;
   break;
}
while(1){
    printf("Enter The your Name: ");
    scanf(" %[^\n]",name);

  if(!isValidName(name)){               //check tha letters
    printf("Enter Leters Only\n");
    continue;
    }
    
  break;
}

FILE *fpointer;
fpointer=fopen("Voters.txt","r");
if(fpointer != NULL){
while(fscanf(fpointer,"%s",idr)==1){
  if(strcmp(idr, id)==0){
    found=1;
    break;
    
  }
  
}
fclose(fpointer);
}

if(found==1){
  printf("\n\n...You All Ready Registered...\n\n");
  return 0;
   
}
    FILE *fcount;
    fcount = fopen("Voters.txt", "r");
    if (fcount != NULL) {             //system enter the VoterId 
      char tempID[30], tempName[50], tempVoter[20];
        while (fscanf(fcount, "%s %s %s",tempID,tempName,tempVoter) == 3){
            x++;
    }
        fclose(fcount);

    }
    fpointer=fopen("Voters.txt","a");
    if (fpointer == NULL) {
    printf("Failed to open file");
    return 0;
}
  
    
      fprintf(fpointer, "%s %s voter%d\n",id,name,x+1);  // All checking are True Save the data Voters.txt File
       printf("\n\n...Your Loging Details...\n\n");//Display the login details
       printf("UserName:Voter%d \n",x+1);
       printf("Password: %s\n",id);
      
      

      fclose(fpointer);
    

printf("\n\n...Your Registertion Sucessful...\n\n");
return 1;

}


int registercandidate() {                    //candidate Registration
FILE *fptr = fopen("candidates.txt", "a+");
if (!fptr) {
printf("File could not be opened!\n");
return 0;
}

char name[100], nic[size+1], password[13], party[30];
int age;
int found;

printf("\n\n-----Registration-----\n\n");

int id = getNextCandidateID();
char username[20];
sprintf(username, "candi%04d", id);

while (1) {
    printf("Enter Full Name: ");         // name letters checking
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    if (strlen(name) == 0) {
        printf("....Name cannot be empty!....\n");
        continue;
    }
    if (!isValidName(name)) {              //name check fountion
        printf("Name must contain English letters only!\n");
        continue;
    }
    break;
    
}

while (1) {
    printf("Enter NIC Number: ");              //Nic checking and getting
    scanf("%13s",nic);

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
    printf("\n.....You All ready Registered......\n");
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
    clearBuffer();         //Buffer cleanning
    if (age < 18) {
        printf("Age must be at least 18 to register.\n");
        return 0;
    }
    break;
}

while (1) {             // Display party
    printf("--Party Type--\n\tParty A\n\tParty B\n\tParty C\n\tParty D\nEnter Party Name: ");
    scanf("%s", party);
    clearBuffer();
    if (!isValidParty(party)) {   // system include party party check the user enter party
        printf("\nInvalid Party! Please choose from Party A, Party B, Party C, Party D.\n");
        continue;
    }
    break;
}

fprintf(fptr, "%s %s %s %s %d\n", nic, name,username,party,age);  //save the data candidate register file
fclose(fptr);

printf("\n\nRegistration Successful!\n\n");


return 0;

}
}

int isValidNIC(char nic[]) {
int len = strlen(nic);         //Nic checkinmg fountion use libray fountion isdigits
for (int i = 0; i < len; i++) {
if (!isdigit(nic[i])) return 0;
}
return 1;
}
 
 int isValidParty(char party[]) {              //system party checking fountion
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

int isregistered(char nic[]) {      //Dublicate Id save the file checking fountion
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

int getNextCandidateID() {           //get the next line read the file fountion
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

void loadData(const char* filename, void* array, int* count, int type) {   //load file data fountin
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {   //line by line file data load and check
        if (type == 1) { 
          User* users = (User*)array;
            if (sscanf(line, "%s %s", users[*count].username, users[*count].password) == 2)
                (*count)++;  // use the sscanf file data separte one space data get dada space and space varible
        }
        else if (type == 2) { // Candidates (id name code party)
            Candidate* cands = (Candidate*)array;
            char id[50], code[50];
            if (sscanf(line, "%s %s %s %s", id, cands[*count].name, code, cands[*count].party) == 4)
                (*count)++;
        }

    else if (type == 3) { // Votes (username vote1 vote2 vote3)
            Vote* vts = (Vote*)array;
            if (sscanf(line, "%s %d %d %d", vts[*count].username,
                       &vts[*count].vote1, &vts[*count].vote2, &vts[*count].vote3) == 4)
                (*count)++;
    }

      
        }
    

    fclose(file);
}

int authenticateUser(char* currentUser) {
    char id[MAX_LENGTH];  // ID number check
    char fileID[MAX_LENGTH], name[MAX_LENGTH], voterID[MAX_LENGTH], age[MAX_LENGTH];
    printf("Enter your ID number: ");
    if (scanf("%s", id) != 1) {
        printf("Error reading ID number!\n");
        return -1;
    }
    
    // Check if ID is a valid (only digits)
    if (!isValidID(id)) {
        printf("Error: ID must contain only numbers! Please try again.\n");
        return -1;
    }
    FILE* voterFile = fopen("voters.txt", "r");
    if (voterFile == NULL) {
        printf("Error: voter.txt file not found!\n");
        return -1;
    }

     int found = 0;
    while (fscanf(voterFile, "%s %s %s", fileID, name, voterID) == 3) {
        if (strcmp(fileID, id) == 0) {
            found = 1;
            strcpy(currentUser, voterID);  // Use voter ID as username
            break;
        }
    }
    fclose(voterFile);
    if (found) {
        return 1; // Login successful
    } else {
        printf("\nError: Invalid ID number! You are not registered as a voter.\n");
        return -1;
    }
}

   void displayCandidates() {       //candidate,cadidateid,party display the terminal funtion 
    FILE *file = fopen("candidates.txt", "r");
    if (file == NULL) {
        printf("Error: candidates.txt file not found!\n");
        return;
    }
    char line[200];
    char id[50], name[50], code[50], party[50];
    int index = 1;

    printf("\n\n=== Candidate List ===\n");  //dispaly file data
    while (fgets(line, sizeof(line), file)) {
    if(sscanf(line, "%s %s %s %s", id, name, code, party) == 4) {
        printf("%d. %s %s %s\n", index, name, code, party);
        index++;
    }
}
    fclose(file);
    printf("\n\n=======================\n\n");
} 

void voteProcess(const char* username) {
    int userVotes[3];
    int choice;
    printf("\n\nYou can vote for 3 candidates.\n\n");

    // Candidate list display
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s - %s\n", i + 1, candidates[i].name, candidates[i].party);
    }
     printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("Enter your choice #%d (1-%d): ", i + 1, candidateCount);  // 3 voters enter the 
        if (scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter a number.\n");
        while (getchar() != '\n'); // clear buffer
        i--; // retry same iteration
        continue;
    }
    
        if (choice < 1 || choice > candidateCount) {
            printf("Invalid candidate number! Try again.\n");  //use tha valid data
            i--;
        }
        userVotes[i] = choice;
    }

    // Save each vote separately with full details
    FILE *file = fopen("votes.txt", "a");
    if (file != NULL) {
        for (int i = 0; i < 3; i++) {
            fprintf(file, "%s %d %s %s %d\n",
                username,
                userVotes[i],
                candidates[userVotes[i] - 1].name,
                candidates[userVotes[i] - 1].party,1 // vote count = 1 for each vote
                );
        }
        fclose(file);
    
    
    printf("\n\nYour votes have been recorded successfully!\n\n");
    printf("You voted for:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s - %s\n", i + 1,        //recode save and display 
               candidates[userVotes[i] - 1].name,
               candidates[userVotes[i] - 1].party);
    }
}
}

int isValidID(const char* password) {     //pasword checking 
    for (int i = 0; password[i]; i++)         //we use pasworrd is Id Number
        if (!isdigit(password[i])) return 0;
    return 1;
}

int hasAlreadyVoted(const char* username) {    //Alresdy voter vote the checking fountion
    FILE *file = fopen("votes.txt", "r");
    if (!file) return 0; // File vote 

    char line[256], user[100];
// line by data read the votes.txt
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%s", user) == 1) {
            if (strcmp(user, username) == 0) {
                fclose(file);
                return 1; // voter vote
            }
        }
    }

    fclose(file);
    return 0; // vote
}

int voting() {    //voting
    char currentUser[MAX_LENGTH];
    int authResult;
    printf("\n\n=== Voting System ===\n\n");

    candidateCount = 0; 
   loadData("candidates.txt", candidates, &candidateCount, 2);  //candidate file data load
   

    
    authResult = authenticateUser(currentUser);  //login voters checking


    if (authResult == 1) {
        printf("\n\nLogin successful! Welcome %s!\n\n", currentUser);

        if (hasAlreadyVoted(currentUser)) {   //dublicate voteing checking
            printf("\nYou have already voted! You cannot vote again.\n");
            return 0;
        }

        displayCandidates();   //display candidate
        voteProcess(currentUser);
        printf("\nThank you for voting!\n");
    } else {
        printf("\nLogin failed! Invalid ID number.\n");
    }
}


int votecalculate() {   //vote calculate fountion
int candidateVotes[CANDIDATES] = {0};
char username[100];
char name[100];
char party[100];
int candNum, voteCount;
int totalCandidates = 0; 
int winner = 0; 
int maxVotes = 0;
int totalVotes = 0;  
char winnerName[100];
//system admin loging auterrized fountion
FILE *adminFile = fopen("admin.txt", "r");
    if (adminFile == NULL) {
        printf("Error: admin.txt file not found!\n");
        return 1;
    }

    char fileUser[100], filePass[100];
    char inputUser[100], inputPass[100];
    int found = 0;

    printf("\n\n=== Admin Login ===\n\n");

    printf("Enter username: ");
    scanf("%s", inputUser);
    printf("Enter password: ");
    scanf("%s", inputPass);

    while (fscanf(adminFile, "%s %s", fileUser, filePass) == 2) {
        if (strcmp(inputUser, fileUser) == 0 && strcmp(inputPass, filePass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(adminFile);

    if (!found) {
        printf("\nInvalid username or password!\n");
        return 0;
    }

    printf("\n\nLogin successful! Welcome, %s\n\n", inputUser);

//read voters file//

    FILE *f2 = fopen("votes.txt", "r"); 
    if (f2 == NULL) {
        printf("File open error");
        return 1;
    }

// Read all votes while 
while(fscanf(f2, "%s %d %s %s %d", username, &candNum, name, party, &voteCount) == 5) {
    candidateVotes[candNum - 1] += voteCount; 
    if (candNum > totalCandidates) 
    totalCandidates = candNum;
    } 
    fclose(f2);
printf("\n\n=== Vote Summary ===\n\n");


FILE *candFile = fopen("candidates.txt", "r"); 
if (candFile == NULL) { 
    printf("Error: candidates.txt file not found!\n");
 return 1;
  }    //candidate file read and display 
    
int index = 1; 
char id[20], code[20];
char line[200];
 while (fgets(line,sizeof(line),candFile)) {
    if (sscanf(line, "%s %s %s %s", id, name, code, party) == 4) {
     printf("%d. %s (%s) - %d votes\n", index, name, party, candidateVotes[index - 1]);
     totalVotes += candidateVotes[index - 1];


      if (candidateVotes[index - 1] > maxVotes) {    //count votes and who winne find
         maxVotes = candidateVotes[index - 1];
          winner = index; 
             strcpy(winnerName, name);}  
           } 
             index++; 
 }
           fclose(candFile);   //avarage of voers
                 double average = 0.0;
                if (totalCandidates > 0) {
                     average = (double)totalVotes / totalCandidates;
}

//Display Winner
            printf("\n\n=== Winner ===\n\n");
             printf("Candidate #%d (%s) received %d votes and won the election!\n", winner, winnerName, maxVotes);
             printf("\n\nAverage votes per candidate: %.2f\n\n", average);
              printf("================\n");
}
