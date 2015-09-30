project: mini.o
	cc mini.o -o project
mini.o: mini.c
	cc -c mini.c