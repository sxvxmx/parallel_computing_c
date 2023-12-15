#!/bin/sh
#module add mpi/openmpi-local
module add openmpi
mpic++ tt.cpp -o runfile

