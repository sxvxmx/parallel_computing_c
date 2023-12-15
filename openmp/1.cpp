#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

int main(){
    int r = 12;
    // omp_set_num_threads(r);
    long n = 1000000000;
    for(long i =10000;i<=n;i*=10){
    auto v = create_vec(i,1);
    vector<int> thr1(r);
    vector<int> thr2(r);
    for(int i = 0;i<r;i++){
        thr1[i] = 313242523;
        thr2[i] = -1;
    }
    // print_vec(v);
    int q = -1;
    int w = 313242523;


    double t1 = omp_get_wtime();
    // #pragma omp parallel for
    for(int o = 0;o<v.size();o++){
        if(v[o] > thr2[o%r]){
            // #pragma omp critical
            thr2[o%r] = max(thr2[o%r],v[o]);
        }

        if(v[o] < thr1[o%r]){
            // #pragma omp critical
            thr1[o%r] = min(v[o],thr1[o%r]);
        }
    };
    for(int i = 0;i<r;i++){
        q = max(q,thr2[i]);
        w = min(thr1[i],w);
    }
    double t2 = omp_get_wtime();
    cout<<t2-t1<<",";
    // cout<<endl<<q << " " << w;
    }
    return 0;
}