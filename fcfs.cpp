#include "FCFS.h"
#include <cmath>

using namespace std;

// método constructor
FCFS::FCFS(int head)
{
    initialHead = head;
}

// las solicitudes son atendidas por orden de llegada.
vector<int> FCFS::getPath(vector<int> requests)
{
    vector<int> path;

    // el recorrido empieza en la posición inicial
    path.push_back(initialHead);

    // se agregan las requests en el orden original
    for (int i = 0; i < requests.size(); i++)
    {
        path.push_back(requests[i]);
    }

    return path;
}

// calcula cuánto se movió el cabezal en total
int FCFS::getTotalMovement(vector<int> requests)
{
    int totalMovement = 0;

    int current = initialHead;

    for (int i = 0; i < requests.size(); i++)
    {
        totalMovement += abs(requests[i] - current);

        current = requests[i];
    }

    return totalMovement;
}
