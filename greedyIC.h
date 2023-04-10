#include "difusioIC.h"
#include <algorithm>

vector<int> greedyFunction(Graph& graph, float diffusionProbability) {
    vector<int> nodes;
    for (int i = 0; i < graph.size(); ++i) {
        nodes.push_back(i);
    }

    sort(nodes.begin(), nodes.end(), [&](int a, int b) { 
        return graph[a].size() > graph[b].size();
    });
    
    vector<int> conjS;
    conjS.push_back(nodes[0]);

    int i = 1;
    int nodesReached = 0;

    while (nodesReached < graph.size() && i != nodes.size()) {

        int newNodesReached = independentCascade(graph, conjS, diffusionProbability);
        //cout << "newNodesReached = " << newNodesReached << endl;

        if (newNodesReached > nodesReached) nodesReached = newNodesReached;

        //cout << "i: " << i << endl;
        if (newNodesReached == graph.size()) return conjS;

        conjS.push_back(nodes[i++]);
        
    }
    return conjS;
}

vector<int> random_greedy_inverse(Graph& graph, float diffusionProbability)
{

    vector<int> S;
    for (int vertex = 0; vertex < graph.size(); vertex++)
    {
        if (graph[vertex].size() > 1)
            S.push_back(vertex);
    }

    random_shuffle(S.begin(), S.end());

    vector<int> S2;
    for (int i = 0; i < S.size(); i++)
    {
        if (i % 5 != 0) {
            S2.push_back(S[i]);
        }
    }

    int total_active = independentCascade(graph, S2, diffusionProbability);
    if (total_active < graph.size())
    {
        cout << "problema, nomes hem activat: " << total_active << " de " << graph.size() << endl;
    }
    return S2;
}