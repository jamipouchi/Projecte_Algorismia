#include "greedyLT.h"
#include <cmath>

vector<int> localSearch(Graph g, float r)
{
    // initial set
    vector<int> S = greedy_until(g, r, 1.0);
    cout << "greedy finished" << endl;


    //parametres simmulated annealing
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

        vector<int> S_new = S;

        //SHA DE FER BE AIXO


        //sha de calclar una aproximacio de la solucio que sigui valida
        //el que hi ha no esta be
        /* EL QUE HI HAVIA ABANS
        if (find(S.begin(), S.end(), vertex) != S.end()) {
            vertex_found = vertex;
            S.erase(find(S.begin(), S.end(), vertex));
        } else {
            vertex_found = -1;
            S.push_back(vertex);
        }*/

        do {
            //chanche S_new

        } while ( LT(g, S_new, r) != n );

        int delta = (S_new.size() - S.size());;
        float p = exp(delta / T);
        

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
    }
    cout << "T: " << T << endl;
    cout << "iter: " << iter << endl;
    return S;
}