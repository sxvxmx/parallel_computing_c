#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{   
    long long  w = 100000000;
    MPI_Init(&argc, &argv);
    for(int n = w;n<=w;n*=10){
        float t1 = MPI_Wtime();
    int rank = -1;
    int cp = -1;
    int s = 0;
    vector<int> v1(n);
    vector<int> v2(n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    long long res = 0;
    //data init
    if(rank == 0){
        v1 = create_vec(n,1);
        v2 = create_vec(n,17);
    }
    MPI_Bcast(&v1[0],n,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&v2[0],n,MPI_INT,0,MPI_COMM_WORLD);
    if(rank != 0){
        s = 0;
        if((floor(n/(cp-1))+1)*(rank-1) < n){
            for(int i = (floor(n/(cp-1))+1)*(rank-1); (i<(floor(n/(cp-1))+1)*(rank)) and (i < n); i++)
                s += v1[i] * v2[i];
        }
    }
    MPI_Allreduce(&s,&res,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    if(rank == 0){
        cout<<MPI_Wtime() - t1<<","<<endl;
    }
    }
    MPI_Finalize();
}
