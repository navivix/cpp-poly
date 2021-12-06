testpoly: testpoly.cpp poly.h
	g++ -g -Wall -fno-elide-constructors $< -o $@

.PHONY: all clean test

all: clear clean test

clear:
	-clear

clean:
	-rm -f testpoly.o testpoly

test: testpoly
	-valgrind --leak-check=full ./testpoly