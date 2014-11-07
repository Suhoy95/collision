collision: collision.o main.o
	g++ main.o collision.o -lGL -lglut -o collision
collision.o: collision.cpp collision.h
	g++ -c collision.cpp
main.o: main.cpp main.h
	g++ -c main.cpp 
open: 
	vim -p main.cpp collision.cpp collision.h main.h makefile
setting:
	vim input
start: collision input
	./collision < input
clean:
	rm *.o collision
