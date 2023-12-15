#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{   

    MPI_Init(&argc, &argv);
    long long  w = 100000000;
    for(int n = 100;n<=w;n*=10){
    float t1 = MPI_Wtime();
    long long q = 100;
    int rank = -1;
    int cp = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    if(rank == 0){
         vector<int> sen(n);
        vector<int> res(n);
        for(int i = 0; i<q; i++){
            MPI_Status Status;
            MPI_Sendrecv(&sen[0], n, MPI_INT, 1, 0, &res[0], n, MPI_INT, 1, 0, MPI_COMM_WORLD, &Status); 
            //for(int i = 0;i<n;i++)
              //  cout<<res[i]<<" ";
            //cout<<endl;
        }
        cout<<MPI_Wtime() - t1<<",";
    }
    if(rank == 1){
        vector<int> sen(n);
        vector<int> res(n);
        for(int i = 0;i<n;i++)
            sen[i] = (7+i)%int(n/3);
        for(int i = 0;i<q;i++){
            MPI_Status Status;
            MPI_Sendrecv(&sen[0], n, MPI_INT, 0, 0, &res[0], n, MPI_INT, 0, 0, MPI_COMM_WORLD, &Status); 
        }
    }
    }
    MPI_Finalize();
}
