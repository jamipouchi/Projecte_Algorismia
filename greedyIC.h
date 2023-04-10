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