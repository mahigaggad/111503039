/*****************************************************************************
 * Copyright (C) Mahima Gaggad   gaggadmg15.comp@coep.ac.in
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/



#include<stdio.h>
#include<string.h>

#include<stdlib.h>
#include<menu.h>
#include<form.h>
#include<ctype.h>
#include<time.h>
#include<math.h>
#include"functions.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4



int rows, cols, ret, i, ret1, count, irate = 6;
FILE *fp, *fp1, *fp2, *fp3;
time_t tt;

typedef struct passwrd {
	char usrname[15], password[20];

}passwrd;

typedef struct account {             //for account details
	char firstname[25], lastname[25];   //take first and last name seperately
	int acc_no;
	char addr[60];
	char city[20];
	char state[20];
	char contact[15];
	double balance;
	int age;
	char email[35];
	char acc_typ[15];
	char dob[15];
	char u_date[15];
	
}account;

 typedef struct staff {        //for staff details
	char id[20], fname[25], lname[25], dob[15], contact[15], nationality[20], email[30];
	}staff; 


account acc2;
WINDOW *win_3;
int main() {
	WINDOW *win_1;
	char *choices[] = {"ADMIN", "STAFF", "DESIGNED BY", "HOME", "EXIT", (char *)NULL};
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        int n_choices;
	
	/* Initialize curses */
	initscr();
	start_color();
	getmaxyx(stdscr, rows, cols);
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	bkgd(0);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_CYAN);
	init_pair(3, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(10, COLOR_RED, COLOR_CYAN);
	init_pair(11, COLOR_RED, COLOR_WHITE);
	init_pair(4, 12, 91);
	init_pair(5, 123, 130);
	init_pair(6, COLOR_CYAN, COLOR_WHITE);
	attron(A_BOLD | A_UNDERLINE| COLOR_PAIR(1) | A_STANDOUT);
	mvprintw(2, (cols - 32)/2, "   WELCOME TO BANK MANAGEMENT SYSTEM   ");
	mvprintw(6, (cols - 32)/2, "      We Provide 6%c Interest Rate!     ", 37);
	mvprintw(4, (cols - 32)/2, "          %s         ", sys_date1());
	attroff(A_BOLD | A_UNDERLINE | COLOR_PAIR(1) | A_STANDOUT);
	refresh();
	
	win_1 = newwin(10, 40, (rows - 10)/2, (cols - 40)/2);
	box(win_1, 0, 0);
	wbkgd(win_1, COLOR_PAIR(6));
	wrefresh(win_1);
	
	/* Create items */
        n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i) 
                my_items[i] = new_item(choices[i], choices[i]);
	my_items[i]=(ITEM *)NULL;	
	/*menu */
	my_menu = new_menu((ITEM **)my_items);
	/* Set menu option*/
	menu_opts_off(my_menu, O_SHOWDESC);
        keypad(win_1, TRUE);
	set_menu_win(my_menu, win_1);
        set_menu_sub(my_menu, derwin(win_1, 7, 38, 3, 0));
	set_menu_format(my_menu, 5, 1);
	set_menu_mark(my_menu, " * ");
	set_menu_fore(my_menu,COLOR_PAIR(2));
	set_menu_back(my_menu,COLOR_PAIR(6));
	set_menu_grey(my_menu,COLOR_PAIR(3));
	print_in_middle(win_1, 1, 0, 40, "BANK MANAGEMENT SYSTEM", COLOR_PAIR(3) | A_REVERSE);
	mvwaddch(win_1, 2, 0, ACS_LTEE);
	mvwhline(win_1, 2, 1, ACS_HLINE, 38);
	mvwaddch(win_1, 2, 39, ACS_RTEE);
	post_menu(my_menu);
	wrefresh(win_1);
	attron(COLOR_PAIR(2) | A_BOLD);
	mvprintw(rows - 1, 0, "Arrow Keys to navigate. ENTER to select");
	attroff(COLOR_PAIR(2) | A_BOLD);
	refresh();
	wrefresh(win_1);
	while((c = wgetch(win_1)) != KEY_F(3))
	{       
		switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			
			case 10:
				if(strcmp(item_name(current_item(my_menu)),"ADMIN") == 0 ) {
					ret1 = make(win_1, 1);
					if(ret1 == 1){
						unpost_menu(my_menu);
        					free_menu(my_menu);
        					for(i = 0; i < n_choices; ++i)
        	        				free_item(my_items[i]);
						make1(win_1, 1);
					}

					main(); 						
				}
				if(strcmp(item_name(current_item(my_menu)),"STAFF") == 0 ) {
					ret1 = make(win_1, 0);
					if(ret1 == 1){
						unpost_menu(my_menu);
        					free_menu(my_menu);
        					for(i = 0; i < n_choices; ++i)
        	        				free_item(my_items[i]);
						make1(win_1, 0);
					}

					main(); 						
				}
				if(strcmp(item_name(current_item(my_menu)),"DESIGNED BY") == 0 ) {
					unpost_menu(my_menu);
        				free_menu(my_menu);
        				for(i = 0; i < n_choices; ++i)
        	        			free_item(my_items[i]);
					ret = designed_by(win_1);
				}
				if(strcmp(item_name(current_item(my_menu)), "HOME") == 0) {
					main();
				} 
				else if(strcmp(item_name(current_item(my_menu)),"EXIT") == 0 ) {
						endwin();
						exit(0);
						return 0;
				}
				break;
		}
                wrefresh(win_1);
	}
	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return 0; 
}

int make2(WINDOW *win_1, int m) {                     //creates new window
	i = 0;
	win_1 = newwin(30, 55, (rows - 26)/2, (cols - 55)/2);
	box(win_1, 0 , 0);	
	wbkgd(win_1, COLOR_PAIR(3));	
	wrefresh(win_1);
	if (m == 0)		
		i = staffmenu(win_1);
	wclear(win_1);
	wbkgd(win_1,COLOR_PAIR(3));
	wrefresh(win_1);
	delwin(win_1);
	return i;
}

int make1(WINDOW *win_1, int m) {          //creates new window
	i = 0;
	win_1 = newwin(22, 50, (rows - 22)/2, (cols - 50)/2);
	box(win_1, 0 , 0);	
	wbkgd(win_1, COLOR_PAIR(3));	
	wrefresh(win_1);
	if (m == 0)		
		i = staffmenu(win_1);
	else if(m == 1)
		i = adminmenu(win_1);
	wclear(win_1);
	wbkgd(win_1,COLOR_PAIR(3));
	wrefresh(win_1);
	delwin(win_1);
	return i;
}

	

int staffmenu(WINDOW* win_1) {            //menu function after staff login
	char *choices1[] = {
                        "ADD ACCOUNT", "CASH DEPOSIT", "CASH WITHDRAWAL", "FUND TRANSFER", "ACCOUNT INFO","DELETE ACCOUNT","PROFILE", "CHANGE PASSWORD", "LOGOUT", (char *)NULL
                  };
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        int n_choices = 0, i;
	n_choices = ARRAY_SIZE(choices1);
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i) 
                my_items[i] = new_item(choices1[i], choices1[i]);
	my_items[i]=(ITEM *)NULL;	
	/*menu */
	my_menu = new_menu((ITEM **)my_items);
	/* Set menu option*/
	menu_opts_off(my_menu, O_SHOWDESC);
        keypad(win_1, TRUE);
	set_menu_win(my_menu, win_1);
        set_menu_sub(my_menu, derwin(win_1, 14, 38, 4, 6));
	wrefresh(win_1);
	set_menu_format(my_menu, 9, 1);
	set_menu_mark(my_menu, " * ");
	set_menu_fore(my_menu,COLOR_PAIR(2));
	set_menu_back(my_menu,COLOR_PAIR(6));
	set_menu_grey(my_menu,COLOR_PAIR(3));
	print_in_middle(win_1, 1, 0, 50, "BANK MANAGEMENT SYSTEM", COLOR_PAIR(3) | A_REVERSE);
	mvwaddch(win_1, 2, 0, ACS_LTEE);
	mvwhline(win_1, 2, 1, ACS_HLINE, 53);
	mvwaddch(win_1, 2, 54, ACS_RTEE);
	post_menu(my_menu);
	wrefresh(win_1);
	while((c = wgetch(win_1)) != KEY_F(3))
	{       
		switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10:
				if(strcmp(item_name(current_item(my_menu)),"ADD ACCOUNT") == 0 ) {
					make(win_1, 4);
	 						
				}
				else if(strcmp(item_name(current_item(my_menu)),"CASH DEPOSIT") == 0 ) {
					make(win_1, 5);
				}
				else if(strcmp(item_name(current_item(my_menu)),"CASH WITHDRAWAL") == 0 ) {
					make(win_1, 6);
				}
				else if(strcmp(item_name(current_item(my_menu)), "FUND TRANSFER") == 0) {
					make(win_1, 7);
				}
				else if(strcmp(item_name(current_item(my_menu)), "DELETE ACCOUNT") == 0) {
					make(win_1, 8);
				}
				else if(strcmp(item_name(current_item(my_menu)), "ACCOUNT INFO"	) == 0) {
					uptodate();
					make3(win_1, 9, 1);
				}
				else if(strcmp(item_name(current_item(my_menu)), "PROFILE") == 0) {
					make3(win_1, 11, 1);
				}
				else if(strcmp(item_name(current_item(my_menu)), "CHANGE PASSWORD") == 0) {
					make(win_1, 10);
				}
				else if(strcmp(item_name(current_item(my_menu)),"LOGOUT") == 0 ) {
						ret1 = make(win_1, 0);
					if(ret1 == 1){
						unpost_menu(my_menu);
        					free_menu(my_menu);
        					for(i = 0; i < n_choices; ++i)
        	        				free_item(my_items[i]);
						make2(win_1, 0);
					}

					main();
				}
				break;
				
		}
                wrefresh(win_1);
	}
	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return 1;
}


