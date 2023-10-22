#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

int main(){
    omp_set_num_threads(4);
    long n = 100000000;
    for(long i =10;i<=n;i*=10){
    auto v = create_vec(i,1);
    // print_vec(v);
    int q = -1;
    int w = 313242523;


    double t1 = omp_get_wtime();
    #pragma omp parallel for
    for(int o = 0;o<v.size();o++){
        #pragma omp critical
            q = max(q, v[o]);
        #pragma omp critical
            w = min(w, v[o]);
    };
    double t2 = omp_get_wtime();
    cout<<t2-t1<<",";
    // cout<<endl<<q << " " << w;
    }
    return 0;
}