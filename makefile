
CC = g++ -std=c++11
DEBUG = -g
WARN = -Wall

hanoi.x: hanoi.cpp
	$(CC) $(WARN) hanoi.cpp -o hanoi.x

clean:
	\rm *.o *~ hanoi.x
