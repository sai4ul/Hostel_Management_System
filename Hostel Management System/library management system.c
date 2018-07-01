//Hostel Management system
// Password: bubt

#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>

char Floor_No[][15]={"1st Floor","2nd Floor","3rd Floor","4th Floor","5th Floor","6th Floor"};
void returnfunc(void);
void mainmenu(void);
void add_student(void);
void Remove_student(void);
void viewstd(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
void Password();
void loaderanim();


FILE *fp,*ft,*fs;
COORD coord = {0, 0};

int s;
char findbook;
char password[10]={"bubt"};
                                // X and Y coordinates(Password mid e state kora)
void gotoxy (int x, int y)
{
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


struct books
{
    int id;
    char stname[20];
    char name[20];
    char sit_number[20];
    int Room_No;
    int Advance;
    int count;
    int rackno;
    char *cat;
};

struct books a;
int main()
{
    Password();
    getch();
    return 0;
}


void mainmenu()
{
    system("cls");
    int i;
    gotoxy(20,3);
    printf(" Bangladesh University Of Business Technology");


    gotoxy(20,5);
    printf("\t\t 1. Add Student");
    gotoxy(20,7);
    printf("\t\t 2. Remove Student list");

    gotoxy(20,9);
    printf("\t\t 3. View Student list");
    gotoxy(20,20);
    t();

switch(getch())
    {
        case '1':
        add_student();
        break;
        case '2':
        Remove_student();
        break;

        case '3':
        viewstd();
        break;
        default:
        {
            gotoxy(10,23);
            printf("\t  Wrong Entry!!!!");
            if(getch())
            mainmenu();
        }
    }
}

void add_student(void)                      //funtion that add student in floor
{
    system("cls");
    int i;
    gotoxy(20,5);
    printf("Select Floor in Hostel");
    gotoxy(20,7);
    printf("\t  1. 1st Floor");
    gotoxy(20,9);
    printf("\t  2. 2nd Floor");
    gotoxy(20,11);
    printf("\t  3. 3rd Floor");
    gotoxy(20,13);
    printf("\t  4. 4th Floor");
    gotoxy(20,15);
    printf("\t  5. 5th Floor");

    gotoxy(20,17);
    printf("\t  6. 6th Floor");

    gotoxy(20,19);
    printf("\t  7. Back to main menu");

    gotoxy(20,22);
    printf("Enter your \:");
    scanf("%d",&s);
    if(s==7)

    mainmenu() ;
    system("cls");
    fp=fopen("sai4ul.txt","ab+");
    if(getdata()==1)
    {
        a.cat=Floor_No[s-1];
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        gotoxy(21,14);
        printf("The record is sucessfully saved");

                                                    //save command
        gotoxy(21,15);
        printf("Save any more?(Y / N):");
        if(getch()=='n')
            mainmenu();
        else
            system("cls");
            add_student();
    }
}


void Remove_student()    //function that delete items from file fp
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
        system("cls");
        gotoxy(10,5);
        printf("Enter Student ID:");
        scanf("%d",&d);
        fp=fopen("sai4ul.txt","rb+");
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
        if(a.id==d)
        {
            gotoxy(10,7);
            printf("Student record is available");
            gotoxy(10,8);
            printf("Student Name is %s",a.name);
            gotoxy(10,9);
            printf("Rack No. is %d",a.rackno);
            findbook='t';
        }
        }
        if(findbook!='t')
        {
            gotoxy(10,10);
            printf("Not Student ID  found!!!");
            if(getch())
            mainmenu();
        }
        if(findbook=='t' )
        {
        gotoxy(10,9);
        printf("Do you want to delete it?(Y/N):");
        if(getch()=='y')
        {
            ft=fopen("test.dat","wb+");  //temporary file for delete
            rewind(fp);
            while(fread(&a,sizeof(a),1,fp)==1)
            {
                if(a.id!=d)
                {
                fseek(ft,0,SEEK_CUR);
                fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that
                }                              //we want to delete
            }
            fclose(ft);
            fclose(fp);
            remove("sai4ul.txt");
            rename("test.dat","sai4ul.txt"); //copy all item from temporary file to fp except that
            fp=fopen("sai4ul.txt","rb+");    //we want to delete
            if(findbook=='t')
            {
                gotoxy(10,10);
                printf("Record is sucessfully deleted");
                gotoxy(10,11);
                printf("Delete another record?(Y/N)");
            }
        }
        else
        mainmenu();
        fflush(stdin);
        another=getch();
        }
    }
    gotoxy(10,15);
    mainmenu();
}



