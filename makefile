project: bms.o
	cc bms.o -o project
bms.o: bms.c
	cc -c bms.c
