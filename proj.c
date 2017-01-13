#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int available[31];                 //initially fill all of them to number of distinct places,subtract during leave approval,add during overtime request,keep updating
bool requested[31];
int const_leaves=-1;               //-1->indicates not initialized
int fine=-1;
int places=-1;
int time=0;
FILE *adm_file,*sec_file;

typedef struct sec_info{
  char name[10];
  char id[20];
  char password[10];
  int leaves;
  int request;
  int req_date;
  bool approved;
  int d0,d1,d2,d3,d4,d5,d6;
}sec_info;

typedef struct admin_info{
  char name[10];
  char id[20];
  char password[10];
}adm_info;

sec_info initialize(sec_info tmp)
{
  tmp.leaves=const_leaves;
  tmp.request=0;
  tmp.approved=0;
  tmp.d0=0;
  tmp.d1=0;
  tmp.d2=0;
  tmp.d3=0;
  tmp.d4=0;
  tmp.d5=0;
  tmp.d6=0;
  return tmp;
}

void admin(int sign)
{
  if (sign==1)
    adm_signup();
  else admin_login();
}

void security(int sign)
{  if (const_leaves==-1 || fine==-1 || places==-1)
    {
        printf("Admin is yet to initialize the sytemm.\nPlease wait while you are redirected to admin signup page\n\n");
        admin(1);
    }
  if (sign==1)
    sec_signup();
  else
    security_login();
}

bool adm_valid(adm_info tmp)
{   adm_file=fopen ("AdminInfo.txt","r");
    adm_info input;
    while (fread (&input, sizeof(adm_info), 1, adm_file))
    {
        if (input.id==tmp.id && input.password==tmp.password)
        {
           fclose(adm_file);
           return true;
        }
    }
   fclose(adm_file);
   return false;
}
bool adm_present(adm_info tmp)
{   adm_file=fopen ("AdminInfo.txt","r");
    adm_info input;
    while (fread (&input, sizeof(adm_info), 1, adm_file))
    {
        if (input.id==tmp.id )
        {
           fclose(adm_file);
           return true;
        }
    }
   fclose(adm_file);
   return false;
}
bool sec_valid(sec_info tmp)
{
    sec_file=fopen ("SecurityInfo.txt","r");
    sec_info input;
    while (fread (&input, sizeof(sec_info), 1, sec_file))
    {
        if (input.id==tmp.id && input.password==tmp.password)
        {
           fclose(adm_file);
           return true;
        }
    }
   fclose(sec_file);
   return false;

}

bool sec_present(sec_info tmp)
{
    sec_file=fopen ("SecurityInfo.txt","r");
    sec_info input;
    while (fread (&input, sizeof(sec_info), 1, sec_file))
    {
        if (input.id==tmp.id )
        {
           fclose(adm_file);
           return true;
        }
    }
   fclose(sec_file);
   return false;

}

void sec_signup()
{
  sec_info tmp;
  printf("Welcome to the signup portal\n");

  printf("Please enter your name\n");
  scanf("%s",tmp.name);
  char stray;
  scanf("%c",&stray);
  printf("Please enter a password\n");
  scanf("%s",tmp.password);
  scanf("%c",&stray);
  printf("Please reenter your password\n");
  char ps2[10];
  scanf("%s",ps2);
  scanf("%c",&stray);
  if(strcmp(ps2,tmp.password)!=0)
  {
      printf("Please try again\nPasswords don't match\n\n\n");
      sec_signup();
  }
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);
  tmp=initialize(tmp);


  if (sec_present(tmp)==true)
  {
      printf("Sorry ,an account with given credentials is already present\nPlease try again\n\n");
      sec_signup();
  }
  sec_file=fopen ("SecurityInfo.txt","a+");
  fwrite (&tmp, sizeof(sec_info), 1,adm_file);
  printf("You have been successfully signed up\n");
  fclose(sec_file);



}

