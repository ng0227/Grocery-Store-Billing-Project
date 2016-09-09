//****************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdlib.h>
//***************************************************************
//                   STRUCTURE USED IN PROJECT
//***************************************************************

struct product
{
 int pno;
 char name[50];
 float price,qty,tax,dis;
 int initial_stock;
 int stock_left;
};


struct bill
{
    char name[10][10];
    int pr_no[10];
    int pr_quantity[10];
    float price[10];
    float amt[10];
    float damt[10];
    float total;
    int bill_no;
    int c;
};

//****************************************************************
//    	global declaration for stream object, object
//****************************************************************

FILE *fp;
struct product pr;
struct bill bi;


	void create_product(struct product*p)
	{
	 printf("\nPlease Enter The Product No. of The Product : ");
	 scanf("%d",&p->pno);
	 printf("\nPlease Enter The Name of The Product : ");
	 scanf("%s",&p->name);
	 printf("\nPlease Enter The Price of The Product : ");
	 scanf("%f",&p->price);
	 printf("\nPlease Enter The Discount  : ");
	 scanf("%f",&p->dis);
	 printf("\nPlease Enter the stock quantity(IN INTEGERS):");
	 scanf("%d",&p->initial_stock);
	 p->stock_left=p->initial_stock;
    }

	void show_product(struct product*p)
	{
	 printf("\nThe Product No. of The Product :%d ",p->pno);
	 printf("\nThe Name of The Product :%s \n",p->name);
	 printf("The Price of The Product : %f ",p->price);
	 printf("\nDiscount :%f %%",p->dis);
	 printf("\nStock Quantity(Available) : %d",p->stock_left);
    }

  int retpno(struct product p)
  {return p.pno;}

  float retprice(struct product p)
  {return p.price;}

  int retstockL(struct product p)
  {
      return p.stock_left;
  }
  int retIstock(struct product p)
  {
      return p.initial_stock;
  }

 /* char* retname(struct product p)
  {
      char *name=p.name;
      return name;
  }
*/
  int retdis(struct product p)
  {return p.dis;}


//***************************************************************
//    	function to write in file
//****************************************************************

void write_product()
   {
    char ch='y';
    fp=fopen("Shop.dat","a");
    if(fp==NULL)
    {
        puts("cannot open file");
        exit(0);
    }

    while(ch=='y'||ch=='Y')
    {
      create_product(&pr);
      fwrite(&pr,sizeof(pr),1,fp);
      printf("\nThe Product Has Been Created ");
      printf("\n\nWant to create more products?(y/n)....");
      fflush(stdin);
      ch=getche();
    }
      fclose(fp);
      getch();
   }


//***************************************************************
//    	function to read all records from file
//****************************************************************


void display_all()
{
    system("cls");
    printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
    fp=fopen("Shop.dat","rb");
    if(fp==NULL)
    {
        printf("cannot open file");
        exit(0);
    }
    rewind(fp);

    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
       show_product(&pr);
       printf("\n\n====================================\n");
       getch();
    }
    fclose(fp);
    getch();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_sp(int n)
{
    int flag=0;
    fopen("Shop.dat","rb");
    if(fp==NULL)
    {
        printf("cannot open file");
        exit(0);
    }
    rewind(fp);

    while(!feof(fp))
    {
       fread(&pr,sizeof(pr),1,fp);
       	if(retpno(pr)==n)
		{
		 system("cls");
		 show_product(&pr);
		 flag=1;
		}
	}

    fclose(fp);
   if(flag==0)
     printf("\n\nrecord not exist");
   getch();
}


//****************************************************************
//    	function to modify record of file
//****************************************************************