int adminmenu(WINDOW* win_1) {              //menu function after admin login
		char *choices1[] = {
                        "ADD USER", "DELETE USER" , "VIEW USER INFO", "CUSTOMER ACCOUNT INFO", "LOGOUT", (char *)NULL
                  };
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        int n_choices = 0, i;
	n_choices = ARRAY_SIZE(choices1);
	my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i) 
                my_items[i] = new_item(choices1[i], choices1[i]);
	my_items[i]=(ITEM *)NULL;	
	/*menu */
	my_menu = new_menu((ITEM **)my_items);
	/* Set menu option*/
	menu_opts_off(my_menu, O_SHOWDESC);
        keypad(win_1, TRUE);
	set_menu_win(my_menu, win_1);
        set_menu_sub(my_menu, derwin(win_1, 14, 38, 4, 6));
	wrefresh(win_1);
	set_menu_format(my_menu, 7, 1);
	set_menu_mark(my_menu, " * ");
	set_menu_fore(my_menu,COLOR_PAIR(2));
	set_menu_back(my_menu,COLOR_PAIR(6));
	set_menu_grey(my_menu,COLOR_PAIR(3));
	print_in_middle(win_1, 1, 0, 50, "BANK MANAGEMENT SYSTEM", COLOR_PAIR(3) | A_REVERSE);
	mvwaddch(win_1, 2, 0, ACS_LTEE);
	mvwhline(win_1, 2, 1, ACS_HLINE, 48);
	mvwaddch(win_1, 2, 49, ACS_RTEE);
	post_menu(my_menu);
	wrefresh(win_1);
	while((c = wgetch(win_1)) != KEY_F(3))
	{       
		switch(c)
	        {	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10:
				if(strcmp(item_name(current_item(my_menu)),"ADD USER") == 0 ) {
					
					make(win_1, 2);
				 						
				}
				if(strcmp(item_name(current_item(my_menu)),"DELETE USER") == 0 ) {
					
					make(win_1, 3);
				}
				if(strcmp(item_name(current_item(my_menu)),"VIEW USER INFO") == 0 ) {
					make3(win_1, 11, 0);
				}
				if(strcmp(item_name(current_item(my_menu)), "CUSTOMER ACCOUNT INFO") == 0) {
					uptodate();
					make3(win_1, 9, 0);
				} 
				else if(strcmp(item_name(current_item(my_menu)),"LOGOUT") == 0 ) {
						ret1 = make(win_1, 1);
					if(ret1 == 1){
						unpost_menu(my_menu);
        					free_menu(my_menu);
        					for(i = 0; i < n_choices; ++i)
        	        				free_item(my_items[i]);
						make1(win_1, 1);
					}

					main();
				}
				break;
				
		}
                wrefresh(win_1);
	}
	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return 1;
}





	
int make(WINDOW *win_1,int m){              //creates new window
	i=0;	
	win_1 = newwin(34, 120, (rows - 30)/2, (cols - 120)/2);	//  creating window
	box(win_1, 0 , 0);	
	wbkgd(win_1, COLOR_PAIR(2));	
	wrefresh(win_1);
	if (m == 0 || m == 1)							
		i = login(win_1, m);
	else if(m == 2)
		i = add_user(win_1);
	else if(m == 3)
		i = del_user(win_1);
	else if(m == 4)
		i = add_account(win_1);
	else if(m == 5)
		i = cash_deposit(win_1);
	else if(m == 6)
		i = cash_withdrawal(win_1);
	else if(m == 7)
		i = fund_transfer(win_1);
	else if(m == 8)
		i = del_account(win_1);
	else if(m == 10)
		i = change_pass(win_1);
	wclear(win_1);
	wbkgd(win_1,COLOR_PAIR(2));
	wrefresh(win_1);
	delwin(win_1);
	return i;
}	

int make3(WINDOW *win_1,int m, int a){                       //creates new window
	i=0;	
	win_1 = newwin(34, 120, (rows - 30)/2, (cols - 120)/2);	//  creating window
	box(win_1, 0 , 0);	
	wbkgd(win_1, COLOR_PAIR(2));	
	wrefresh(win_1);
	if(m == 9)
		account_info(win_1, a);
	else if(m == 11)
		user_info(win_1, a);
	wclear(win_1);
	wbkgd(win_1,COLOR_PAIR(2));
	wrefresh(win_1);
	delwin(win_1);
	return i;
}	
	
