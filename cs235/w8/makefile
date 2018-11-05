###############################################################
# Program:
#     Week 08, Binary Tree
#     Brother JonesL, CS235
# Author:
#     Nik Huff - 5 hours
#     Tyler Peterson
#     Keith Wheeler - 2 hours
# Summary:
#     Creates the notion of a Binary Tree.
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week08.o huffman.o 
	g++ -o a.out week08.o huffman.o -g
	tar -cf week08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week08.o     : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
week08.o: bnode.h huffman.h week08.cpp
	g++ -c week08.cpp -g

huffman.o: bnode.h huffman.h huffman.cpp vector.h
	g++ -c huffman.cpp -g