void viewstd(void)  //show student list
{
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("                Hostel Management System  Student List      ");
    gotoxy(2,2);//enter add
    gotoxy(3,3);
    printf(" Floor NO.    ID      Name      Sit No.      Room NO   Advance TK");

    j=4;
    fp=fopen("sai4ul.txt","rb");
    while(fread(&a,sizeof(a),1,fp)==1)
    {
        gotoxy(3,j);
        printf("%s",a.cat);
        gotoxy(16,j);
        printf("%d",a.id);
        gotoxy(22,j);
        printf("%s",a.name);
        gotoxy(36,j);
        printf("%s",a.sit_number);

        gotoxy(50,j);
        printf("%d",a.Room_No);

        gotoxy(57,j);
        printf("%d",a.Advance);
        printf("\n\n");
        j++;
        i=i+a.Room_No;
    }
    //gotoxy(3,25);
    //printf("Total Books =%d",i);
    //fclose(fp);
   gotoxy(35,25);
    returnfunc();
}


void returnfunc(void)
{
    {
    printf(" Press ENTER to return to main menu");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
                               //Enter student information
int getdata()
{
    int t;
    gotoxy(20,3);printf("Enter student information");

    gotoxy(46,5);
    gotoxy(46,6);
    gotoxy(20,7);
    gotoxy(46,7);
    gotoxy(20,8);
    gotoxy(46,8);
    gotoxy(20,9);
    gotoxy(46,9);
    gotoxy(20,10);
    gotoxy(46,10);
    gotoxy(20,11);
    gotoxy(46,11);

    gotoxy(21,5);
    printf("Floor No:");
    gotoxy(31,5);
    printf("%s",Floor_No[s-1]);
    gotoxy(21,6);
    printf("Std ID:");
    gotoxy(30,6);
    scanf("%d",&t);
    if(checkid(t) == 0)
    {
        gotoxy(21,13);
        printf("\t Student id already exists");
        getch();
        mainmenu();
        return 0;
    }
    a.id=t;
    gotoxy(21,7);
    printf("std Name:");gotoxy(33,7);
    scanf("%s",a.name);

    gotoxy(21,8);
    printf("sit No:");gotoxy(30,8);
    scanf("%s",a.sit_number);

    gotoxy(21,9);
    printf("Room No:");gotoxy(31,9);
    scanf("%d",&a.Room_No);

    gotoxy(21,10);
    printf("Adv.TK:");
    gotoxy(28,10);
    scanf("%d",&a.Advance);
    return 1;
}





int checkid(int t)  //check whether the book is exist in library or not
{
    rewind(fp);
    while(fread(&a,sizeof(a),1,fp)==1)
    if(a.id==t)
    return 0;  //returns 0 if book exits
    return 1; //return 1 if it not
}



int t(void) //for time
{}


             //for password option

void Password(void)
{
    system("cls");

   // char d[25]="    BUBT University  ";
    char ch,pass[10];
    int i=0,j;
    gotoxy(15,7);
    printf("Enter Password:");

    while(ch!=13)
    {
        ch=getch();

        if(ch!=13 && ch!=8)
        {
            putch('*');
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0';
    if(strcmp(pass,password)==0)
    {
        mainmenu();
    }
    else
    {
        gotoxy(15,16);
        printf("\t Incorrect Password !!!!!");
        getch();
        Password();
    }
}