int display(WINDOW *win,  int n1, int a) {            // function to display customer account details
	int k;
	wclear(win);
	wbkgd(win,0);
	wrefresh(win);
	delwin(win);
	win = newwin(28, 120, (rows - 24)/2, (cols - 120)/2);
	box(win, 0 , 0);	
	wbkgd(win, COLOR_PAIR(3));	
	i = 0;
	account acc1;
	char *choice[]={"FIRST NAME","LAST NAME","DATE OF BIRTH","AGE","CONTACT NO.","EMAIL-ID","PERMANENT ADDRESS","CITY", "STATE", "ACCOUNT TYPE", "BALANCE(Rs.)"};
	while(i < 11){
		wattron(win, COLOR_PAIR(2) | A_BOLD);
		mvwprintw(win, 3 + 2*i, 33, "%s", choice[i]);
		wattroff(win, COLOR_PAIR(2) | A_BOLD);
		i++;
	}
	cbreak();
	keypad(win, TRUE);	
	wrefresh(win);
	wattron(win, COLOR_PAIR(2) | A_BOLD);
	mvwprintw(win, 1, 45, " Account no.          Informatiom ");
	mvwprintw(win, 1, 58, "%d", n1);
	wattroff(win, COLOR_PAIR(2) | A_BOLD);
	fp = fopen("data_account.txt", "r");
	i = 0;
	while(fscanf(fp, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", &acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, &acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, &acc1.balance, acc2.u_date) != EOF) {
		if(acc1.acc_no == n1) {
			mvwprintw(win, 3 , 53, "%s", acc1.firstname);
			mvwprintw(win, 5 , 53, "%s", acc1.lastname);
			mvwprintw(win, 7 , 53, "%s", acc1.dob);
			mvwprintw(win, 9, 53, "%d", acc1.age);
			mvwprintw(win, 11 , 53, "%s", acc1.contact);
			mvwprintw(win, 13 , 53, "%s", acc1.email);
			for(i=0; i < 30; i++) {  //In order to display address, '+' is replaced by space
            			if (acc1.addr[i] == '+') 
            				acc1.addr[i] = 32;
            		}
			mvwprintw(win, 15 , 53, "%s", (acc1.addr));
			mvwprintw(win, 17, 53, "%s", acc1.city);
			mvwprintw(win, 19, 53, "%s", acc1.state);
			mvwprintw(win, 21 , 53, "%s", acc1.acc_typ);
			mvwprintw(win, 23, 53, "%.2lf", acc1.balance);
			wattron(win, COLOR_PAIR(1) | A_BOLD);
			mvwprintw(win, 26, 50, "**ESC TO EXIT**");
			wattroff(win, COLOR_PAIR(1) | A_BOLD);
			wrefresh(win);
			break;
		}
	}
	fclose(fp);
	while((k = wgetch(win))) {
		if(k == 27) {
			wclear(win);
			wrefresh(win);
			if (a == 1)
				make2(win, 0);
			else if (a == 0)
				make1(win, 1);
		}
	}			
	return 1;
	
}	

int display1(WINDOW *win,  char *str, int a) {          // function to display user details
	int k;
	wclear(win);
	wbkgd(win,0);
	wrefresh(win);
	delwin(win);
	win = newwin(28, 120, (rows - 24)/2, (cols - 120)/2);
	box(win, 0 , 0);	
	wbkgd(win, COLOR_PAIR(3));	
	i = 0;
	staff st2;
	char *choice[]={"USER ID","FIRST NAME", "LAST NAME", "DOB(DD/MM/YYYY)", "NATIONALITY", "CONATCT NO.","EMAIL"};
	while(i < 7){
		wattron(win, COLOR_PAIR(2) | A_BOLD);
		mvwprintw(win, 3 + 2*i, 35, "%s", choice[i]);
		wattroff(win, COLOR_PAIR(2) | A_BOLD);
		i++;
	}
	cbreak();
	keypad(win, TRUE);
	wattron(win, COLOR_PAIR(2) | A_BOLD);
	mvwprintw(win, 1, 45, "  Staff User Informatiom ");
	wattroff(win, COLOR_PAIR(2) | A_BOLD);	
	wrefresh(win);
	fp = fopen("data_staff.txt", "r");
	i = 0;
	while(fscanf(fp, " %s %s %s %s %s %s %s\n", st2.id, st2.fname, st2.lname, st2.dob, st2.contact, st2.nationality, st2.email) != EOF) {
		if(strcmp(str, st2.id) == 0) {
			mvwprintw(win, 3 , 55, "%s", st2.id);
			mvwprintw(win, 5 , 55, "%s", st2.fname);
			mvwprintw(win, 7 , 55, "%s", st2.lname);
			mvwprintw(win, 9, 55, "%s", st2.dob);
			mvwprintw(win, 11 , 55, "%s", st2.nationality);
			mvwprintw(win, 13 , 55, "%s", st2.contact);
			mvwprintw(win, 15 , 55, "%s", st2.email);
			wattron(win, COLOR_PAIR(1) | A_BOLD);
			mvwprintw(win, 21, 50, "**ESC TO EXIT**");
			wattroff(win, COLOR_PAIR(1) | A_BOLD);
			wrefresh(win);
			break;
		}
	}
	fclose(fp);
	while((k = wgetch(win))) {
		if(k == 27) {
			wclear(win);
			wrefresh(win);
			if (a == 1)
				make2(win, 0);
			else if (a == 0)
				make1(win, 1);
		}
	}			
	return 1;
	
}
int designed_by(WINDOW *win_1) {         // function to display info of student
	int k;	
	wclear(win_1);
	wbkgd(win_1,0);
	wrefresh(win_1);
	delwin(win_1);
	win_1 = newwin(28, 120, (rows - 26)/2, (cols - 120)/2);
	box(win_1, 0 , 0);	
	wbkgd(win_1, COLOR_PAIR(3));	
	print_in_middle(win_1, 4, 0, 120, "BANK MANAGEMENT SYSTEM", COLOR_PAIR(2));
	print_in_middle(win_1, 6, 0, 120, "CREATED BY  :  MAHIMA GAGGAD", COLOR_PAIR(2));
	print_in_middle(win_1, 8, 0, 120, "ID  :  111503039", COLOR_PAIR(2));
	print_in_middle(win_1, 10, 0, 120, "SY COMP, S2", COLOR_PAIR(2));
	print_in_middle(win_1, 12, 0, 120, "EMAIL  :  mahimagaggad@gmail.com", COLOR_PAIR(2));
	print_in_middle(win_1, 14, 0, 120,"CONTACT : 9823075031", COLOR_PAIR(2));
	wrefresh(win_1);
	while((k = wgetch(win_1))) {
		if(k == 27)
			main();
	}			
	return 0;
}


//function to print in middle of line
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}


int login(WINDOW *win, int m) {           // function to create login form for admin and staff
	FIELD **field;
	FORM *form;
	int size, i = 0, x, y;
	char *field_names[] = {"USER NAME:", "PASSWORD:"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	init_pair(7, COLOR_BLACK, COLOR_YELLOW);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 4) * sizeof(FIELD*));
	
	field[0] = new_field(1, 25, 7, 50, 0, 0);
	field_opts_off(field[0], O_AUTOSKIP);
	set_field_back(field[0], COLOR_PAIR(7));
	set_field_fore(field[0], COLOR_PAIR(7));

	field[1] = new_field(1, 25, 9 , 50, 0, 0);
	field_opts_off(field[1], O_PUBLIC | O_AUTOSKIP);
	set_field_back(field[1], COLOR_PAIR(7));
	//set_field_fore(field[1], COLOR_PAIR(7));
	
	field[2] = new_field(1, 10, 11, 50, 0, 0);
	field_opts_off(field[2], O_AUTOSKIP | O_EDIT);
	set_field_back(field[2], COLOR_PAIR(7));
	//set_field_fore(field[2], COLOR_PAIR(7));
	set_field_buffer(field[2], 0, " LOGIN ");
	
	field[3] = new_field(1, 10, 11, 62, 0, 0);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	set_field_back(field[3], COLOR_PAIR(7));
	//set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[3], 0, " HOME ");

	field[4] = NULL;

	form = new_form(field);
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	if( m == 1)
		print_in_middle(win,1,0,120,"ADMINISTRATOR", COLOR_PAIR(8));
	if( m == 0)
		print_in_middle(win,1,0,120,"STAFF MEMBER",COLOR_PAIR(8));

	mvwprintw(win, 7, 38, "%s: ", field_names[0]);
	mvwprintw(win, 9, 38, "%s: ", field_names[1]);	
	print_in_middle(win, 20, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[2] == current_field(form)){
								ret = match((field_buffer(field[0], 0)),(field_buffer(field[1], 0)), m);
								if(ret == 0) {
									print_in_middle(win, 17, 0, 120,"Incorrect user ID or password!", COLOR_PAIR(3));
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
								}
								else if(ret == 1)
									goto end;
							}
							else if(field[3] == current_field(form)){
									main();
								}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
							break;
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	end:
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}


