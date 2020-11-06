#include </usr/include/mysql/my_global.h>
#include </usr/include/mysql/mysql.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void validate(MYSQL* connection){
if(connection==NULL){
printf(" Can not establish the conenction!");
exit(0);
}
fprintf(stderr,"error:%s",mysql_error(connection));

exit(0);

}

void connect_to_mysql_server(){

MYSQL *connection_init=mysql_init(NULL);

connection_init=mysql_real_connect(connection_init,"localhost","patrick","@vernom28_niyo",NULL,3306,NULL,0);

if(connection_init==NULL)
validate(connection_init);



int query_result=mysql_query(connection_init,"create database smartbook");
if(query_result)
validate(connection_init);


}


MYSQL *connect_to_db(){

MYSQL *connection_init=mysql_init(NULL);


connection_init=mysql_real_connect(connection_init,"localhost","patrick","@vernom28_niyo","smartbook",3306,NULL,0);

if(connection_init==NULL)
validate(connection_init);


return connection_init;
}



void create_table(MYSQL *connection){
    int query_result = mysql_query(connection,"CREATE TABLE users1 (id INT PRIMARY KEY AUTO_INCREMENT,user_name TEXT,user_age INT)");

    if(query_result){
        fprintf(stderr,"%s",mysql_error(connection));
    }
}







