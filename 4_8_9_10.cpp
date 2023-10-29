#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

int main(){
    int n = 10000;
    for(int k = 0;k<=14; k+=2){
    // omp_set_num_threads(k);
    omp_set_nested(k);
    vector<vector<int>> a(n);
    for(int i = 0;i<n;i++){
        a[i] = create_vec(n,i+1);
        // print_vec(a[i]);
        // cout<<endl;
    }
    int m = -1;
    vector<int> mem(n);
    for(int i = 0;i<n;i++)
        mem[i] = 2513526;
    double t1 = omp_get_wtime();
    #pragma omp parallel shared(a, mem, m)
    {
    #pragma omp for nowait
    for(int i = 0;i<n;i++){
        for(int o = 0;o<n;o++){
            mem[i] = min(mem[i], a[i][o]);
        }
    }
    #pragma omp for
    for(int o = 0;o<n;o++)
    if(m < mem[o]){
        #pragma omp critical
        m = max(m,mem[o]);
    }
    }
    double t2 = omp_get_wtime();
    cout<<t2-t1<<",";
    }
    return 0;
}