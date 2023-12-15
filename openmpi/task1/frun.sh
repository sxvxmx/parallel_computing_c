module add openmpi
mpic++ minvec.cpp -o runfile

sbatch -n 8 mpirun runfile
