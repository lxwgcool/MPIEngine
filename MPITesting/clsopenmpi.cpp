#include "clsopenmpi.h"
#include "mpi.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>

ClsOpenMPI* ClsOpenMPI::m_pOpenMPI = nullptr;
pthread_mutex_t ClsOpenMPI::m_mtt;

ClsOpenMPI::ClsOpenMPI()
{
    pthread_mutex_init(&m_mtt, nullptr);
}

void ClsOpenMPI::MPIForMultiConfigs(int argc, char* argv[])
{
    //Do MPI
    int iRank, iNumProcs, iProcsNameLen;
    char cProcessor_name[MPI_MAX_PROCESSOR_NAME];

//    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &iRank);
    MPI_Comm_size(MPI_COMM_WORLD, &iNumProcs);
    MPI_Get_processor_name(cProcessor_name, &iProcsNameLen);
//    char message[30];

//    if(iRank == 1)
//    {
//           strcpy(message, "Hello,process lxwgcool");
//           MPI_Send(message, 30, MPI_CHAR, 3, 990, MPI_COMM_WORLD);
//    }
//    else if(iRank == 3)
//    {
//           MPI_Recv(message, 30, MPI_CHAR, 1, 990, MPI_COMM_WORLD, &status);
//           //cout << myrank << " Process Received: " << message << endl;
//           printf(" %d received:%s/n", iRank, message);
//           cout << endl;
//    }

    string strCmd = "";
    switch(argc)
    {
        case 3:
            strCmd = MPIRunArg3(iRank, argv[1], argv[2]);
            break;
        case 4:
            strCmd = MPIRunArg4(iRank, argv[1], argv[2], argv[3]);
            break;
        default:
            cout << "Wrong Arugments" << endl;
            break;
    }
    if(strCmd != "")
    {
        cout << strCmd
             << "---" << endl;
        system(strCmd.c_str());
    }

    MPI_Finalize();
}

string ClsOpenMPI::GetArg(string strConfigFile, int iRank)
{
    iRank++;
    if(strConfigFile == "")
        return to_string(iRank);
    else
    {
        string strTempFile = "./___" + to_string(iRank);
        string strCmd = "sed -n \'" + to_string(iRank) + "p\' " + strConfigFile + " > " + strTempFile;
        //cout << strCmd << endl;
        system(strCmd.c_str());

        //Read config.ini File
        ifstream ifs;
        ifs.open(strTempFile.c_str());
        string strLine = "";
        getline(ifs, strLine);
        ifs.close();
        //Remove File
        strCmd = "rm " + strTempFile;
        system(strCmd.c_str());

        return strLine;
    }
}

string ClsOpenMPI::MPIRunArg3(int iRank, string strYourExe, string strConfigFile) // e.g. MPIEngine YourProgram arguments
{
    string strCmd = "";
    if(access(strYourExe.c_str(), 0) !=0)
        cout << "Bad YourExe!" << endl;
    else if(access(strConfigFile.c_str(), 0) !=0)
        cout << "Bad ConfigFile!" << endl;
    else
    {
        string strParameter = GetArg(strConfigFile, iRank);
        if(strParameter == "")
        {}
        else
            strCmd = strYourExe + " " + strParameter;
    }
    return strCmd;
}

string ClsOpenMPI::MPIRunArg4(int iRank, string strBinaryExe, string strYourSourceFile, string strConfigFile) // e.g. MPIEngine python YourProgram.py arguments
{
    string strCmd = "";
    if(access(strYourSourceFile.c_str(), 0) !=0)
        cout << "Bad SourceFile!" << endl;
    else if(access(strConfigFile.c_str(), 0) !=0)
        cout << "Bad ConfigFile!" << endl;
    else
    {
        string strParameter = GetArg(strConfigFile, iRank);
        if(strParameter == "")
        {}
        else
            strCmd = strBinaryExe + " " + strYourSourceFile + " " + strParameter;
    }
    return strCmd;
}
