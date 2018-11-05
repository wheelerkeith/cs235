#####################################
# Program:
#     Week 07, LIST
#     Brother Jonesl, CS235
# Author:
#     Nik Huff - 1 hour
#     Tyler Petersen - 2 hours
#     Keith Wheeler - 2 hours
# Summary:
#     Creates a linked list that then goes through a series
#       of test to confirm it works properly. It then 
#       can also calculate Fibinacci numbers. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h node.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h node.h week07.cpp
	g++ -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h node.h
	g++ -c fibonacci.cpp

