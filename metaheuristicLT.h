#include "greedyLT.h"

Conjunt reproduce(Graph &graph, float r, Conjunt &A, Conjunt &B)
{
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    Conjunt child;
    Conjunt to_consider;
    int a = 0;
    int b = 0;
    int size_diff = abs(int(A.size() - B.size()));
    while (a < A.size() && b < B.size())
    {
        if (A[a] == B[b])
        {
            child.push_back(A[a]);
            a++;
            b++;
        }
        else if (A[a] < B[b])
        {
            to_consider.push_back(A[a]);
            a++;
        }
        else
        {
            to_consider.push_back(B[b]);
            b++;
        }
    }
    while (a < A.size())
    {
        to_consider.push_back(A[a]);
        a++;
    }
    while (b < B.size())
    {
        to_consider.push_back(B[b]);
        b++;
    }
    while (LT(graph, child, r) < graph.size())
    {
        for (int i = 0; i < size_diff / 10; i++)
        {
            int idx = rand() % to_consider.size();
            child.push_back(to_consider[idx]);
            to_consider.erase(to_consider.begin() + idx);
        }
    }
    return child;
}

vector<int> choose_parents(vector<Conjunt> &population)
{
    vector<int> parents;
    for (int selection_step = 0; selection_step < 4; selection_step++)
    {
        vector<int> candidats;
        for (int i = 0; i < 3; i++)
        {
            int candidate = rand() % population.size();
            while (find(parents.begin(), parents.end(), candidate) != parents.end())
            {
                candidate = rand() % population.size();
            }
            candidats.push_back(candidate);
        }
        int best = candidats[0];
        for (int i = 1; i < candidats.size(); i++)
        {
            if (population[candidats[i]].size() < population[best].size())
            {
                best = candidats[i];
            }
        }
        parents.push_back(best);
    }
    return parents;
}

int population_indicator(vector<Conjunt> &population)
{
    int indicator = 0;
    for (int i = 0; i < population.size(); i++)
    {
        indicator += population[i].size();
    }
    return indicator;
}

Conjunt metaheuristic(Graph &graph, float r)
{
    vector<Conjunt> population;
    for (int i = 0; i < 10; i++)
    {
        population.push_back(random_greedy_inverse(graph, r));
    }

    int curr_indicator = population_indicator(population);
    int past_indicator = curr_indicator * 2;

    while (float(past_indicator) / float(curr_indicator) > 1.05)
    {
        cout << "Current indicator: " << curr_indicator << endl;
        vector<int> parents = choose_parents(population);
        vector<Conjunt> childs;
        for (int i = 0; i < parents.size(); i++)
        {
            for (int j = i + 1; j < parents.size(); j++)
            {
                childs.push_back(reproduce(graph, r, population[parents[i]], population[parents[j]]));
            }
        }
        vector<int> family;
        for (int i = 0; i < parents.size() + childs.size(); i++)
        {
            if ( i < parents.size())
                family.push_back(parents[i]);
            else
            //areglar aixo
                family.push_back(i + parents.size());

        }
        sort(family.begin(), family.end(), [&](int a, int b)
             { 
                if (a >= parents.size() && b >= parents.size()) {
                    return childs[a - parents.size()].size() < childs[b - parents.size()].size();
                }
                else if (a >= parents.size()) {
                    return childs[a - parents.size()].size() < population[b].size();
                }
                else if (b >= parents.size()) {
                    return population[a].size() < childs[b - parents.size()].size();
                }
                else {
                    return population[a].size() < population[b].size();
                } });
        vector<Conjunt> next_population(parents.size());
        for (int i = 0; i < population.size(); i++)
        {
            if (family[i] >= parents.size())
            {
                next_population[i] = childs[family[i] - parents.size()];
            }
            else
            {
                next_population[i] = population[family[i]];
            }
        }
        population = next_population;
        past_indicator = curr_indicator;
        curr_indicator = population_indicator(population);
    }
    return population[0];
}