#include "CSCAN.h"
#include <algorithm>
#include <cmath>

using namespace std;

// Constructor
CSCAN::CSCAN(int head, int max)
{
    initialHead = head;
    maxCylinder = max;
}

// Algoritmo C-SCAN:
// siempre avanza hacia arriba.
// Cuando llega al final del disco,
// vuelve al cilindro 0 y continúa.
vector<int> CSCAN::getPath(vector<int> requests)
{
    vector<int> path;

    // El recorrido empieza en la posición inicial
    path.push_back(initialHead);

    vector<int> upper;
    vector<int> lower;

    // Separar requests mayores y menores al cabezal
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

    // Ordenar ambas listas
    sort(upper.begin(), upper.end());
    sort(lower.begin(), lower.end());

    // Atender primero las requests mayores
    for (int i = 0; i < upper.size(); i++)
    {
        path.push_back(upper[i]);
    }

    // El cabezal sigue hasta el final del disco
    path.push_back(maxCylinder);

    // Luego vuelve al inicio
    path.push_back(0);

    // Finalmente atiende las requests menores
    for (int i = 0; i < lower.size(); i++)
    {
        path.push_back(lower[i]);
    }

    return path;
}

// Calcula el movimiento total del cabezal
int CSCAN::getTotalMovement(vector<int> requests)
{
    vector<int> path = getPath(requests);

    int totalMovement = 0;

    for (int i = 1; i < path.size(); i++)
    {
        totalMovement += abs(path[i] - path[i - 1]);
    }

    return totalMovement;
}