#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
  	char username[20];
	char password[20];
	int status;
	struct node *next;
}node;

node *head = NULL;

void insert(char username[20], char password[20], int status){
	node *temp;
	temp=(node *)malloc(sizeof(node));
	strcpy(temp->username, username);
	strcpy(temp->password, password);
	temp->status = status;
	temp->next = head;
	head = temp;
}

node *find(char name[20]){

   //bat dau tim tu first link
   node *current = head;

   //neu list la trong
   if(head == NULL)
	{
      return NULL;
    }

   while(strcmp(current->username, name) != 0){
      if(current->next == NULL){
         return NULL;
      }else {
         current = current->next;
      }
   }      
   return current;
}

void printAll()
{
    node *temp;
    temp = head;
    while(temp)
    {
    	printf("%20s %20s %d",temp->username, temp->password, temp->status);
        printf("\n");
        temp=temp->next;
    }
    printf("\n");
}

void openFile(){
	node *acc;
	char *username;
	char *password;
	int status;
	char c;
	int u = 0, p = 0, blank = 0;
	username = (char *)malloc(20);
	password = (char *)malloc(20);
    FILE *fptr;
	if((fptr=fopen("account.txt","r+"))==NULL){
		printf("Khong tim thay %s\n","account.txt");
		return;
	}
	while(1){
		fscanf(fptr,"%s",username);
		fscanf(fptr,"%s",password);
		fscanf(fptr,"%d",&status);
		if(feof(fptr)) break;
		insert(username, password, status);
	}
	free(username); free(password);
	fclose(fptr);
}

void writeFile(){
	FILE *fptr;
	node *temp;
    temp = head;
    fptr=fopen("account.txt","w+");
    while(temp){
    	fprintf(fptr, "%s %s %d", temp->username, temp->password, temp->status);
    	fprintf(fptr, "\n");
    	temp=temp->next;
    }
    fclose(fptr);
}

void registerAccount(){
	char username[20];
	char password[20];
	//__fpurge(stdin);
	printf("---------Register\n");
	printf("Username: "); scanf("%s", username);//gets(username); __fpurge(stdin);
	printf("\n");
	printf("Password: "); scanf("%s", password);//gets(password); __fpurge(stdin);
	printf("\n");
	if(find(username) != NULL){
	printf("Account already exists!");	
	} 
	else{
		insert(username, password, 1);
		writeFile();
		printAll();
	}
	printf("\n");
}

node *signin(){
	char username[20];
	char password[20];
	int login_count = 0;
	printf("---------Sign In\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){
		if(acc->status == 0){
			printf("Account has been blocked!\n");
			return NULL;
		}
		do{
		printf("Password: "); scanf("%s", password);
		printf("\n");
		if(strcmp(acc->password,password) == 0){
			printf("Success\n");
			return acc; //both pass and username are correct
			}
		else {
			printf("Wrong Password\n");
			login_count++;
			//return NULL; //pass is incorrect
			}
		}while(login_count < 3);
		if(login_count == 3) {
			printf("The account has been locked\n");//khi do login_acc = Null -> core dump
			acc->status = 0;
			writeFile();
			return NULL;
		}
	}
	else{
		printf("Account does not exist\n");
		return NULL; // username is incorrect
	} 
}

void search(){
	char username[20];
	printf("---------Search\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc != NULL){
		printf("Username: %20s Status: %d\n", acc->username, acc->status);
	}
	else printf("Account does not exist\n");
}

node *signout(){
	char username[20];
	printf("---------Sign Out\n");
	printf("Username: "); scanf("%s", username);
	printf("\n");
	node *acc = find(username);
	if(acc == NULL){
		printf("Account does not exist\n");
		return NULL;
	}
	else return acc;
}

int choice(){
	int c = 0;
	printf("USER MANAGEMENT PROGRAM\n");
	printf("-----------------------------------\n");
	printf("1. Register\n");
	printf("2. Sign in\n");
	printf("3. Search\n");
	printf("4. Sign out\n");
	printf("Your choice (1-4, other to quit):\n"); scanf("%d", &c);
	return c;	
}

int main()
{
	openFile();
	printAll();

	int ch;
	//int i_login = 0;
	node *login_acc = NULL;
	node *signout_acc = NULL;
	do{
		ch = choice();
		//printf("%d\n", ch);
		switch(ch){
		case 1: registerAccount(); break;
		case 2: login_acc = signin(); break;
		case 3: {
			if(login_acc != NULL) {
				//printf("%s\n", login_acc->username);
				search();
			}
			else printf("Sign in, please!\n");
		} break;
		case 4: {
			if(login_acc == NULL) printf("Sign in, please!\n"); //check sign in
			else{
				signout_acc = signout();
				if(signout_acc)
				if(strcmp(signout_acc->username,login_acc->username) == 0){
					printf("Sign Out Successfull\n");
					login_acc = NULL;
				}
				else printf("Wrong Username!\n");
			}			
		} break;
	}
	}
	while(ch > 0 && ch < 5);
	

	return 0;
}