int match(char* usrname, char* pass, int m) {    // function to check if password matches
	passwrd p;
	int l1, l2;
	FILE *fp;
	if(m == 0)
		fp = fopen("pass_staff.txt", "r");
	else if(m == 1)
		fp = fopen("pass_admin.txt", "r");
	if(fp == NULL)
		exit(0);
	while(fscanf(fp, "%s %s\n", p.usrname, p.password) != EOF) {
		l1 = strlen(p.usrname);
		l2 = strlen(p.password);
		if((strncmp(usrname, p.usrname, l1) == 0) && (strncmp(pass, p.password, l2) == 0)) { 
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}	



int add_user(WINDOW *win) {        // function to create add user form
	ret = 0;
	FIELD **field;
	FORM *form;
	char *s;
	int j = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"USER ID","FIRST NAME", "LAST NAME", "DOB(DD/MM/YYYY)", "NATIONALITY", "CONATCT NO.","EMAIL", "PASSWORD"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	init_pair(7, COLOR_BLACK, COLOR_YELLOW);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	for(i = 0; i < 8; i++) {			
		field[i] = new_field(1, 30, 5 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[8] = new_field(1, 10, 21, 50, 0, 0);
	field_opts_off(field[8], O_AUTOSKIP | O_EDIT);
	set_field_back(field[8], COLOR_PAIR(7));
	set_field_fore(field[8], COLOR_PAIR(7));
	set_field_buffer(field[8], 0, " ADD USER ");

	field[9] = new_field(1, 8, 21, 72, 0, 0);
	field_opts_off(field[9], O_AUTOSKIP | O_EDIT);
	set_field_back(field[9], COLOR_PAIR(7));
	set_field_fore(field[9], COLOR_PAIR(7));
	set_field_buffer(field[9], 0, " EXIT ");

	field[10] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 8; i++) {
		if(i == 0)
			mvwprintw(win, 6 + 2*i, 50, "(can be alphanumeric, no spaces.)");
		if(i == 1)		
			mvwprintw(win, 6 + 2*i, 56, "(only alphabets)");
		if(i == 2)		
			mvwprintw(win, 6 + 2*i, 56, "(only alphabets)");
		if(i == 3)	
			mvwprintw(win, 6 + 2*i, 56, "(dd/mm/yyyy)");
		if(i == 4)			
			mvwprintw(win, 6 + 2*i, 56, "(Ex. Indian)");
		if(i == 5)		
			mvwprintw(win, 6 + 2*i, 56, "(10 digit number(0-9))");
		mvwprintw(win, 5 + 2*i, 35, "%s: ", field_names[i]);
	}
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**ADD USER**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[8] == current_field(form)) {
								count = 0;
								i = 0;
								while(i < 7) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = add_to_file(form, field);
									if(ret == 3) {
										wattron(win, A_BOLD | COLOR_PAIR(10));
										mvwprintw(win, 12, 56, "  *invalid date*  ");
										wattroff(win, A_BOLD | COLOR_PAIR(10));
									}
									else if(ret == 2) {
									wattron(win, A_BOLD | COLOR_PAIR(10));
									mvwprintw(win, 16, 48, "*invalid contact. Should be 10 digits.* ");
									wattroff(win, A_BOLD | COLOR_PAIR(10));
									}
									else if(ret == 0) {
										for(i = 0; i < size; i++)
											mvwprintw(win, 6 + 2*i, 48, "                                                ");
										print_in_middle(win, 23, 0, 120,"   ID/ACCOUNT ALREADY IN USE.   ", COLOR_PAIR(3));
									}
									else if(ret == 1) {
										for(i = 0; i < size; i++)
											mvwprintw(win, 6 + 2*i, 48, "                                                ");
										print_in_middle(win, 23, 0, 120,"USER ACCOUNT ADDED SUCCESFULLY", COLOR_PAIR(3));
										j = wgetch(win);
										if((j == KEY_DOWN) || (j == KEY_UP)) {
										i = 0;
										while( i < size ) 
											set_field_buffer(field[i++], 0, "");
										}	
									}
									j = wgetch(win);
									if((j == KEY_DOWN) || (j == KEY_UP)) {
										print_in_middle(win, 23, 0, 120,"                                          ", COLOR_PAIR(10));
									}
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[9] == current_field(form)) {
								make1(win, 1);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}


int del_user(WINDOW* win) {         // function to create delete user form
	ret = 0;
	FIELD **field;
	FORM *form;
	char *s;
	int j = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j < 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"USER ID","FIRST NAME", "LAST NAME"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < 3; i++) {			
		field[i] = new_field(1, 30, 9 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[3] = new_field(1, 15, 17, 50, 0, 0);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	set_field_back(field[3], COLOR_PAIR(7));
	set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[3], 0, " DELETE USER ");

	field[4] = new_field(1, 8, 17, 72, 0, 0);
	field_opts_off(field[4], O_AUTOSKIP | O_EDIT);
	set_field_back(field[4], COLOR_PAIR(7));
	set_field_fore(field[4], COLOR_PAIR(7));
	set_field_buffer(field[4], 0, " EXIT ");

	field[5] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 3; i++)
		mvwprintw(win, 9 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**DELETE USER**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[3] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < size) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = delete_from_file(form, field);
									if(ret == 1)
										print_in_middle(win, 23, 0, 120,"USER ACCOUNT DELETED SUCCESFULLY", COLOR_PAIR(3));
									else if(ret == 2)
										print_in_middle(win, 23, 0, 120,"   ACCOUNT NO. AND NAME DOESN'T MATCH  ", COLOR_PAIR(3));
								
									else if(ret == 0)
										print_in_middle(win, 23, 0, 120,"ID/ACCOUNT NOT FOUND", COLOR_PAIR(3));
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
									j = wgetch(win);
									if((j == KEY_DOWN) || (j == KEY_UP))
										print_in_middle(win, 23, 0, 120,"                                                          ", COLOR_PAIR(10));
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[4] == current_field(form)) {
								make1(win, 1);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}
	




int add_to_file(FORM *form, FIELD **field) {  // function to add user details to a file
	passwrd p1;
	i = 0;
	count = 0;	
	int l = field_count(form), l2;
	staff st1, st2;
	fp = fopen("data_staff.txt", "a+");
	fp1 = fopen("pass_staff.txt", "a+");
	char **stf;
	char *stf1;
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l){
		stf[i] = field_buffer(field[i], 0);
		i++;
	}
	stf1 = string(stf[0]);
	strcpy(st2.id, stf1);
	l2 = strlen(st2.id);
		while(fscanf(fp, " %s %s %s %s %s %s %s\n", st1.id, st1.fname, st1.lname, st1.dob, st1.contact, st1.nationality, st1.email) != EOF) {
			if(strncmp(st1.id, st2.id, l2) == 0)
				return 0;
			else if(feof(fp))
				break;
		}
	stf1 = string(stf[1]);
	strcpy(st2.fname,stf1);
	stf1 = string(stf[2]);
	strcpy(st2.lname,stf1);
	stf1 = string(stf[3]);
	strcpy(st2.dob,stf1);
	if (check_date(st2.dob) == 0)     // checkin if date entry is valid or not
		return 3;
	stf1 = string(stf[5]);
	strcpy(st2.contact,stf1);
	// checking if contact entered is correct or not
	for(i = 0; i < strlen(st2.contact); i++) {
		if(!(((st2.contact[i] >= '0' && st2.contact[i] <= '9') && strlen(st2.contact) == 10))) 
			return 2;
	}
	stf1 = string(stf[4]);
	strcpy(st2.nationality,stf1);
	stf1 = string(stf[6]);
	strcpy(st2.email,stf1);
	stf1 = string(stf[0]);
	strcpy(p1.usrname, stf1);
	stf1 = string(stf[7]);
	strcpy(p1.password, stf1);
	fprintf(fp, " %s %s %s %s %s %s %s\n", st2.id, st2.fname, st2.lname, st2.dob, st2.contact, st2.nationality, st2.email);
	fprintf(fp1, "%s %s\n", p1.usrname, p1.password);
	//fwrite(&p1, sizeof(passwrd), 1, fp1);
	free(stf);
	fclose(fp);
	fclose(fp1);
	return 1;
}


	
char *string(char *stf) {   
	int i = 0;
	char *ch;
	ch = (char *)malloc(sizeof(char) * 30);
	while(stf[i] != 32) {
		ch[i] = stf[i];
		i++;
	}
	ch[i] = '\0';
	return ch;
}
		
char *string1(char *stf) {
	int i = 0;
	char *ch;
	ch = (char *)malloc(sizeof(char) * 30);
	while(i < strlen(stf)) {
		if(stf[i] == 32)
			ch[i] = '+';
		else
			ch[i] = stf[i];
		i++;
	}
	ch[i] = '\0';
	return ch;
}

int delete_from_file(FORM *form, FIELD **field) {            // function to remove user details from file
	passwrd p1;
	i = 0;
	int j = 0;
	int l = field_count(form), l2;
	staff st1, st2;
	fp = fopen("data_staff.txt", "r");
	fp1 = fopen("pass_staff.txt", "r");
	fp2 = fopen("temp1.txt", "w+");
	fp3 = fopen("temp2.txt", "w+");
	char **stf;
	char *stf1;	
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l) {
		stf[i] = field_buffer(field[i], 0);
		i++;
	}
	stf1 = string(stf[0]);
	strcpy(st1.id, stf1);
	l2 = strlen(st1.id);
	stf1 = string(stf[1]);
	strcpy(st1.fname, stf1);
	stf1 = string(stf[2]);
	strcpy(st1.lname, stf1);
	while(fscanf(fp, " %s %s %s %s %s %s %s\n", st2.id, st2.fname, st2.lname, st2.dob, st2.contact, st2.nationality, st2.email) != EOF) {
		
		if((strncmp(st1.id, st2.id, l2) != 0))
			fprintf(fp2, " %s %s %s %s %s %s %s\n", st2.id, st2.fname, st2.lname, st2.dob, st2.contact, st2.nationality, st2.email);
		else if(strncmp(st1.id, st2.id, l2) == 0)
			j++;
		else if(feof(fp))
			break;
	}
	while(fscanf(fp1, "%s %s\n", p1.usrname, p1.password) != EOF) {
		if(strncmp(st1.id, p1.usrname, l2) != 0) 
			fprintf(fp3, "%s %s\n", p1.usrname, p1.password);
		else if(feof(fp1))
			break;
	}
	remove("data_staff.txt");
	remove("pass_staff.txt");
	rename("temp1.txt", "data_staff.txt");
	rename("temp2.txt", "pass_staff.txt");
	free(stf);
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	if (j == 0)
		return 0;
	return 1;
}

