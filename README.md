CS441-Project1-1
================

CS441 Project1-1 Files
-----------------------------------------------------------------
_____  _______ 		          ____		      	       _______
|    ||		         /\	     |    \  	  |\        /| |
|____||		        /  \     |	   \  	| \      / | |
| \   |_______   /____\    |	   |  	|  \    /  | |_______
|  \  |		      /      \   |     /  	|   \  /   | |
|   \ |_______ /        \  |____/   	|    \/    | |_______
-----------------------------------------------------------------
By: Tyler Nickel and Nathan Harris
Date: 2/11/2014

---------
|Summary|
---------

----------------
|Software Build|
----------------
	
#
# To compile the program using 'make' (optional) (Do not type the 'shell$')
#
shell$ make
gcc -o finput -Wall -g -O0 finput.c
gcc -o calc calc.c -Wall -g -O0 -lm
shell$

#
# To compile the program using GCC (Do not type the 'shell$')
#
shell$ gcc -o finput finput.c -Wall -g -O0 -lm
shell$ gcc -o calc calc.c -Wall -g -O0 -lm

#
# To run the program 
#
shell$ ./finput
...
shell$
shell$ ./calc
...
shell$

#
# To cleanup the directory using 'make clean' (optional)
#
shell$ make clean
rm -f finput
rm -f calc
rm -f -rf *.o *.dSYM
shell$

#
# To cleanup the directory using GCC 
#
shell$ rm -f finput
shell$ rm -f calc
shell$ rm -f -rf *.o *.dSYM
shell$

----------------
|Software Usage|
----------------



----------------
|Software Tests|
----------------

	


----------
|Examples|
----------


---------------------
|Known Bugs/Problems|
---------------------
	At the time of this writing, there are no known bugs or problems with FINPUT or CALC
