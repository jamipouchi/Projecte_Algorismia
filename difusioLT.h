#include <iostream>
#include <vector>
#include <set>
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

int LT(Graph &graph, vector<int> &S, float r)
{
    int n = graph.size();
    vector<bool> active(n, false);
    int total_active = 0;
    set<int> influencable;
    for (int vertex : S)
    {
        active[vertex] = true;
        total_active++;
    }
    for (int vertex : S)
    {
        for (int neighbor : graph[vertex])
        {
            if (!active[neighbor])
            {
                influencable.insert(neighbor);
            }
        }
    }

    bool at_least_one_activated = true;

    while (at_least_one_activated && influencable.size() > 0)
    {
        at_least_one_activated = false;
        vector<int> to_activate;

        for (int vertex : influencable)
        {
            int active_neighbors = 0;
            for (int neighbor : graph[vertex])
            {
                if (active[neighbor])
                {
                    active_neighbors++;
                }
            }
            if (float(active_neighbors) >= r * float(graph[vertex].size()))
            {
                to_activate.push_back(vertex);
            }
        }
        if (to_activate.size() > 0)
        {
            at_least_one_activated = true;
            for (int vertex : to_activate)
            {
                active[vertex] = true;
                total_active++;
                influencable.erase(vertex);

                for (int neighbor : graph[vertex])
                {
                    if (!active[neighbor])
                    {
                        influencable.insert(neighbor);
                    }
                }
            }
        }
    }

    return total_active;
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