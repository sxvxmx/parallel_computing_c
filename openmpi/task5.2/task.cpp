#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv){
    long long n = 10000;
    long long w = 8;
    long long e = 1000000;
    MPI_Init(&argc, &argv);//
    for(long long q = 1000;q<=e;q*=10){
    for(long long calc = 3;calc<=w;calc+=1){
    float t1 = MPI_Wtime();
long long loops = 1;
    int rank = -1;
    int cp = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    if(rank == 0){
        int res[n];
        MPI_Status Status;
        for(int p = 0;p<loops;p++){
            for(int i = 0; i<q; i++){
                MPI_Recv(&res, n, MPI_INT, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &Status); 
                //for(int i = 0;i<n;i++)
                //  cout<<res[i]<<" ";
                //cout<<endl;
            }
            sleep(calc);
        }
        cout<<MPI_Wtime() - t1<<",";
    }
    if(rank == 1){
        for(int p = 0;p<loops;p++){
            int s[n];
            for(int i = 0;i<n;i++)
                s[i] = 7;
            for(int i = 0;i<q;i++)
                MPI_Send(&s,n,MPI_INT,0,rank,MPI_COMM_WORLD);
        }
    }
    }
	cout<<endl;
    }
    MPI_Finalize();
}
