#!/bin/sh
#module add mpi/openmpi-local
module add openmpi
mpic++ minvec.cpp -o runfile

