#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//thao tac danh sach lien ket
char loggin[50];// luu tai khoan dang loggin
typedef struct node
{
	char user_name[50];
	char pass_word[50];
	int status;
	struct node *next;
}node;
node *head=NULL;
void insert(char username[50], char password[50],int status)
{
   struct node *new = (struct node*) malloc(sizeof(struct node));
   strcpy(new->user_name,username);
   strcpy(new->pass_word,password);
   new->status=status;
   new->next=head;
   head=new;
}
struct node* find(char key[50]){
   struct node* current = head;
   if(head == NULL)
	{
      return NULL;
   }
   while(strcmp(current->user_name,key)!=0){
      if(current->next == NULL){
         return NULL;
      }else {
         current = current->next;
      }
   }      
   return current;
}

struct node *search(char name[50],char pass[50]){
	struct node *current=head;
	if(head==NULL)
		return NULL;
	for(;current!=NULL;current=current->next){
		if(strcmp(current->user_name,name)==0 && strcmp(current->pass_word,pass)==0)
			return current;
	}      
   return NULL;

}

void print(){
	struct node* current = head;
	for(current=head;current!=NULL;current=current->next)
	{
		printf("%s %s %d\n",current->user_name,current->pass_word,current->status);
	}
	//printf("het \n");
}
//thao tac voi file 
int count_fp(FILE *fp){
	int c;
	int count=1;
	   do
   	{
      c = fgetc(fp);
      if( feof(fp) )
         break ;
     else
     	if(c=='\n')
     		count++;
   }while(1);
   return count;
}
void read_file(FILE *fp){
	int count=count_fp(fp);
	//printf("%d\n",count);
	rewind(fp);
	char user_name[50];
	char pass_word[50];
	int status;
	for(int i=0;i<count;i++){
		fscanf(fp,"%s %s %d",user_name,pass_word,&status);
		//printf("%s %s %d\n",user_name,pass_word,active );
		insert(user_name,pass_word,status);
		//printf("insert vao dau day ..\n");
	}
}
void wirte_file(FILE *fp){
	rewind(fp);
	struct node *current=head;
	for(;current!=NULL;current=current->next){
		fprintf(fp, "%s %s %d\n",current->user_name,current->pass_word,current->status );
	}
	printf("done in file \n");
}

//THAO TAC VOI CAC CHUC NANG 


void register_1(FILE *fp)
	{
		//NHAP THONG TIN TAI KHOAN THU BAN PHIM USERNAME VA PASSWORD,DA TON TAI =>LOI
		//LUU VAO fp ACCOUNT.TXT , THEM TRANG THAI HOAT DONG
		char new_user_name[50];char new_pass_word[50];
		__fpurge(stdin);
		printf("enter your username ?\n");
		gets(new_user_name); __fpurge(stdin);
		printf("enter your password ?\n");
		gets(new_pass_word); __fpurge(stdin);

		struct node *new=find(new_user_name);
		if(new!=NULL)
			printf("Account existed \n");
		else
		{	
			insert(new_user_name,new_pass_word,1);
			fprintf(fp, "\n%s %s 1",new_user_name,new_pass_word);
			rewind(fp);
			//printf("%s %s\n",new_user_name,new_pass_word );
			printf("Successful registration \n");
		}
	}

int sign_in(){
		char name_input[50];
		char pass_input[50];
		int count_pass=0;
		do {
		__fpurge(stdin);
		printf("enter your username ?\n");
		gets(name_input); __fpurge(stdin);
		printf("enter your password ?\n");
		gets(pass_input); __fpurge(stdin);


		struct node *check1=search(name_input,pass_input);
		struct node *check2=find(name_input);

		if(check2!=NULL&&check1==NULL)
			{printf("Password is incorrect\n");
				count_pass++;
			}
		if(check1!=NULL&&check1->status==1)
		{
			printf("Hello %s\n",name_input ); strcpy(loggin,name_input); break;
		}
		if(check1!=NULL&&check1->status==0)
		{ printf("Account is blocked\n"); break;}
		if(check2==NULL)
			{ printf(" Cannot find account\n"); break;}
		}while(count_pass<3);
		if(count_pass==3)
		{
			printf("Password is incorrect. Account is blocked!\n");
			struct node *new=find(name_input);
			if(new==NULL){
				printf("NULL\n");
			}
			else
			{	
				new->status=0;
				return 0;
				//gan lai toan bo file
			}
		}
		return 1;
}

void search3(){
	printf("Input your username !\n");
	char name_input[50];
	__fpurge(stdin); 
	gets(name_input);
	__fpurge(stdin);

	struct node *new =find(name_input);

	if(new->status==0)
	{
		printf("Account is blocked\n");
	}
	else if(new->status==1)
		printf("Account is active \n");
	else if(new==NULL)
		printf("Cannot find account\n");

}


void sign_out(){
		printf("Input your username !\n");
	char name_input[50];
	__fpurge(stdin); 
	gets(name_input);
	__fpurge(stdin);
	//printf("saaaaaaaaaa %s\n",name_input );
	struct node *new = find(name_input);
	printf("%s\n",name_input );
	if(new!=NULL)
	{
		if(strcmp(new->user_name,loggin)==0)
		{
			printf("Goodbye %s\n",name_input );
			strcpy(loggin,"");
		}
		else
			printf("You are not sign in\n");
	}
	else
		printf("Cannot find account\n");
}


//HAM MAIN
 int main(int argc, char const *argv[])
{	
	FILE *fp;
	FILE *fp2;
	if(fp==NULL)
		printf("open file error !\n");
	int select;
		fp=fopen("account.txt","r+");
		read_file(fp);
	do{ printf("MENU\n");
		printf("USER MANAGEMENT PROGRAM\n");
		printf("-----------------------------------------\n");
		printf("1. Register\n");
		printf("2. Sign in\n"); //cap nhat trang thai va sua file la xong
		printf("3. find\n");
		printf("4. Sign out\n");
		printf("Your choice (1-4,other to quit):\n");
		scanf("%d",&select);
		switch(select){
			case 1: 
			{
				register_1(fp);
				fclose(fp);
				break;

			}



			case 2:

			{	
				print();
				//printf("222222222\n");
				fclose(fp);
				int chek_pass=sign_in();
				
				if(chek_pass==0){
					fp2=fopen("account.txt","w+");
					wirte_file(fp2);
					fclose(fp2);
				}

				 break;
			}



			case 3:

			{
				search3(); break;
			}



			case 4:  sign_out(); break;
		}
	}while(select>=1&&select<=4);
	return 0;
}

//bay gio chi con sai 