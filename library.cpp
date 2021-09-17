//============================================================================
// Name        : Library.cpp
// Author      : MEHMET BATUHAN ORAK
// Copyright   : Your copyright notice
// Description : Library in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <iostream>
#include<windows.h>//sleep()
#include<conio.h> //getch()
#include <unistd.h>//sleep()
#include<string.h>   //strcmp()


using namespace std;
FILE *fp,*ft;
 struct kitap
 {
   int id;
   char name[30];
   char Author[30];
 };
  void panel(void);//printing actions
  void mainmenu(void); //printing mainmenu
  void addbooks(void);// add a book in list
  void deletebooks(void);// delete a book in list
  void editbooks(void);// edit a book in list
  void searchbooks(void);// search a book in list by name
  void searchbooksfora(void);//search a book in list by author
  void viewbooks(void);// viewing book list
   void viewforedit(void);// viewing book list for functions(addbooks ,deletebooks...)
   int b;
   struct kitap a;
  int  checkid(int);//in the list checking id if it exist or not
  int main()
  {
      printf("Welcome to our library! Please select the action you want to take! \n");
      panel();
      getch();
      return 0;
   }
  void panel()
  {
	 int p;
	printf("Press 1 to Add Books \n");
	printf("Press 2 to Delete Books \n");
	printf("Press 3 to Organize Books \n");
	printf("Press 4 to Search Books  \n");
	printf("Press 5 to List Books \n");
	printf("Press 6 to Exit\n");
	scanf("%d",&b);
    switch(b)
	{   case 1:
              addbooks();
                     break;
        case 2:
                 deletebooks();
                      break;
        case 3:
                editbooks();
                     break;
        case 4:

             system("cls");
             viewforedit();
             printf("Please select the action you want to search with by name or by author \n");
             printf("Press 1 to search for by name\n");
             printf("Press 2 to search for by author\n");
             printf("Press any button without 1 and 2 to back menu\n");
             scanf("%d",&p);
           	switch(p)
				{

                	 case 1:
                     searchbooks();
                         break;
                     case 2:
			         searchbooksfora();
			         break;
			         default:
			          mainmenu();
			          break;
				}

                     break;
        case 5:
                 viewbooks();
                     break;
        default:
        	exit(0);
                      break;


   }
  }
   void mainmenu()
  {
    system("cls"); //clear the interface
    viewforedit();
    panel();

   }
    void addbooks(void)
	{
	    system("cls"); //clear the interface
	    viewforedit();//printing list
    	fp=fopen("lib.dat","ab+"); //file open or create a file for update in binary mode; writing is done at the end of the file.
    	int get;
    	printf("Add Book ID:\t");
    	scanf("%d",&get);

    	if(checkid(get)== 0) //book exits
		{ printf("The book id already exists\n");
		  printf( "You have to use another id\n");
	   	  printf("Do you want to add a book (Y) or Backmenu (N)\n");
		    if(getch()!='n' )
	    	 {
			 addbooks();
	       	 }
	    	else
		    {
		     mainmenu();
		    }


		}
       else //There is no book with this id
        {
	        	a.id=get;
	        	printf("Book Name:");
	     	    scanf("%s",a.name);
	        	printf("Author:");
	        	scanf("%s",a.Author);
	        	printf("Do you want to save (Y ): or Backmenu(N)");
	         if(getch()!='n')
	         {
                 fseek(fp,0,SEEK_END);//sets the file position of End of file.
                 fwrite(&a,sizeof(a),1,fp);//write user data over  file
                 fclose(fp);//close file
                 printf("\nThe Record Is Sucessfully Saved\n");
                 printf("A new menu is printing, Please wait!");
                 sleep(2);
                 viewforedit();//printing list
                 panel();

             }
             else
			 {
             	 fclose(fp);//close file
			     mainmenu();
			 }
     	}
     }
    void deletebooks(void)
	{
	     system("cls");//clear the interface
	     viewforedit();//printing list
	     printf("Please enter the ID of the book you want to delete.\n ");
	     fp=fopen("lib.dat","ab+");//file open or create a file for update in binary mode; writing is done at the end of the file.
	     int get2;
	     scanf("%d",&get2);

	     if (checkid(get2)==0) //if book exits in librarry
	     {
		     printf("name :%s \t",a.name);
	         printf("author:%s\n",a.Author);
             printf("Do you want to delete a book (Y): or Backmenu(N)\n");
                 if(getch()!='n')
	        	 {
                     ft=fopen("test.dat","wb+");  //temporary file for delete
                     rewind(fp);//move pointer at the begining of file
                     while(fread(&a,sizeof(a),1,fp)==1)//This reads the contents of a structure variable from the file
                      {
                         if(a.id!=get2)
                             {
                                  fseek(ft,0,SEEK_CUR);//sets the file position of current position
                                 fwrite(&a,sizeof(a),1,ft); //write all in tempory file except that we want to delete
                             }
                       }
                     fclose(ft);//close file
                     fclose(fp);//close file
                     remove("lib.dat");//delete old data
                     rename("test.dat","lib.dat"); //copy all item from temporary file to fp except that we want to delete
                     printf("Registration Successfully Deleted\n");
                     printf("A new menu is printing, Please wait!");
                     sleep(2);
                     viewforedit();
                     panel();
			     }
			   else
			   {
			   	fclose(fp);//close file
			    mainmenu();

               }
         }


	    else
		{    fclose(fp);//close file
		     printf("You dont have this id in your library.if you want to delete,you must enter true id \n.");
	   	     printf("Do you want to delete a book (Y): or Backmenu (N)\n");
		     if(getch()!='n')
	         {
			  	deletebooks();
	        }
		     else
	       	{
	         	mainmenu();
		     }
		}
    }

    void editbooks(void)
	{
	    system("cls");//clear the interface
	    viewforedit();//printing list
    	printf("Please enter the ID of the book you want to edit!\n ");

	    int get2;
	    scanf("%d",&get2);
	    fp=fopen("lib.dat","rb+");//Open an existing file for update (reading and writing) in binary mode.


	    if (checkid(get2)==0) //if book exits in librarry
	    {
		     printf("This here your book  \t");
	         printf("Name :%s \t",a.name);
	         printf("Author:%s\n",a.Author);
	         printf("Do you want to edit a book ( Y ): or Backmenu (N)\n");



			    if(getch()!='n')
			    {
			    	 printf("Enter New Name:");scanf("%s",a.name);
			    	 printf("Enter New Author:");scanf("%s",a.Author);
			  	     printf("The record is modified\n");
			  	     fseek(fp,ftell(fp)-sizeof(a),0);//sets the file position of what will change book
                     fwrite(&a,sizeof(a),1,fp);//write user data what will change
                     fclose(fp);//close file
	        	     printf("A new menu is printing, Please wait!");
                     sleep(2);
                     viewforedit();//printing list
                     panel();
                }
                else
				{
			    	fclose(fp);//close file
				    mainmenu();
				 }
		 }

	   else
	   {
	   	     fclose(fp);//close file
	         printf("There is no book registered with this ID in your library!\n");
	   	     printf("Do you want to edit a book (Y) or Backmenu (N)\n");
		      if(getch()!='n')
			  {
	         	editbooks();
			  }
		     else
			 {
	      	    mainmenu();
			  }
	   }
	}
    void searchbooks(void)
	{
	     system("cls");//clear the interface
	     viewforedit();//printing list
      	 char s[30];
	     printf("Please enter what you search name\n ");
	     fp=fopen("lib.dat","rb+"); //open file for reading propose
         rewind(fp);   //move pointer at the begining of file
	     printf("Enter Book Name:");
	     scanf("%s",s);
	     int d=0;
	     while(fread(&a,sizeof(a),1,fp)==1) //This reads the contents of a structure variable from the file
         {
                 if(strcmp(a.name,(s))==0) //checks whether a.name is equal to s or not
                     {
	                     printf("The Book Is Available \t");
	                     printf("id :%d:name:%s author :%s\n",a.id,a.name,a.Author);
	                        d++;
	                 }
	      }
	      fclose(fp);//close file
	     if(d!=0)
	     {
		      printf("You have %d book in your library with this name \n",d);
			  printf("Do you want to make a new search (Y) or Back menu(N) ");
	          if(getch()!='n')
		         {
				   searchbooks();
	              }
	       	else
			 {
	     	mainmenu();
			 }
	     }
	   if(d==0)
	 	{
		     printf("There is no book registered with this name in your library\n ");
		     printf("Do you want to make a new search (Y) or Back menu(N) ");
		      if(getch()!='n')
		     {
		     searchbooks();
	         }
		     else
		     {
		     mainmenu();
			 }
	  	}


     }
    void searchbooksfora(void)
	{
	     system("cls");//clear the interface
	     viewforedit();//printing list
	     char s[30];
	     printf("Please enter what you search author\n ");
	     fp=fopen("lib.dat","rb+"); //open file for reading propose
         rewind(fp);   //move pointer at the begining of file
	     printf("Enter Book author:");
	     scanf("%s",s);
	     int d=0;
	     while(fread(&a,sizeof(a),1,fp)==1) //This reads the contents of a structure variable from the file
         {
             if(strcmp(a.Author,(s))==0) //checks whether a.name is equal to s or not
              {
	             printf("The Book Is Available \t");
	             printf("id :%d:name:%s authour :%s\n",a.id,a.name,a.Author);
	              d++;
	          }
	     }
	     fclose(fp);//close file
	     if(d!=0)
	     {
	     	 printf("You have %d book in your library with this author \n",d);
	         printf("Do you want to make a new search (Y) or Back menu(N) ");
	         if(getch()!='n')
		     {
			 searchbooks();
	         }
	     	else
			 {
		     mainmenu();
			 }
	     }
	     if(d==0)
		 {
		     printf("There is no book registered with this Author in your library\n ");
		     printf("Do you want to make a new search (Y) or Back menu(N) ");
		     if(getch()!='n')
		     {
			  searchbooks();
	         }
		     else
			 {
		     mainmenu();
			 }
	  	}


     }

    void viewbooks(void)
	{
	     system("cls");//clear the interface
	     printf("view\t\t\t\t\t\t\tview");
	     fp=fopen("lib.dat","rb");//open file for reading propose
	     printf("\n\tid\t\tNAME\t\tauthor");
	     int c=0;
	     int counter=0;
         while(fread(&a,sizeof(a),1,fp)==1) //This reads the contents of a structure variable from the file
         {

             printf("\n\t%d\t\t%s\t\t%s",a.id,a.name,a.Author);
             c++;
	     }
	     printf("\nYou have %d books on your library",counter);
	     fclose(fp);//file close
	     if (c==0)
         {
		   printf("\nNO RECORDS!!\n");
		  }
		 printf("\n");
         printf("Do you want to Back menu(Y) or Exit (N) ");

             if(getch()!='n')  mainmenu();
            else exit(0);





     }
    void viewforedit(void)
	{
	      system("cls");//clear the interface
	     printf("view\t\t\t\t\t\t\tview");
	     fp=fopen("lib.dat","rb");//open file for reading propose
    	 printf("\n\tid\t\tNAME\t\tauthor");
	     int c=0;
         while(fread(&a,sizeof(a),1,fp)==1) //This reads the contents of a structure variable from the file
         {
             printf("\n\t%d\t\t%s\t\t%s",a.id,a.name,a.Author);
             c++;
	      }
	     fclose(fp);//file close
	     if (c==0)
         {
		     printf("\nNO RECORDS!!\n");
		  }
		 printf("\n");
     }

    int checkid(int dondur)
	 {
	     rewind(fp); //move pointer at the begining of file
         while(fread(&a,sizeof(a),1,fp)==1) //This reads the contents of a structure variable from the file and stores it in the variable

	         if(a.id==dondur) return 0;  //returns 0 if book exits
             return 1; //return 1 if it not
	 }












