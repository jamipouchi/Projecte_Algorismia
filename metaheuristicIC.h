#include "greedyIC.h"
#include <list>


vector<int> getRandomNeighbor(vector<int> bestCandidate, vector<int>& nodesVisitats) {
    vector<int> auxiliar = bestCandidate;
    int randomNumber = (rand()%(nodesVisitats.size()-1)); 
    int node0 = nodesVisitats[randomNumber];


    vector<int>::iterator findIterV = find(nodesVisitats.begin(), nodesVisitats.end(), node0);
    if (auxiliar.size() > 1 && findIterV != nodesVisitats.end()) {
        auxiliar.erase(auxiliar.begin()+randomNumber);
        nodesVisitats.erase(findIterV);
    }
    return auxiliar;
}

vector<int> tabuSearch(Graph& graph, float diffusionProbability) {
    vector<int> conjS = greedyFunction(graph, diffusionProbability);
    cout << "tamany de la solucio en greedy " << conjS.size() << endl;
 
    vector<int> bestCandidate = conjS;
    list<vector<int>> tabuList;
    tabuList.push_back(bestCandidate);
    int maxTabuSize = 20;
    srand(time(NULL));
    vector<int> nodesVisitats = bestCandidate;

    int i = 0;
    while (bestCandidate.size() > 1) {
        vector<int> nouCandidate = getRandomNeighbor(bestCandidate, nodesVisitats);

        if(nodesVisitats.empty()) {
            return bestCandidate;
        }

        list<vector<int>>::iterator findIter = find(tabuList.begin(), tabuList.end(), nouCandidate);
        if (findIter == tabuList.end()) {

            int conjSCandidateSolution = independentCascade(graph, nouCandidate, diffusionProbability);

            if (conjSCandidateSolution == graph.size()) {

                /*cout << "La solucio es valida" << endl;
                cout << "El tamany del conjunt solucio en nouCandidat es: " << nouCandidate.size() << endl;
                cout << "El tamany del conjunt solucio en bestCandidate es: " << bestCandidate.size() << endl;*/

                if (nouCandidate.size() < bestCandidate.size()) {
                    bestCandidate = nouCandidate;

                    nodesVisitats = bestCandidate;

                    tabuList.push_back(bestCandidate);
                    if (tabuList.size() > maxTabuSize) {
                        tabuList.pop_front();
                    }
                }
            }
        }       
        ++i;
    }
    return bestCandidate;

}

