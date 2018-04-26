.PHONY: all p1 p2 p3 p4 zip clean

all: clean p1 p2 p3 p4 zip

p1:
	g++ Part\ 1/p1.cpp -o p1 && ./p1

p2:
	g++ Part\ 2/p2.cpp -o p2 && ./p2

p3:
	g++ Part\ 3/p3.cpp -o p3 && ./p3

p4:
	g++ Part\ 4/p4.cpp -o p4 && ./p4

zip:
	zip submission.zip -9 -xi Part*/* Makefile
	du -b submission.zip
	unzip -t submission.zip

clean:
	rm -f *.exe
	rm -f submission.zip