int add_account(WINDOW *win) {         // function to create a form to add a bank customer
	ret = 0;
	FIELD **field;
	FORM *form;
	char *s;
	int j = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"FIRST NAME", "LAST NAME", "DOB(DD/MM/YYYY)", "AGE", "CONATCT NO.","EMAIL", "PERMANENT ADDRESS","CITY", "STATE", "ACCOUNT TYPE", "OPENING BALANCE(Rs.)"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	init_pair(7, COLOR_BLACK, COLOR_YELLOW);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	for(i = 0; i < 11; i++) {			
		field[i] = new_field(1, 30, 5 + 2*i, 52, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[11] = new_field(1, 15, 29, 52, 0, 0);
	field_opts_off(field[11], O_AUTOSKIP | O_EDIT);
	set_field_back(field[11], COLOR_PAIR(7));
	set_field_fore(field[11], COLOR_PAIR(7));
	set_field_buffer(field[11], 0, " ADD ACCOUNT ");

	field[12] = new_field(1, 8, 29, 72, 0, 0);
	field_opts_off(field[12], O_AUTOSKIP | O_EDIT);
	set_field_back(field[12], COLOR_PAIR(7));
	set_field_fore(field[12], COLOR_PAIR(7));
	set_field_buffer(field[12], 0, " EXIT ");

	field[13] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	i = 0;
	for(i = 0; i < 11; i++) {
		mvwprintw(win, 5 + 2*i, 33, "%s: ", field_names[i]);
	}
	mvwprintw(win, 24, 52, "   <savings/current>");
	print_in_middle(win, 2 , 0, 120,"**ADD ACCOUNT**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[11] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < 11) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 27, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = add_acc_to_file(form, field);
									if(ret == 1) {
										wattron(win, A_BOLD | COLOR_PAIR(10));
										mvwprintw(win, 10, 56, "  *invalid date*  ");
										wattroff(win, A_BOLD | COLOR_PAIR(10));
									}
									else if(ret == 2) {
										wattron(win, A_BOLD | COLOR_PAIR(10));
										mvwprintw(win, 14, 52, "*invalid contact. Should be 10 digits.* ");
										wattroff(win, A_BOLD | COLOR_PAIR(10));
									}
									else {
										for(i = 0; i < 11; i++)
											mvwprintw(win, 6 + 2*i, 50, "                                                ");
										print_in_middle(win, 27, 0, 120,"USER ACCOUNT ADDED SUCCESFULLY", COLOR_PAIR(3));
										wattron(win, COLOR_PAIR(3));
										mvwprintw(win, 28, 42, "Account number is : ");
										mvwprintw(win, 28, 62, "%d", ret);
										wattroff(win, COLOR_PAIR(3));
										
										j = wgetch(win);
										if((j == KEY_DOWN) || (j == KEY_UP)) {
											i = 0;
											while( i < size ) 
												set_field_buffer(field[i++], 0, "");
											print_in_middle(win, 27, 0, 120,"                                          ", COLOR_PAIR(10));
											wattron(win, COLOR_PAIR(10));
											mvwprintw(win, 28, 42, "                      ");
											mvwprintw(win, 28, 62, "           ");
											wattroff(win, COLOR_PAIR(10));
										}
											
									}
									i = 0;
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[12] == current_field(form)) {
								make2(win, 0);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}


int add_acc_to_file(FORM *form, FIELD **field) {    // gunction to save customer account details in a file
	i = 0;
	count = 0;
	int n;
	int l = field_count(form);
	srandom(time(&tt));
	account acc1;
	fp = fopen("data_account.txt", "a+");
	char **stf;
	char *stf1;
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l){
		stf[i] = field_buffer(field[i], 0);
		i++;
	}   
	random:
	n = random() % 10000000;                                                               
		while(fscanf(fp, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", &acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, &acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, &acc1.balance,acc1.u_date) != EOF) {
			if( n == acc1.acc_no)
				goto random;
			else if(n != acc1.acc_no)
				 acc2.acc_no = n; 
			else if (feof(fp))
				break;
		}
	stf1 = string(stf[0]);
	strcpy(acc2.firstname,stf1);
	stf1 = string(stf[1]);
	strcpy(acc2.lastname,stf1);
	stf1 = string(stf[2]);
	strcpy(acc2.dob,stf1);
	if (check_date(acc2.dob) == 0)
		return 1;
	stf1 = string(stf[3]);
	acc2.age = atoi(stf1);
	stf1 = string(stf[4]);
	strcpy(acc2.contact,stf1);
	for(i = 0; i < strlen(acc2.contact); i++) 
		if(!(((acc2.contact[i] >= '0' && acc2.contact[i] <= '9') && strlen(acc2.contact) == 10))) 
			return 2;
	stf1 = string(stf[5]);
	strcpy(acc2.email,stf1);
	stf1 = string1(stf[6]);
	strcpy(acc2.addr,stf1);
	stf1 = string(stf[7]);
	strcpy(acc2.city, stf1);
	stf1 = string(stf[8]);
	strcpy(acc2.state, stf1);
	stf1 = string(stf[9]);
	strcpy(acc2.acc_typ, stf1);
	stf1 = string(stf[10]);
	acc2.balance = atof(stf1);
	strcpy(acc2.u_date, sys_date());
	
	fprintf(fp,  "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", acc2.acc_no,  acc2.firstname, acc2.lastname, acc2.dob, acc2.age, acc2.addr, acc2.city, acc2.state, acc2.contact, acc2.email, acc2.acc_typ, acc2.balance, acc2.u_date);
	free(stf);
	fclose(fp);
	return n;
}




int cash_deposit(WINDOW* win) {     // function to create form for cash deposit
	ret = 0;
	FIELD **field;
	FORM *form;
	float bal;
	char *s;
	int j = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j < 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"ACCOUNT NUMBER","AMOUNT(Rs.)"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < 2; i++) {			
		field[i] = new_field(1, 30, 9 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[2] = new_field(1, 15, 17, 50, 0, 0);
	field_opts_off(field[2], O_AUTOSKIP | O_EDIT);
	set_field_back(field[2], COLOR_PAIR(7));
	set_field_fore(field[2], COLOR_PAIR(7));
	set_field_buffer(field[2], 0, " DEPOSIT ");

	field[3] = new_field(1, 8, 17, 72, 0, 0);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	set_field_back(field[3], COLOR_PAIR(7));
	set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[3], 0, " EXIT ");

	field[4] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 2; i++)
		mvwprintw(win, 9 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**CASH DEPOSIT**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[2] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < size) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = cash_file(form, field, 1);
									bal = ret;
									if(ret != 0){
										print_in_middle(win, 23, 0, 120,"AMOUNT DEPOSITED  SUCCESFULLY", COLOR_PAIR(3));
										wattron(win, COLOR_PAIR(3));
										mvwprintw(win, 21, 45, "ACCOUNT BALANCE IS : Rs.");
										mvwprintw(win, 21, 70, "%.2f", bal);
										wattroff(win, COLOR_PAIR(3));
										
									}
									else if(ret == 0.0)
										print_in_middle(win, 23, 0, 120,"    ID/ACCOUNT NOT FOUND    ", COLOR_PAIR(3));
									
									j = wgetch(win);
									if((j == KEY_DOWN) || (j == KEY_UP)) {
										i = 0;
										while( i < size ) 
											set_field_buffer(field[i++], 0, "");
										print_in_middle(win, 23, 0, 120,"                                           ", COLOR_PAIR(10));
										wattron(win, COLOR_PAIR(10));
										mvwprintw(win, 21, 45, "                      ");
										mvwprintw(win, 21, 65, "                 ");
										wattroff(win, COLOR_PAIR(10));
									}
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[3] == current_field(form)) {
								make2(win, 0);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}





float cash_file(FORM *form, FIELD **field, int m) {    //function to make changes in file after cah witdrawal or deposit
	i = 0;
	count = 0;
	int n;
	float amt, bal;
	int l = field_count(form);
	account acc1;
	fp = fopen("data_account.txt", "r");
	fp1 = fopen("temp.txt", "w+");
	char **stf;
	char *stf1;
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l){
		stf[i] = field_buffer(field[i], 0);
		i++;
	}   
	stf1 = string(stf[0]);
	n = atoi(stf1);	
	stf1 = string(stf[1]);
	amt = atof(stf1);                                                           
	while(fscanf(fp, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", &acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, &acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, &acc1.balance, acc1.u_date) != EOF) {
		if( n == acc1.acc_no) {
			count++;
			if(m == 1)
				acc1.balance += amt;
			else if(m == 2){
				if(acc1.balance < amt)
					return 2.0;
				else
					acc1.balance -= amt;
			}
			bal = acc1.balance;
		}
		fprintf(fp1, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, acc1.balance, acc1.u_date);
			
	}
	remove("data_account.txt");
	rename("temp.txt", "data_account.txt");
	free(stf);
	fclose(fp);
	fclose(fp1);
	if(count == 0)
		return 0.0;
	else
		return bal;
}



int cash_withdrawal(WINDOW* win) {     // function to create form for cash withdrawal
	FIELD **field;
	FORM *form;
	float bal;
	char *s;
	int j = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j < 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"ACCOUNT NUMBER","AMOUNT(Rs.)"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < 2; i++) {			
		field[i] = new_field(1, 30, 9 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[2] = new_field(1, 15, 17, 50, 0, 0);
	field_opts_off(field[2], O_AUTOSKIP | O_EDIT);
	set_field_back(field[2], COLOR_PAIR(7));
	set_field_fore(field[2], COLOR_PAIR(7));
	set_field_buffer(field[2], 0, " WITHDRAW ");

	field[3] = new_field(1, 8, 17, 72, 0, 0);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	set_field_back(field[3], COLOR_PAIR(7));
	set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[3], 0, " EXIT ");

	field[4] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 2; i++)
		mvwprintw(win, 9 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**CASH WITHDRAWAL**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[2] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < size) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = cash_file(form, field, 2);
									bal = ret;
									if(bal == 2.0)
										print_in_middle(win, 23, 0, 120,"    NOT ENOUGH BALANCE!	    ", COLOR_PAIR(3));
									else if(bal == 0.0)
										print_in_middle(win, 23, 0, 120,"    ID/ACCOUNT NOT FOUND    ", COLOR_PAIR(3));
									else {
										print_in_middle(win, 23, 0, 120,"AMOUNT WITHDRAWN  SUCCESFULLY", COLOR_PAIR(3));
										wattron(win, COLOR_PAIR(3));
										mvwprintw(win, 21, 45, "ACCOUNT BALANCE IS : Rs.");
										mvwprintw(win, 21, 70, "%.2f", bal);
										wattroff(win, COLOR_PAIR(3));
										
									}
									
									j = wgetch(win);
									if((j == KEY_DOWN) || (j == KEY_UP)) {
										i = 0;
										while( i < size ) 
											set_field_buffer(field[i++], 0, "");
										print_in_middle(win, 23, 0, 120,"                                           ", COLOR_PAIR(10));
										wattron(win, COLOR_PAIR(10));
										mvwprintw(win, 21, 45, "                      ");
										mvwprintw(win, 21, 65, "                 ");
										wattroff(win, COLOR_PAIR(10));
									}
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[3] == current_field(form)) {
								make2(win, 0);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}




int fund_transfer(WINDOW* win) {                 // function to create form for fund transfer
	ret = 0;
	FIELD **field;
	FORM *form;
	float bal;
	char *s;
	int j = 0, count1 = 0;
	s = (char *)malloc(sizeof(char) * 21);
	while(j < 20){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, x, y;
	char *field_names[] = {"FROM (ACC NO. 1)","TO (ACC NO. 2)", "AMOUNT(Rs.)"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < size; i++) {			
		field[i] = new_field(1, 20, 9 + 2*i, 55, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[3] = new_field(1, 15, 21, 50, 0, 0);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	set_field_back(field[3], COLOR_PAIR(7));
	set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[3], 0, " TRANSFER ");

	field[4] = new_field(1, 8, 21, 72, 0, 0);
	field_opts_off(field[4], O_AUTOSKIP | O_EDIT);
	set_field_back(field[4], COLOR_PAIR(7));
	set_field_fore(field[4], COLOR_PAIR(7));
	set_field_buffer(field[4], 0, " EXIT ");

	field[5] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 3; i++)
		mvwprintw(win, 9 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**FUND TRANSFER**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[3] == current_field(form)) {
								i = 0;
								count1 = 0;
								while(i < 3) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 17, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count1++;
										break;
									}
									i++;
								}
								if(count1 == 0) {
									ret = transfer_file(form, field);
									bal = ret;
									if(bal == 2.0)
										print_in_middle(win, 17, 0, 120,"    NOT ENOUGH BALANCE!	    ", COLOR_PAIR(3));
									else if(bal == 0.0)
										print_in_middle(win, 17, 0, 120,"    ACCOUNT NUMBER 1 NOT FOUND    ", COLOR_PAIR(3));
									else if(bal == 1.0)
										print_in_middle(win, 17, 0, 120,"    ACCOUNT NUMBER 2 NOT FOUND    ", COLOR_PAIR(3));
									else if(bal != 0){
										print_in_middle(win, 17, 0, 120,"AMOUNT TRANSFERRED", COLOR_PAIR(3));
										wattron(win, COLOR_PAIR(3));
										mvwprintw(win, 19, 45, "ACCOUNT 2 BALANCE IS   : Rs.");
										mvwprintw(win, 19, 73, "%.2f", bal);
										wattroff(win, COLOR_PAIR(3));
										
									}
									
									
									j = wgetch(win);
									if((j == KEY_DOWN) || (j == KEY_UP)) {
										i = 0;
										while( i < size ) 
											set_field_buffer(field[i++], 0, "");
										print_in_middle(win, 19, 0, 120,"                                             ", COLOR_PAIR(10));
										wattron(win, COLOR_PAIR(10));
										mvwprintw(win, 17, 42, "           	               ");
										mvwprintw(win, 17, 65, "                 ");
										wattroff(win, COLOR_PAIR(10));
									}
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[4] == current_field(form)) {
								make2(win, 0);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}


float transfer_file(FORM *form, FIELD **field) {     //function to make changes in file after fund transfer
	i = 0;
	count = 0;
	int n1, n2, count2 = 0;
	float amt, bal;
	int l = field_count(form);
	account acc1;
	fp = fopen("data_account.txt", "r");
	fp1 = fopen("temp.txt", "w+");
	char **stf;
	char *stf1;
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l) {
		stf[i] = field_buffer(field[i], 0);
		i++;
	}   
	stf1 = string(stf[0]);
	n1 = atoi(stf1);	
	stf1 = string(stf[1]);
	n2 = atoi(stf1);
	stf1 = string(stf[2]);
	amt = atof(stf1);        
	while(fscanf(fp, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", &acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, &acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, &acc1.balance, acc1.u_date) != EOF) {
		if(n1 == acc1.acc_no || n2 == acc1.acc_no) {
			if(acc1.acc_no == n1){
				count++; 
				if(acc1.balance < amt)
					return 2.0;
				else
					acc1.balance -= amt;
			}
			else if(acc1.acc_no == n2) {
				count2++;		
				acc1.balance += amt;
				bal = acc1.balance;
			}
		}
		fprintf(fp1, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, acc1.balance, acc1.u_date);
			
	}
	remove("data_account.txt");
	rename("temp.txt", "data_account.txt");
	free(stf);
	fclose(fp);
	fclose(fp1);
	if(count == 0 || count2 == 0) {
		if(count == 0)
			return 0.0;
		else if(count2 == 0)
			return 1.0;
	}
	else
		return bal;
}

int del_account(WINDOW* win) {     //// function to create form for deleteing a bank account
	ret = 0;
	FIELD **field;
	FORM *form;
	char *s;
	int j = 0, k = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j < 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"ACCOUNT NUMBER", "FIRST NAME", "LAST NAME"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < 3; i++) {			
		field[i] = new_field(1, 30, 9 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[3] = new_field(1, 15, 17, 50, 0, 0);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	set_field_back(field[3], COLOR_PAIR(7));
	set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[3], 0, " DELETE ACCOUNT ");

	field[4] = new_field(1, 8, 17, 72, 0, 0);
	field_opts_off(field[4], O_AUTOSKIP | O_EDIT);
	set_field_back(field[4], COLOR_PAIR(7));
	set_field_fore(field[4], COLOR_PAIR(7));
	set_field_buffer(field[4], 0, " EXIT ");

	field[5] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 3; i++)
		mvwprintw(win, 9 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**DELETE ACCOUNT**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[3] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < size) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = delete_acc_file(form, field);
									if(ret == 1)
										print_in_middle(win, 23, 0, 120,"      ACCOUNT DELETED SUCCESFULLY     ", COLOR_PAIR(3));
									else if(ret == 0)
										print_in_middle(win, 23, 0, 120,"      ACCOUNT NOT FOUND      ", COLOR_PAIR(3));
									else if(ret == 2)
										print_in_middle(win, 23, 0, 120,"   ACCOUNT NO. AND NAME DOESN'T MATCH  ", COLOR_PAIR(3));
									else if(ret == 3)  //account can't be deleted if it still contains money
										print_in_middle(win, 23, 0, 120,"    ACCOUNT STILL CONTAIN MONEY!   ", COLOR_PAIR(3));
									
									k = wgetch(win);
									if((k == KEY_DOWN) || (k == KEY_UP)) {
										i = 0;
										while( i < size ) 
											set_field_buffer(field[i++], 0, "");
										print_in_middle(win, 23, 0, 120,"                                                          ", COLOR_PAIR(10));
									}
								}
								form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[4] == current_field(form)) {
								make2(win, 0);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}



