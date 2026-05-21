#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "FCFS.h"
#include "SCAN.h"
#include "CSCAN.h"

const int MAX_CYLINDER = 4999;
const int NUM_REQUESTS = 1000;

void writeJSArray(std::ofstream &file, const std::string &name, const std::vector<int> &values)
{
    file << "const " << name << " = [\n";
    for (int i = 0; i < (int)values.size(); i++)
    {
        file << "    " << values[i];
        if (i < (int)values.size() - 1)
            file << ",";
        file << "\n";
    }
    file << "];\n\n";
}

int main(int argc, char *argv[])
{
    // leer l aposición inicial del cabezal desde la línea de comandos
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <initial_head_position>\n";
        std::cerr << "Example: " << argv[0] << " 2500\n";
        return 1;
    }

    int initialHead = std::atoi(argv[1]);

    if (initialHead < 0 || initialHead > MAX_CYLINDER)
    {
        std::cerr << "Error: initial head must be between 0 and " << MAX_CYLINDER << "\n";
        return 1;
    }

    // 1000 requests de cilindros aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> requests;
    requests.reserve(NUM_REQUESTS);
    for (int i = 0; i < NUM_REQUESTS; i++)
    {
        requests.push_back(std::rand() % (MAX_CYLINDER + 1));
    }

    // correr cada algoritmo
    FCFS fcfs(initialHead);
    SCAN scan(initialHead, MAX_CYLINDER);
    CSCAN cscan(initialHead, MAX_CYLINDER);

    std::vector<int> pathFCFS = fcfs.getPath(requests);
    std::vector<int> pathSCAN = scan.getPath(requests);
    std::vector<int> pathCSCAN = cscan.getPath(requests);

    int movFCFS = fcfs.getTotalMovement(requests);
    int movSCAN = scan.getTotalMovement(requests);
    int movCSCAN = cscan.getTotalMovement(requests);

    // Print summary to console
    std::cout << "=== Disk Scheduling: Resultados ===\n";
    std::cout << "Posicion Inicial del Cabezal : " << initialHead << "\n";
    std::cout << "Numero de Solicitudes    : " << NUM_REQUESTS << "\n\n";
    std::cout << "Movimiento total de FCFS  : " << movFCFS << " cylinders\n";
    std::cout << "Movimiento total de SCAN  : " << movSCAN << " cylinders\n";
    std::cout << "Movimiento total de CSCAN : " << movCSCAN << " cylinders\n";
    std::cout << "\ndata.js generado con exito.\n";
    std::cout << "\nNOTA: C-SCAN y SCAN empiezan, por defecto, hacia arriba.\n";

    // Write data.js
    std::ofstream file("data.js");
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo generar el data.js\n";
        return 1;
    }

    file << "const MAX_CYLINDER = " << MAX_CYLINDER << ";\n";
    file << "const INITIAL_HEAD = " << initialHead << ";\n";
    file << "const NUM_REQUESTS = " << NUM_REQUESTS << ";\n\n";

    file << "// Movement totals\n";
    file << "const MOVEMENT_FCFS  = " << movFCFS << ";\n";
    file << "const MOVEMENT_SCAN  = " << movSCAN << ";\n";
    file << "const MOVEMENT_CSCAN = " << movCSCAN << ";\n\n";

    writeJSArray(file, "REQUESTS", requests);
    writeJSArray(file, "PATH_FCFS", pathFCFS);
    writeJSArray(file, "PATH_SCAN", pathSCAN);
    writeJSArray(file, "PATH_CSCAN", pathCSCAN);

    file.close();
    return 0;
}