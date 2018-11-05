###############################################################
# Program:
#     Week 02, STACK
#     Brother JonesL, CS235
# Author:
#     Nik Huff, Keith Wheeler, Tyler Petersen
# Summary:
#     Creates a stack template class that functions the same as
#     the standard stack. Also implements this stack by
#     converting infix to postfix notation.
# Time:
#     Nik Huff - 3 hrs
#     Tyler Petersen - 2 hours
#     Keith Wheeler - 5 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h week02.o infix.o 
	g++ -o a.out week02.o infix.o 
	tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
	g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

clean:
	rm *.o *.tar
