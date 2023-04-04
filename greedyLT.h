#include "difusioLT.h"
#include <algorithm>

vector<int> greedy_until(Graph &graph, float r, float completion_ratio)
{
    vector<int> vertexs(graph.size());
    vector<int> degrees(graph.size());
    for (int i = 0; i < graph.size(); i++)
    {
        vertexs[i] = i;
        // degrees[i] = graph[i].size();
    }
    /* for (int i = 0; i < vertexs.size(); i++)
    {
        int max_degree = -1;
        int max_idx = -1;
        for (int vertex = 0; vertex < degrees.size(); vertex++)
        {
            if (degrees[vertex] > max_degree)
            {
                max_degree = degrees[vertex];
                max_idx = vertex;
            }
        }
        degrees[i] = -1;
        for (int neighbor : graph[vertexs[i]])
        {
            degrees[neighbor] -= 1;
        }
    } */

    // int perfect_neighbors = int(r * float(graph.size()));

    sort(vertexs.begin(), vertexs.end(), [&](int a, int b)
         //{ return abs(int(graph[a].size() - perfect_neighbors)) < abs(int(graph[b].size() - perfect_neighbors)); });
         { return graph[a].size() > graph[b].size(); });

    vector<int> S;
    S.push_back(vertexs[0]);
    int num_nodes = 1;
    int reached = 0;
    while (reached < graph.size() * completion_ratio)
    {
        int next_reached = LT(graph, S, r);
        if (next_reached > reached)
            reached = next_reached;
        else
            S.pop_back();
        S.push_back(vertexs[num_nodes++]);
        if (reached == graph.size())
        {
            return S;
        }
    }
    return S;
}

vector<int> greedy(Graph &graph, float r)
{
    return greedy_until(graph, r, 1.0);
}

vector<int> random_greedy_inverse(Graph &graph, float r)
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
    int total_active = LT(graph, S2, r);
    if (total_active < graph.size())
    {
        cout << "problema, nomes hem activat: " << total_active << " de " << graph.size() <<endl;
    }
    return S2;
}