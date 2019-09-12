#ifndef CLSOPENMPI_H
#define CLSOPENMPI_H

#include<pthread.h>
#include<string>
#include<iostream>
using namespace std;

//use singleton to do this job
class ClsOpenMPI
{
private:
    ClsOpenMPI(); //constructor
    ~ClsOpenMPI(); //deconstructor
    ClsOpenMPI(const ClsOpenMPI&); //copy deconstructor
    ClsOpenMPI& operator = (const ClsOpenMPI&);

public:
    static ClsOpenMPI* GetInstance()
    {
        if(m_pOpenMPI == nullptr)
        {
            pthread_mutex_lock(&m_mtt); //thread safe
            if(m_pOpenMPI == nullptr)
            {
               m_pOpenMPI = new ClsOpenMPI();
            }
            pthread_mutex_unlock(&m_mtt);
        }
        return m_pOpenMPI;
    }

private:
    //release the memory of m_pOpenMPI
    class ClsDeOpenMPI
    {
    public:
        ~ClsDeOpenMPI()
        {
            if(ClsOpenMPI::m_pOpenMPI == nullptr)
            {
                delete ClsOpenMPI::m_pOpenMPI;
                ClsOpenMPI::m_pOpenMPI = nullptr;
            }
        }
    };

private:
    static ClsOpenMPI* m_pOpenMPI;
    static pthread_mutex_t m_mtt;
    static ClsDeOpenMPI m_deOpenMPI;

public:
    void MPIForMultiConfigs(int argc, char* argv[]);
    void WhoAmI()
    {
        cout << "I am MPI Engine" << endl;
    }

private:
    string GetArg(string strConfigFile, int iRank);
    string MPIRunArg3(int iRank, string strYourExe, string strConfigFile); //Contain 3 argument (The first argument is always the name of current program "MPIEngine")
    string MPIRunArg4(int iRank, string strBinaryExe, string strYourSourceFile, string strConfigFile); //Contain 4 argument
};


#endif // CLSOPENMPI_H
