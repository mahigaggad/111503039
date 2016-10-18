#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*#include<ncurses.h>*/
#include<string.h>
#include<errno.h>
time_t tt;
void money();
void new_acc();
void increment();
int acc_no = 0;
int check_date(char *);
char* sys_date();
char* sys_time();

typedef struct account {
	char firstname[20], lastname[20];   //take first and last name seperately
	long acc_no;
	char *date;
	char addr[60];
	char contact[15];
	double balance;
	char acc_typ;
	char sex;
	char dob[15];
	float RoI; // rate of interest
	
	/*struct date dob;
	struct date last_deposit;
	struct date last_withdraw;
	struct date new;*/
}account;
account add_acc, del_acc, updte_acc, transact, temp;
typedef struct log{
	char usrid[10];
	char name[50];
	char date[15];
	char intime[12]; //log in time
	char outtime[12]; // log out time
}usr_log;
/*typedef struct transact{*/


void new_acc() {
	account acc;
	char ch;
	int i;
	long n;
	FILE *fp1, *fp;
	fp = fopen("data.dat", "r");
	random:
	n = random() % 100000000;
	if (fp == NULL)
		acc.acc_no = n;
	else
		while(fscanf(fp, " %s %s %ld %s %s %s %lf %c %c %s %f\n", acc.firstname, acc.lastname, &acc.acc_no, acc.date, acc.addr, acc.contact, &acc.balance, &acc.acc_typ, &acc.sex, acc.dob, &acc.RoI) != EOF) {
			if( n == acc.acc_no)
				goto random;
			else acc.acc_no = n; 
		} 	
	personal:		
	system("clear");
	printf("PERSONAL DETAILS:\n");
	printf("\nEnter first Name	: 	");
	scanf("%s", acc.firstname);
	printf("\nEnter last Name		: 	");
	scanf("%s", acc.lastname);
	sex:
	printf("\nGENDER <M/F>		:	");
	scanf("\n%c", &acc.sex);
	if(acc.sex == 'f' || acc.sex == 'F' || acc.sex == 'm' || acc.sex == 'M')
		goto date;
	else {
		printf("Please enter again.");
		goto sex;
	}
	date:
	printf("\nDOB (DD/MM/YYYY)	:	");
	scanf("%s", acc.dob);
	if (check_date(acc.dob) == 0) {
		printf("invalid date. please enter again");
 		goto date;	
	}
	printf("\nAddress          :    "); 
	scanf(" %[^\n]s",acc.addr);
	for(i=0; i < strlen(acc.addr); i++) {
		if (acc.addr[i] == ' ') 
			acc.addr[i]=',';
	}
	contact:	
	printf("\nContact number   :    "); 
	scanf("\n%s",acc.contact);
	for(i = 0; i < strlen(acc.contact); i++) 
	if(!((acc.contact[i] >= '0' && acc.contact[i] <= '9' || acc.contact[i] == '-') && strlen(acc.contact) >= 10)) {
			printf("invalid contact. please enter again");
			goto contact;
		}
	char ch1;
	printf("\nEnter 1 to continue, 0 to edit.\n");
	scanf("\n%s", &ch1);
	if(ch1 == '1')
		goto account;
	else
		goto personal;
	account:
	system("clear");
	printf("ACCOUNT DETAILS\n");
	printf("\nA/C number	:	%ld", acc.acc_no);
	acctype:
	printf("\nA/C type <S/C>	:	");
	scanf("\n %c", &acc.acc_typ);
	if((acc.acc_typ == 's') || (acc.acc_typ == 'S')) {
		printf("\n*SAVINGS ACCOUNT*");
		acc.RoI = 6.5;
	}
	else if((acc.acc_typ == 'c' ) || (acc.acc_typ == 'C')) {
		printf("\n*CURRENT ACCOUNT*");
		acc.RoI = 3.5;
	}
	else {
		printf("please enter again");
		goto acctype;
	}
	printf("\nDate of opening account	:	 %s", sys_date());
	acc.date = (char*)malloc(11);
	strcpy(acc.date, sys_date());
	balance:
	printf("\nOpening Balance (Rs.)	:	");
	scanf("%lf", &acc.balance);
	if(acc.balance < 0) {
		printf("\nPlease enter again.");
		goto balance;
	}
	char ch2;
	printf("\nEnter 1 to continue, 0 to edit.\n");
	scanf("\n%s", &ch2);
	if(ch2 == '1')
		goto store;
	else
		goto account;
	store:
	system("clear");
	fp=fopen("data.dat","a");
	fprintf(fp,"%ld %s %s %s %s %s %c %s %c %.2f %.2f\n",acc.acc_no,acc.firstname,acc.lastname,acc.dob,acc.addr,acc.contact,acc.sex,acc.date,acc.acc_typ,acc.balance, acc.RoI);
        fclose(fp);
	printf("Account added succesfully!");	
}

