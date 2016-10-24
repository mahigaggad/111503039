project: main_1.o
	cc main_1.o -o project -lncurses -lmenu -lform
main_1.o :main_1.c
	cc -c main_1.c
