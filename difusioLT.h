#include "lib.h"

#include <set>

using namespace std;

typedef vector<vector<int>> Graph;
typedef vector<int> Conjunt;

int LT(Graph &graph, vector<int> &S, float r)
{
    int n = graph.size();
    vector<bool> active(n, false);
    int total_active = 0;
    set<int> influenciable;
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
                influenciable.insert(neighbor);
            }
        }
    }

    bool at_least_one_activated = true;

    while (at_least_one_activated && influenciable.size() > 0)
    {
        at_least_one_activated = false;
        vector<int> to_activate;

        for (int vertex : influenciable)
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
                influenciable.erase(vertex);

                for (int neighbor : graph[vertex])
                {
                    if (!active[neighbor])
                    {
                        influenciable.insert(neighbor);
                    }
                }
            }
        }
    }

    return total_active;
}

