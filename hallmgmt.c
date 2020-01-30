#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define KCYN  "\x1B[36m"
#define KMAG  "\x1B[35m"
#define RESET "\x1b[0m"
int main();
struct department_list
{
    int code;
    char name[20];
};
struct hall_list
{
    int number;
    char name[20];
};
struct checking
{
    int hall_num,slot_num,dept_code;
    char description[100];
};
struct totalavailable
{
    int hall_num,slot_num;
};


int file_exists(const char *date)
{
    FILE *fp;
    fp = fopen(date, "r");
    if(fp == NULL)
    	return 0;
    fclose(fp);
        return 1;
}
void  view_availability(char *option)
{

    if (*option == 'm') return ;
    system("clear");
    printf(KMAG "\n\n==========================================================================================================================================\n" RESET);
    printf(KCYN "                                                     CONFERENCE HALL BOOKING MANAGEMENT SYSTEM\n" RESET);
    printf(KMAG "==========================================================================================================================================\n\n\n" RESET);
    printf("\n                                               Option : View detils of Available Halls/Booked Halls\n\n");

    struct checking booked[60];
    int hallno,b_hallno,slotno,usercode,count=0,count1=0,bookedflag;
    char status,description[50],des[50];
    char booking_date[8];
    FILE *fp;
    int slot_num,hall_num, exist;
    printf("\nEnter the date in YYMMDD format(mandatory): ");
    scanf("%s",&booking_date);
    printf("\nEnter slot number. Enter 0 if you do not want to enter slot number: ");
    scanf("%d",&slot_num);
    printf("\nEnter hall number. Enter 0 if you do not want to enter hall number: ");
    scanf("%d",&hall_num);
    printf("\nEnter the status: a for available and b for booked: ");
    scanf(" %c",&status);
    if(status == 'b' || status =='B')
    {
        if (fopen(booking_date,"r"))
        {
            fp=fopen(booking_date,"r");
	    while(feof(fp)==0)
	    {
	        fscanf(fp,"%5d %5d %5d %[^\n]%*c",&hallno,&slotno, &usercode,des );
                count++;
	    }
	    fclose(fp);
            count--;
            fp=fopen(booking_date,"r");
	    printf("\nBooked halls are: \n");
	    printf("Hall number     Slot number     Department code    Description\n");
	    int i;
            for(i=0;i<count; i++)
	    {
		fscanf(fp,"%5d %5d %5d %20[^\n]s \n",&booked[i].hall_num,&booked[i].slot_num,&booked[i].dept_code,booked[i].description);
		if(((slot_num == 0) && (hall_num == 0)) || ((hall_num == 0) && (booked[i].slot_num==slot_num)) || ((slot_num == 0) && (booked[i].hall_num==hall_num)) || (( slot_num !=0 && hall_num!=0) && (slot_num==booked[i].slot_num && hall_num==booked[i].hall_num)))
                    printf("%10d %10d %12d %30s \n",booked[i].hall_num,booked[i].slot_num,booked[i].dept_code,booked[i].description);
	    }
	    fclose(fp);
        }
        else
            printf("\nNo bookings found for the given date !\n");
    }
    if(status == 'a' || status == 'A')
    {
	struct totalavailable finalavailable[60];
	int totalslot[3]={1,2,3},i,j,k,l=0,fileexistsflag=0;

	if (fopen(booking_date,"r"))
	{
            fileexistsflag = 1 ;
	    fp=fopen(booking_date,"r");
	    //counting booking_date and storing into structure
            while(feof(fp)==0)
	    {
	        fscanf(fp,"%5d %5d %5d %[^\n]%*c",&hallno,&slotno, &usercode,des );
                count++;
            }
            fclose(fp);
	    count--;
            fp=fopen(booking_date,"r");
	    int i;
	    for(i=0;i<count; i++)
	    {
	    fscanf(fp,"%5d %5d %5d %[^\n]%*c",&booked[i].hall_num,&booked[i].slot_num,&booked[i].dept_code,booked[i].description);
            }
	    fclose(fp);
        }

    	fp=fopen("hall_list.txt","r");
        struct hall_list totalhalls[20];
	//counting total halls and storing into structure
	while(feof(fp)==0)
	{
	    fscanf(fp,"%5d %20[^\n]s \n",&totalhalls[0].number,totalhalls[0].name);
    	    count1++;
    	}
	rewind(fp);
	count1--;
	for(i=0;i<count1;i++)
	{
            fscanf(fp,"%5d %20[^\n]s \n",&totalhalls[i].number,totalhalls[i].name);
	}
	fclose(fp);

	//comparing and storing into final available stucture
	for(i=0;i< count1; i++)
	{
            for(j=0;j<3;j++)
	    {
                bookedflag = 0;
                if (fileexistsflag )
                {
		    for(k=0;k<count;k++)
		    {
			if(totalhalls[i].number == booked[k].hall_num && totalslot[j] == booked[k].slot_num)
			{
		            bookedflag = 1;
		            exit ;
			}
		    }
                }
                if (bookedflag == 0)
                {
                    finalavailable[l].hall_num=totalhalls[i].number;
		    finalavailable[l].slot_num=totalslot[j];
		    l++;
                }
            }
	}
	//printing final available structure
	char temp[20];
	printf("\nThe available halls are: \n");
	printf("Hall number    Slot number      Hall name\n");
        for(i=0;i<l;i++)
        {
            for(j=0;j<count1;j++)
	    {
	        if(totalhalls[j].number==finalavailable[i].hall_num)
		    strcpy(temp,totalhalls[j].name);
            }
	    if(((slot_num == 0) && (hall_num == 0)) || ((hall_num == 0) && (finalavailable[i].slot_num==slot_num)) || ((slot_num == 0) && (finalavailable[i].hall_num==hall_num)) || (( slot_num !=0 && hall_num!=0) && (slot_num==finalavailable[i].slot_num && hall_num==finalavailable[i].hall_num)))

	        printf("%10d %10d %20s \n",finalavailable[i].hall_num,finalavailable[i].slot_num,temp);
	}
    }
    printf("\nPress 'm' to go back to the main menu. '1' for view availability again: ");
    scanf(" %c",option);

    view_availability (option);
    if(*option == 'm')
    return;
}

