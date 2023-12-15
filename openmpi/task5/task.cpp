#include <bits/stdc++.h>
#include "help.h"
#include <mpi.h>

using namespace std;

void mlt(vector<vector<int>>& a, vector<vector<int>>& b, vector<vector<int>>& c){
    for(int i = 0;i<c.size();i++){
        for(int o = 0;o<c[i].size();o++){
            for(int p = 0;p<c[i].size();p++){
                c[i][o] += a[i][p] * b[p][o];
            }
        }
    }
}

void send_m(int cp, int begin1, int end1, int begin2, int end2, int rank, vector<vector<int>>& v){
    for(int i = begin1; i<end1;i++){
	int mem[end2-begin2];
	int q = 0;
        for(int o = begin2; o<end2;o++){
            if(o<v[i].size() and i<v.size()){
                mem[q] = v[i][o];
		}
            else
                mem[q] = 0;
	    q++;
        }
	cout<<endl;
        MPI_Send(&mem, end1-begin1, MPI_INT, cp, rank, MPI_COMM_WORLD);
    }
}

void receive_m(vector<vector<int>>& v){
    MPI_Status Status;
    for(int i = 0; i<v.size(); i++){
        int mem[v[i].size()]{0};
        MPI_Recv(&mem, v[i].size(), MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status); 
        for(int o = 0; o<v[i].size(); o++){
            v[i][o] = mem[o];
        }
    }
}

void receive_m(int cp, vector<vector<int>>& v){
    MPI_Status Status;
    for(int i = 0; i<v.size(); i++){
        int mem[v[i].size()];
        MPI_Recv(&mem, v[i].size(), MPI_INT, cp, MPI_ANY_TAG, MPI_COMM_WORLD, &Status); 
	for(int o = 0; o<v[i].size(); o++){
            v[i][o] = mem[o];
        }
    }
}

void show_m(vector<vector<int>>& v){
    cout<<endl;
    for(int i = 0;i<v.size();i++){
        for(int o = 0;o<v[i].size();o++){
            cout<<v[i][o]<<" ";
        }
        cout<<endl;
    }
}

//copy v2 to v1
void mcopy(vector<vector<int>>& v1, vector<vector<int>>& v2){
    for(int i = 0;i<v1.size();i++){
        for(int o = 0;o<v1[i].size();o++){
            v1[i][o] = v2[i][o];
        }
    }
}

int main(int argc, char **argv){
    float t1 = MPI_Wtime();
    long long  n = 3;
    MPI_Init(&argc, &argv);
    int rank = -1;
    int cp = -1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &cp);
    cp--;
    int size = ceil(n/floor(sqrt(cp)));
    if(rank == 0){
        vector<vector<int>> matrix1(n);
        vector<vector<int>> matrix2(n);
        for(int i = 0;i<n;i++)
            matrix1[i] = create_vec(n, i+3), matrix2[i] = create_vec(n, i+98);
        cout<<"my rank "<<rank<<endl;
        show_m(matrix1);
        show_m(matrix2);
        int q = 1;
        for(int i = 1; i*size <= n; i++){
            for(int o = 1; o*size <= n; o++){
                send_m(q, (i-1)*size, i*size, (o-1)*size, o*size, 0, matrix1);
                send_m(q, (i-1)*size, i*size, (o-1)*size, o*size, 0, matrix2);
                q++;
            }
        }
        //cout<<"time: "<<MPI_Wtime() - t1<<endl;
    }
    else{
        vector<vector<int>> matrix_a(size);
        vector<vector<int>> matrix_b(size);
        vector<vector<int>> matrix_c(size);
        vector<vector<int>> memory_a(size);
        vector<vector<int>> memory_b(size);
        for(int i = 0;i<size;i++){
            for(int o = 0;o<size;o++){
                matrix_a[i].push_back(0);
                matrix_b[i].push_back(0);
                matrix_c[i].push_back(0);
                memory_a[i].push_back(0);
                memory_b[i].push_back(0);
            }
        }
        receive_m(0, matrix_a);
        receive_m(0, matrix_b);
        mcopy(memory_a,matrix_a);
        mcopy(memory_b,matrix_b);
        if(cp >= 4){
            int net_size = n/size;
            //seg fault 
            int start = 0;
            for(int i = 0;i<net_size;i++){
                // a matrix distribution ?
                start += 1;
                int start_ins = start;
                for(int o = 0;o<net_size-1;o++){
			int u = 0;
                    for(int p = start_ins;u < net_size;){
                        int line = ceil(float(rank)/float(net_size));
                        int q1 = p;
                        int q2 = p+1;
                        if(p > line*net_size)
                            q1 = (line-1)*net_size + (p - line*net_size);
                        if(p+1 > line*net_size)
                            q2 = (line-1)*net_size + ((p+1) - line*net_size);
                        if(line == u+1){
                            if(rank == q1){
                                if(o == 0)
                                   memory_a = matrix_a;
                                cout<<"proc:1 "<<rank<<" my rank i send to "<<q2<<endl;
				cout<<"line "<<line<<" q1,q2 "<<q1<<","<<q2<<" p,u "<<p<<" "<<u<<" net size "<<net_size<<endl;
				cout<<" start_ins "<<start_ins<<" o "<<o<<endl;
                                send_m((q2), 0, matrix_a.size(), 0, matrix_a.size(), rank, memory_a);
                            }
                            if(rank == q2){
                                receive_m(q1,memory_a);
                                cout<<"proc:1 "<<rank<<" my rank i 1 receive form "<<q1<<endl;
                            }
                        }
			if(p % net_size == 0)
				p++;
			else
				p = p+net_size+1;
			
					MPI_Barrier(MPI_COMM_WORLD);
	u+=1;
                    }
                    start_ins++;
			if(start_ins > net_size)
			start_ins %= net_size;
                }
                mlt(memory_a,matrix_b,matrix_c);
                int l = 0, r = n/size;
                // b matrix rotation
                for(int o = 0;o<net_size;o++){
                    if(rank <= r and rank > l){
                        if((rank+net_size)%int(pow(net_size,2)) != 0)
                            cout<<"proc:2 "<<rank<<" my rank i send to "<<(rank+net_size)%int(pow(net_size,2))<<endl,
                            send_m((rank+net_size)%int(pow(net_size,2)),0,matrix_b.size(),0,matrix_b.size(), rank, matrix_b);
                        else
                            cout<<"proc:2 "<<rank<<" my rank i send to "<<rank+net_size<<endl,
                            send_m(rank+net_size,0,matrix_b.size(),0,matrix_b.size(), rank, matrix_b);
                    }
                    if(r+ net_size <= pow(net_size,2)){
                        if(rank <= r+net_size and rank > l+net_size)
                            cout<<"proc:2 "<<rank<<" my rank i receive from"<<rank-net_size<<endl,
                            receive_m(rank-net_size,memory_b);
                    }
                    else{
                        if(rank <= net_size)
                            cout<<"proc:2 "<<rank<<" my rank i receive from "<<net_size*(net_size-1)+rank<<endl,
                            receive_m(net_size*(net_size-1)+rank,memory_b);
                    }
                    l += net_size; r += net_size;
                }

                mcopy(matrix_b,memory_b);
			MPI_Barrier(MPI_COMM_WORLD);

            }

        }
        else
            mlt(memory_a,matrix_b,matrix_c);
        show_m(matrix_c);
    }
    MPI_Finalize();
}
