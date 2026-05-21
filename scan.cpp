#include "SCAN.h"
#include <algorithm>
#include <cmath>

using namespace std;

// Constructor
SCAN::SCAN(int head, int max)
{
    initialHead = head;
    maxCylinder = max;
}

// SCAN:
// primero se mueve en una sola dirección hacia arriba, y luego baja.
vector<int> SCAN::getPath(vector<int> requests)
{
    vector<int> path;

    // el recorrido empieza en la posición inicial
    path.push_back(initialHead);

    vector<int> upper;
    vector<int> lower;

    // separar requests mayores y menores al cabezal
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] >= initialHead)
        {
            upper.push_back(requests[i]);
        }
        else
        {
            lower.push_back(requests[i]);
        }
    }

    // ordenar las requests mayores de menor a mayor
    sort(upper.begin(), upper.end());

    // ordenar las menores también de menor a mayor
    sort(lower.begin(), lower.end());

    // primero se atienden las de arriba
    for (int i = 0; i < upper.size(); i++)
    {
        path.push_back(upper[i]);
    }

    // el cabezal llega hasta el extremo del disco antes de bajar
    path.push_back(maxCylinder);

    // luego se baja, atendiendo desde la mayor
    for (int i = lower.size() - 1; i >= 0; i--)
    {
        path.push_back(lower[i]);
    }

    return path;
}

// calcular el movimiento total del cabezal
int SCAN::getTotalMovement(vector<int> requests)
{
    vector<int> path = getPath(requests);

    int totalMovement = 0;

    for (int i = 1; i < path.size(); i++)
    {
        totalMovement += abs(path[i] - path[i - 1]);
    }

    return totalMovement;
}