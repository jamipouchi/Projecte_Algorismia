all:
	g++ -c difusioIC.cpp
	g++ -c greedyIC.cpp
	g++ -o greedyIC greedyIC.o difusioIC.o