#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
    int day;
    int month;
    int year;

} DOB;

typedef struct
{
    char last_name[50];
    char first_name[50];
    DOB date;
    char address[50];
    char phone_number[50];
    char email[50];
} contact;

contact S[100];
char targetsearch[100];
int number=0;

void load ()
{
    int i=0;
    FILE *f1;
    f1=fopen("phonebook.txt","r");
    if(f1!=NULL)
    {
        while(!feof(f1))
        {
            fscanf(f1,"%[^,],",S[i].last_name);
            fscanf(f1,"%[^,],",S[i].first_name);
            fscanf(f1,"%d-%d-%d,",&S[i].date.day,&S[i].date.month,&S[i].date.year);
            fscanf(f1,"%[^,],",S[i].address);
            fscanf(f1,"%[^,],",S[i].phone_number);
            fscanf(f1,"%s\n",S[i].email);
            i++;
        }
        number=i;
        fclose(f1);
        printf("Load is Successfully Done\n\n");
    }
    else
        printf("File is not found");
}
void query()
{
    int i,n=1;
    int index=0;
    printf("Please Enter The Name Of The Contact Or Type 0 To Return To Main Menu : ");
    scanf("%s",targetsearch);
    printf("\n");
    if (targetsearch[0]=='0')
    {
        printf("\n");
        return;
    }
    for(i=0; i<number; i++)
    {
        if (strcasecmp(S[i].last_name,targetsearch)==0)
        {
            printf("Contact No.%d: ",n);
            printf("%s, ",S[i].first_name);
            printf("%s, ",S[i].address);
            printf("%s, ",S[i].email);
            printf("%s\n",S[i].phone_number);
            index++;
            n++;
        }
    }
    if (index==0)
    {
        printf("There Is No Contact Saved With The Name %s\n",targetsearch);
        query();
    }
    printf("\n");
}
int IsValidEmail(char s[50])
{
    int i,j,k,index1=0,index2=0;
    for(i=0; i<strlen(s)+1; i++)
    {
        if(s[i]=='@')
            index1=i;
    }
    for(j=0; j<(strlen(s)+1); j++)
    {
        if(s[j]=='.')
            index2=j;
    }
    for (k=0; k<strlen(s)+1; k++)
    {
        if(s[k]==' ')
        {
            return 0;
        }
    }
    if (!isalpha(s[0]))
        return 0;
    if(index2-index1>1&&(index2+1)!=strlen(s)&&index1!=0&&index2!=0)
        return 1;
    else
        return 0;

}
int IsValidNumber(char s[30])
{
    int i=0;
    while (s[i]!='\0')
    {
        if (!isdigit(s[i]))
            return 0;
        i++;
    }
    return 1;
}
void ADD()
{
    int i=number;
    printf("Please Enter The Last Name:\n");
    scanf("%s",S[i].last_name);
    printf("\nPlease Enter The First Name:\n");
    scanf("%s",S[i].first_name);
    printf("\nPlease Enter The Date of Birth:\n");
    printf("Enter The Day: ");
    scanf("%d",&S[i].date.day);
    printf("Enter The Month: ");
    scanf("%d",&S[i].date.month);
    printf("Enter The Year: ");
    scanf("%d",&S[i].date.year);
    printf("\n\n");
    while(S[i].date.day>31||S[i].date.day<=0||S[i].date.month>12||S[i].date.month<=0||S[i].date.year>2021||S[i].date.year<=0||S[i].date.month==2&&S[i].date.day>29||S[i].date.month==4&&S[i].date.day>30||S[i].date.month==6&&S[i].date.day>30||S[i].date.month==9&&S[i].date.day>30||S[i].date.month==11&&S[i].date.day>30)
    {
        printf("Invalid Date of Birth\n\n");
        printf("Please Enter The Date of Birth\n");
        printf("Enter The Day: ");
        scanf("%d",&S[i].date.day);
        printf("Enter The Month: ");
        scanf("%d",&S[i].date.month);
        printf("Enter The Year: ");
        scanf("%d",&S[i].date.year);
    }
    printf("Please Enter The Address:\n");
    getchar();
    gets(S[i].address);
    printf("\nPlease Enter The Phone Number:\n");
    scanf("%s",S[i].phone_number);
    while (!IsValidNumber(S[i].phone_number))
    {
        printf("Invalid Number\n");
        printf("Please Enter The Phone Number\n");
        scanf("%s",S[i].phone_number);
    }
    printf("\nPlease Enter The Email\n");
    getchar();
    gets(S[i].email);
    while(IsValidEmail(S[i].email)==0)
    {
        printf("\nInvalid Email\n\n");
        printf("Please Enter The Email\n");
        gets(S[i].email);
    }
    number++;
    printf("\nContact Is Added\n\n");
}
void delete2 (char m[30],char n[30])
{
    int i=0;
    while(i<number)
    {
        if (strcasecmp(m,S[i].last_name)==0&&strcasecmp(n,S[i].first_name)==0)
        {
            while(i<number)
            {
                S[i]=S[i+1];
                i=i+1;
            }
            number--;
        }
        else
            i=i+1;
    }
}
void DELETE()
{
    char m[20],n[20];
    int i=0;
    int j=i;
    int check=0;
    printf("Enter The last Name Which You Want To Delete or Type 0 To Return To Main Menu : ");
    scanf("%s",m);
    if (m[0]=='0')
    {
        printf("\n\n");
        return;
    }
    printf("Enter The First Name Which You Want To Delete : ");
    scanf("%s",n);
    for (i=0; i<number; i++)
    {
        if (strcasecmp(m,S[i].last_name)==0&&strcasecmp(n,S[i].first_name)==0)
        {
            check++;
        }
    }
    while(1)
    {
        if (check==0)
        {
            printf("\nThere Is No Contact With The Last Name: %s and First Name: %s\n\n",m,n);
            printf("Enter The Last Name Which You Want To Delete or Type 0 To Return To Main Menu : ");
            scanf("%s",m);
            if (m[0]=='0')
            {
                printf("\n\n");
                return;
            }
            printf("Enter The First Name Which You Want To Delete : ");
            scanf("%s",n);
            for (i=0; i<number; i++)
            {
                if (strcasecmp(m,S[i].last_name)==0&&strcasecmp(n,S[i].first_name)==0)
                {
                    check++;
                }
            }
        }
        else
            break;
    }
    while (check!=0)
    {
        delete2(m,n);
        check--;
    }
    printf("\nContact Is Deleted\n\n");
}
void Sorted_DOB()
{
    int m,n,x=1;
    contact index;
    for (m=0; m<number; m++)
    {
        for(n=0; n<number; n++)
        {
            if(S[n].date.year<S[n+1].date.year)
            {
                index=S[n];
                S[n]=S[n+1];
                S[n+1]=index;
            }
            else if (S[n].date.year==S[n+1].date.year)
            {
                if(S[n].date.month<S[n+1].date.month)
                {
                    index=S[n];
                    S[n]=S[n+1];
                    S[n+1]=index;
                }
                else if(S[n].date.month==S[n+1].date.month)
                {
                    if (S[n].date.day<S[n+1].date.day)
                    {
                        index=S[n];
                        S[n]=S[n+1];
                        S[n+1]=index;
                    }
                }
            }
        }
    }
    int i;
    printf("The Sorted Values Are :\n");

    for(i=0; i<number; i++)
    {
        printf("Contact No.%d: ",x);
        printf("%s,",S[i].last_name);
        printf("%s,",S[i].first_name);
        printf("%d-%d-%d,",S[i].date.day,S[i].date.month,S[i].date.year);
        printf("%s,",S[i].address);
        printf("%s,",S[i].phone_number);
        printf("%s\n",S[i].email);
        x++;
    }
    printf("\n\n");

}
void sorted_lastname()
{
    int i;
    int j;
    contact temp;
    for(i=0; i<number; i++)
    {
        for(j=i+1; j<number; j++)
        {
            if (strcasecmp(S[i].last_name,S[j].last_name)>0)
            {
                temp=S[j];
                S[j]=S[i];
                S[i]=temp;
            }
        }
    }
}