int delete_acc_file(FORM *form, FIELD **field) {     //function to remove account details from file
	i = 0;
	int j = 0, n1;
	int l = field_count(form);
	account acc1, acc2;
	fp = fopen("data_account.txt", "r");
	fp1 = fopen("temp1.txt", "w+");
	char **stf;
	char *stf1;	
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l) {
		stf[i] = field_buffer(field[i], 0);
		i++;
	}
	stf1 = string(stf[0]);
	n1 = atoi(stf1);
	stf1 = string(stf[1]);
	strcpy(acc2.firstname,stf1);
	stf1 = string(stf[2]);
	strcpy(acc2.lastname,stf1);
	while(fscanf(fp, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", &acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, &acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, &acc1.balance, acc1.u_date) != EOF) {
		if(acc1.acc_no != n1)
			fprintf(fp1, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, acc1.balance, acc1.u_date);
		else if(acc1.acc_no == n1) {
			j++;
			if(strcmp(acc1.firstname, acc2.firstname) != 0)
				return 2;
			else if(strcmp(acc1.lastname, acc2.lastname) != 0)
				return 2;
			else if(acc1.balance != 0)
				return 3;
		}
		else if(feof(fp))
			break;
	}
	remove("data_account.txt");
	rename("temp1.txt", "data_account.txt");
	free(stf);
	fclose(fp);
	fclose(fp1);
	if (j == 0)
		return 0;
	return 1;
}



