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
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    vector<int> res(cp,0);
    //problem with partitioning size
    long long size = floor(n/(cp));
    vector<int> v1(n);
    vector<int> v2(n);
    vector<int> v1_r(size);
    vector<int> v2_r(size);
    if(rank == 0){
        v1 = create_vec(n,1);
        v2 = create_vec(n,17);
    }
    MPI_Scatter(&v1[0],size,MPI_INT,&v1_r[0],size,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(&v2[0],size,MPI_INT,&v2_r[0],size,MPI_INT,0,MPI_COMM_WORLD);
    if(rank != 0){
        for(int i = 0; (i<size) and (i < n); i++)
                s += v1_r[i] * v2_r[i];
    }
    MPI_Gather(&s,1,MPI_INT,&res[0],1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank == 0){
        MPI_Status Status;
        int q = 0;
        for(int i = 0;i<cp;i++){
            q += res[i];
        }
        cout<<MPI_Wtime() - t1<<","<<endl;
    }
    }
    MPI_Finalize();
}
