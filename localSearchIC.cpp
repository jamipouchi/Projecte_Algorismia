#include "localSearchIC.h"
#include <chrono>

int main(int argc, char const *argv[])
{
    string filename = argv[1];
    cout << "Introdueix la probabilitat de difusio" << endl;
    float diffusionProbability;
    cin >> diffusionProbability;
    Graph graph = read_graph(filename);

    //let's count the time of the metod greedy
    auto ini = chrono::high_resolution_clock::now();
    vector<int> S = localSearchIC(graph, diffusionProbability);
    auto fi = chrono::high_resolution_clock::now();
    auto temps = chrono::duration_cast<chrono::microseconds>(fi - ini);

    //print the time in seconds
    cout << "ALGORITME: LOCAL SEARCH" << endl;
    cout << "INPUT: " << filename << endl;
    cout << "OUTPUT: " << endl;
    cout << "\t#S = " << S.size() << endl;
    cout << '\t' << "Temps: " << temps.count() / 1000000.0 << "s" << endl;
}