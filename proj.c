#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define max_places 50
#define max_security 100

void main_input();

bool timetable[31],admin_signed_up=false;
int const_leaves=-1;               //-1->indicates not initialized
int fine=-1;
int places=-1;
int n_security=-1;
int signed_up=0;                    //stores number of security personal already signed up
int TIME=0;
int def_salary;
FILE *adm_file,*sec_file,*org_file;
int max_leaves;

typedef struct node{
char id[20];
}node;

typedef struct duty{
int place;
int start;
int end;
}duty;

typedef struct oduty{
    int place;
    int start;
    int end;
    int req;
}oduty;
typedef struct sec_info{
  char name[10];
  char id[20];
  char password[10];
  int leaves;
  int request;
  int req_date;
  bool approved;
  duty month1[16],month2[16];
  oduty over1[16],over2[16];

}sec_info;
sec_info person[max_security];

typedef struct admin_info{
  char name[10];
  char id[20];
  char password[10];
}adm_info;

bool next_seven(int time)
{   int i;
    for (i=1;i<=7 && (time+i<=30);i++)
        if (!timetable[i+time])
            return false;
    return true;
}


void check_for_next_seven()
{   //timetable priniting for debugging
    int i;
   /* for (i=1;i<=10;i++)
    {
        if (timetable[i])
            printf("done for %d\n",i);
        else
            printf("not done for %d\n",i);
    }*/
    bool check=next_seven(TIME);
    if (check==true)
        return;
    else
    {
        printf("Timetable yet to be prepared for next 7 days.Admin requested to do so.\nRedirected\n\n");
        admin_login();
        check_for_next_seven();
    }
}

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
        tmp1.over1[i]=tmp2.over1[i];
        tmp1.over2[i]=tmp2.over2[i];
    }
    return tmp1;
}
sec_info last_occurence(sec_info key)
{

        sec_file=fopen ("SecurityInfo.txt","r");
        sec_info tmp;
        sec_info input;
        while (fread (&input, sizeof(sec_info), 1, sec_file))
        {

            if (strcmp(input.id,key.id)==0)
                tmp=assign(tmp,input);
        }
        fclose(sec_file);

        return tmp;
}


