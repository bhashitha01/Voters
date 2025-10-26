#include <stdio.h>
#include <string.h>
#define CANDIDATES 100
int votecalculate();


int votecalculate() {
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

FILE *adminFile = fopen("admin.txt", "r");
    if (adminFile == NULL) {
        printf("Error: admin.txt file not found!\n");
        return 1;
    }

    char fileUser[100], filePass[100];
    char inputUser[100], inputPass[100];
    int found = 0;

    printf("=== Admin Login ===\n");

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

    printf("\nLogin successful! Welcome, %s\n\n", inputUser);

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
printf("=== Vote Summary ===\n");


FILE *candFile = fopen("candidates.txt", "r"); 
if (candFile == NULL) { 
    printf("Error: candidates.txt file not found!\n");
 return 1;
  }
    
int index = 1; 
char id[20], code[20];
char line[200];
 while (fgets(line,sizeof(line),candFile)) {
    if (sscanf(line, "%s %s %s %s", id, name, code, party) == 4) {
     printf("%d. %s (%s) - %d votes\n", index, name, party, candidateVotes[index - 1]);
     totalVotes += candidateVotes[index - 1];


      if (candidateVotes[index - 1] > maxVotes) {
         maxVotes = candidateVotes[index - 1];
          winner = index; 
             strcpy(winnerName, name);}  
           } 
             index++; 
 }
           fclose(candFile);
                 double average = 0.0;
                if (totalCandidates > 0) {
                     average = (double)totalVotes / totalCandidates;
}


            printf("\n=== Winner ===\n");
             printf("Candidate #%d (%s) received %d votes and won the election!\n", winner, winnerName, maxVotes);
             printf("\nAverage votes per candidate: %.2f\n", average);
              printf("================\n");
}
int main(){
   votecalculate();
    return 0;
}
