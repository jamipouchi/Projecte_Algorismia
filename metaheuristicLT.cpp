#include "metaheuristicLT.h"

#include <chrono>

int main(int argc, char const *argv[])
{
    //string filename = argv[1];
    string filename = "graph_jazz.dimacs";
    float r = 0.5;
    Graph graph = read_graph(filename);

    //let's count the time of the metod greedy
    auto ini = chrono::high_resolution_clock::now();
    vector<int> S = metaheuristic(graph, r);
    auto fi = chrono::high_resolution_clock::now();
    auto temps = chrono::duration_cast<chrono::microseconds>(fi - ini);

    //print the time in seconds
    cout << "ALGORITME: METAHEURISTIC" << endl;
    cout << "INPUT: " << filename << endl;
    cout << "OUTPUT: " << endl;
    cout << "\t#S = " << S.size() << endl;
    cout << '\t' << "Temps: " << temps.count() / 1000000.0 << "s" << endl;
}