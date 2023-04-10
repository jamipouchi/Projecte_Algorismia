OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++11

greedyIC.o: greedyIC.cpp greedyIC.h difusioIC.h lib.h
	g++ -c greedyIC.cpp $(OPCIONS)
	g++ -o greedyIC greedyIC.o

localSearchIC.o: localSearchIC.cpp localSearchIC.h greedyIC.h difusioIC.h lib.h
	g++ -c localSearchIC.cpp $(OPCIONS)
	g++ -o localSearchIC localSearchIC.o

metaheuristicIC.o: metaheuristicIC.cpp metaheuristicIC.h greedyIC.h difusioIC.h lib.h
	g++ -c metaheuristicIC.cpp $(OPCIONS)
	g++ -o metaheuristicIC metaheuristicIC.o

metaheuristicIC2.o: metaheuristicIC2.cpp metaheuristicIC2.h greedyLT.h difusioLT.h lib.h
	g++ -c metaheuristicIC2.cpp $(OPCIONS)
	g++ -o metaheuristicIC2 metaheuristicIC2.o