#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>

using namespace std;

int main(int argc, char **argv)
{   
    long long  n = 100000000;
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int ranks_in[int(floor(sqrt(size-1)))];
    for(int i = 1;i<=int(floor(sqrt(size-1)));i++){
        ranks_in[i-1] = i;
    }

    MPI_Group originalGroup, newGroup;
    MPI_Comm_group(MPI_COMM_WORLD, &originalGroup);
    MPI_Group_incl(originalGroup, int(floor(sqrt(size-1))), ranks_in, &newGroup);
    MPI_Comm newComm;
    MPI_Comm_create_group(MPI_COMM_WORLD, newGroup, 1, &newComm);

    int s = 0;
    vector<int> v1(n);
    vector<int> v2(n);
    float t1 = MPI_Wtime();
    long long res = 0;
if(rank > 0 and rank <= int(floor(sqrt(size-1)))){
    if(rank == 1){
        v1 = create_vec(n,1);
        v2 = create_vec(n,17);
    }
    MPI_Bcast(&v1[0],n,MPI_INT,1,newComm);
    MPI_Bcast(&v2[0],n,MPI_INT,1,newComm);
    if(rank != 0){
        s = 777;
    }
    MPI_Reduce(&s,&res,1,MPI_INT,MPI_SUM,1,newComm);
    if(rank == 1){
        cout<<MPI_Wtime() - t1<<endl;
    }
}
// ɫɨɡɞɚɧɢɟ ɞɜɭɯɦɟɪɧɨɣ ɪɟɲɟɬɤɢ 4x4
	MPI_Comm GridComm;
	int dims[2];int periods[2];int reorder = 1;
	dims[0] = dims[1] = 4;
	periods[0] = periods[1] = 1;
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &GridComm); 

    MPI_Finalize();
}