void modify_product()
{
    int no,found=0;
    system("cls");
    printf("\n\n\tTo Modify ");
    printf("\n\nPlease Enter The Product No. of The Product: ");
    scanf("%d",&no);
    fp=fopen("Shop.dat","r+b");
    if(fp==NULL)
    {
        printf("cannot open file");
        exit(0);
    }

    rewind(fp);

    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(retpno(pr)==no)
        {
            found=1;
            show_product(&pr);
            printf("\n\nPlease Enter The New Details of Product\n");
            struct product np;
            create_product(&np);

            fseek(fp,-sizeof(pr),SEEK_CUR);
            fwrite(&np,sizeof(np),1,fp);
            printf("Record Updated");
            break;
        }
    }

    fclose(fp);
    if(found==0)
    printf("\n\n Record Not Found ");
    getch();
}


//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_product()
   {
    FILE *ft;
    int no,found;
    char ch1='y';
    system("cls");
    printf("\n\n\n\tDelete Record");
    while(ch1=='y'||ch1=='Y')
    { found=0;
      printf("\nPlease Enter The product no. of The Product You Want To Delete:  ");
      scanf("%d",&no);

      ft=fopen("Temp.dat","wb");

      fp=fopen("Shop.dat","rb");
      rewind(fp);

      while(fread(&pr,sizeof(pr),1,fp)==1)
      {
          if(retpno(pr)!=no)
            fwrite(&pr,sizeof(pr),1,ft);

            else
            {
               found=1;
               printf("Record Deleted");
            }
    }

	  if(found==0)
	   printf("\nRecord not found");

    fclose(fp);
    fclose(ft);
    remove("Shop.dat");
    rename("Temp.dat","Shop.dat");

    printf("\nWant to delete another record?(y/n).....");
    fflush(fp);
    fflush(ft);
    ch1=getche();
   }
    getch();
}


//***************************************************************
//    	function to display all products price list
//****************************************************************

    void menu()
    {
       system("cls");
       fp=fopen("Shop.dat","rb");
       if(fp==NULL)
       {
	     printf("ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File");
	     printf("\n\n\n Program is closing ....");
	     getch();
	     exit(0);
       }

        printf("\n\n\t\tProduct MENU\n\n");
	    printf("=============================================================================================\n");
	    printf("P.NO.\t\tNAME\t\t\t\tPRICE\t\t\tSTOCK AVAILABALE\n");
	    printf("=============================================================================================\n");

	   while(fread(&pr,sizeof(pr),1,fp)==1)
	    {
          printf("%d\t\t%s\t\t\t\t%f\t\t\t\%d\n",retpno(pr),pr.name,retprice(pr),retstockL(pr));
	    }
	   fclose(fp);
    }


//***************************************************************
//   UPDATE STOCK
//****************************************************************

void update_stock(int orderNo[],int quantity[],int c)
{
    fp=fopen("Shop.dat","r+b");
		 if(fp==NULL)
         {
             printf("cannot open file");
             exit(0);
         }
         rewind(fp);

         int i;
         for(i=0;i<c;i++)
         {
            rewind(fp);
            while(fread(&pr,sizeof(pr),1,fp)==1)
            {
              if(retpno(pr)==orderNo[i])
              {
                  if(retstockL(pr)-quantity[i]<0)
                    ;
                  else
                  {
                    pr.stock_left=retIstock(pr)-quantity[i];
                    fseek(fp,-sizeof(pr),SEEK_CUR);
                    fwrite(&pr,sizeof(pr),1,fp);
                    break;
                  }
              }
            }
         }

         fclose(fp);
}




//***************************************************************
//   DISPLAY STOCK
//****************************************************************

void stock()
{
    system("cls");
    printf("\n\n\n\tDISPLAY STOCK !!!\n\n");
    fp=fopen("Shop.dat","rb");
    if(fp==NULL)
    {
        printf("cannot open file");
        exit(0);
    }
    rewind(fp);

     printf("P.NO.\t\tNAME\t\t\t\tINITIAL STOCK\t\t\tSTOCK AVAILABALE\n\n");

    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      printf("\n%d\t\t%s\t\t\t\t\t%d\t\t\t\t%d",retpno(pr),pr.name,retIstock(pr),retstockL(pr));
    }
    fclose(fp);
    getch();
}









