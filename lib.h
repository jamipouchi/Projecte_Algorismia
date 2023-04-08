#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

using namespace std;


typedef vector<vector<int>> Graph;
typedef vector<int> Conjunt;

Graph read_graph(string filename)
{
    string prefix = "instances/";
    ifstream file(prefix + filename);
    string ignore;
    int n, m;
    file >> ignore >> ignore >> n >> m;
    Graph graph(n, vector<int>());
    int u, v;
    for (int i = 0; i < m; i++)
    {
        file >> ignore >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }
    file.close();
    return graph;
}

int number_of_connected_components(Graph &graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    int num_components = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            num_components++;
            queue<int> q;
            q.push(i);
            while (!q.empty())
            {
                int vertex = q.front();
                q.pop();
                visited[vertex] = true;
                for (int neighbor : graph[vertex])
                {
                    if (!visited[neighbor])
                    {
                        q.push(neighbor);
                    }
                }
            }
        }
    }
    return num_components;
}