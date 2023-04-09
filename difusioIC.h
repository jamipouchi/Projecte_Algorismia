#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <cstdlib>
#include <unistd.h>

using namespace std;

typedef vector<vector<int>> Graph;

int independentCascade(Graph& graph, vector<int>& nodesActivats, int diffusionProbability);