void print()
{
    int i,n=1;
    printf("Please Choose The Type of Printing :\n1)Just Print The Contacts\n2)Sorting By Last Name\n3)Sorting By Date of Birth\n4)Return To Main Menu\n");
    printf("Your Choice is :");
    char x[20];
    scanf("%s",x);
    printf("\n");
    while (1)
    {
        if (strlen(x)==1)
        {
        if(*x=='1')
        {
            for(i=0; i<number; i++)
            {
                printf("Contact No.%d: ",n);
                printf("%s,",S[i].last_name);
                printf("%s,",S[i].first_name);
                printf("%d-%d-%d,",S[i].date.day,S[i].date.month,S[i].date.year);
                printf("%s,",S[i].address);
                printf("%s,",S[i].phone_number);
                printf("%s\n",S[i].email);
                n++;
            }
            printf("\n\n");
            break;
        }
        else if(*x=='2')
        {
            printf("The sorted values are :\n");
            sorted_lastname();
            for(i=0; i<number; i++)
            {
                printf("Contact No.%d: ",n);
                printf("%s,",S[i].last_name);
                printf("%s,",S[i].first_name);
                printf("%d-%d-%d,",S[i].date.day,S[i].date.month,S[i].date.year);
                printf("%s,",S[i].address);
                printf("%s,",S[i].phone_number);
                printf("%s\n",S[i].email);
                n++;
            }
            printf("\n\n");
            break;
        }

        else if (*x=='3')
        {
            Sorted_DOB();
            break;
        }
        else if (*x=='4')
        {
            return;
        }
        else
        {
            printf("Wrong number please choose number from 1 to 4:");
            scanf("%s",x);
        }
        }
        else
        {
            printf("Wrong number please choose number from 1 to 4:");
            scanf("%s",x);
        }
    }
}
void modify()
{
    int counter=0;
    int i,n=0;
    char x[20];
    char M_Last_Name[50];
    printf("Please Enter The Last Name of The Contact You Want To Modify or Type 0 To Return To Main Menu: ");
    scanf("%s",M_Last_Name);
    if (M_Last_Name[0]=='0')
    {
        return;
    }
    for(i=0; i<number; i++)
    {
        if(strcasecmp(M_Last_Name,S[i].last_name)==0)
        {
            counter++;
            n++;
            printf("%d.%s,",n,S[i].last_name);
            printf("%s,",S[i].first_name);
            printf("%d-%d-%d,",S[i].date.day,S[i].date.month,S[i].date.year);
            printf("%s,",S[i].address);
            printf("%s,",S[i].phone_number);
            printf("%s\n\n",S[i].email);
        }
    }
    if(counter==0)
    {
        printf("\t Last Name Is Not In The File\n\n");
    }
    else if (counter==1)
    {
        for (i=0; i<number; i++)
        {
            if (strcasecmp(M_Last_Name,S[i].last_name)==0)
                counter=i;
        }
        while (1)
        {
            printf(" Please Choose What Do You Want To Modify\n\n Last Name Enter:1\n First Name Enter:2\n Date of Birth Enter:3\n Address Enter:4\n Phone Number Enter:5\n Email Enter:6\n Exit Enter :7\n ");
            printf("Enter Your Choice:");
            scanf("%s",x);
            switch(*x)
            {
            case '1':
                printf("Please Enter The New Last Name You Want:");
                scanf("%s",S[counter].last_name);
                printf("\nLast Name Has Been Modified\n");
                break;
            case '2':
                printf("Please Enter The New First Name You Want:");
                scanf("%s",S[counter].first_name);
                printf("\nFirst Name Has Been Modified\n");
                break;
            case '3':
                printf("Please Enter The New Date Of Birth:\n");
                printf("Enter the Day:");
                scanf("%d",&S[counter].date.day);
                printf("Enter the Month:");
                scanf("%d",&S[counter].date.month);
                printf("Enter the Year:");
                scanf("%d",&S[counter].date.year);
                while (S[counter].date.day>31||S[counter].date.day<=0||S[counter].date.month>12||S[counter].date.month<=0||S[counter].date.year>2021||S[counter].date.year<=0||S[counter].date.month==2&&S[counter].date.day>29||S[counter].date.month==4&&S[counter].date.day>30||S[counter].date.month==6&&S[counter].date.day>30||S[counter].date.month==9&&S[counter].date.day>30||S[counter].date.month==11&&S[counter].date.day>30)
                {
                    printf("\nWrong Date of Birth\n");
                    printf("\nPlease Enter The Date of Birth\n\n");
                    printf("Enter the Day:");
                    scanf("%d",&S[counter].date.day);
                    printf("Enter the Month:");
                    scanf("%d",&S[counter].date.month);
                    printf("Enter the Year:");
                    scanf("%d",&S[counter].date.year);
                }
                printf("\nDate of Birth Has Been Modified\n");
                break;
            case '4':
                printf("Please Enter The New Address You Want:");
                getchar();
                gets(S[counter].address);
                printf("\nAddress Has Been Modified\n");
                break;
            case '5':
                printf("\nPlease Enter The New Phone Number You Want:");
                scanf("%s",S[counter].phone_number);
                while (IsValidNumber(S[counter].phone_number)==0)
                {
                    printf("Invalid Number\n");
                    printf("Please Enter The New Phone Number You Want:\n");
                    scanf("%s",S[counter].phone_number);
                }
                printf("\nNumber Has Been Modified\n");
                break;
            case '6':
                printf("\nPlease Enter The New Email You Want:\n");
                getchar();
                gets(S[counter].email);
                while (IsValidEmail(S[counter].email)==0)
                {
                    printf("Invalid Email\n");
                    printf("Please Enter The New Email You Want:");
                    getchar();
                    gets(S[counter].email);
                }
                printf("\nEmail Has Been Modified\n");
                break;
            case '7':
                return;
            default:
                printf("Wrong Number Please choose Number From 1 and 7\n\n");
            }
        }
    }
    else
    {
        int y,j,z=0;
        printf("Please Choose Which Contact Do You Want For Example(If The 1st Press 1):");
        scanf("%d",&y);
        printf("\n");
        while (y==0||y>counter||y<0)
        {
            printf("invalid, Please Choose Which Contact Do You Want: For Example (If The 1st Press 1)\n");
            scanf("%d",&y);
            printf("\n");
        }
        counter=0;
        for(int i=0; i<number; i++)
        {
            if (strcasecmp(M_Last_Name,S[i].last_name)==0)
            {
                counter++;
                if(counter==y)
                {
                    j=i;
                }
            }
        }
        while (1)
        {
            printf(" \nPlease Choose What Do You Want To Modify\n\n Last Name Enter:1\n First Name Enter:2\n Date of Birth Enter:3\n Address Enter:4\n Phone Number Enter:5\n Email Enter:6\n Exit Enter :7\n ");
            printf("Enter Your Choice: ");
            scanf("%s",x);
            if (strlen(x)==1)
            {
            switch(*x)
            {
            case '1':
                printf("Please Enter The New Last Name You Want :");
                scanf("%s",S[j].last_name);
                printf("\nLast Name Has Been Modified\n");
                break;
            case '2':
                printf("Please Enter The New First Name You Want: ");
                scanf("%s",S[j].first_name);
                printf("\nFirst Name Has Been Modified\n");
                break;
            case '3':
                printf("Please Enter The New Date of Birth You Want:\n");
                printf("Enter the Day:");
                scanf("%d",&S[j].date.day);
                printf("Enter the Month:");
                scanf("%d",&S[j].date.month);
                printf("Enter the Year:");
                scanf("%d",&S[j].date.year);
                while (S[j].date.day>31||S[j].date.day<=0||S[j].date.month>12||S[j].date.month<=0||S[j].date.year>2021||S[j].date.year<=0||S[j].date.month==2&&S[j].date.day>29||S[j].date.month==4&&S[j].date.day>30||S[j].date.month==6&&S[j].date.day>30||S[j].date.month==9&&S[j].date.day>30||S[j].date.month==11&&S[j].date.day>30)
                {
                    printf("\nWrong Date of Birth\n");
                    printf("\nPlease Enter The New Date of Birth\n\n");
                    printf("Enter the Day: ");
                    scanf("%d",&S[j].date.day);
                    printf("Enter the Month: ");
                    scanf("%d",&S[j].date.month);
                    printf("Enter the Year: ");
                    scanf("%d",&S[j].date.year);
                }
                printf("\nDate of Birth Has Been Modified\n");
                break;
            case '4':
                printf("Please Enter The New Address You Want: ");
                getchar();
                gets(S[j].address);
                break;
            case '5':
                printf("Please Enter The New Phone Number You Want: ");
                scanf("%s",S[j].phone_number);
                while (!IsValidNumber(S[j].phone_number))
                {
                    printf("Number Is Invalid\n");
                    printf("Please Enter The Phone Number You want: ");
                    scanf("%s",S[j].phone_number);
                }
                printf("\nPhone Number Has Been Modified\n");
                break;
            case '6':
                printf("Please Enter The New Email You Want:");
                getchar();
                gets(S[j].email);
                while (IsValidEmail(S[j].email)==0)
                {
                    printf("Invalid Email\n\n");
                    printf("Please Enter The Email\n");
                    getchar();
                    gets(S[j].email);
                }
                printf("\nEmail Has Been Modified\n");
                break;
            case '7':
                return;
            default:
                printf("Wrong Number Please choose Number From 1 and 7\n");
            }
            }
            else
            {
                printf("\nWrong Number Please choose Number From 1 and 7\n");
            }
        }
    }
}
void save()
{
    int i;
    FILE*f2;
    f2=fopen("phonebook.txt","w");
    for(i=0; i<number; i++)
    {
        fprintf(f2,"%s,",S[i].last_name);
        fprintf(f2,"%s,",S[i].first_name);
        fprintf(f2,"%d-%d-%d,",S[i].date.day,S[i].date.month,S[i].date.year);
        fprintf(f2,"%s,",S[i].address);
        fprintf(f2,"%s,",S[i].phone_number);
        fprintf(f2,"%s\n",S[i].email);
    }
    fclose(f2);
    printf("The changes Have Been Saved\n\n");
}
int main()
{
    char x[20];
    while(1)
    {
        printf(" Please Choose What You Want To Do\n\n Load The Data Enter:1\n Search For Contact Enter:2\n Add Contact Enter:3\n Delete Contact Enter:4\n Modify Contact Enter:5\n Print contact:6\n Save Changes Enter:7\n Quit The Program Enter:8\n\n Press Your Choice:");
        scanf("%s",x);
        printf("\n");
        if (strlen(x)==1)
        {
            switch(*x)
            {
            case '1':
                load();
                break;
            case '2':
                query();
                break;
            case '3':
                ADD();
                break;
            case '4':
                DELETE();
                break;
            case '5':
                modify();
                break;
            case '6':
                print();
                break;
            case '7':
                save();
                break;
            case '8':
                exit(0);
            default:
                printf("     Wrong Choice Please Choose Number From 1 to 8:\n\n");
            }
        }
        else
        {
            printf("     Wrong Choice Please Choose Number From 1 to 8:\n\n");
        }
    }
    return 0;
}
