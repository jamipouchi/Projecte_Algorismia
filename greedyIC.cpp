#include "difusioIC.h"
#include <algorithm>

vector<int> greedyFunction(Graph& graph, vector<int>& nodesActivats, vector<int>& nodesNoActivats, int diffusionProbability) {
    vector<int> conjS;
    conjS.push_back(nodesActivats[0]);

    int i = 1;
    int j = 0;
    int nodesReached = 0;

    while (nodesReached < graph.size()) {

        int newNodesReached = independentCascade(graph, conjS, diffusionProbability);
        cout << "newNodesReached = " << newNodesReached << endl;

        if (newNodesReached > nodesReached) nodesReached = newNodesReached;
        else conjS.pop_back();

        if (nodesReached == graph.size()) return conjS;


        if (i < nodesActivats.size()) conjS.push_back(nodesActivats[i++]);
        else conjS.push_back(nodesNoActivats[j++]);
        
    }
    return conjS;
}

int main() {
    int nodes, edges, diffusionProbability, nodeActivat;
    cout << "Introdueix el nombre de nodes" << endl;
    cin >> nodes;
    cout << "Introdueix el nombre de edges" << endl;
    cin >> edges;
    cout << "Introdueix la probabilitat de difusio" << endl;
    cin >> diffusionProbability;
    
    cout << "Introdueix el nombre de nodes activats" << endl;
    int nNodesActivats;
    cin >> nNodesActivats;

    vector<int> nodesActivats;

    vector<int> nodesNoActivats;
    for (int i = 0; i < nodes; ++i) {
        nodesNoActivats.push_back(i);
    }

    cout << "Introdueix els id dels nodes activats" << endl;
    int nBorrats = 0;
    for (int i = 0; i<nNodesActivats; ++i) {
        cin >> nodeActivat;
        nodesActivats.push_back(nodeActivat);
        nodesNoActivats.erase(nodesNoActivats.begin()+nodeActivat-nBorrats);
        ++nBorrats;
    }

    cout << "Tamany de nodesActivats " << nodesActivats.size() << endl;

    Graph graph(nodes);
    int u, v;

    cout << "Introdueix els edges" << endl;
    for (int i = 0; i < edges; ++i) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    sort(nodesActivats.begin(), nodesActivats.end(), [&](int a, int b) { 
        return graph[a].size() > graph[b].size();
    });

    sort(nodesNoActivats.begin(), nodesNoActivats.end(), [&](int a, int b) { 
        return graph[a].size() > graph[b].size();
    });

    for (int i = 0; i<nodesActivats.size(); ++i) {
        cout << "El node " << nodesActivats[i] << " te grau " << graph[nodesActivats[i]].size() << endl;
    }

    for (int i = 0; i<nodesNoActivats.size(); ++i) {
        cout << "El node " << nodesNoActivats[i] << " te grau " << graph[nodesNoActivats[i]].size() << endl;
    }

    vector<int> conjS = greedyFunction(graph, nodesActivats, nodesNoActivats, diffusionProbability);

    cout << "Tamany del conjunt minim es " << conjS.size() << " d'un total de " << nodes << endl;
    
}