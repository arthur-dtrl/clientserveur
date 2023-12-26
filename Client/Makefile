# Fichier Makefile

CC = gcc
CFLAGS = -g -Wall -ansi -D _SVID_SOURCE 
CFLAG2 = -c -Wall -ansi -D _SVID_SOURCE 
OBJETS = CL_main.o CL_connect.o 

all: cl CL

cl : $(OBJETS) CL_main.c
	$(CC) $(CFLAGS) $(OBJETS) -o cl_zz
	$(CC) $(CFLAGS) CL_main.c -o CL

CL_main.o : CL_main.c CL_include
	$(CC) $(CFLAG2) CL_main.c -o CL_main.o

CL_connect.o : CL_connect.c CL_include CL_connect.h
	$(CC) $(CFLAG2) CL_connect.c -o CL_connect.o

clean:
	@rm -f *~ *.o cl_zz CL