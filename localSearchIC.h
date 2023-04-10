#include "greedyIC.h"

vector<int> localSearchIC(Graph& graph, float diffusionProbability) {
    vector<int>greedyS = greedyFunction(graph, diffusionProbability);
    
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
        cout << "greedysize -> " << greedyS.size() << endl;
        int randomNumber = (rand()%(auxiliar.size()-1)); 
        node0 = auxiliar[randomNumber];
        if (auxiliar.size() > 1) {
            cout << "Borro el node " << node0 << " del vector solucio" << endl;

            for (int j = 0; j<auxiliar.size(); ++j) {
                cout << auxiliar[j] << " , ";
            }
            cout << endl;

            auxiliar.erase(auxiliar.begin()+randomNumber);
            cout << "Despres de l'erase el vector auxiliar te size " << auxiliar.size() << endl;

            int eval = independentCascade(graph, auxiliar, diffusionProbability);
            cout << "El nou valor de IC es " << eval << " i l'anterior era " << objective << endl;
            if (eval < objective) {
                auxiliar.insert(auxiliar.begin()+randomNumber, node0);
            }
        }
        ++i;    
    }

    return auxiliar;
}