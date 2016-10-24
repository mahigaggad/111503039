#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<menu.h>
#include<form.h>
#include<ctype.h>
#include<time.h>
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
int make(WINDOW *win1,int);
int make1(WINDOW *win_1, int m);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
int login(WINDOW *win, int m);
int designed_by(WINDOW *win_1);
int match(char* usrname, char* pass, int m);
int staffmenu(WINDOW* win);
int adminmenu(WINDOW* win);
int add_user(WINDOW *win);
int add_to_file(FORM *form, FIELD **field);
char *string(char *stf);



int rows, cols, ret, i, ret1, count;
FILE *fp, *fp1;
time_t tt;

typedef struct passwrd {
	char usrname[15], password[20];

}passwrd;

typedef struct account {
	char firstname[25], lastname[25];   //take first and last name seperately
	int acc_no;
	char *date;
	char addr[60];
	char contact[15];
	double balance;
	char acc_typ;
	char sex;
	char dob[15];
	float RoI; // rate of interest
	
}account;

 typedef struct staff {
	char id[20], fname[25], lname[25], dob[15], contact[15], nationality[20], email[30];
	}staff; 




int main() {
	WINDOW *win_1, *win_2, *win_3;
	int ch;
	char *choices[] = {"ADMIN", "STAFF", "DESIGNED BY", "HOME", "EXIT", (char *)NULL};
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
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
	init_pair(4, 12, 91);
	init_pair(5, 123, 130);
	init_pair(6, COLOR_CYAN, COLOR_WHITE);
	attron(A_BOLD | A_UNDERLINE| COLOR_PAIR(1) | A_STANDOUT);
	mvprintw(4, (cols - 32)/2, "WELCOME TO BANK MANAGEMENT SYSTEM");
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
					if(ret == 1)
						main();
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
	end:
	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return 0;
}

int make1(WINDOW *win_1, int m) {
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

int staffmenu(WINDOW* win_1) {
	char *choices1[] = {
                        "ADD ACCOUNT", "CASH DEPOSIT", "CASH WITHDRAWAL" , "FUND TRANSFER", "ACCOUNT INFO","TRANSACTION INFO","PROFILE", "CHANGE PASSWORD", "LOGOUT", (char *)NULL
                  };
	int ch, x, y;
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
				if(strcmp(item_name(current_item(my_menu)),"ADMIN") == 0 ) {
					make(win_1, 0);
					main(); 						
				}
				if(strcmp(item_name(current_item(my_menu)),"STAFF") == 0 ) {
					ret1 = make(win_1, 1);
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
					if(ret == 1)
						main();
				}
				if(strcmp(item_name(current_item(my_menu)), "HOME") == 0) {
					main();
				} 
				else if(strcmp(item_name(current_item(my_menu)),"LOGOUT") == 0 ) {
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
				break;
				
		}
                wrefresh(win_1);
	}	
	end:
	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return 1;
}