sec_info initialize(sec_info tmp)
{
  tmp.leaves=const_leaves;
  tmp.request=0;
  tmp.approved=0;
  int i;
  for (i =0;i<=15;i++)
        tmp.month2[i].place=tmp.month1[i].place=0;
  for (i =0;i<=15;i++)
    {
        tmp.over1[i].place=tmp.over2[i].place=0;
        tmp.over1[i].req=tmp.over2[i].req=0;
    }


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
    //printf("entering check %s %s\n",tmp.id,tmp.password);
    sec_info input;
    while (fread (&input, sizeof(sec_info), 1, org_file))
    {
        //printf("check %s %s\n",input.id,input.password);
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
  fflush(stdin);
  sec_info tmp;
  printf("\n\n---------------------\nWelcome to the Security Personnel Signup Portal\n");

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


  strcpy(person[signed_up].id,tmp.id);

  sec_file=fopen ("SecurityInfo.txt","a");
  //printf("Writing to security file %s %s %s\n",tmp.id,tmp.password,tmp.name);

  int i2=fwrite(&tmp, sizeof(sec_info), 1,sec_file);
  //printf(" %d ints \n",i2);
  printf("You have been successfully signed up\n");



    fclose(sec_file);

  signed_up++;
  if (signed_up<n_security)
  {
      printf("----------\nAll security persons are yet to sign up\n.Please sign up\n-------------\n");
      sec_signup();
  }
}

void adm_signup()
{
  adm_info tmp;
  printf("\n\n------------------\nWelcome to the Admin Sign Up Portal\n");
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
             printf("\n---------------------\nPlease enter the following:\nThe number of places to be secured:");
             scanf("%d",&places);
             printf("The number of leaves allowed:");
             scanf("%d",&const_leaves);

             printf("The fine amount to be deducted on exceeding default leaves:");
             scanf("%d",&fine);

             printf("The number of security persons:");
             scanf("%d",&n_security);
             printf("The default salary:");
             scanf("%d",&def_salary);
             printf("------------------\n");
     // scanf("%d %d %d %d",&places,&const_leaves,&fine,&n_security);

  }
  if (adm_present(tmp)==true)
  {
      printf("Sorry ,an account with given credentials is already present\nPlease try again\n\n");
      adm_signup();
  }
  adm_file=fopen ("AdminInfo.txt","a+");
  fwrite (&tmp, sizeof(adm_info), 1,adm_file);


   printf("You have been successfully signed up\n");
   admin_signed_up=true;
   fclose(adm_file);

}
void check_overtime_request(sec_info tmp)
{
    tmp=last_occurence(tmp);
    printf("Please enter the date of your overtime request\n");
    int check_date;
    scanf("%d",&check_date);
    if (timetable[check_date]==false)
    {
        printf("Admin is yet to prepare timetable for %d\nPlease check again later\n----------------\n",check_date);
    }
    if (check_date<=15)
    {
        //printf("%d in check leave,%s\n",tmp.month1[check_date],tmp.id);
        if (timetable[check_date]==true && tmp.over1[check_date].req==-1)
            printf("Your over time request on %d has been approved\n",check_date);
        else if (timetable[check_date]==true && tmp.over1[check_date].req==0)
            printf("Sorry.Your overtime request on %d has been declined by the manager\n",check_date);
    }
    else
    {
        if (timetable[check_date]==true && tmp.over2[check_date-15].req==-1)
            printf("Your overtime request on %d has been approved\n",check_date);
        else if (timetable[check_date]==true && tmp.over2[check_date-15].req==0)
            printf("Sorry.Your overtime request on %d has been declined by the manager\n",check_date);
    }
}
void check_leave_request(sec_info tmp)
{
    tmp=last_occurence(tmp);
    printf("Please enter the date of your leave request\n");
    int check_date;
    scanf("%d",&check_date);
    if (timetable[check_date]==false)
    {
        printf("Admin is yet to prepare timetable for %d\nPlease check again later\n----------------\n",check_date);
    }
    if (check_date<=15)
    {
        //printf("%d in check leave,%s\n",tmp.month1[check_date],tmp.id);
        if (timetable[check_date]==true && tmp.month1[check_date].place==0)
            printf("Your leave request on %d has been approved\n",check_date);
        else if (timetable[check_date]==true && tmp.month1[check_date].place!=0)
            printf("Sorry.Your leave request on %d has been declined by the manager\n",check_date);
    }
    else
    {
        if (timetable[check_date]==true && tmp.month2[check_date-15].place==0)
            printf("Your leave request on %d has been approved\n",check_date);
        else if (timetable[check_date]==true && tmp.month2[check_date-15].place!=0)
            printf("Sorry.Your leave request on %d has been declined by the manager\n",check_date);
    }
}
void update_overtime(sec_info key,int date)
{
    sec_file=fopen ("SecurityInfo.txt","a+");
    sec_info tmp;
    sec_info input;
    char id[20];
    int count=0,i=0;
        for(i =0;i<n_security;i++)
    //while (fread (&input, sizeof(adm_info), 1, sec_file))
    {
        strcpy(id,person[i].id);
        input=last_occurence(person[i]);
        if (strcmp(input.id,key.id)==0 )
        {
            tmp=input;
            fclose(sec_file);
            if (date<=15)
            {
                tmp.over1[date].req=1;
            }
            else
            {
                tmp.over2[date-15].req=1;
            }
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
void update_request(sec_info key,int date)
{
    sec_file=fopen ("SecurityInfo.txt","a+");
    sec_info tmp;
    sec_info input;
    char id[20];
    int count=0,i=0;
        for(i =0;i<n_security;i++)
    //while (fread (&input, sizeof(adm_info), 1, sec_file))
    {
        strcpy(id,person[i].id);
        input=last_occurence(person[i]);
        if (strcmp(input.id,key.id)==0 && input.request==0)
        {
            tmp=input;
            fclose(sec_file);
            tmp.request=1;
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
      update_overtime(tmp,date);
      //check for leave request on that date ie for a vacancy
      //update timetable and number of leaves for that person accordingly
    }
    else request(tmp);

}

void view_duty(sec_info key)
{  //invoke file print for the next 7 days for the person and return

    check_for_next_seven();
     sec_file=fopen ("SecurityInfo.txt","a+");
    sec_info tmp;                      //for storing the last entry
    sec_info input;
    while (fread (&input, sizeof(sec_info), 1, sec_file))
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
            if (tmp.month1[f_day].place==0)
                printf("You don't have any duty on %d\n",f_day);
            else
                printf("Duty at %d on %d from %d Hours to %d Hours\n",tmp.month1[f_day].place,f_day,tmp.month1[f_day].start,tmp.month1[f_day].end);
            if (tmp.over1[f_day].req==-1)
                printf("You have been approved overtime at %d on %d from %d to %d Hours\n",tmp.over1[f_day].place,f_day,tmp.over1[f_day].start,tmp.over1[f_day].end);
        }
     else
        {   if (f_day-15<=15)
          {
             if (tmp.month2[f_day-15].place==0)
                printf("You don't have any duty on %d\n",f_day-15);
            else
                printf("Duty at %d on %d from %d Hours to %d Hours\n",tmp.month1[f_day-15].place,f_day-15,tmp.month2[f_day-15].start,tmp.month2[f_day-15].end);
             if (tmp.over2[f_day-15].req==-1)
                printf("You have been approved overtime at %d on %d from %d to %d Hours\n",tmp.over1[f_day-15].place,f_day,tmp.over1[f_day-15].start,tmp.over1[f_day-15].end);
          }
        }
    }
    fclose(sec_file);
    printf("Thank You!\n-----------------\n");

}

void view_leave(sec_info key)                               //change ret type into int,will help in request()
{
    if (!admin_signed_up)
    {
        printf("Admin is yet to initialize system\n.Redirected to main menu\n-----------------\n");
        main_input();
    }
    sec_file=fopen ("SecurityInfo.txt","a+");
    sec_info tmp;                      //for storing the last entry
    sec_info input;
    while (fread (&input, sizeof(sec_info), 1, sec_file))
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
  printf("\n\n------------------\nWelcome to the Security Sign In Portal\n");
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
      printf("Enter 0 to Log out \n1 To view duty status for the next week \n2 To view leave status \n3 To request for leave or to do over duty\n4 To check status of leave request\n5 To check overtime request\n");
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
        else if (option==4)
        {
            check_leave_request(tmp);
        }
      else if (option==5)
      {
          check_overtime_request(tmp);
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

void check_status_by_admin()
{
    fflush(stdin);
    char identity[10];
    printf("Enter the ID of the security person you want to check status for: ");
    scanf("%s",identity);
    sec_info tmp;
    tmp=initialize(tmp);
    strcpy(tmp.id,identity);
    tmp=last_occurence(tmp);
    if (TIME!=0)
    {

    if (TIME<=15)
    {
        if (tmp.month1[TIME].place==0)
            printf("Sir,%s is on an approved leave\n",identity);
        else
            printf("%s is on duty at %d\n",identity,tmp.month1[TIME].place);
    }
    else
    {
      if (tmp.month2[TIME-15].place==0)
            printf("Sir,%s is on an approved leave\n",identity);
        else
            printf("%s is on duty at %d\n",identity,tmp.month2[TIME-16].place);
    }
    }
    printf("%s has %d leaves left \n-------------------------\n",identity,tmp.leaves);

}

void admin_login()
{
  adm_info tmp;
  fflush(stdin);
  printf("\n\n---------------\nWelcome to the Admin Sign In portal\n");
  //load the main file
  char stray;
  printf("Please enter your insitude ID number\n");
  scanf("%s",tmp.id);
  scanf("%c",&stray);
  printf("Please enter your  password\n");
  scanf("%s",tmp.password);


  //check validity
  if(adm_valid(tmp)==true)
  {
      int tmp;
      printf("You are successfully logged in,Sir\n");
      printf("Enter preferences:\n1 for making timetable\n2 Check status for a security person\n3 EXIT \n");
      scanf("%d",&tmp);
      if (tmp==1)
      {
          int date;
          printf("Please enter the date you would like to make time table for in DD form:\n");
          scanf("%d",&date);
          make_timetable(date);
          timetable[date]=true;
      }
      if (tmp==3)
        return;
      if (tmp==2)
        check_status_by_admin();

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
    while (fread (&input, sizeof(sec_info), 1, sec_file))
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
    sec_info approved[max_security];
    int count=0;
    while (fread (&input, sizeof(sec_info), 1, sec_file))
    {
        if (input.request==1 && input.req_date==date && input.approved==false)
        {
            approved[count]=assign(tmp,input);
            approved[count].approved=true;
            approved[count].request=1;
            approved[count].req_date=date;                 //let it remain that way helps in query by sec personnel
            if (date<=15)
                approved[count].month1[date].place=0;
            else
                approved[count].month2[date-15].place=0;
            approved[count].leaves-=1;
            count++;
        }
    }
    fclose(sec_file);
    sec_file=fopen ("SecurityInfo.txt","a+");
    int i_count=0;
    for(i_count=0;i_count<=count;i_count++)
    {
        sec_info tmp;
        tmp=approved[i_count];
        //printf("writing approval for %s\n",tmp.id,tmp.req_date);
        int write=fwrite (&(approved[i_count]), sizeof(sec_info), 1,sec_file);
        //printf("%d is returned by fwrite\n",write);
    }
    fclose(sec_file);


}


bool check_all_places(int place_array[])
{   int i;
    for( i=1;i<places+1;i++)
        if (!place_array[i])
            return false;
    return true;

}
void make_timetable(int date)
{
    if (signed_up<n_security)
    {
        printf("Sorry Sir.But all the security personnel are yet to sign up\nYou are redirected to the main menu\n--------------\n");
        main_input();
    }
    int places_assigned=0,feasible_leaves=(n_security-places),appr_count=0,notappr_count=0;
    int n_requested=count_requests(date);
    //printf("Number of leaves requested on %d is %d\n",date,n_requested);
    //printf("Feasible is %d\n",feasible_leaves);
    sec_info approved[n_security],not_approved[n_security];
    if (n_requested<=feasible_leaves)
    {
        printf("Sir,all the leave requested are feasible to be approved\n\nApproving them\nMaking necessary changes\n");
        approve_all(date);

    }

    else
    {   //get them approved individually
        org_file=fopen ("OrgSecurity.txt","a+");
        sec_info tmp;
        sec_info input;
        char id[20];
        int count=0,i=0;
        for(i =0;i<n_security;i++)
        //while (fread (&input, sizeof(sec_info), 1, org_file))
        {    strcpy(id,person[i].id);
                sec_info tmp2;
                tmp2=assign(tmp2,person[i]);
            input=last_occurence(tmp2);


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
                        input.leaves--;
                        if (date<=15)
                        {
                            input.month1[date].place=0;
                        }
                        else
                        {
                            input.month2[date-15].place=0;
                        }
                        approved[appr_count++]=input;
                        //printf("Leave approved for %s on %d\n",approved[appr_count-1].id,date);
                    }
                else
                    {
                        input.approved=false;
                        if (date<=15)
                        {
                            input.month1[date].place=100;
                        }
                        else
                        {
                            input.month2[date-15].place=100;
                        }

                        not_approved[notappr_count++]=input;
                    }

            }
        }

        fclose(org_file);
         if (appr_count>feasible_leaves)
            {
                printf("Error:Deficit of personnel.Please try again\n");
                make_timetable(date);
            }
    }
    //printf("Out of if\n");
    sec_file=fopen ("SecurityInfo.txt","a+");
    int i_count=0;
    for(i_count=0;i_count<appr_count;i_count++)
    {
        int write=fwrite (&(approved[i_count]), sizeof(sec_info), 1,sec_file);
        //printf("Leave writing  for %s on %d ,%d returned by write\n",approved[appr_count-1].id,date,write);

    }
    for(i_count=0;i_count<notappr_count;i_count++)
    {
        fwrite (&(not_approved[i_count]), sizeof(sec_info), 1,sec_file);

    }
    fclose(sec_file);

     //assigning final places of duty

    sec_info input,tmp,f_record[max_security];
     int duty;
    int count=0;
    int place_array[max_places+1]={0};
    char id[20];
    int i=0;

        for(i =0;i<n_security;i++)
    {
        sec_info tmp2=assign(tmp2,person[i]);
        tmp=last_occurence(person[i]);


        if (tmp.request==0 || (tmp.approved==false /*&& tmp.request==1 && tmp.req_date==date*/))
        {
            int s,e;
            printf("Enter the place of duty for %s:",tmp.id);
            scanf("%d",&duty);
            place_array[duty]=1;
            printf("Enter the start time of the duty in 24 hours format in HH form\n");
            scanf("%d",&s);
            printf("Enter the end time of the duty in a similar format\n");
            scanf("%d",&e);
            if (date<=15)
            {
               tmp.month1[date].place=duty;
               tmp.month1[date].start=s;
               tmp.month1[date].end=e;
               if (tmp.over1[date].req==1)
               {
                   printf("%s has requested for overtime on this day\n.Enter -1 to approve 0 to decline\n",tmp.id);
                   int over,os,oe,oplace;
                   scanf("%d",&over);
                   if (over==-1)
                   {
                      tmp.over1[date].req=-1;
                       printf("Enter the place of duty for %s:",tmp.id);
                      scanf("%d",&oplace);
                      printf("Enter the start time of the over time in 24 hours format in HH form\n");
                      scanf("%d",&os);
                      printf("Enter the end time of the duty in a similar format\n");
                      scanf("%d",&oe);
                      if ((os>=s && oe<=e)||(s>=os && e<=oe))
                      {
                          printf("Error in assigning duty time!Please try again\n------------------\n");
                          make_timetable(date);
                      }
                      tmp.over1[date].place=oplace;
                      tmp.over1[date].start=os;
                      tmp.over1[date].end=oe;
                      (tmp.leaves)++;

                   }
                   else
                   {
                       tmp.over1[date].req=0;
                   }

               }
               f_record[count++]=tmp;
               //printf("duty given is %d\n",f_record[count-1].month1[date]);
            }
            else
            {
               tmp.month2[date-15].place=duty;
               tmp.month2[date].start=s;
               tmp.month2[date].end=e;
               f_record[count++]=tmp;
               if (tmp.over1[date].req==1)
               {
                   printf("%s has requested for overtime on this day\n.Enter -1 to approve 0 to decline\n",tmp.id);
                   int over,os,oe,oplace;
                   scanf("%d",&over);
                   if (over==-1)
                   {
                      tmp.over2[date-15].req=-1;
                      (tmp.leaves)++;
                       printf("Enter the place of duty for %s:",tmp.id);
                      scanf("%d",&oplace);
                      printf("Enter the start time of the over time in 24 hours format in HH form\n");
                      scanf("%d",&os);
                      printf("Enter the end time of the duty in a similar format\n");
                      scanf("%d",&oe);
                      if ((os>=s && oe<=e)||(s>=os && e<=oe))
                      {
                          printf("Error in assigning duty time!Please try again\n------------------\n");
                          make_timetable(date);
                      }
                      tmp.over2[date-15].place=oplace;
                      tmp.over2[date-15].start=os;
                      tmp.over2[date-15].end=oe;
                   }
                   else
                   {
                       tmp.over2[date-15].req=0;
                   }

               }
            }

        }
        else if(tmp.request==1 && tmp.approved==true)
        {
             if (date<=15)
            {
               tmp.month1[date].place=0;
               f_record[count++]=tmp;
            }
            else
            {
               tmp.month2[date-15].place=0;
               f_record[count++]=tmp;
            }
        }
        else
            printf("else in for\n");
    }


    if (!check_all_places(place_array))
    {
        printf("All places have not been assigned properly\nPlease try again\n\n");
        make_timetable(date);
    }
    //save final changes to the file for day 'day'

    sec_file=fopen("SecurityInfo.txt","a+");
    for(i_count=0;i_count<count;i_count++)
    {
        //printf("Writing to file, %d for %s on %d",f_record[i_count].month1[date],f_record[i_count].id,date);
        int i=fwrite (&(f_record[i_count]), sizeof(sec_info), 1,sec_file);
        //printf("Write returns %d\n",i);
    }
    fclose(sec_file);
    timetable[date]=true;
}


void main_input()
{
         printf("----------------\nDay %d\nMain Menu\n",TIME);
        printf("Please enter -1 as a preference if no operations are left to be performed for today\n---------------------\n");
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
        printf("Enter preferences:\nM for manager \nS for security personnel\n");
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
           /* if ((!next_seven(TIME))&&(n_security==-1)&&(person!='M')  );
            {
                if (signed_up!=0)
                {
                    printf("n security :%d  TIme :%d \n ",n_security,TIME);
                    printf("Admin needs to login and make time table for the next seven days\n\n");
                    admin_login();
                }
            }*/


    }

}


void salary()
{
    printf("------------------\nWelcome to the salary portal\n");

    sec_info tmp;
    int i;
    for(i=0;i<n_security;i++)
    {
        tmp=last_occurence(person[i]);
        int exceed=tmp.leaves>0?0:(-1*tmp.leaves);
        int sal=def_salary-(exceed*fine);
        printf("Salary for %s is Rs. %d\n",tmp.id,sal);
    }
}

int main()
{ int time_counter=0;
  int i;
  printf("--------------------------------------\nINSTRUCTIONS:Security personnels are requested to submit requests for leave or over time for the next 7 days in advance\n----------------------------------\n");
  for(i=0;i<31;i++)                         //initializing timetable to all false i.e not prepared
    timetable[i]=false;
  for(time_counter=0;TIME<=30;TIME++)
  {
      main_input();
      if (signed_up==0)
      {
          printf("All users need to sign up\n-------------\n");
          sec_signup();

      }
      if (!admin_signed_up)
      {
          printf("Admin should Sign Up\n");
          adm_signup();
      }
      check_for_next_seven();
  }
  salary();
  return 0;
}




