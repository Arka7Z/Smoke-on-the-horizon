#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct info{
  char name[10];
  char id[20];
  char password[7];
}info;


int main()
{ 
  int sign;
  printf("Please enter 1 to sign up or 0 to sign in to the Security System\n");
  scanf("%d",&sign);
  if (sign!=1 ||sign!=0)
    {
      printf("Please enter a valid input\n");
       scanf("%d",&sign);
    }

  char person;
  printf("Please enter 'M' if you are a manager or 'S' if you are a security personnel\n");
  scanf("%c",&person);
  if (person!='M' ||person!='S')
    {
      printf("Please enter a valid input\n");
       scanf("%c",&person);
    }
  if (person=='M')
    admin(sign);
  else 
    security(sign);
}


void admin(int sign)
{
  if (sign==1)
    signup();
  else admin_login();
}

void security(int sign)
{
  if (sign==1)
    signup();
  else security_login();
}

void signup()
{ 
  info tmp;
  printf("Welcome to the signup portal\n");
  //load the main file
  printf("Please enter your name\n");
  scanf("%s",tmp.name);
  prinf("Please enter a password\n");
  scanf("%s",tmp.password);
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);

  //append this to file
  //new func to check if record with the given id  already present or not
  
}


void security_login()
{
  info tmp;
  printf("Welcome to the sign in portal\n");
  //load the main file
  printf("Please enter your name\n");
  scanf("%s",tmp.name);
  prinf("Please enter your  password\n");
  scanf("%s",tmp.password);
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);
  //check validity
  if(valid(tmp)==1)
    {
      printf("You are successfully logged in\n");
      printf("Enter 0 to Log out \n 1 To view duty status for the next week \n 2 To view leave status or 3 To request for leave or to do over duty\n");
      int option;
      if(option==0)
	return;
      else if (option==1)
	{
	}
      else if (option==2)
	{
	}
      else if (option==3)
	{
	}
      else
	{
	}
      
    }

}
