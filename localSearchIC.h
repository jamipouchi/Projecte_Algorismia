#include "greedyIC.h"

vector<int> localSearchIC(Graph& graph, float diffusionProbability) {
    vector<int>greedyS = greedyFunction(graph, diffusionProbability);
    cout << "greedy solution size -> " << greedyS.size() << endl;    
    vector<int> conjS;
    for (int i = 0; i < graph.size(); ++i) {
        conjS.push_back(i);
    }

    srand(time(NULL));

    int node0;
    int objective = graph.size();
    vector<int> auxiliar = greedyS;
    int i = 0;
    while (auxiliar.size() != 1) {
        
        int randomNumber = (rand()%(auxiliar.size()-1)); 
        node0 = auxiliar[randomNumber];
        if (auxiliar.size() > 1) {

            auxiliar.erase(auxiliar.begin()+randomNumber);

            int eval = independentCascade(graph, auxiliar, diffusionProbability);

            if (eval < objective) {
                auxiliar.insert(auxiliar.begin()+randomNumber, node0);
            }
        }
        ++i;    
    }

    return auxiliar;
}