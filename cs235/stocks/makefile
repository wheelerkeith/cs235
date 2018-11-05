###############################################################
# Program:
#     Week 03, QUEUE
#     Brother JonesL, CS235
# Author:
#     Nik Huff, Keith Wheeler, Tyler Petersen
# Summary:
#     This program so far correctly utilizes a queue, and tests
#      it's attributes. 
#     It also handles and executes the stocks program. The only 
#      thing wrong is it will display 4.10 as 4.09, 155 as 149.99
#      and 5.1 as 5.09.
# Time:
#     keith - 2 hours
#     Tyler - 4 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h week03.o dollars.o stock.o
	g++ -o a.out week03.o dollars.o stock.o
	tar -cf week03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      week03.o       : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
week03.o: queue.h week03.cpp
	g++ -c week03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp
