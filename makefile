
CC = g++ -std=c++11
DEBUG = -g
WARN = -Wall
INCLUDE = -I .

hanoi.x: hanoi.o main.o
	$(CC) $(WARN) $(INCLUDE) hanoi.o main.o -o hanoi.x

main.o: main.cpp
	$(CC) $(WARN) $(INCLUDE) main.cpp -c

hanoi.o: hanoi.h hanoi.cpp
	$(CC) $(WARN) $(INCLUDE) hanoi.cpp -c

clean:
	\rm *.o *~ hanoi.x
