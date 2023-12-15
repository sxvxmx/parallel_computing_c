#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>
#include <unistd.h>
#include <time.h>
using namespace std;

int main(int argc, char **argv){  
    int w = 100;
    MPI_Init(&argc, &argv);
    for(int job  = 10;job<=w;job+=20){
    int rank = -1;
    int cp = -1;
    int q = 100;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    if(rank == 0){
        float t1 = MPI_Wtime();
        for(int i = 1;i<cp;i++){
            float sen = float(job)/float((cp-1));
            for(int p = 0;p<q;p++)
                MPI_Send(&sen,1,MPI_FLOAT,i,rank,MPI_COMM_WORLD);
        }
        MPI_Status Status;
	float tt = 0;
        for(int i = 1; i < cp; i++){
            for(int p = 0;p<q;p++)
                MPI_Recv(&tt, 1, MPI_FLOAT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status); 
        }
        cout<<MPI_Wtime() - t1<<","<<endl;
    }
    else{
        float s = 0;
        MPI_Status Status;
        for(int p = 0;p<q;p++)
            MPI_Recv(&s, 1, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
	usleep(int(s*1000000)); 
        for(int p = 0;p<q;p++)
            MPI_Send(&s,1,MPI_FLOAT,0,rank,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}
