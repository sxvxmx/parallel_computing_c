#!/bin/sh
#module add mpi/openmpi-local
module add openmpi
mpic++ scalar.cpp -o runfile

