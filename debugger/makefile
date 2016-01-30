all: file1.o
	c++ -std=c++11 file1.o main.o -o main
file1.o: file1.h
	c++ -std=c++11 -c file1.h
main.o: main.cpp file1.h
	c++ -std=c++11 -c main.cpp
clean:
	rm *.o main
run:
	./main