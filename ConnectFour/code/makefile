all: exe

exe: main.o 
	g++ -o exe main.o ConnectFourPlusUndo.o ConnectFourDiagonal.o ConnectFourPlus.o ConnectFourAbstract.o Cell.o

main.o: main.cpp
	g++ -c main.cpp ConnectFourPlusUndo.cpp ConnectFourDiagonal.cpp ConnectFourPlus.cpp ConnectFourAbstract.cpp Cell.cpp  -std=c++11


# ConnectFourPlusUndo ConnectFourDiagonal


clean: 
	rm *.o exe