void adm_signup()
{
  adm_info tmp;
  printf("Welcome to the signup portal\n");
  //load the main file
  printf("Please enter your name\n");
  scanf("%s",tmp.name);
  char stray;
  scanf("%c",&stray);
  printf("Please enter a password\n");
  scanf("%s",tmp.password);
  scanf("%c",&stray);
  printf("Please reenter your password\n");
  char ps2[10];
  scanf("%s",ps2);
  scanf("%c",&stray);
  if(strcmp(ps2,tmp.password)!=0)
  {
      printf("Please try again\nPasswords don't match\n\n\n");
      adm_signup();
  }
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);

  if (const_leaves==-1 || fine==-1 || places==-1)
  {
      printf("Please enter the number of places to be secured,the number of leaves allowed and the fine amount to be deducted respectively\n");
      scanf("%d %d %d",&places,&const_leaves,&fine);

  }
  if (adm_present(tmp)==true)
  {
      printf("Sorry ,an account with given credentials is already present\nPlease try again\n\n");
      adm_signup();
  }
  adm_file=fopen ("AdminInfo.txt","a+");
  fwrite (&tmp, sizeof(adm_info), 1,adm_file);


   printf("You have been successfully signed up\n");
   fclose(adm_file);

}





void request(sec_info tmp)
{
    printf("REQUEST PORTAL\n");
    printf("Enter 1 to request for a leave or 0 to request to do overtime\n");
    int req;
    scanf("%d",&req);
    if (req==1)                     //leave
    {
      //check feasibility for tmp wrt to number of leaves
      printf("Enter request date in the form DD\n");
      int date;
      scanf("%d",&date);
      //check feasibilty on that date
      //output date,change number of leaves and timetable file accordingly
    }
    else if(req==0)                 //overtime
    {
      printf("Enter request date in the form DD\n");
      int date;
      scanf("%d",&date);
      //check for leave request on that date ie for a vacancy
      //update timetable and number of leaves for that person accordingly
    }
    else request(tmp);

}

void view_duty(sec_info tmp)
{  //invoke file print for the next 7 days for the person and return

}

void view_leave(sec_info tmp)                               //change ret type into int,will help in request()
{
        //just numerical quantity
}



void security_login()
{
  sec_info tmp;
  printf("Welcome to the sign in portal\n");
  //load the main file
  printf("Please enter your name\n");
  scanf("%s",tmp.name);
  printf("Please enter your  password\n");
  scanf("%s",tmp.password);
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);
  //check validity
  if(sec_valid(tmp)==true)
    {
      printf("You are successfully logged in\n");
      printf("Enter 0 to Log out \n1 To view duty status for the next week \n2 To view leave status \n3 To request for leave or to do over duty\n");
      int option;
      if(option==0)
        return;                 //log out
      else if (option==1)
	    {
            view_duty(tmp);
        }
      else if (option==2)
        {
            view_leave(tmp);
        }
      else if (option==3)
        {
            request(tmp);
        }
      else
        {
            printf("Invalid input\n");
            security_login();
        }

    }
    else
    {
        printf("The input credentials are incorrect\n");
        security_login();
    }

}

void admin_login()
{
  adm_info tmp;
  printf("Welcome to the sign in portal\n");
  //load the main file
  char stray;
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);
  printf("Please enter your  password\n");
  scanf("%s",tmp.password);
  scanf("%c",&stray);

  //check validity
  if(adm_valid(tmp)==true)
  {
      printf("You are successfully logged in,Sir\n");
      //create routine for upcoming 7 days
      //check the leave request as well as availability and update all the files
      //approve/decline request-----monitor
      //log out

  }
  else
    {
        printf("The input credentials are incorrect\n");
        admin_login();
    }
}

int main()
{
  int sign;
  printf("Enter preference option from the following:\n1.Sign up\n2.Sign In\n");
  scanf("%d",&sign);
  if (sign!=1 && sign!=0)
    {
      printf("Please enter a valid input\n");
       scanf("%d",&sign);
    }

  char person;
  char tmp;
  scanf("%c",&tmp);
  printf("Enter preferences:\n'M' if you are a manager \n 'S' if you are a security personnel\n");
  scanf("%c",&person);
  if (person!='M' && person!='S')
    {
        printf("Please enter a valid input\n");
        scanf("%c",&person);
    }
  else
    {
        if (person=='M')
            admin(sign);
        else
            security(sign);
    }
}