int change_pass(WINDOW* win) {            // function to create form for changing password
	ret = 0;
	FIELD **field;
	FORM *form;
	char *s;
	int j = 0, k = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j < 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int  size, i = 0, count = 0, x, y;
	char *field_names[] = {"USER ID", "OLD PASSWORD", "NEW PASSWORD", "CONFIRM PASSWORD"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < 4; i++) {			
		field[i] = new_field(1, 30, 7 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[4] = new_field(1, 18, 17, 50, 0, 0);
	field_opts_off(field[4], O_AUTOSKIP | O_EDIT);
	set_field_back(field[4], COLOR_PAIR(7));
	set_field_fore(field[4], COLOR_PAIR(7));
	set_field_buffer(field[4], 0, " CHANGE PASSWORD ");

	field[5] = new_field(1, 8, 17, 72, 0, 0);
	field_opts_off(field[5], O_AUTOSKIP | O_EDIT);
	set_field_back(field[5], COLOR_PAIR(7));
	set_field_fore(field[5], COLOR_PAIR(7));
	set_field_buffer(field[5], 0, " EXIT ");

	field[6] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 4; i++)
		mvwprintw(win, 7 + 2*i, 33, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 23, 0, 120,"**ONLY ONE ATTEMPT ALLOWED**", COLOR_PAIR(11));
	print_in_middle(win, 2 , 0, 120,"**CHANGE PASSWORD**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[4] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < size) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = change_pass_file(form, field);
									if(ret == 1) {
										print_in_middle(win, 23, 0, 120,"      PASSWORD CHANGED SUCCESSFULLY     ", COLOR_PAIR(3));
										i = 0;
										while( i < size ) 
											set_field_buffer(field[i++], 0, "");
									}
									else if(ret == 0)
										print_in_middle(win, 23, 0, 120,"      ACCOUNT NOT FOUND      ", COLOR_PAIR(3));
									else if(ret == 2)
										print_in_middle(win, 23, 0, 120,"   USER ID AND PASSWORD DOESN'T MATCH  ", COLOR_PAIR(3));
									else if(ret == 3)
										print_in_middle(win, 23, 0, 120,"   NEW AND CONFIRM PASSWORDS DOESN’T MATCH  ", COLOR_PAIR(3));
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
									k = wgetch(win);
									if(k) {
										make2(win, 0);
									}
								}
								form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[5] == current_field(form)) {
								make2(win, 0);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}


int change_pass_file(FORM *form, FIELD **field) {   //function for file handling while changing password
	passwrd p1, p2;
	int j = 0;
	int l = field_count(form);
	char new[20], confirm[20];
	
	fp = fopen("pass_staff.txt", "r");
	fp1 = fopen("temp4.txt", "w+");
	char **stf;
	char *stf1;	
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l) {
		stf[i] = field_buffer(field[i], 0);
		i++;
	}
	stf1 = string(stf[0]);
	strcpy(p2.usrname, stf1);
	stf1 = string(stf[1]);
	strcpy(p2.password, stf1);
	stf1 = string(stf[2]);
	strcpy(new, stf1);
	stf1 = string(stf[3]);
	strcpy(confirm, stf1);
	while(fscanf(fp, "%s %s\n", p1.usrname, p1.password) != EOF) {
		if(strcmp(p2.usrname, p1.usrname) != 0) 
			fprintf(fp1, "%s %s\n", p1.usrname, p1.password);
		else if(strcmp(p2.usrname, p1.usrname) == 0) {
			j++;
			if(strcmp(p2.password, p1.password) != 0) {
				return 2;
			}
			else if(strcmp(p2.password, p1.password) == 0) {
				fprintf(fp1, "%d\n", j);
				if(strcmp(new, confirm) == 0) {
					strcpy(p1.password, confirm);
					fprintf(fp1, "%s %s\n", p1.usrname, p1.password);
				}
				else if(strcmp(new, confirm) != 0) {
					return 3;
				}
			}
		}
		else if(feof(fp))
			break;
	}	
	remove("pass_staff.txt");
	rename("temp4.txt", "pass_staff.txt");
	free(stf);
	fclose(fp);
	fclose(fp1);
	if (j == 0)
		return 0;
	return 1;
}


int account_info(WINDOW* win, int a) {         // function to create form for account info
	ret = 0;
	FIELD **field;
	FORM *form;
	char *s;
	int j = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j < 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"ACCOUNT NUMBER"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < 1; i++) {			
		field[i] = new_field(1, 30, 9 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[1] = new_field(1, 15, 15, 50, 0, 0);
	field_opts_off(field[1], O_AUTOSKIP | O_EDIT);
	set_field_back(field[1], COLOR_PAIR(7));
	set_field_fore(field[1], COLOR_PAIR(7));
	set_field_buffer(field[1], 0, " VIEW ");

	field[2] = new_field(1, 8, 15, 72, 0, 0);
	field_opts_off(field[2], O_AUTOSKIP | O_EDIT);
	set_field_back(field[2], COLOR_PAIR(7));
	set_field_fore(field[2], COLOR_PAIR(7));
	set_field_buffer(field[2], 0, " EXIT ");

	field[3] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 1; i++)
		mvwprintw(win, 9 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**ACCOUNT INFORMATION**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[1] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < size) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = view_acc_file(form, field, win, a);
									if(ret == 0)
										print_in_middle(win, 23, 0, 120,"      ACCOUNT NOT FOUND      ", COLOR_PAIR(3));
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
									j = wgetch(win);
									if((j == KEY_DOWN) || (j == KEY_UP)) {
										print_in_middle(win, 23, 0, 120,"                                           ", COLOR_PAIR(10));
									}
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[2] == current_field(form)) {
								if(a == 1)
									make2(win, 0);
								else if(a == 0)
									make1(win, 1);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}