void hall_booking(char *option)
{

    if (*option == 'm') return ;
    system("clear");

    printf(KMAG "\n\n==========================================================================================================================================\n" RESET);
    printf(KCYN "                                                     CONFERENCE HALL BOOKING MANAGEMENT SYSTEM\n" RESET);
    printf(KMAG "==========================================================================================================================================\n\n\n" RESET);
    printf("\n                                               		   Option : Hall booking\n\n");


    struct checking booked[60];
    int hallno,b_hallno,slotno,usercode,count=0,count1=0,bookedflag;
    char status,des[50];
    char booking_date[8];
    FILE *fp;
    int slot_num,hall_num, exist;
    printf("\nEnter the date in YYMMDD format(mandtory):");
    scanf("%s",&booking_date);
    printf("\nEnter slot number. Enter 0 if you do not want to enter slot number: ");
    scanf("%d",&slot_num);
    printf("\nEnter hall number. Enter 0 if you do not want to enter hall number: ");
    scanf("%d",&hall_num);

    //counting booking_date and storing into structure
    struct totalavailable finalavailable[60];
    int totalslot[3]={1,2,3},i,j,k,l=0,fileexistsflag=0;
    if (fopen(booking_date,"r"))
    {
        fileexistsflag = 1 ;
	fp=fopen(booking_date,"r");
        while(feof(fp)==0)
        {
            fscanf(fp,"%5d %5d %5d %[^\n]%*c",&hallno,&slotno, &usercode,des );
	    count++;
	}
	fclose(fp);
	count--;

        fp=fopen(booking_date,"r");
        for(i=0;i<count; i++)
        {
	    fscanf(fp,"%5d %5d %5d %[^\n]%*c",&booked[i].hall_num,&booked[i].slot_num,&booked[i].dept_code,booked[i].description);
        }
        fclose(fp);
    }
    //counting total halls and storing into structure
    fp=fopen("hall_list.txt","r");
    struct hall_list totalhalls[20];
    while(feof(fp)==0)
    {
        fscanf(fp,"%5d %20[^\n]s \n",&totalhalls[0].number,totalhalls[0].name);
    	count1++;
    }
    rewind(fp);
    count1--;
    for(i=0;i<count1;i++)
    {
	fscanf(fp,"%5d %20[^\n]s \n",&totalhalls[i].number,totalhalls[i].name);
    }
    fclose(fp);

    //comparing and storing into final available stucture
    for(i=0;i< count1; i++)
    {
	for(j=0;j<3;j++)
	{
            bookedflag = 0;
            if (fileexistsflag )
	    {
		for(k=0;k<count;k++)
		{
		    if(totalhalls[i].number == booked[k].hall_num && totalslot[j] == booked[k].slot_num)
                    {
		        bookedflag = 1;
		        exit ;
                    }
	        }
            }
            if (bookedflag == 0)
	    {
                finalavailable[l].hall_num=totalhalls[i].number;
		finalavailable[l].slot_num=totalslot[j];
		l++;
            }
	}
    }
    //printing final available structure
    printf("\nThe available halls are: \n");
    printf("Hall number    Slot number      Hall name\n");
    char temp[20];
    for(i=0;i<l;i++)
    {
        for(j=0;j<count1;j++)
	{
	    if(totalhalls[j].number==finalavailable[i].hall_num)
	    strcpy(temp,totalhalls[j].name);
        }
        if(((slot_num == 0) && (hall_num == 0)) || ((hall_num == 0) && (finalavailable[i].slot_num==slot_num)) || ((slot_num == 0) && (finalavailable[i].hall_num==hall_num)) || (( slot_num !=0 && hall_num!=0) && (slot_num==finalavailable[i].slot_num && hall_num==finalavailable[i].hall_num)))
	    printf("%10d %10d %20s \n",finalavailable[i].hall_num,finalavailable[i].slot_num,temp);
    }

    //entering data to book hall
    struct checking book;
    printf("\nEnter the hall number to be booked: ");
    scanf("%d",&book.hall_num);
    printf("\nEnter the slot number to be booked: ");
    scanf("%d",&book.slot_num);
    printf("\nEnter your department code (enter 0 to open the department list) : ");
    scanf("%d",&book.dept_code);
    //printf("\n%d\n",book.dept_code);
    //printing department list when 0 given
    while(book.dept_code == 0)
    {
        int count =0,menu_control,dept_code,temp;
        char c,dept_name[20],confirm,temp1 [20];
        printf("\n                          List of Departments\n");

        FILE *fp;
        fp=fopen("department_list.txt","r");
        struct department_list dept[20];
        while(feof(fp)==0)
        {
            fscanf(fp,"%5d %[^\n]%*c \n",&temp,temp1);
    	    count++;
        }

        rewind(fp);
	printf("\nDepartment code               Name\n\n");

        for(i=0;i<count;i++)
	{
	    fscanf(fp,"%5d %[^\n]s \n",&dept[i].code,dept[i].name);
	}
	fclose(fp);
	for(i=0;i<count;i++)
	{
	    printf("%15d %20s\n",dept[i].code,dept[i].name);
	}

	printf("\nEnter your department code (enter 0 to open the department list) : ");
	scanf("%d",&book.dept_code);
    }

    printf("\nEnter description: ");
    scanf(" %[^\n]%*c", book.description);
    //writing into file the newly booked hall details
    if (fileexistsflag == 1)
    {
        fp=fopen(booking_date, "a+");
 	fprintf(fp,"%5d %5d %5d %20s\n",book.hall_num,book.slot_num,book.dept_code,book.description );
	printf("       Hall number %d successfully booked ",book.hall_num);
	fclose(fp);
    }
    else
	if(fileexistsflag == 0)
        {
	    fp=fopen(booking_date, "w");
            fprintf(fp,"%5d %5d %5d %20s\n",book.hall_num,book.slot_num,book.dept_code,book.description );
            printf("       Hall number %d successfully booked ",book.hall_num);
	    fclose(fp);
	}

    printf("\nPress 'm' number to go back to the main menu: ");
    scanf("%c",option);
    hall_booking(option);
    if(*option == 'm')
        return;
}


