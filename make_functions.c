#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<menu.h>
#include<form.h>
#include<ctype.h>
#include<time.h>
#include<math.h>
#include"functions.h"

int make2(WINDOW *win_1, int m) {
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


