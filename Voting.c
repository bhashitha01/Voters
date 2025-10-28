#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_USERS 100
#define MAX_CANDIDATES 20
#define MAX_LENGTH 100

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


void loadData(const char* filename, void* array, int* count, int type);

int authenticateUser(char* currentUser);
void displayCandidates();
void voteProcess(const char* username);
int isValidID(const char* password);
int hasAlreadyVoted(const char* username);
int voting();


void loadData(const char* filename, void* array, int* count, int type) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        if (type == 1) { 
          User* users = (User*)array;
            if (sscanf(line, "%s %s", users[*count].username, users[*count].password) == 2)
                (*count)++;
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



int isValidID(const char* password) {
    for (int i = 0; password[i]; i++)
        if (!isdigit(password[i])) return 0;
    return 1;
}


    int hasAlreadyVoted(const char* username) {
    FILE *file = fopen("votes.txt", "r");
    if (!file) return 0; // File vote 

    char line[256], user[100];

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
        printf("Error: Invalid ID number! You are not registered as a voter.\n");
        return -1;
    }
}
    


void displayCandidates() {
    FILE *file = fopen("candidates.txt", "r");
    if (file == NULL) {
        printf("Error: candidates.txt file not found!\n");
        return;
    }
    char line[200];
    char id[50], name[50], code[50], party[50];
    int index = 1;

    printf("=== Candidate List ===\n");
    while (fgets(line, sizeof(line), file)) {
    if(sscanf(line, "%s %s %s %s", id, name, code, party) == 4) {
        printf("%d. %s %s %s\n", index, name, code, party);
        index++;
    }
}
    fclose(file);
    printf("=======================\n\n");
}

void voteProcess(const char* username) {
    int userVotes[3];
    int choice;
    printf("You can vote for 3 candidates.\n");

    // Candidate list display
    for (int i = 0; i < candidateCount; i++) {
        printf("%d. %s - %s\n", i + 1, candidates[i].name, candidates[i].party);
    }

    for (int i = 0; i < 3; i++) {
        printf("Enter your choice #%d (1-%d): ", i + 1, candidateCount);
        if (scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter a number.\n");
        while (getchar() != '\n'); // clear buffer
        i--; // retry same iteration
        continue;
    }
    
        if (choice < 1 || choice > candidateCount) {
            printf("Invalid candidate number! Try again.\n");
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
    }

    printf("\nYour votes have been recorded successfully!\n");
    printf("You voted for:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s - %s\n", i + 1,
               candidates[userVotes[i] - 1].name,
               candidates[userVotes[i] - 1].party);
    }
}




int voting() {
    char currentUser[MAX_LENGTH];
    int authResult;
    printf("=== Voting System ===\n\n");

    
   loadData("candidates.txt", candidates, &candidateCount, 2);
   

    
    authResult = authenticateUser(currentUser);

    if (authResult == 1) {
        printf("\nLogin successful! Welcome %s!\n\n", currentUser);

        if (hasAlreadyVoted(currentUser)) {
            printf("You have already voted! You cannot vote again.\n");
            return 0;
        }

        displayCandidates();
        voteProcess(currentUser);
        printf("\nThank you for voting!\n");
    } else {
        printf("\nLogin failed! Invalid ID number.\n");
    }
}
int main(){
   voting();
    return 0;
}





