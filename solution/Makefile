all: solution

solution: main.o unsigned_ultra_long.o
	g++ -std=c++11 -O3 main.o unsigned_ultra_long.o -o solution

main.o: main.cpp
	g++ -std=c++11 -O3 -c main.cpp

unsigned_ultra_long.o: unsigned_ultra_long.cpp
	g++ -std=c++11 -O3 -c unsigned_ultra_long.cpp

clean:
	rm -rf *.o solution
