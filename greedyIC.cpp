#include "greedyIC.h"
#include <chrono>

int main(int argc, char const *argv[]) {
    string filename = argv[1];
    cout << "Introdueix la probabilitat de difusio" << endl;
    float diffusionProbability;
    cin >> diffusionProbability;
    Graph graph = read_graph(filename);

    auto ini = chrono::high_resolution_clock::now();
    vector<int> conjS = greedyFunction(graph, diffusionProbability);
    auto fi = chrono::high_resolution_clock::now();
    auto temps = chrono::duration_cast<chrono::microseconds>(fi - ini);

    cout << "ALGORITME: GREEDYIC" << endl;
    cout << "INPUT: " << filename << endl;
    cout << "OUTPUT: " << endl;
    cout << "\t#S = " << conjS.size() << endl;
    cout << '\t' << "Temps: " << temps.count() / 1000000.0 << "s" << endl;
}