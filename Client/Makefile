# Fichier Makefile

CC = gcc
CFLAGS = -g -Wall -ansi -D _SVID_SOURCE 
CFLAG2 = -c -Wall -ansi -D _SVID_SOURCE 
OBJETS = CL_monitor.o CL_main.o
SRC =CL_monitor.c CL_main.c

all: cl CL

cl : $(CC) CL_monitor.c CL_main.c  -o CL.o
	

CL_main.o : CL_main.c CL_include
	$(CC) $(CFLAG2) CL_main.c -o CL_main.o

CL_monitor.o : CL_monitor.c CL_include CL_monitor.h
	$(CC) $(CFLAG2) CL_monitor.c -o CL_monitor.o

clean:
	@rm -f *~ *.o cl_zz CL