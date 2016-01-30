all: main.o
	c++ -std=c++11 main.o -o main

main.o: main.cpp My_vec.h
	c++ -std=c++11 -c -g main.cpp
clean:
	rm *.o main
