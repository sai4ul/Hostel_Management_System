//BUBT Hostel Management System
//Password: bubt

#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<dos.h>                     //contains _dos_getdate


                        //password bubt
char catagories[][15]={"Fllor one","Fllor two","Fllor three"};


void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
//void show_mouse(void);
void Password();
void issuerecord();
void loaderanim();

//list of global files that can be acceed form anywhere in program
FILE *fp,*ft,*fs;


COORD coord = {0, 0};



//list of global variable
int s;
char findbook;
char password[10]={"bubt"};

void gotoxy (int x, int y)
{
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Author[20];


    int quantity;
    float Price;

    int count;
    int rackno;

    char *cat;

    struct meroDate issued;
    struct meroDate duedate;
};


struct books a;
main()
{
    Password();
    getch();
}
    void mainmenu()
    {
    system("cls");
    int i;
    gotoxy(20,5);
    printf("1. Add student   ");

    gotoxy(20,7);
    printf("2. Delete");

    gotoxy(20,9);
    printf("3. View Book list");

    t();
    gotoxy(20,21);
    printf("Enter your choice:");

switch(getch())
{
        case '1':
        addbooks();
        break;
        case '2':
        deletebooks();
        break;

        case '3':
        viewbooks();
        break;
        case '6':
default:
        {
            gotoxy(10,23);
            printf("Wrong Password!!");

            if(getch())
            mainmenu();
        }
}
}

       //Add of the book

void addbooks(void)    //funtion that add books
{
    int i;

    gotoxy(20,7);
    printf("1. First Fllor");
    gotoxy(20,9);
    printf("2. Second Fllor");
    gotoxy(20,11);
    printf("3. Third Fllor");
    gotoxy(20,13);
    printf("4. Fourth Fllor");
    gotoxy(20,15);
    printf("5. Fifth Fllor");
    gotoxy(20,17);
    printf("6. Seven Fllor");
    gotoxy(20,19);
    printf("7. Back");


    printf("Enter your choice:");
    scanf("%d",&s);
    if(s==7)

    mainmenu() ;
    system("cls");
    fp=fopen("sai4ul.txt","ab+");
    if(getdata()==1)
    {
        a.cat=catagories[s-1];
        fseek(fp,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fp);
        fclose(fp);
        gotoxy(21,14);
        printf("The record is sucessfully saved");

        if(getch()=='n')
        mainmenu();
        else
        system("cls");
        addbooks();
    }
}

void deletebooks()    //function that delete items from file fp
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
        system("cls");
        gotoxy(10,5);
        printf("Enter the Book ID to  delete:");
        scanf("%d",&d);
        fp=fopen("sai4ul.txt","rb+");
        rewind(fp);
        while(fread(&a,sizeof(a),1,fp)==1)
        {
            if(a.id==d)
            {
                gotoxy(10,7);
                printf("The book record is available");
                gotoxy(10,8);
                printf("Book name is %s",a.name);
                gotoxy(10,9);
                printf("Rack No. is %d",a.rackno);
                findbook='t';
            }
        }

        if(findbook!='t')
        {
            gotoxy(10,10);
            printf("No record is found modify the search");
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
                    printf("The record is sucessfully deleted");
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


void viewbooks(void)  //show the list of book persists in library
{
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("            Bangladesh University of Business Technology    ");
    gotoxy(2,2);
    printf("\n");
    gotoxy(3,3);
    printf("   Fllor_No        ID    Student_Name     AUTHOR       QTY     PRICE ");
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
    printf("%s",a.Author);
    gotoxy(50,j);
    printf("%d",a.quantity);
    gotoxy(57,j);
    printf("%.2f",a.Price);
    gotoxy(69,j);
    printf("%d",a.rackno);
    printf("\n\n");
    j++;
    i=i+a.quantity;
    }
    gotoxy(3,25);
    printf("Total Books =%d",i);
    fclose(fp);
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

                    // add students
int getdata()
{
    int t;
    gotoxy(20,5);
    gotoxy(46,5);
    gotoxy(20,6);
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

    printf("Category:");
    gotoxy(31,5);

    printf("%s",catagories[s-1]);
    gotoxy(21,6);
    printf("STD ID:\t");
    gotoxy(30,6);
    scanf("%d",&t);
    if(checkid(t) == 0)
    {
    gotoxy(21,13);
    printf("\a Student id exists\a");
    getch();
    mainmenu();
    return 0;
    }
    a.id=t;
    gotoxy(21,7);
    printf("STD Name:");gotoxy(33,7);
    scanf("%s",a.name);
    gotoxy(21,8);
    printf("Author:");gotoxy(30,8);
    scanf("%s",a.Author);
    gotoxy(21,9);
    printf("Quantity:");gotoxy(31,9);
    scanf("%d",&a.quantity);
    gotoxy(21,10);
    printf("Price:");gotoxy(28,10);
    scanf("%f",&a.Price);
    gotoxy(21,11);
    printf("Rack No:");gotoxy(30,11);
    scanf("%d",&a.rackno);
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
{
    time_t t;
    time(&t);
    printf("Date and time:%s\n",ctime(&t));

    return 0 ;
}

void Password(void) //for password option
{
    gotoxy(10,10);
    char d[25]="Login only admin";
    char ch,pass[10];
    int i=0,j;

    gotoxy(10,10);
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
    }else
        {
            gotoxy(15,16);
            printf("\a Incorrect Password");

        }
}
