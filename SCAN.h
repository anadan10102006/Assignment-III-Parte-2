#ifndef SCAN_H
#define SCAN_H

#include <vector>

using namespace std;

class SCAN
{
private:
    int initialHead;
    int maxCylinder;

public:
    // método constructor
    SCAN(int head, int max);

    // devuelve el recorrido del cabezal
    vector<int> getPath(vector<int> requests);

    // devuelve el movimiento total
    int getTotalMovement(vector<int> requests);
};

#endif