int adminmenu(WINDOW* win_1) {
		char *choices1[] = {
                        "ADD USER", "DELETE USER", "VIEW USER LOG" , "VIEW USER INFO", "CUSTOMER ACCOUNT INFO","CHANGE PASSWORD", "LOGOUT", (char *)NULL
                  };
	int ch, x, y;
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
				if(strcmp(item_name(current_item(my_menu)),"STAFF") == 0 ) {
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
				if(strcmp(item_name(current_item(my_menu)),"DESIGNED BY") == 0 ) {
					unpost_menu(my_menu);
        				free_menu(my_menu);
        				for(i = 0; i < n_choices; ++i)
        	        			free_item(my_items[i]);
	
					ret = designed_by(win_1);
					if(ret == 1)
						main();
				}
				if(strcmp(item_name(current_item(my_menu)), "HOME") == 0) {
					main();
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
	end:
	/* Unpost and free all the memory taken up */
	unpost_menu(my_menu);
        free_menu(my_menu);
        for(i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
	endwin();
	return 1;
}





	
int make(WINDOW *win_1,int m){
	i=0;	
	win_1 = newwin(28, 120, (rows - 26)/2, (cols - 120)/2);	//  creating window
	box(win_1, 0 , 0);	
	wbkgd(win_1, COLOR_PAIR(4));	
	wrefresh(win_1);
	if (m == 0 || m == 1)							
		i = login(win_1, m);
	else if(m == 2)
		i = add_user(win_1);
	wclear(win_1);
	wbkgd(win_1,COLOR_PAIR(4));
	wrefresh(win_1);
	delwin(win_1);
	return i;
}		

int designed_by(WINDOW *win_1) {
	int i;	
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
	print_in_middle(win_1, 12, 0, 120, "EMAIL  :  mahmagaggad@gmail.com", COLOR_PAIR(2));
	print_in_middle(win_1, 14, 0, 120,"CONTACT : 9823075031", COLOR_PAIR(2));
	wrefresh(win_1);
	while(wgetch(win_1) == 27)
		return 1;
	return 0;
}

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


int login(WINDOW *win, int m) {
	FIELD **field;
	FORM *form;
	int ch = 0, size, i = 0, count = 0, x, y;
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
	
	field[3] = new_field(1, 20, 11, 62, 0, 0);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	set_field_back(field[3], COLOR_PAIR(7));
	//set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[3], 0, " forget Password? ");

	field[4] = new_field(1, 8, 13, 56, 0, 0);
	field_opts_off(field[4], O_AUTOSKIP | O_EDIT);
	set_field_back(field[4], COLOR_PAIR(7));
	//set_field_fore(field[3], COLOR_PAIR(7));
	set_field_buffer(field[4], 0, " HOME ");
	field[5] = NULL;

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
	while(i = wgetch(win)) {
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
								if(ret == 0)
									print_in_middle(win, 17, 0, 120,"Incorrect user ID or password!", COLOR_PAIR(3));
								else if(ret == 1)
									goto end;
							}
							else if(field[4] == current_field(form)){
									main();
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
















int match(char* usrname, char* pass, int m) {
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



int add_user(WINDOW *win) {
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
	int ch = 0, size, i = 0, count = 0, x, y;
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
	for(i = 0; i < 8; i++)
		mvwprintw(win, 5 + 2*i, 35, "%s: ", field_names[i]);
	print_in_middle(win, 28, 0, 120,"USE UP AND DOWN KEYS TO MOVE BETWEEN FIELDS", COLOR_PAIR(3));
	
	form_driver(form, REQ_FIRST_FIELD);	
	wrefresh(win);
	while(i = wgetch(win)) {
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
									 if(ret == 1)
										print_in_middle(win, 23, 0, 120,"USER ACCOUNT ADDED SUCCESFULLY", COLOR_PAIR(3));
									else if(ret == 0)
										print_in_middle(win, 23, 0, 120,"ID/ACCOUNT ALREADY IN USE.", COLOR_PAIR(3));
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
								}
									form_driver(form, REQ_FIRST_FIELD);
							}
							else if(field[9] == current_field(form)) {
								make1(win, 1);
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
 int add_to_file(FORM *form, FIELD **field) {
	passwrd p1;
	i = 0;
	count = 0;
	int j = 0;
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
	strcpy(st1.id, stf1);
	l2 = strlen(st1.id);
		while(fscanf(fp, " %s %s %s %s %s %s %s\n", st1.id, st1.fname, st1.lname, st1.dob, st1.contact, st1.nationality, st1.email) != EOF) {
			if(feof(fp))
				break;
			else if(strncmp(st1.id, st2.id, l2) == 0)
				return 0;
		}
	stf1 = string(stf[1]);
	strcpy(st2.fname,stf1);
	stf1 = string(stf[2]);
	strcpy(st2.lname,stf1);
	stf1 = string(stf[3]);
	strcpy(st2.dob,stf1);
	stf1 = string(stf[4]);
	strcpy(st2.contact,stf1);
	stf1 = string(stf[5]);
	strcpy(st2.nationality,stf1);
	stf1 = string(stf[6]);
	strcpy(st2.email,stf1);
	stf1 = string(stf[0]);
	strcpy(p1.usrname, stf1);
	stf1 = string(stf[7]);
	strcpy(p1.password, stf1);
	fprintf(fp, " %s %s %s %s %s %s %s\n", st2.id, st2.fname, st2.lname, st2.dob, st2.contact, st2.nationality, st2.email);
	//fprintf(fp1, "%s %s\n", p1.usrname, p1.password);
	fwrite(&p1, sizeof(passwrd), 1, fp1);
	free(stf);
	fclose(fp);
	fclose(fp1);
	return 1;
}


//generate random user id	
int ran(int m) {
	srandom(time(&tt));
	int n;
	account acc;
	staff st;
	random:
	n = random() % 10000000;
	/*if(m == 0)
		fp = fopen("data_staff.dat", "r");
		if (fp == NULL)
			st.id = n;
		else
			while(fscanf(fp, " %s %s %s %s %s %s %s\n", st.id, st.firstname, st.lastname, st.dob, st.contact, st.nationality, st.email ) != EOF) {
				if( n == st.id)
					goto random;
				else st.id = n; 
		} */	
		
	if(m == 1 )
		fp = fopen("data.dat", "r");
		if (fp == NULL)
			acc.acc_no = n;
		else
			while(fscanf(fp, " %s %s %d %s %s %s %lf %c %c %s\n", acc.firstname, acc.lastname, &acc.acc_no, acc.date, acc.addr, acc.contact, &acc.balance, &acc.acc_typ, &acc.sex, acc.dob) != EOF) {
			if( n == acc.acc_no)
				goto random;
			else acc.acc_no = n; 
		}
	return n;		
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
