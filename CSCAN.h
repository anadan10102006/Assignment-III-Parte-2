#ifndef CSCAN_H
#define CSCAN_H

#include <vector>

using namespace std;

class CSCAN
{
private:
    int initialHead;
    int maxCylinder;

public:
    // Constructor
    CSCAN(int head, int max);

    // Devuelve el recorrido del cabezal
    vector<int> getPath(vector<int> requests);

    // Devuelve el movimiento total
    int getTotalMovement(vector<int> requests);
};

#endif