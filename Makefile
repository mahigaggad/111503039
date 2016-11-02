project: main_1.o
	cc main_1.o -o project -lncurses -lmenu -lform -lm
main_1.o :main_1.c functions.h
	cc -c main_1.c
