CPPFLAGS=-g -pthread -std=c++11 -O3
LDFLAGS=-g

autograde: main.o
	g++ $(LDFLAGS) -o autograde main.o 

main.o: main.cpp split.h
	g++ $(CPPFLAGS) -c main.cpp

clean:
	rm -f *.o
	rm autograde