#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{   float t1 = MPI_Wtime();
    MPI_Init(&argc, &argv);
    long long  w = 10000000;
    for(int n = 10000;n<=w;n*=10){
    long long q = 100;
    int rank = -1;
    int cp = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    if(rank == 0){
        vector<int> res(n);
        MPI_Status Status;
        for(int i = 0; i<q; i++){
            MPI_Recv(&res[0], n, MPI_INT, 17, MPI_ANY_TAG, MPI_COMM_WORLD, &Status); 
            //for(int i = 0;i<n;i++)
              //  cout<<res[i]<<" ";
            //cout<<endl;
        }
        cout<<MPI_Wtime() - t1<<",";
    }
    if(rank == 17){
        vector<int> s(n);
        for(int i = 0;i<n;i++)
            s[i] = 7;
        for(int i = 0;i<q;i++)
            MPI_Send(&s[0],n,MPI_INT,0,rank,MPI_COMM_WORLD);
    }
    }
    MPI_Finalize();
}