//payement function
void payment(MYSQL*connection,char journey_code[2]){
     system("clear");
    char firstname[50],lastname[50],phone[20],pin[5];
    printf("\n\n                BOOK NOW");
    printf("\n\n                      CUSTOMER NAMES");
    printf("\n\n                         First Name: ");
    scanf("%s",firstname);
    printf("\n\n                         Last Name: ");
    scanf("%s",lastname);
    system("clear");
    printf("\n\n                MOBILE ACCOUNT");
    printf("\n\n                Mobile Phone Number: ");
    scanf("%s",phone);

    if(strlen(phone) != 10){
        system("clear");
        printf("\n\n               INVALID PHONE 404");
        
        printf("\n\n                Re-enter Mobile Phone Number: ");
        scanf("%s",phone);

          if(strlen(phone) != 10){
                printf("\n\n               INVALID PHONE AGAIN");
                exit(-1);
          }

    }
   
char pf_mode[256];     // Destination string
    pf_mode[3] = 0;
    strncpy(pf_mode,phone, 3);
char curr_phone[40];
strcpy(curr_phone,phone);    

    printf("\n\n                PIN: ");
    scanf("%s",pin);

    if(strlen(pin) != 5){
        system("clear");
        printf("\n\n               INVALID PIN 404");
        
        printf("\n\n                Re-enter PIN: ");
        scanf("%s",pin);

          if(strlen(pin) != 5){
                printf("\n\n               INVALID PIN AGAIN");
                exit(-1);
          }

    }
    

  //=================inserting in customers
//    printf("mode %s",pf_mode);
//    printf("\n\n ****** new phone %s\n",curr_phone);

    char p_mode_query[200]="";
	    
		// strcat(search_query,"select * from place where agency_id = ' arrival LIKE '%");

      	strcat(p_mode_query,"select * from payement_forms where code = '");

        strcat(p_mode_query,pf_mode);
		
		strcat(p_mode_query,"';");


        int p_mode_query_result=mysql_query(connection,p_mode_query);
		if(p_mode_query_result)
		validate(connection);

		MYSQL_RES *p_mode_query_result_set=mysql_store_result(connection);
		int p_mode_query_num_cols=mysql_num_fields(p_mode_query_result_set);
        char pf_form_id[2];

		MYSQL_ROW p_mode_query_row;
		
        while( p_mode_query_row=mysql_fetch_row(p_mode_query_result_set)){
		for(int p_mode_query_col=0;p_mode_query_col<p_mode_query_num_cols;p_mode_query_col++){

		    //  printf("%s",p_mode_query_row[p_mode_query_col]);
          
             strcpy(pf_form_id,p_mode_query_row[0]);
            
	  
        }
        }

//   printf("pf id: %s",pf_form_id);


       //fetching the journey description from table place
       char customer_book_inserter[200]="";
       strcat(customer_book_inserter,"insert into customer_book (firstname,lastname,book_id,pf_id) values ('");
       strcat(customer_book_inserter,firstname);
       strcat(customer_book_inserter,"','");
       strcat(customer_book_inserter,lastname);
       strcat(customer_book_inserter,"','");
       strcat(customer_book_inserter,journey_code);
       strcat(customer_book_inserter,"','");
       strcat(customer_book_inserter,pf_form_id);
       strcat(customer_book_inserter,"');");


       int customer_book_inserter_result=mysql_query(connection,customer_book_inserter);
		if(customer_book_inserter_result)
		validate(connection);

        // printf("\n\n           200");

        char book_descr[200]="";
        strcat(book_descr,"select *from place where place_id = '");
        strcat(book_descr,journey_code);
        strcat(book_descr,"';");

         char departing[50],arriving[50],time[50],date[50],tickets[3],price[11];
        
        int book_descr_result=mysql_query(connection,book_descr);
		if(book_descr_result)
		validate(connection);

		MYSQL_RES *book_descr_query_result_set=mysql_store_result(connection);
		int book_descr_query_num_cols=mysql_num_fields(book_descr_query_result_set);
        

		MYSQL_ROW book_descr_query_row;
		
        while( book_descr_query_row=mysql_fetch_row(book_descr_query_result_set)){
		for(int book_descr_query_col=0;book_descr_query_col<book_descr_query_num_cols;book_descr_query_col++){

		    //  printf("%s",p_mode_query_row[p_mode_query_col]);
          
             strcpy(departing,book_descr_query_row[1]);
             strcpy(arriving,book_descr_query_row[2]);
             strcpy(tickets,book_descr_query_row[3]);
             strcpy(time,book_descr_query_row[5]);
             strcpy(date,book_descr_query_row[6]);
             strcpy(price,book_descr_query_row[7]);
          

            }
        }
        // printf("\n\nDeparting: %s, Arriving: %s,Tickets: %s,Time: %s,Date: %s, Place: %s ",departing,arriving,tickets,time,date,price);

        //inserting into customer table
           char customer_inserter[200]="";
       strcat(customer_inserter,"insert into customer (departure,arrival,time,date,id) values ('");
       strcat(customer_inserter,departing);
       strcat(customer_inserter,"','");
       strcat(customer_inserter,arriving);
       strcat(customer_inserter,"','");
       strcat(customer_inserter,time);
       strcat(customer_inserter,"','");
       strcat(customer_inserter,date);
       strcat(customer_inserter,"','");
        strcat(customer_inserter,journey_code);
       strcat(customer_inserter,"');");


       int customer_inserter_result=mysql_query(connection,customer_inserter);
		if(customer_inserter_result)
		validate(connection);

        // printf("\n\n          200");
        
        int tickets_num =  atoi(tickets); 
        int update_ticket_num = tickets_num -1;

        // printf("\n\n************* %d",update_ticket_num);

        char update_tickets_strng[20]; 
          
         sprintf(update_tickets_strng, "%d", update_ticket_num); 
        
         getchar();

        // int sum = itoa(update_ticket_num, update_tickets_strng, 10);
        // char updated_tickets[3];

        
        // strcpy(updated_tickets,tickets_num-1);

        // printf("\n\n updated tickets: %d",tickets_num-1);

      //  updating the total the reamining tickets in place table


        char tickets_decrementer[200] = "";
        strcat(tickets_decrementer,"update place set tickets = '");
        strcat(tickets_decrementer,update_tickets_strng);
        strcat(tickets_decrementer,"' where place_id = '");
        strcat(tickets_decrementer,journey_code);
        strcat(tickets_decrementer,"';");


       int tickets_decrementer_result=mysql_query(connection,tickets_decrementer);
		if(tickets_decrementer_result)
		validate(connection);

        //================Getting the agency id from place================
             char agency_id[3];
             char get_agency_id[200]="";
             strcat(get_agency_id,"SELECT*FROM place where place_id = '");
             strcat(get_agency_id,journey_code);
             strcat(get_agency_id,"';");

              int get_agency_id_result=mysql_query(connection,get_agency_id);
                if(get_agency_id_result)
                validate(connection);

                MYSQL_RES *get_agency_id_result_set=mysql_store_result(connection);
                int get_agency_id_num_cols=mysql_num_fields(get_agency_id_result_set);
                

                MYSQL_ROW get_agency_id_row;
                
                while( get_agency_id_row=mysql_fetch_row(get_agency_id_result_set)){
                for(int get_agency_id_col=0;get_agency_id_col<get_agency_id_num_cols;get_agency_id_col++){

                    //  printf("%s",p_mode_query_row[p_mode_query_col]);
                    strcpy(agency_id,get_agency_id_row[0]);
                    // printf("\n\n Agency id: %s",agency_id);
                }
                }


          
        //=================End of getting agency id============
         
        //=============== getting the agency name from agency===
             char agency_name[50];
             char get_agency_name[200]="";
             strcat(get_agency_name,"SELECT*FROM agency where agency_id = '");
             strcat(get_agency_name,agency_id);
             strcat(get_agency_name,"';");

              int get_agency_name_result=mysql_query(connection,get_agency_name);
                if(get_agency_name_result)
                validate(connection);

                MYSQL_RES *get_agency_name_result_set=mysql_store_result(connection);
                int get_agency_name_num_cols=mysql_num_fields(get_agency_name_result_set);
                

                MYSQL_ROW get_agency_name_row;
                
                while( get_agency_name_row=mysql_fetch_row(get_agency_name_result_set)){
                for(int get_agency_name_col=0;get_agency_name_col<get_agency_name_num_cols;get_agency_name_col++){

                    //  printf("%s",p_mode_query_row[p_mode_query_col]);
                    strcpy(agency_name,get_agency_name_row[1]);
                   
                }
                }
               //  printf("\n\n Agency Name: %s",agency_name);
        //=============== End of getting the agency name from place=


       system("clear");
    //  char agency=readAgency(connection);
     printf("\n\n *******************RECEIPT FOR JOURNEY");
     printf("\n\n AGency Name:%s",agency_name);
     printf("\n\nclient FirstName:%s",firstname);
     printf("\n\nClient LastName:%s",lastname);   
     printf("\n\n Seat N0:%d",tickets_num);
     printf("\n\n Time: %s",time);
     printf("\n\n Date: %s",date);
     printf("\n\nPrice: %sFRW",price);
     printf("\n\n******************************************");
  
  }



