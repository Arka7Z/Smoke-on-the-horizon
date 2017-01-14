#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define max_places 50
#define max_security 100

bool timetable[31];
int const_leaves=-1;               //-1->indicates not initialized
int fine=-1;
int places=-1;
int n_security=-1;
int signed_up=0;                    //stores number of security personal already signed up
int TIME=0;
FILE *adm_file,*sec_file,*org_file;
int max_leaves;

typedef struct sec_info{
  char name[10];
  char id[20];
  char password[10];
  int leaves;
  int request;
  int req_date;
  bool approved;
  int month1[16],month2[16];

}sec_info;

typedef struct admin_info{
  char name[10];
  char id[20];
  char password[10];
}adm_info;

sec_info assign(sec_info tmp1,sec_info tmp2)
{   strcpy(tmp1.name,tmp2.name);
    strcpy(tmp1.id,tmp2.id);
    strcpy(tmp1.password,tmp2.password);
    tmp1.leaves=tmp2.leaves;
    tmp1.request=tmp2.request;
    tmp1.approved=tmp2.approved;
    tmp1.req_date=tmp2.req_date;
    int i;
    for (i =0;i<=15;i++)
    {
        tmp1.month1[i]=tmp2.month1[i];
        tmp1.month2[i]=tmp2.month2[i];
    }
    return tmp1;
}
sec_info last_occurence(sec_info key)
{


        sec_file=fopen ("SecurityInfo.txt","a+");
        sec_info tmp;
        sec_info input;
        while (fread (&input, sizeof(adm_info), 1, sec_file))
        {
            if (input.id==key.id)
                tmp=assign(tmp,input);
        }
        return tmp;
}


sec_info initialize(sec_info tmp)
{
  tmp.leaves=const_leaves;
  tmp.request=0;
  tmp.approved=0;
  int i;
  for (i =0;i<=15;i++)
    tmp.month2[i]=tmp.month1[i]=0;

  return tmp;
}

void admin(int sign)
{
  if (sign==1)
    adm_signup();
  else admin_login();
}

void security(int sign)
{  if (const_leaves==-1 || fine==-1 || places==-1||n_security==-1)
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
        if (strcmp(input.id,tmp.id)==0 && strcmp(input.password,tmp.password)==0)
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
        if (strcmp(input.id,tmp.id)==0 )
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
    org_file=fopen ("SecurityInfo.txt","r");
    printf("entering check %s %s\n",tmp.id,tmp.password);
    sec_info input;
    while (fread (&input, sizeof(sec_info), 1, org_file))
    {
        printf("check %s %s\n",input.id,input.password);
        if (strcmp(input.id,tmp.id)==0 && strcmp(input.password,tmp.password)==0)
        {
           fclose(adm_file);
           return true;
        }
    }
   fclose(org_file);
   return false;

}

