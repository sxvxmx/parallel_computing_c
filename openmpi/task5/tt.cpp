#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>

using namespace std;


int main(int argc, char **argv){  
    int w = 100000000;
    MPI_Init(&argc, &argv);
    for(int n = 10;n<=w;n*=10){
    int rank = -1;
    int cp = -1;
    int q = 10;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    if(rank == 0){
        int job = 10;
        float t1 = MPI_Wtime();
        for(int i = 1;i<cp;i++){
            float sen = job/(cp-1);
            for(int p = 0;p<q;p++)
                MPI_Send(&sen,1,MPI_FLOAT,i,rank,MPI_COMM_WORLD);
        }
        MPI_Status Status;
        for(int i = 1; i < cp; i++){
            for(int p = 0;p<q;p++)
                MPI_Recv(&res[i], 1, MPI_FLOAT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &Status); 
        }
        cout<<MPI_Wtime() - t1<<","<<endl;
    }
    else{
        float s = 0;
        MPI_Status Status;
        for(int p = 0;p<q;p++)
            MPI_Recv(&s, 1, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &Status); 
        sleep(s);
        for(int p = 0;p<q;p++)
            MPI_Send(&s,1,MPI_FLOAT,0,rank,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}