//read places
void readPlaces(MYSQL*connection,char agency_id[20]){

            
  system("clear");


             printf("\n\n                 AVAILABLE BOOKS\n\n");

        char book_query[200]="";
	    
		strcat(book_query,"select * from place where agency_id = '");
		strcat(book_query,agency_id);
		strcat(book_query,"';");

        int book_query_result=mysql_query(connection,book_query);
		if(book_query_result)
		validate(connection);

		MYSQL_RES *book_query_result_set=mysql_store_result(connection);
		int book_query_num_cols=mysql_num_fields(book_query_result_set);

		MYSQL_ROW book_query_row;
		printf("\n\nID\tdeparture arrival\tid\t time\t\tdate\t\tprice\tagency_id\n");
        printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        while( book_query_row=mysql_fetch_row(book_query_result_set)){
          // printf("\n%s",book_query_row[5]);
		for(int book_query_col=0;book_query_col<book_query_num_cols;book_query_col++){

		     printf("%s\t",book_query_row[book_query_col]);

	  

		}
		printf("\n");
		}



        char arrival[50];
        printf("\n\n                            SEARCH ");
        printf("\n                                   Arrival: ");
        scanf("%s",arrival);
          
system("clear");
        char search_query[200]="";
	    
		// strcat(search_query,"select * from place where agency_id = ' arrival LIKE '%");

      	strcat(search_query,"select * from place where agency_id = '");

        strcat(search_query,agency_id);
		strcat(search_query,"' AND arrival LIKE '%");  
		strcat(search_query,arrival);
		strcat(search_query,"%';");

        int search_query_result=mysql_query(connection,search_query);
		if(search_query_result)
		validate(connection);

		MYSQL_RES *search_query_result_set=mysql_store_result(connection);
		int search_query_num_cols=mysql_num_fields(search_query_result_set);

		MYSQL_ROW search_query_row;
printf("\n\nCODE\tdeparture arrival\tid\t time\t\tdate\t\tprice\tagency_id\n");
printf("------------------------------------------------------------------------------------------------------------------------------------\n");
        while( search_query_row=mysql_fetch_row(search_query_result_set)){
		for(int search_query_col=0;search_query_col<search_query_num_cols;search_query_col++){

		     printf("%s\t",search_query_row[search_query_col]);

	  

		}
		printf("\n");
		}  
           char journey_code[2];
           printf("\n\n                        Enter the Journey Code: ");
           scanf("%s",journey_code);

           payment(connection,journey_code);

    }
	






//===================reading agencyies ===============