void cancel_booking(char *option)
{
    if (*option == 'm') return ;
    system("clear");

    printf(KMAG "\n\n==========================================================================================================================================\n" RESET);
    printf(KCYN "                                                     CONFERENCE HALL BOOKING MANAGEMENT SYSTEM\n" RESET);
    printf(KMAG "==========================================================================================================================================\n\n\n" RESET);
    printf("\n                                                       Option : Cancel booked halls\n\n");

    struct checking cancel[60];
    int hallno,b_hallno,slotno,usercode,count=0,count1=0,bookedflag,cancel_num,cancel_slot;
    char status,description[50],des[50],confirm;
    char cancelling_date[8];
    FILE *fp;
    int slot_num,hall_num, exist;

    printf("\nEnter the date in YYMMDD format(mandatory):");
    scanf("%s",&cancelling_date);
    printf("\nEnter slot number. Enter 0 if you do not want to enter slot number: ");
    scanf("%d",&slot_num);
    printf("\nEnter hall number. Enter 0 if you do not want to enter hall number: ");
    scanf("%d",&hall_num);

    if (fopen(cancelling_date,"r"))
    {
        fp=fopen(cancelling_date,"r");
        //counting cancelling_date
        while(feof(fp)==0)
        {
            fscanf(fp,"%5d %5d %5d %[^\n]%*c",&hallno,&slotno, &usercode,des );
            count++;
        }
        fclose(fp);
        count--;
        fp=fopen(cancelling_date,"r");
        printf("\nThe list of booked halls: \n");
	printf("\nHall no      Slot no     Department code      Description\n");
        int i;
        for(i=0;i<count; i++)
        {
            fscanf(fp,"%5d %5d %5d %20[^\n]s \n",&cancel[i].hall_num,&cancel[i].slot_num,&cancel[i].dept_code,cancel[i].description);
	    if(((slot_num == 0) && (hall_num == 0)) || ((hall_num == 0) && (cancel[i].slot_num==slot_num)) || ((slot_num == 0) && (cancel[i].hall_num==hall_num)) || (( slot_num !=0 && hall_num!=0) && (slot_num==cancel[i].slot_num && hall_num==cancel[i].hall_num)))
                printf("%10d %10d %10d %20s \n",cancel[i].hall_num,cancel[i].slot_num,cancel[i].dept_code,cancel[i].description);
        }
	fclose(fp);
	printf("\nEnter the hall number to be deleted: ");
	scanf("%d",&cancel_num);
	printf("\nEnter the slot number to be deleted: ");
	scanf("%d",&cancel_slot);

        printf("\nPress Y to cancel booking of hall of number %d and slot %d, any other key to abort: ",cancel_num, cancel_slot);
        scanf(" %c",&confirm);

        if(confirm == 'y' || confirm == 'Y')
        {
	    //printf("\nENtered confirm...");
            fp=fopen(cancelling_date,"r");
            count = 0;
	    while(feof(fp)==0)
	    {
		fscanf(fp,"%5d %5d %5d %[^\n]%*c",&hallno,&slotno, &usercode,des );
	        count++;
	    }
	    fclose(fp);
            count-- ;
	    //printf("\nHere count is..%d",count);
            fp=fopen(cancelling_date,"r");
        int i;
	    for(i=0;i<count;i++)
	    {
		fscanf(fp,"%5d %5d %5d %20[^\n]s",&cancel[i].hall_num,&cancel[i].slot_num,&cancel[i].dept_code,cancel[i].description);
              //  printf("%5d %5d %5d %20s",cancel[i].hall_num,cancel[i].slot_num,cancel[i].dept_code,cancel[i].description);
            }
	    fclose(fp);

            fp = fopen(cancelling_date, "w");
            //printf("\nCheck1");
	    for(i=0;i<count;i++)
	    {
	        if(cancel[i].hall_num != cancel_num || cancel[i].slot_num != cancel_slot)
		{
                    //printf("%5d %5d %5d %20s",cancel[i].hall_num,cancel[i].slot_num,cancel[i].dept_code,cancel[i].description);
		    fprintf(fp, "%5d %5d %5d %20s\n",cancel[i].hall_num,cancel[i].slot_num,cancel[i].dept_code,cancel[i].description);
                }
	    }
	    printf("       Hall number %d successfully cancelled ",cancel_num);
	    fclose(fp);

	}

    }
    else
	printf("\nBooking does not exist on this date. ");
    printf("\nPress 'm' to go back to the main menu: ");
    scanf(" %c",option);
    cancel_booking(option);
    if(*option == 'm')
        return;
}



