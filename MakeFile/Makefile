MPIPATH=/apps2/mpi/openmpi/3.1.3/include
MPIPATH_LD=/apps2/mpi/openmpi/3.1.3/lib

CC = g++
CFLAGS = -O3 -Wall -std=c++11 -I$(MPIPATH) -L$(MPIPATH_LD)
LIBS += -lmpi

OBJ = ./obj/

all: MPIEngine

clsopenmpi.o: ../MPITesting/clsopenmpi.cpp ../MPITesting/clsopenmpi.h
	$(CC) $(CFLAGS) -c ../MPITesting/clsopenmpi.cpp

main.o: ../MPITesting/main.cpp 
	$(CC) $(CFLAGS) -c ../MPITesting/main.cpp

MPIEngine: clsopenmpi.o main.o 
	$(CC) $(CFLAGS) -o MPIEngine clsopenmpi.o main.o -lmpi


RM-F := rm -f
.PHONY : all deps objs clean veryclean rebuild info
clean :	
	@$(RM-F) *.o
	@$(RM-F) *.d

veryclean: clean
	@$(RM-F) CheckScafInfo

