#include "greedyLT.h"
#include <cmath>

vector<int> localSearch(Graph g, float r)
{
    // initial set
    vector<int> S = random_greedy_inverse(g, r);
    //vector<int> S = greedy_until(g, r, 1.0);
    cout << "greedy finished" << endl;


    //parametres simmulated annealing
    float ratio_change = 0.01;
    int n = g.size();
    int max_iter = 100000;
    int iter = 0;
    float T = 1.0;
    float T_min = 0;
    float alpha = 0.99;

    while (T > T_min && iter < max_iter)
    {
        vector<int> S_new;
        int size = S.size();

        do {
            S_new = S;
 
            int to_change = rand () % int(size * ratio_change);
            for (int i = 0; i < to_change; ++i)
            {
                int x = rand () % n;
                //search the index of x in S
                auto it = find(S_new.begin(), S_new.end(), x);
                if (it != S_new.end()) S_new.erase(it);
                else S_new.push_back(x);
            }
        } while ( LT(g, S_new, r) != n );

        //MIRAT A PARTIR DE AQUI
        int delta = (S_new.size() - S.size());;
        float p = exp(delta / T);

        cout << S.size() << "->" << S_new.size() << '\t' << delta << '\t' << p << '\t' << T << endl;

        if (delta > 0 && (rand() / (float)RAND_MAX) < p)
        {
            S = S_new;
            T *= alpha;       
        }
        //MIRAT FINS AQUI
        
        iter++;  
    }
    return S;
}

