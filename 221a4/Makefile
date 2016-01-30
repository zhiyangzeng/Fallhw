all: BinaryNode.o BinarySearchTree.o main.o
	c++ -std=c++11 BinaryNode.o BinarySearchTree.o main.o -o main
	
BinaryNode.o : BinaryNode.cpp BinaryNode.h
	c++ -std=c++11 -c -g BinaryNode.cpp

BinarySearchTree.o : BinarySearchTree.cpp BinaryNode.h BinarySearchTree.h 
	c++ -std=c++11 -c -g BinarySearchTree.cpp

main.o: main.cpp BinarySearchTree.h 
	c++ -std=c++11 -c -g main.cpp
	
clean:
	rm *.o main
