test:testGa.cpp ga.h
	g++ -g -o testGa -std=c++11 -Wall testGa.cpp
clean:
	-rm testGa
