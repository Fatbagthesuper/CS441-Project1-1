# MakeFile
# Tyler Nickel and Nathanial Harris
# Feb. 13, 2013
#
# CS441/541: Project 1 Part 1
#
#####################################################################
#
# Type "make" or "make OurShell" to compile your code
# 
# Type "make clean" to remove the executable (and any object files)
#
#####################################################################

CC=gcc
CFLAGS=-Wall -g

all: OurShell

myshell: OurShell.c OurShell.h 
	$(CC) -o OurShell OurShell.c  $(CFLAGS)

Support.o: Support.h Support.c
	$(CC) -c -o Support.o Support.c $(CFLAGS)

clean:
	$(RM) OurShell *.o
	$(RM) -rf *.dSYM
