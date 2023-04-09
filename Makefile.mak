OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++11

greedyIC.o: greedyIC.cpp greedyIC.h difusioIC.h lib.h
	g++ -c greedyIC.cpp $(OPCIONS)
	g++ -o greedyIC greedyIC.o
	