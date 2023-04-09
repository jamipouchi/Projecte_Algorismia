#include "lib.h"
#include <time.h>

int independentCascade(Graph& graph, vector<int>& nodesActivats, float diffusionProbability) {
    queue<int> nodesPerTractar;
    int nodesTractats = 0;
    srand(time(NULL));

    vector<bool> nodesActivatsBool(graph.size(), false);
    
    for (int i = 0; i < nodesActivats.size(); ++i) {
        nodesPerTractar.push(nodesActivats[i]);
        nodesActivatsBool[nodesActivats[i]] = true;
    }

    while (!nodesPerTractar.empty()) {
        int node = nodesPerTractar.front();
        //cout << "Vaig a tractar el node " << node << endl;
        nodesPerTractar.pop();

        for (int i = 0; i < graph[node].size(); ++i) {
            if (nodesActivatsBool[graph[node][i]] == false) {
                bool randBool = ((rand() % 100)) < diffusionProbability*100;
                if (randBool == true) {
                    //cout << "Em propagare de " << node << " a " << graph[node][i] << endl;
                    nodesPerTractar.push(graph[node][i]);
                    nodesActivatsBool[graph[node][i]] = true;
                    
                }
                //else cout << "No em propagare de " << node << " a " << graph[node][i] << endl;
            }
        }
        ++nodesTractats;
    }
    return nodesTractats;
}