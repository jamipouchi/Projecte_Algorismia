#include "difusioIC.h"

int independentCascade(Graph& graph, vector<int>& nodesActivats, int diffusionProbability) {
    queue<int> nodesPerTractar;
    int nodesTractats;
    srand(time(NULL));

    vector<bool> nodesActivatsBool(graph.size(), false);
    
    for (int i = 0; i < nodesActivats.size(); ++i) {
        nodesPerTractar.push(nodesActivats[i]);
        nodesActivatsBool[nodesActivats[i]] = true;
    }

    while (!nodesPerTractar.empty()) {
        int node = nodesPerTractar.front();
        cout << "Vaig a tractar el node " << node << endl;
        nodesPerTractar.pop();

        for (int i = 0; i < graph[node].size(); ++i) {
            cout << "el node que estic mirant " << graph[node][i] << endl;
            if (nodesActivatsBool[graph[node][i]] == false) {
                bool randBool = (rand() % 100) < diffusionProbability;
                if (randBool == true) {
                    cout << "Em propagare de " << node << " a " << graph[node][i] << endl;
                    nodesPerTractar.push(graph[node][i]);
                    nodesActivatsBool[graph[node][i]] = true;
                }
                else cout << "No em propagare de " << node << " a " << graph[node][i] << endl;
            }
        }
        ++nodesTractats;
    }
    return nodesTractats;
}


/*int main() {
    int nodes, edges, diffusionProbability, nodeActivat;
    cout << "Introdueix el nombre de nodes" << endl;
    cin >> nodes;
    cout << "Introdueix el nombre de edges" << endl;
    cin >> edges;
    cout << "Introdueix la probabilitat de difusio" << endl;
    cin >> diffusionProbability;
    vector<int> nodesActivats;

    cout << "Introdueix el nombre de nodes activats" << endl;
    int nNodesActivats;
    cin >> nNodesActivats;

    cout << "Introdueix els id dels nodes activats" << endl;
    for (int i = 0; i<nNodesActivats; ++i) {
        cin >> nodeActivat;
        nodesActivats.push_back(nodeActivat);
    }

    Graph graph(nodes);
    int u, v;
    
    cout << "Introdueix els edges" << endl;
    for (int i = 0; i < edges; ++i) {
        cin >> u >> v;
        graph[u].push_back(v);  
        graph[v].push_back(u);
    }

    int nodesTractats = independentCascade(graph, nodesActivats, diffusionProbability);
    cout << "Nodes tractats " << nodesTractats << "/" << nodes << endl;
}*/