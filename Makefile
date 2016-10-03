test:test.cpp ga.h
	g++ -g -o test -std=c++11 -Wall test.cpp
clean:
	-rm test
