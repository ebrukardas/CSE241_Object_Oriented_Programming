all: main1 main0 clean

main1: main.o
	g++ main.o -o main
	./main deneme.txt 1

main0: 
	./main deneme.txt 0

clean:
	rm *.o main