void hall_list_management(char *option)
{
    if (*option == 'm') return ;
    system("clear");

    printf(KMAG "\n\n==========================================================================================================================================\n" RESET);
    printf(KCYN "                                                     CONFERENCE HALL BOOKING MANAGEMENT SYSTEM\n" RESET);
    printf(KMAG "==========================================================================================================================================\n\n\n" RESET);
    printf("\n                                               	        Option : Halls - Master page\n\n");


    int count =0,menu_control,hall_num,temp;
    char c,hall_name[20],confirm,temp1 [20];

    printf("                        List of Halls\n");
    printf("\nHall no      Hall name\n\n");
    //counting
    FILE *fp;
    fp=fopen("hall_list.txt","r");
    struct hall_list halls[20];
    while(feof(fp)==0)
    {
        fscanf(fp,"%5d %[^\n]%*c \n",&temp,temp1);
        count++;
    }

    rewind(fp);
    //storing detaila into array
    int i;
    for(i=0;i<count;i++)
    {
	fscanf(fp,"%5d %[^\n]%*c \n",&halls[i].number,halls[i].name);
    }
    fclose(fp);
    for(i=0;i<count;i++)
    {
 	printf("%5d %15s\n",halls[i].number,halls[i].name);
    }

    printf("\nPress: \n'a' for adding a hall\n'd' for deleting a hall\n'e' for editing an existing hall, 'm' for main menu:   ");
    scanf(" %c",option);

    if(*option == 'a')
    {

        printf("\nEnter the name of the new hall : ");
        scanf(" %[^\n]%*c",hall_name);
	printf("\nEnter the number of the new hall : ");
        scanf("%d",&hall_num);
        printf("\nPress Y to add hall record with name %s and number %d to the Hall list, any other key to abort: ",hall_name,hall_num);
        scanf(" %c",&confirm);
        if(confirm == 'y' || confirm == 'Y')
        {
            fp = fopen("hall_list.txt", "a+");
            fprintf(fp, "%5d %20s\n", hall_num, hall_name);
            fclose(fp);
        }
        hall_list_management(option);
    }

    if(*option=='d')
    {
        printf("\nEnter the number of the hall to be deleted : ");
        scanf("%d",&hall_num);
        printf("\nPress Y to delete record with number %d from the Hall list, any other key to abort: ",hall_num);
        scanf(" %c",&confirm);
        if(confirm == 'y' || confirm == 'Y')
        {
            fp=fopen("hall_list.txt","r");
            count = 0;
	    while(feof(fp)==0)
	    {
	        fscanf(fp,"%5d %20[^\n]c\n",&temp,temp1);
	        count++;
	    }
	    fclose(fp);
            count-- ;
            printf("\ncount is %d",count);

            fp=fopen("hall_list.txt","r");
	    for(i=0;i<count;i++)
	    {
		fscanf(fp,"%5d %20[^\n]s\n",&halls[i].number,halls[i].name);
		printf("read from file %5d %20s\n",halls[i].number,halls[i].name);
            }
	    fclose(fp);
	    fp = fopen("hall_list.txt", "w");

	    for(i=0;i<count;i++)
	    {
	        if(halls[i].number != hall_num)
		{
		printf(" writing to file %5d %20s\n",halls[i].number,halls[i].name);
	        fprintf(fp, "%5d %20s\n", halls[i].number,halls[i].name);
                }
	    }
	    fclose(fp);
	}
        hall_list_management(option);
    }

    char new_name[20], confirm1;
    if(*option=='e')
    {
        printf("\nEnter the number of the hall to be edited : ");
        scanf("%d",&hall_num);

	printf("\nEnter the name of the new hall : ");
        scanf(" %[^\n]%*c",new_name);

	printf("\nPress Y to change record name of the record number %d as %s, any other key to abort: ",hall_num,new_name);
	scanf(" %c",&confirm1);

	if(confirm1 == 'y' || confirm1 == 'Y')
	{
            fp=fopen("hall_list.txt","r");
	    count = 0;
	    while(feof(fp)==0)
	    {
	        fscanf(fp,"%5d %20[^\n]c\n",&temp,temp1);
	        count++;
	    }
	    fclose(fp);
            count-- ;
            for(i=0;i<count;i++)
	    {
		if(halls[i].number == hall_num)
	    	{
	             strcpy(halls[i].name,new_name);
 		}
            }
	    fp = fopen("hall_list.txt", "w");
	    for(i=0;i<count;i++)
	    {
		fprintf(fp, "%5d %20s\n", halls[i].number,halls[i].name);
	    }
	    fclose(fp);
	}
        hall_list_management(option);
    }

}

