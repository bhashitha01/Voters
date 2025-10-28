#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>


#define size 12

void Registration(int age);  //Voter
int check(const char* prompt);
int isValidName(char name[]);
int checkid();


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
          printf("registercandidate()");// Voting
          break;
          
          case 3:
          printf("voting()"); // Result viwe
          break;

          case 4:
          printf("votecalculate()"); //vote calculating
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