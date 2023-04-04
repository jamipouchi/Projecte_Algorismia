#include "greedyLT.h"
#include <cmath>

vector<int> localSearch(Graph g, float r)
{
    // initial set
    vector<int> S = greedy_until(g, r, 1.0);
    cout << "greedy finished" << endl;

    int old_size = S.size();

    // simmulated annealing
    int n = g.size();
    int max_iter = 100000;
    int iter = 0;
    float T = 1.0;
    float T_min = 0.00001;
    float alpha = 0.99;

    while (T > T_min && iter < max_iter)
    {

        int vertex = rand() % n;
        int vertex_found;

        if (find(S.begin(), S.end(), vertex) != S.end())
        {
            // remove vertex
            vertex_found = vertex;
            S.erase(find(S.begin(), S.end(), vertex));
        }
        else
        {
            // add vertex
            vertex_found = -1;
            S.push_back(vertex);
        }

        int new_size = LT(g, S, r);
        cout << new_size << endl;
        if (new_size == n)
        {
            cout << "completat" << endl;
            return S;
        }
        int delta = 10 * (new_size - old_size);
        float p = exp(delta / T);
        // p is big when delta tends to 0 // likely to accept
        // p is small when delta tens to negative infinity // unlikely to accept
        if (delta < 0 && (rand() / (float)RAND_MAX) < p)
        {
            cout << "rebutjat with probability: " << p << ' ';
            // rebutjem
            if (vertex_found == -1)
            {
                S.pop_back();
            }
            else
            {
                S.push_back(vertex_found);
            }
        }
        else
        {
            cout << "acceptat with probability: " << p << ' ';
        }
        T *= alpha;
        iter++;
        old_size = new_size;
    }
    cout << "T: " << T << endl;
    cout << "iter: " << iter << endl;
    return S;
}

int main(int argc, char const *argv[])
{
    string filename = argv[1];
    float r = 0.5;
    Graph graph = read_graph(filename);
    cout << "read" << endl;
}
