#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

int tri_mat(vector<vector<int>> a){
    int n = a.size();
    int m = -1;
    vector<int> mem(n);
    for(int i = 0;i<n;i++)
        mem[i] = 2513526;
    double t1 = omp_get_wtime();
    #pragma omp parallel shared(mem, m)
    {
    //runtime runtime
    #pragma omp for nowait schedule(runtime)
    for(int i = 0;i<n;i++){
        for(int o = 0;o<n-i;o++){
            mem[i] = min(mem[i], a[i][o]);
        }
    }
    #pragma omp for
    for(int o = 0;o<n;o++)
        #pragma omp critical
        m = max(m,mem[o]);
    }
    return m;
}

int rib_mat(vector<vector<int>> a, int size = 1){
    int n = a.size();
    int m = -1;
    vector<int> mem(n);
    for(int i = 0;i<n;i++)
        mem[i] = 2513526;
    double t1 = omp_get_wtime();
    #pragma omp parallel shared(a, mem, m)
    {
    #pragma omp for nowait schedule(runtime)
    for(int i = 0;i<n;i++){
        for(int o = max(0,i-size); o<min(n,i+size);o++){
            mem[i] = min(mem[i], a[i][o]);
        }
    }
    #pragma omp for
    for(int o = 0;o<n;o++)
        #pragma omp critical
        m = max(m,mem[o]);
    }
    return m;
}


int main(){
    int n = 10000;
    vector<vector<int>> a(n);
    for(int i = 0;i<n;i++){
        a[i] = create_vec(n,i+1);
        // print_vec(a[i]);
        // cout<<endl;
    }
    double t1 = omp_get_wtime();
    cout<<tri_mat(a)<<endl;
    double t2 = omp_get_wtime();
    cout<<t2-t1<<" time"<<endl;

    t1 = omp_get_wtime();
    cout<<rib_mat(a)<<endl;
    t2 = omp_get_wtime();
    cout<<t2-t1<<" time"<<endl;
}