void department_list_management(char *option)
{

    if (*option == 'm') return ;
    system("clear");

    printf(KMAG "\n\n==========================================================================================================================================\n" RESET);
    printf(KCYN "                                                     CONFERENCE HALL BOOKING MANAGEMENT SYSTEM\n" RESET);
    printf(KMAG "==========================================================================================================================================\n\n\n" RESET);
    printf("\n                                                          Option : Users - Master page\n\n");

    int count =0,menu_control,dept_code,temp;
    char c,dept_name[20],confirm,temp1 [20];
    printf("\n                          List of Departments\n");
    printf("\nDepartment code            Name\n\n");

    //counting
    FILE *fp;
    fp=fopen("department_list.txt","r");
    struct department_list dept[20];
    while(feof(fp)==0)
    {
	fscanf(fp,"%5d %[^\n]%*c \n",&temp,temp1);
    	count++;
    }
    //storing details into array
    rewind(fp);
    int i;
    for(i=0;i<count;i++)
    {
    	fscanf(fp,"%5d %[^\n]%*c \n",&dept[i].code,dept[i].name);
    }
    fclose(fp);
    for(i=0;i<count;i++)
    {
	printf("%5d %25s\n",dept[i].code,dept[i].name);
    }
    printf("\nPress: \n'a' for adding a new department\n'd' for deleting an existing\n'e' for editing an existing department, 'm' for main menu :  ");
    scanf(" %c",option);

    if(*option == 'a')
    {
        printf("\nEnter the name of the new department: ");
        scanf(" %[^\n]%*c",dept_name);
	printf("\nEnter the new department code : ");
        scanf("%d",&dept_code);
        printf("\nPress Y to add department with name %s and code %d to the Department list, any other key to abort: ",dept_name,dept_code);
        scanf(" %c",&confirm);
        if(confirm == 'y' || confirm == 'Y')
        {
     	    fp = fopen("department_list.txt", "a+");
            fprintf(fp, "%5d %20s\n", dept_code, dept_name);
            fclose(fp);
        }
        department_list_management(option);
    }

    if(*option=='d')
    {
        printf("\nEnter the code of the department to be deleted : ");
        scanf("%d",&dept_code);
        printf("\nPress Y to delete department with number %d from the Departments list, any other key to abort: ",dept_code);
        scanf(" %c",&confirm);

        if(confirm == 'y' || confirm == 'Y')
        {
	    fp=fopen("department_list.txt","r");
            count = 0;
	    while(feof(fp)==0)
	    {
	        fscanf(fp,"%5d %20[^\n]c\n",&temp,temp1);
	        count++;
	    }
	    fclose(fp);
            count-- ;

            fp=fopen("department_list.txt","r");
	    for(i=0;i<count;i++)
            {
            fscanf(fp,"%5d %20[^\n]s\n",&dept[i].code,dept[i].name);
            }
	    fclose(fp);

            fp = fopen("department_list.txt", "w");
            for(i=0;i<count;i++)
	    {
	        if(dept[i].code != dept_code)
                {
	        fprintf(fp, "%5d %20s\n", dept[i].code,dept[i].name);
                }
            }
            fclose(fp);
        }
        department_list_management(option);
    }

    char new_name[20], confirm1;
    if(*option=='e')
    {
        printf("\nEnter the number of the department to be edited : ");
        scanf("%d",&dept_code);
    	printf("\nEnter the name of the new department: ");
        scanf(" %[^\n]%*c",new_name);
	printf("\nPress Y to change department name of the department code %d as %s, any other key to abort: ",dept_code,new_name);
	scanf(" %c",&confirm1);
	if(confirm1 == 'y' || confirm1 == 'Y')
	{
            fp=fopen("department_list.txt","r");
	    count = 0;
	    while(feof(fp)==0)
	    {
	        fscanf(fp,"%5d %20[^\n]c\n",&temp,temp1);
	        count++;
	    }
	    fclose(fp);
            count-- ;
            for(i=0;i<count;i++)
	    {
		if(dept[i].code == dept_code)
	    	{
                    strcpy(dept[i].name,new_name);
		}
	    }
	    fp = fopen("department_list.txt", "w");
            for(i=0;i<count;i++)
	    {
		fprintf(fp, "%5d %20s\n", dept[i].code,dept[i].name);
            }
           fclose(fp);
	}
        department_list_management(option);
    }
}




