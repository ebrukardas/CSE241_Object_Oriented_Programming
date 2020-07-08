all: exe

exe: main.o 
	g++ -o exe GTUSet.o GTUMap.o myException.o

main.o: main.cpp 
	g++ -c GTUSet.cpp GTUMap.cpp myException.cpp -std=c++11

clean: 
	rm *.o exe