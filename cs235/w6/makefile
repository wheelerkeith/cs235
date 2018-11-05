###############################################################
# Program:
#     Week 06, NODE
#     Brother Jonesl, CS235
# Author:
#     Nik Huff - 3 hours
#     Tyler Petersen - 2 hours
#     Keith Wheeler - 1 hour
# Summary:
#     Implements a linked list using nodes. 
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h week06.o 
	g++ -o a.out week06.o  -g
	tar -cf week06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week06.o      : the driver program
#      <anything else?>
##############################################################
week06.o: node.h week06.cpp sortInsertion.h
	g++ -c week06.cpp -g
