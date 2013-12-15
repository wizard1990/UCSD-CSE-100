# A simple makefile for CSE 100 P1

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -g -Wall

#include debugging symbols in executable
LDFLAGS= -g	

bst: test_BST.o 
	g++ -o bst test_BST.o

test_BST.o: BST.hpp BSTNode.hpp BSTIterator.hpp 


