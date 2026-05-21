#ifndef FCFS_H
#define FCFS_H

#include <vector>

using namespace std;

class FCFS
{
private:
    int initialHead;

public:
    // constructor
    FCFS(int head);

    // devuelve el recorrido completo del cabezal
    vector<int> getPath(vector<int> requests);

    // devuelve el movimiento total del cabezal
    int getTotalMovement(vector<int> requests);
};

#endif