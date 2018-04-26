.PHONY: all p1 p2 p3 p4

all: p1 p2 p3 p4

p1:
	g++ p1.cpp -o p1 && ./p1

p2:
	g++ p2.cpp -o p2 && ./p2

p3:
	g++ p3.cpp -o p3 && ./p3

p4:
	g++ p4.cpp -o p4 && ./p4
