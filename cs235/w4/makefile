###############################################################
# Program:
#     Week 04, DEQUE
#     Brother JonesL, CS235
# Author:
#     Nik Huff, Keith Wheeler, Tyler Petersen
# Summary:
#     This program creates a Deque container, then tests it
#      thoroughly. It also has a now serving function to serve
#      incoming students asking for help from TA's.
# Time:
#     Tyler - 2 hours
#     Nik - 5 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h week04.o nowServing.o
	g++ -o a.out week04.o nowServing.o
	tar -cf week04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week04.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
week04.o: deque.h week04.cpp
	g++ -c week04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp
