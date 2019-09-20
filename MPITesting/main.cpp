#include <iostream>
#include <mpi.h>
#include <string.h>
#include "clsopenmpi.h"

using namespace std;

int main(int argc,char *argv[])
{
    if(argc == 1 ||
       (argc == 2 &&
        (strcmp(argv[1], "--help") == 0 ||
         strcmp(argv[1], "-H") == 0 ||
         strcmp(argv[1], "-h") == 0)
        ))
    {
        cout << "**************************************************" << endl
             << "******************* UConn HPC ********************" << endl
             << "******************* MPIEngine ********************" << endl
             << "**************************************************" << endl
             << "1: Boost any exe with multiple processes by using different argument for each process." << endl
             << "2: Usage: (1) MPIEngine -n <number of cores> your_program" << endl
             << "          (2) Fill the parameters into \"config.ini\". Each line is corresponding to all the arguments of one process." << endl
             << "3: Example: there are three examples, and each of them applies 8 cores to run the program with multiple parameters of each." << endl
             << "     E.g.1: mpirun -n 8 MPIEngine config.ini" << endl
             << "     E.g.2: mpirun -n 8 MPIEngine myprogram.exe config.ini" << endl
             << "     E.g.3: mpirun -n 8 MPIEngine python mySourceCode.py config.ini" << endl;
    }
    else
    {
        ClsOpenMPI::GetInstance()->MPIForMultiConfigs(argc, argv);
    }
}