void readAgency(MYSQL*connection){
    printf("\n\n                     SELECT AGENCY\n\n");
	int agency_mysql_result =  mysql_query(connection,"select * from agency");
    if(agency_mysql_result)
		validate(connection);

		MYSQL_RES *agency_result_set=mysql_store_result(connection);
		int agency_num_cols=mysql_num_fields(agency_result_set);

		MYSQL_ROW agency_row;
		printf("\n\n        \tAgency Code    \tAgency Name");

            printf("\n       ______________________________________\n\n");
            while( agency_row=mysql_fetch_row(agency_result_set)){
                for(int agency_col=0;agency_col<agency_num_cols;agency_col++){
                printf("         \t%s",agency_row[agency_col]);

                }
                printf("\n");

                }
                 
              char agency_id[20];
                 printf("                  Enter the agency(code): ");
                 scanf("%s",agency_id);

                 readPlaces(connection,agency_id);
                
            
                 
}

    // =================Reading place 

    


//===================== start inserting in agency
void insert_agency(MYSQL *connection){
    char contain_agency_name[200]="";
        char agency_name[200];
        printf("\n\nEnter the Name Of New Agency:");
        scanf("%s",agency_name);   
     
    strcat(contain_agency_name,"insert into  agency (agency_name)VALUES('");
    strcat(contain_agency_name,agency_name);
    strcat(contain_agency_name,"');");

    int insert_agency = mysql_query(connection,contain_agency_name);

    if(insert_agency){
        fprintf(stderr,"%s",mysql_error(connection));
    }
    printf("\n\nAGANCY INSERTED SUCCESSFULLY*********");
}

//==============================end inserting in agency


// ========================INSERT START INSERT INTO PLACES====================

void insert_into_places(MYSQL *connection){

char from_where[50];
char to_where[50];
char Number_of_passenger[3];
char journey_id[3];
char time[3];
char date[50];
char price[50];
char agency_id[4];

printf("\n\n******Car From where:");
scanf("%s",from_where);

printf("\n\n******Car is Going to: ");
scanf("%s",to_where);

printf("\n\n *****What Number Of Passenger Do You Want: ");
scanf("%s",Number_of_passenger);

printf("\n\n ******What Enter Journey Id: ");
scanf("%s",journey_id);

printf("\n\n *****WHAT time To Live: ");
scanf("%s",time);

printf("\n\n******Enter the date: ");
scanf("%s",date);

printf("\n\n******Enter Agency_id: ");
scanf("%s",agency_id);

printf("\n\n*******Enter the price : ");
scanf("%s",price);

 char place_inserter[500]="";
       strcat(place_inserter,"insert into place(departure,arrival,tickets,id,time,date,price,agency_id) values ('");
       strcat(place_inserter,from_where);
       strcat(place_inserter,"','");
       strcat(place_inserter,to_where);
       strcat(place_inserter,"','");
       strcat(place_inserter,Number_of_passenger);
       strcat(place_inserter,"','");
       strcat(place_inserter,journey_id);
       strcat(place_inserter,"','");
        strcat(place_inserter,time);
        strcat(place_inserter,"','");
        strcat(place_inserter,date);
        strcat(place_inserter,"','");
        strcat(place_inserter,price);
        strcat(place_inserter,"','");
        strcat(place_inserter,agency_id);
        strcat(place_inserter,"');");

 int place_inserter_result=mysql_query(connection,place_inserter);
		if(place_inserter_result)
		validate(connection);


printf("\n\n********NEW PLACE HAS BEEN INSERTED SUCCESSFULL ********");
}



//=====================END INSERT INTO PLACES===============



//==================================================================================================================================================
//==================================================================================================================================================
//===============================================READ FROM DATABASE  ===============================================================================

 void read_places(MYSQL *connection){

		int place_read_mysql_result =  mysql_query(connection,"select * from place");
    if(place_read_mysql_result)
		validate(connection);

		MYSQL_RES * place_read_result_set=mysql_store_result(connection);
		int  place_read_num_cols=mysql_num_fields(place_read_result_set);

		MYSQL_ROW  place_read_row;
		printf("\n\n\tID\tDeparture\tArrival\tjour_id\ttime\tdate\tprice\tagency_id");
            printf("\n____________________________________________________________________________________________________\n\n");
            while(place_read_row=mysql_fetch_row(place_read_result_set)){
                for(int  place_read_col=0; place_read_col< place_read_num_cols; place_read_col++){
                printf("\t%s", place_read_row[ place_read_col]);

                }
                printf("\n");

                }
                 
            }
    