int main()
{

    int menu_option=0;
    char hall_menu_option = 'a';
    char view_availability_option = 'b' ;
    char hall_booking_option='c';
    char dept_menu_option = 'd';
    char hall_cancel_option='e';



    do
    {
	system("clear");
	printf(KMAG "==========================================================================================================================================\n" RESET);
        printf(KCYN "                                                     CONFERENCE HALL BOOKING MANAGEMENT SYSTEM\n" RESET);
        printf(KMAG "==========================================================================================================================================\n\n\n" RESET);

        printf("\n  1.View availability\n  2.Hall booking.\n  3.Cancel booking.\n  4.Hall list management.\n  5.User list management.\n  6.Exit.\n");
        printf("                                                     Enter the menu option required: ");
        scanf("%d",&menu_option);
        switch(menu_option)
        {
            case 1:
                view_availability(&view_availability_option);
                view_availability_option= 'b';
                break;
            case 2:
                hall_booking(&hall_booking_option);
                hall_booking_option= 'c';
                break;
            case 3:
                cancel_booking(&hall_cancel_option);
		hall_cancel_option='e';
                break;
            case 4:
                hall_list_management(&hall_menu_option);
                hall_menu_option = 'a';
                break;
            case 5:
                department_list_management(&dept_menu_option);
	        dept_menu_option = 'd';
                break;
            case 6:
                exit(0);
        }
    }while(menu_option!=6);
}