void deposit() {
	account acc;
	FILE *fp, *fp1;
	char name[50], temp[50];
	int i;
	long ac_no;
	float amount;
	printf("\nDeposit to Account Number	:	");
	scanf("%ld", &ac_no);
	fp = fopen("data.dat", "r");
	while(fscanf(fp, " %s %s %ld %s %s %s %lf %c %c %s %f\n", acc.firstname, acc.lastname, &acc.acc_no, acc.date, acc.addr, acc.contact, &acc.balance, &acc.acc_typ, &acc.sex, acc.dob, &acc.RoI) != EOF) {
		if (ac_no == acc.acc_no) {
			i++;
			strcpy(name, acc.firstname);
			strcat(name, " ");
			strcat(name, acc.lastname);
		}
	fclose(fp);
	if(i == 0)
		printf("\nINVALID ACCOUNT NUMBER. No such account exists.");
	printf("\nACCOUNT HOLDER	:	[ %s ]", name);
	printf("\nEnter amount to b Deposited (Rs.)	:	");
	scanf("%f", &amount);
	}
}		

		
			


void money() {    // integer 1234567 to string 1,234,567
	return;

}


int check_date(char *date) {      
	int i = 0,  d, m , y;
   	if(strlen(date) != 10) 
		i++;
    	m = (date[3] - 48)*10 + (date[4] - 48);
    	if (m > 12)
		i++;
    	y = (date[6] - 48)*1000 + (date[7] - 48)*100 + (date[8] - 48)*10 + (date[9] - 48);
	if(date[2] != '/'|| date[5]!='/') 
		i++;
	d = (date[0] - 48)*10 + (date[1] - 48);
    switch(m)
    {
        case 1: 
		if (d>31) 
			i++;
	break;
        case 2:
        	if (d>28) 
			i++;
		if (y % 4 == 0 && d == 29) 
			i--;
        break;
        case 3: 
		if (d>31) 
			i++; 
	break;
        case 4: 
		if (d>30) 
			i++; 
	break;
        case 5: 
		if (d>31) 
			i++; 
	break;
        case 6: 
		if (d>30) 
			i++; 
	break;
        case 7: 
		if (d>31) 
			i++; 
	break;
        case 8: 
		if (d>31) 
			i++; 
	break;
        case 9: 
		if (d>30) 
			i++; 
	break;
        case 10: 
		if (d>31) 
			i++; 
	break;
        case 11: 
		if (d>30) 
			i++; 
	break;
        case 12: 
		if (d>31) 
			i++; 
	break;

    }

    if (i == 0)
        return 1;
    else
        return 0;

}
char* sys_date() {
	char *buf2;
	buf2 = (char*)malloc(20);
   	time_t curtime;
   	struct tm *loc_time;
   	curtime = time (NULL);
   	loc_time = localtime (&curtime);
	strftime (buf2, 150, "%d/%m/%Y\n", loc_time);
	return buf2;
}
char* sys_time() {
	char *buf1;
	buf1 = (char*)malloc(11);
   	time_t curtime;
   	struct tm *loc_time;
   	curtime = time (NULL);
   	loc_time = localtime (&curtime);
	strftime (buf1, 150, "Time is %I:%M %p.\n", loc_time);
	return buf1;
}
void main() {
	/*printf("%s", sys_date());
	printf("%s", sys_time());*/
	srandom(time(&tt));
	new_acc();
	return;
}