//==================================READ CUSTOMERS=======================================================


void read_customer(MYSQL *connection){

		int customer_read_mysql_result =  mysql_query(connection,"select * from customer");
    if(customer_read_mysql_result)
		validate(connection);

		MYSQL_RES * customer_read_result_set=mysql_store_result(connection);
		int  customer_read_num_cols=mysql_num_fields(customer_read_result_set);

		MYSQL_ROW customer_read_row;
		printf("\n\n\t\tcust_id\t\tDeparture\t\tArrival\t\ttime\t\tdate\t\tid");
            printf("\n____________________________________________________________________________________________________\n\n");
            while(customer_read_row=mysql_fetch_row(customer_read_result_set)){
                for(int  customer_read_col=0; customer_read_col< customer_read_num_cols; customer_read_col++){
                printf("\t\t%s", customer_read_row[ customer_read_col]);

                }
                printf("\n");

                }
                 
            }



void read_customer_book(MYSQL *connection){

		int customer_book_read_mysql_result =  mysql_query(connection,"select * from customer_book  ");
    if(customer_book_read_mysql_result)
		validate(connection);

		MYSQL_RES * customer_book_read_result_set=mysql_store_result(connection);
		int  customer_book_read_num_cols=mysql_num_fields(customer_book_read_result_set);

		MYSQL_ROW customer_book_read_row;
		printf("\n\n\t\tID\t\tFIRSTNAME\t\tLASTNAME\t\tBOOK_ID\t\tPROF_ID");
            printf("\n____________________________________________________________________________________________________\n\n");
            while(customer_book_read_row=mysql_fetch_row(customer_book_read_result_set)){
                for(int  customer_book_read_col=0; customer_book_read_col< customer_book_read_num_cols; customer_book_read_col++){
                printf("\t\t%s",customer_book_read_row[customer_book_read_col]);

                }
                printf("\n");

                }
                 
            }






int main(){

int api_option;
while(api_option != 99){


scanf("%d",&api_option); 

	// GETTING DETAILS of our mysql client instance
  //printf("MySQL client version: %s\n", mysql_get_client_info());


// connect_to_mysql_server();
// connect_to_mysql_server();

MYSQL *connection=connect_to_db();
// create_table(connection);
// add_data(connection);
// read_data(connection);


if(api_option == 1){
    char client_api[20];
    printf("\n\n                     :: ");
    scanf("%s",client_api);

    char api[20] = "*128*1#";
    char admin[20] = "*128*2#";
    if(strcmp(api,client_api)==0){
        // printf("\n\n correct client api");

        int primary_choice;

        printf("\n\n                            HILLerrand\n\n");
        printf("\n                                   1.Book Ticket");
        printf("\n                                   2.View In   \n\n");


       scanf("%d",&primary_choice);

       if(primary_choice == 1){
           system("clear");
           readAgency(connection);
          
       
       }

    }
      else if(strcmp(admin,client_api)==0){
          int admins_choice;
            printf("\n\n  Admin Dashboard");
            printf("\n\n                           MAKE YOUR CHOICE");
           printf("\n\n           1. insert in Agency");
           printf("\n\n           2. Insert into Places");  
           printf("\n\n           3. Read Data");

  
  printf("\n\nEnter The Code  Choice:");
  scanf("%d",&admins_choice);
  
if(admins_choice==1){
printf("\n\nwelcome to insert in agency");
insert_agency(connection);
}

else if(admins_choice==2){
insert_into_places(connection);
}

else if(admins_choice==3){

int choice_read;
    printf("\n\n********* 1.places");
    printf("\n\n********* 2.customer  ");
    printf("\n\n********* 3.customer_book    ");
 
 
 printf("\n\nEnter Your Choice to Read");
 scanf("%d",&choice_read);

 if(choice_read==1){
 read_places(connection);
 }
else if(choice_read==2){
read_customer(connection);}
else if(choice_read==3){
    read_customer_book(connection);
}

else{
    printf("\n\n INVALID CODE SEE ABOVE AND RETRY ");
}

}

      }
    else{ printf("\n\n Wrong client api");}
   
	// create_table(connection);
}

else{
	printf("\n\n\n                                       Option not found          404 \n\n\n");
	exit(0);
}
}
return 0;

}



