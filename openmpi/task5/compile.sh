#!/bin/sh
#module add mpi/openmpi-local
module add openmpi
mpic++ task.cpp -o build