bool sec_present(sec_info tmp)
{
    sec_file=fopen ("SecurityInfo.txt","r");
    sec_info input;
    while (fread (&input, sizeof(sec_info), 1, sec_file))
    {
        if (!strcmp(input.id,tmp.id) )
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
  sec_info tmp2;
  tmp2=initialize(tmp2);
  strcpy(tmp2.id,tmp.id);
  strcpy(tmp2.password,tmp.password);
  strcpy(tmp2.name,tmp.name);
  tmp=assign(tmp,tmp2);


  if (sec_present(tmp)==true)
  {
      printf("Sorry ,an account with given credentials is already present\nPlease try again\n\n");
      sec_signup();
  }
  tmp2=assign(tmp2,tmp);
  org_file==fopen("Original.txt","a+");
  fwrite (&tmp2, sizeof(sec_info), 1,org_file);

  sec_file=fopen ("SecurityInfo.txt","a+");

  fwrite (&tmp, sizeof(sec_info), 1,sec_file);
  printf("You have been successfully signed up\n");


  fclose(org_file);
    fclose(sec_file);

  signed_up++;
  if (signed_up<n_security)
  {
      printf("All security persons are yet to sign up\n.Please sign up\n\n");
      sec_signup();
  }
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

  if (const_leaves==-1 || fine==-1 || places==-1 || n_security==-1)
  {
      printf("Please enter the number of places to be secured,the number of leaves allowed ,the fine amount to be deducted respectively and the number of security persons\n");
      scanf("%d %d %d %d",&places,&const_leaves,&fine,&n_security);

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

void update_request(sec_info key,int date)
{
    sec_file=fopen ("SecurityInfo.txt","a+");
    sec_info tmp;
    sec_info input;
    while (fread (&input, sizeof(adm_info), 1, sec_file))
    {
        input=last_occurence(input);
        if (strcmp(input.id,key.id)==0 && input.request==false)
        {
            tmp=input;
            fclose(sec_file);
            tmp.request=true;
            tmp.req_date=date;
            sec_file=fopen("SecurityInfo.txt","a+");
            fwrite (&tmp, sizeof(sec_info), 1,sec_file);
            printf("Request Application updated successfully\n");
            fclose(sec_file);
            return;
        }
    }
    printf("Error!Please try again\n");
    security_login();


}




void request(sec_info tmp)
{
    printf("REQUEST PORTAL\n");
    printf("Enter:\n1 to request for a leave.\n 0 to request to do overtime.\n");
    int req;
    scanf("%d",&req);
    if (req==1)                     //leave
    {
      printf("Enter request date in the form DD\n");
      int date;
      scanf("%d",&date);
      update_request(tmp,date);
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

void view_duty(sec_info key)
{  //invoke file print for the next 7 days for the person and return
     sec_file=fopen ("SecurityInfo.txt","a+");
    sec_info tmp;                      //for storing the last entry
    sec_info input;
    while (fread (&input, sizeof(adm_info), 1, sec_file))
    {
        if (strcmp(input.id,key.id)==0)
            tmp=input;
    }
    //print duty
    printf("Your duty schedule for the next 7 days is as follows:\n");
    int day=0;
    for(day=1;day<=7;day++)
    {
     int f_day=TIME+day;
     if(f_day<=15)
        {
            if (tmp.month1[f_day]=0)
                printf("You don't have any duty on %d\n",f_day);
            else
                printf("Duty on %d at %d\n",tmp.month1[f_day],f_day);
        }
     else
        {   if (f_day-15<=15)
          {
             if (tmp.month2[f_day-15]=0)
                printf("You don't have any duty on %d\n",f_day-15);
            else
                printf("Duty on %d at %d\n",tmp.month1[f_day-15],f_day-15);
          }
        }
    }
    fclose(sec_file);
    printf("Thank You!\n\n");

}

void view_leave(sec_info key)                               //change ret type into int,will help in request()
{
        sec_file=fopen ("SecurityInfo.txt","a+");
    sec_info tmp;                      //for storing the last entry
    sec_info input;
    while (fread (&input, sizeof(adm_info), 1, sec_file))
    {
        if (strcmp(input.id,key.id)==0)
            tmp=input;
    } //just numerical quantity
    printf("The number of leaves you can avail for this month: %d",max_leaves-tmp.leaves);
    fclose(sec_file);

}



void security_login()
{
  sec_info tmp;
  fflush(stdin);
  printf("\nWelcome to the sign in portal\n");
  //load the main file
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);
  char stray;
  scanf("%c",&stray);
  printf("Please enter your  password\n");
  scanf("%s",tmp.password);

  printf("%s %s \n",tmp.id,tmp.password);

  //check validity
  if(sec_valid(tmp)==true)
    {
      printf("You are successfully logged in\n");
      printf("Enter 0 to Log out \n1 To view duty status for the next week \n2 To view leave status \n3 To request for leave or to do over duty\n");
      int option;
      scanf("%d",&option);
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
      int tmp;
      printf("You are successfully logged in,Sir\n");
      printf("Enter preferences:\n1 for making timetable\n2 Exit\n ");
      scanf("%d",&tmp);
      if (tmp==1)
      {
          int date;
          printf("Please enter the date you would like to make time table for in DD form:\n");
          scanf("%d",&date);
          make_timetable(date);
          timetable[date]=true;
      }
      if (tmp==2)
        return;

  }
  else
    {
        printf("The input credentials are incorrect\n");
        admin_login();
    }
}

int count_requests(int date)
{
    sec_file=fopen ("SecurityInfo.txt","r");
    sec_info input;
    int count=0;
    while (fread (&input, sizeof(adm_info), 1, adm_file))
    {
        if (input.request==1 && input.req_date==date)
                count++;
    }
    return count;

}
void approve_all(int date)
{
    sec_file=fopen ("SecurityInfo.txt","r");
    sec_info tmp;
    sec_info input;
    sec_info approved[n_security-places];
    int count=0;
    while (fread (&input, sizeof(adm_info), 1, sec_file))
    {
        if (input.request==1 && input.req_date==date && input.approved==false)
        {
            approved[count]=assign(tmp,input);
            approved[count].approved=true;
            approved[count].request=false;
            approved[count].req_date=date;                 //let it remain that way helps in query by sec personnel
            if (date<=15)
                approved[count].month1[date]=0;
            else
                approved[count].month2[date-14]=0;
            approved[count].leaves+=1;
            count++;
        }
    }
    fclose(sec_file);
    sec_file=fopen ("SecurityInfo.txt","a+");
    int i_count=0;
    for(i_count=0;i_count<=count;i_count++)
    {
        fwrite (&(approved[i_count]), sizeof(sec_info), 1,sec_file);
    }
    fclose(sec_file);


}


bool check_all_places(int place_array[])
{   int i;
    for( i=0;i<places+1;i++)
        if (!place_array[i])
            return false;
    return true;

}
void make_timetable(int date)
{   int places_assigned=0,feasible_leaves=(n_security-places),appr_count=0,notappr_count=0;
    int n_requested=count_requests(date);
    sec_info approved[n_security],not_approved[n_security];
    if (n_requested<=feasible_leaves)
    {
        printf("Sir,all the leave requested are feasible to be approved\n\nApproving them\nMaking necessary changes\n");
        approve_all(date);

    }
    else
    {   //get them approved individually
        org_file=fopen ("Original.txt","a+");
        sec_info tmp;
        sec_info input;
        int count=0;
        while (fread (&input, sizeof(sec_info), 1, org_file))
        {
            input=last_occurence(input);
            if (approved>feasible_leaves)
            {
                printf("Error:Deficit of personnel.Please try again\n");
                make_timetable(date);
            }
            if (input.request==true && input.req_date==date)
            {
                fflush(stdin);
                printf("Sir,do you want to approve leave for %s on %d ?\n",input.id,date);
                printf("Enter:\n'Y' to approve.\n'N' to decline the request.\n");

                char in;
                scanf("%c",&in);
                if (in=='Y')
                    {
                        input.approved=true;
                        approved[appr_count++]=input;
                    }
                else
                    {
                        input.approved=false;
                        not_approved[notappr_count++]=input;
                    }

            }
        }
        fclose(org_file);
    }
    sec_file=fopen ("SecurityInfo.txt","a+");
    int i_count=0;
    for(i_count=0;i_count<appr_count;i_count++)
    {
        fwrite (&(approved[i_count]), sizeof(sec_info), 1,sec_file);
    }
    for(i_count=0;i_count<notappr_count;i_count++)
    {
        fwrite (&(not_approved[i_count]), sizeof(sec_info), 1,sec_file);
    }
    fclose(sec_file);

     //assigning final places of duty
    org_file=fopen("Original.txt","r");
    sec_info input,tmp,f_record[max_security];
     int duty;
    int count=0;
    int place_array[max_places+1]={0};
    while (fread (&input, sizeof(adm_info), 1, org_file))
    {   tmp=last_occurence(input);
        if (tmp.request==false || (tmp.approved==false && tmp.request==true && tmp.req_date==date))
        {

            printf("Enter the place of duty for %s:",input.id);
            scanf("%d",&duty);
            place_array[duty]=1;
            if (date<=15)
            {
               tmp.month1[date]=duty;
               f_record[count++]=input;
            }
            else
            {
               tmp.month2[date-15]=duty;
               f_record[count++]=input;
            }
        }
        else if(input.request==true && input.approved==true)
        {
             if (date<=15)
            {
               tmp.month1[date]=0;
               f_record[count++]=input;
            }
            else
            {
               tmp.month2[date-15]=0;
               f_record[count++]=input;
            }
        }
        else
            ;
    }
    fclose(org_file);
    if (!check_all_places(place_array))
    {
        printf("All places have not been assigned properly\nPlease try again\n\n");
        make_timetable(date);
    }
    //save final changes to the file for day 'day'

    sec_file=fopen("SecurityInfo.txt","a+");
    for(i_count=0;i_count<count;count++)
    {
        fwrite (&(f_record[i_count]), sizeof(sec_info), 1,sec_file);
    }
    fclose(sec_file);

}

bool next_seven(int TIME)
{   int i;
    for (i=1;i<=7 && (TIME+i<=30);i++)
        if (!timetable[i+TIME])
            return false;
    return true;
}
int main()
{ int time_counter=0;
  for(time_counter=0;TIME<=30;time_counter++,TIME++)
  {     printf("Day %d",TIME);
        printf("Please enter -1 as a preference if no operations are left to be performed for today\n\n");
        while(1)
    {

        int sign;
        printf("Enter preference option from the following:\n1.Sign up\n2.Sign In\n");
        scanf("%d",&sign);
        if (sign!=1 && sign!=2 && sign!=-1)
            {
                printf("Please enter a valid input\n");
                continue;
            }
        if (sign==-1)
            break;

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
            if ((!next_seven(TIME))&&(n_security==-1))
            {
                printf("Admin needs to login and make time table for the next seven days\n\n");
                admin_login();
            }
    }
  }
}




