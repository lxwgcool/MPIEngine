# MPIEngine
Boost any exe with multiple processes by using different argument for each process

# How to use it
Example 1: MPIEngine myprogram.exe config.ini
Example 2: MPIEngine python mySourceCode.py config.ini

# SBATCH Script Example:
#!/bin/bash
#SBATCH -A hpc-admin
#SBATCH -p general
#SBATCH -N 2
#SBATCH --ntasks-per-node=4

module purge
module load gcc/5.4.0-alt zlib/1.2.11 java/1.8.0_162 mpi/openmpi/3.1.3 python/2.7.6 mpiengine/1.0

mpirun -n 8 MPIEngine python ./test.py ./config.ini