//***************************************************************
//   STORING BILL IN FILE
//****************************************************************


       void addBill(int orderNo[],int quantity[],float total,int billNo,int c,float amt[],float damt[])
       {
          struct bill bi1;

          FILE *fp,*ft;
          ft=fopen("BILL.dat","a+b");
          if(ft==NULL)
         {
             printf("cannot open file");
             exit(0);
         }



         fp=fopen("Shop.dat","rb");
		 if(fp==NULL)
         {
             printf("cannot open file");
             exit(0);
         }

         int i;
         for(i=0;i<c;i++)
         {
            while(fread(&pr,sizeof(pr),1,fp)==1)
           {
			 if(retpno(pr)==orderNo[i])
			 {
               if(retstockL(pr)-quantity[i]<0)
                {
                    bi1.pr_no[i]=0;
                    strcpy(bi1.name[i],pr.name);
                }
               else
               {
                  bi1.pr_no[i]=orderNo[i];
                  strcpy(bi1.name[i],pr.name);
                  bi1.pr_quantity[i]=quantity[i];
                  bi1.amt[i]=amt[i];
                  bi1.damt[i]=damt[i];
                  bi1.price[i]=retprice(pr);
               }
			 }
           }
           fflush(fp);
           rewind(fp);
         }

             bi1.bill_no=billNo;
             bi1.total=total;
             bi1.c=c;
             fwrite(&bi1,sizeof(bi1),1,ft);
             fclose(ft);
             fclose(fp);

             update_stock(orderNo,quantity,c);
             return;
       }




//****************************************************************
//    	function to place order and generating bill for Products
//****************************************************************

   void place_order()
   {
    int  order_arr[50],quan[50],c=0;
    float amt,damt,total=0;
    char ch='y';
    menu();
    printf("\n============================");
    printf("\n    PLACE YOUR ORDER");
    printf("\n============================\n");
    do{
	 printf("\nEnter The Product No. Of The Product : ");
	 scanf("%d",&order_arr[c]);
	 printf("Quantity in number : ");
	 scanf("%d",&quan[c]);
	 c++;
	 printf("\nDo You Want To Order Another Product ? (y/n)...");
	// scanf("%c",&ch);
	ch=getche();
    }while(ch=='y' ||ch=='Y');



     printf("\nThank You For Placing The Order");
     getch();
     system("cls");
     printf("\n\n********************************INVOICE***********************************************\n");
     printf("\nPr No.\tPr Name\tQuantity \tPrice \t\tAmount \t\tAmount after discount\n");
     int i;
     float amt1[10],damt1[10];
     for(i=0;i<=c;i++)
       {
		 fp=fopen("Shop.dat","rb");
		 if(fp==NULL)
         {
             printf("cannot open file");
             exit(0);
         }

         while(fread(&pr,sizeof(pr),1,fp)==1)
         {
			 if(retpno(pr)==order_arr[i])
             {
                 if(retstockL(pr)-quan[i]<0)
                 {
                     printf("\n%d\t%s\t STOCK IS INSUFFICIENT FOR THE INPUT QUANTITY\n",order_arr[i],pr.name);
                 }
                 else
                 {
                   amt=retprice(pr)*quan[i];
                   amt1[i]=amt;
                   damt=amt-(amt*retdis(pr)/100);
                   damt1[i]=damt;
                   printf("\n%d\t%s\t%d\t\t%f\t%f\t\t%f",order_arr[i],pr.name,quan[i],retprice(pr),amt,damt);
                   total+=damt;
                 }
             }
         }
       }
         fclose(fp);
         printf("\n\n\n\t\t\t\t\t\t\t    TOTAL = Rs. %f ",total);
         time_t t;
         time(&t);
         printf("\nBILL date and time: %s",ctime(&t));

         fp=fopen("BILL.dat","rb");
         if(fp==NULL)
         {
             printf("cannot open file");
             exit(0);
         }
         fseek(fp,0,SEEK_END);
         int len=ftell(fp);
         if(len>0)
         {
             fseek(fp,-sizeof(bi),SEEK_END);
             fread(&bi,sizeof(bi),1,fp);
             i=bi.bill_no+1;
         }
         else
         {
             i=1;
         }
         fclose(fp);

         printf(" \nBILL No: %d\n",i);

         addBill(order_arr,quan,total,i,c,amt1,damt1);
         getch();
       }