int view_acc_file(FORM *form, FIELD **field, WINDOW *win, int a) {     //function for extracting account info from file in order to display
	i = 0;
	int j = 0, n1;
	int l = field_count(form);
	account acc1;
	fp = fopen("data_account.txt", "r+");
	char **stf;
	char *stf1;	
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l) {
		stf[i] = field_buffer(field[i], 0);
		i++;
	}
	stf1 = string(stf[0]);
	n1 = atoi(stf1);
	while(fscanf(fp, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", &acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, &acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, &acc1.balance, acc1.u_date) != EOF) {	
		if(acc1.acc_no == n1) {
			j++;
			display(win, n1, a);
		}
		else if(feof(fp))
			break;
	}
	free(stf);
	fclose(fp);
	if (j == 0)
		return 0;
	return 1;
}

int view_user_file(FORM *form, FIELD **field, WINDOW *win, int a) {        //function for extracting account info from file in order to display
	i = 0;
	int j = 0;
	int l = field_count(form);
	staff st1, st2;
	fp = fopen("data_staff.txt", "r+");
	char **stf;
	char *stf1;	
	stf = (char **)malloc(sizeof(char *) * l);
	while(i < l) {
		stf[i] = field_buffer(field[i], 0);
		i++;
	}
	stf1 = string(stf[0]);
	strcpy(st1.id, stf1);
	while(fscanf(fp, " %s %s %s %s %s %s %s\n", st2.id, st2.fname, st2.lname, st2.dob, st2.contact, st2.nationality, st2.email) != EOF) {
		if(strcmp(st1.id, st2.id) == 0) {
			j++;
			display1(win, st1.id, a);
		}
		else if(feof(fp))
			break;
	}
	free(stf);
	fclose(fp);
	if (j == 0)
		return 0;
	return 1;
}

int user_info(WINDOW* win, int a) {       // function to create form for user info
	ret = 0;
	FIELD **field;
	FORM *form;
	char *s;
	int j = 0;
	s = (char *)malloc(sizeof(char) * 31);
	while(j < 30){
		s[j] = ' ';
		j++;
	}
	s[j] = '\0';
	int size, i = 0, count = 0, x, y;
	char *field_names[] = {"USER ID"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(win, TRUE);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	for(i = 0; i < 1; i++) {			
		field[i] = new_field(1, 30, 9 + 2*i, 50, 0, 0);
	}
	i = 0;
	while(i < size) {
		field_opts_off(field[i], O_AUTOSKIP );
		set_field_back(field[i], COLOR_PAIR(7));
		i++;
	} 
	field[1] = new_field(1, 15, 15, 50, 0, 0);
	field_opts_off(field[1], O_AUTOSKIP | O_EDIT);
	set_field_back(field[1], COLOR_PAIR(7));
	set_field_fore(field[1], COLOR_PAIR(7));
	set_field_buffer(field[1], 0, " VIEW ");

	field[2] = new_field(1, 8, 15, 72, 0, 0);
	field_opts_off(field[2], O_AUTOSKIP | O_EDIT);
	set_field_back(field[2], COLOR_PAIR(7));
	set_field_fore(field[2], COLOR_PAIR(7));
	set_field_buffer(field[2], 0, " EXIT ");

	field[3] = NULL;
	form = new_form(field);	
	scale_form(form, &y, &x);

	set_form_win(form, win);
	set_form_sub(form, derwin(win, y, x, 1, 60));
	post_form(form);
	for(i = 0; i < 1; i++)
		mvwprintw(win, 9 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	print_in_middle(win, 2 , 0, 120,"**STAFF USER INFORMATION**", COLOR_PAIR(3));
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while((i = wgetch(win))) {
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
						case 10:
							if(field[1] == current_field(form)) {
								i = 0;
								count = 0;
								while(i < size) {
									if(strcmp(field_buffer(field[i], 0), s) == 0 ) {
										print_in_middle(win, 23, 0, 120,"     FIELD CAN'T BE EMPTY!    ", COLOR_PAIR(3));
										count++;
										break;
									}
									i++;
								}
								if(count == 0) {
									ret = view_user_file(form, field, win, a);
									if(ret == 0)
										print_in_middle(win, 23, 0, 120,"      ACCOUNT NOT FOUND      ", COLOR_PAIR(3));
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
									j = wgetch(win);
									if((j == KEY_DOWN) || (j == KEY_UP)) {
										print_in_middle(win, 23, 0, 120,"                                           ", COLOR_PAIR(10));
									}
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[2] == current_field(form)) {
								if(a == 1)
									make2(win, 0);
								else if(a == 0)
									make1(win, 1);
							}
							else {
								form_driver(form, REQ_NEXT_FIELD);
								form_driver(form, REQ_END_LINE);
							}
						break;									
						case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
				  				
			}
		}
	}
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(win, 3 + 2 * i, 1);
		wclrtoeol(win);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(win, 0, 0);
	wrefresh(win);
	return ret;
}


int check_date(char *date) {     // function to check for valid date entry   
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


char* sys_date() {     //function to obtain system date
	char *buf2;
	buf2 = (char*)malloc(20);
   	time_t curtime;
   	struct tm *loc_time;
   	curtime = time (NULL);
   	loc_time = localtime (&curtime);
	strftime (buf2, 150, "%d/%m/%Y", loc_time);
	return buf2;
}

char* sys_date1() {         //function to obtain system date
	char *buf2;
	buf2 = (char*)malloc(20);
   	time_t curtime;
   	struct tm *loc_time;
   	curtime = time (NULL);
   	loc_time = localtime (&curtime);
	strftime (buf2, 150, "Today is %e %b %Y", loc_time);
	return buf2;
}

// function to keep account up to date i.e adding interest in currnt balance till date and updates date in file
void uptodate()
{
    account acc1;
    int no_of_yr, no_of_month, no_of_days, n1, n2;
    float r;
    char date[15];
    fp = fopen("data_account.txt","r");
    strcpy(date, sys_date());
    if (fp != NULL)//performs every thing only when file exists i.e. only wen pointer is not null
    {
        fp1 = fopen("temp.txt","w+");
        i=0;
        while(fscanf(fp, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", &acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, &acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, &acc1.balance, acc1.u_date) != EOF) {
        //extracting no of days, months and yr of system date
        no_of_yr=(date[8]-48)*10+(date[9]-48);
        no_of_month=(date[3]-48)*10+(date[4]-48);
        no_of_days=(date[0]-48)*10+(date[1]-48);

        n1 = no_of_yr*365 + no_of_month*30 + no_of_days;//n1 is no. of days elasped

        //extracting no of days, months and yr of date stored in data_account.txt
        no_of_yr = (acc1.u_date[8] - 48)*10 + (acc1.u_date[9]-48);
        no_of_month=(acc1.u_date[3] - 48)*10 + (acc1.u_date[4]-48);
        no_of_days=(acc1.u_date[0] - 48)*10 + (acc1.u_date[1]-48);
        n2 = no_of_yr*365 + no_of_month*30 + no_of_days;  //n2 is no. of days elasped on last updated date

        r = 6.0/365;
	
        acc1.balance = acc1.balance * (pow((1 + r/100), n1 - n2));   //calculation of compound interest
        strcpy(acc1.u_date,date);
        fprintf(fp1, "%d %s %s %s %d %s %s %s %s %s %s %lf %s\n", acc1.acc_no,  acc1.firstname, acc1.lastname, acc1.dob, acc1.age, acc1.addr, acc1.city, acc1.state, acc1.contact, acc1.email, acc1.acc_typ, acc1.balance, acc1.u_date);

        }
        fclose(fp);
        fclose(fp1);
        remove("data_account.txt");
        rename("temp.txt", "data_account.txt");
    }


}