//****************************************************************
//    	SEARCHING FOR BILL
//****************************************************************

       void billDetails()
       {
          system("cls");
          fp=fopen("BILL.dat","rb");
		  if(fp==NULL)
           {
             printf("cannot open file");
             exit(0);
           }

          int n,i,flag=0;
          printf("Enter the BILL NUMBER(only in integer):");
          scanf("%d",&n);
          rewind(fp);

          while(fread(&bi,sizeof(bi),1,fp)==1)
          {
              if(bi.bill_no==n)
              {
                  system("cls");
                  printf("\n\n********************************INVOICE***********************************************\n");
                  printf("\n\nBILL NO:%d \n\n",bi.bill_no);
                  printf("\nPr No.\tPr Name\tQuantity \tPrice \t\tAmount \t\tAmount after discount\n");
                 for(i=0;i<bi.c;i++)
                  {
                   if(bi.pr_no[i]==0)
                    ;
                   else
                   {
                      printf("\n %d\t%s\t%d\t\t%f\t%f\t\t%f",bi.pr_no[i],bi.name[i],bi.pr_quantity[i],bi.price[i],bi.amt[i],bi.damt[i]);
                   }

                  }
                  printf("\n\n\n\t\t\t\t\t\t\t    TOTAL = Rs. %f ",bi.total);

                  flag=1;
                   break;
              }
          }
        if(flag==0)
            printf("NOT FOUND");

          fclose(fp);
          getch();
    }


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
 system("cls");
 printf("\n\n\n\n\n\t\t\t\t\tSUPER MARKET BILLING");
// printf("\n\n\n\n\t\t\t\t\t BILLING PROJECT");
 printf("\n\n\n  MADE BY : NAMAN GUPTA \n\t");
 printf("\n\n\n  COLLEGE : MAIT");
 getch();

}

//***************************************************************
//    	ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{
 system("cls");
  char ch2;
  int num;
  printf("\n\n\n\tADMIN MENU");
  printf("\n\n\t1.CREATE PRODUCT");
  printf("\n\n\t2.DISPLAY ALL PRODUCTS");
  printf("\n\n\t3.QUERY ");
  printf("\n\n\t4.MODIFY PRODUCT");
  printf("\n\n\t5.DELETE PRODUCT");
  printf("\n\n\t6.VIEW PRODUCT MENU");
  printf("\n\n\t7.SEARCH FOR BILL");
  printf("\n\n\t8.STOCK");
  printf("\n\n\t9.BACK TO MAIN MENU");
  printf("\n\n\tPlease Enter Your Choice (1-7):  ");
  scanf("%c",&ch2);
  switch(ch2)
  {
    case '1': system("cls");
	      write_product();
	      break;

    case '2': display_all();
	      break;

    case '3':  system("cls");
	       printf("\n\n\tPlease Enter The Product No. ");
	       scanf("%d",&num);
	       display_sp(num);
	       break;

      case '4': modify_product();
		break;

      case '5': delete_product();
		break;

      case '6': menu();
		getch();

      case '7': billDetails();
                break;

      case '8': stock();

      case '9': break;

      default:admin_menu();
   }
}

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
  char ch;
  intro();
  do
    {
	  system("cls");
	  printf("\n\n\n\tMAIN MENU");
	  printf("\n\n\t01. CUSTOMER");
	  printf("\n\n\t02. ADMINISTRATOR");
	  printf("\n\n\t03. EXIT");
	  printf("\n\n\tPlease Select Your Option (1-3):  ");
	  scanf("%c",&ch);
	  switch(ch)
	  {
		 case '1': system("cls");
			       place_order();
			       getch();
			       break;
         case '2': admin_menu();
		     	    break;
         case '3':exit(0);
	}
    }while(ch!='3');

    return 0;
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
