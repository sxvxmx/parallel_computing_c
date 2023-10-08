#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

int main(){
    auto v = create_vec(1000000,1);
    // print_vec(v);
    int q = -1;
    int w = 313242523;


    double t1 = omp_get_wtime();
    #pragma omp for
    for(int i = 0;i<v.size();i++){
            q = max(q,v[i]);
            w = min(w,v[i]);
    };
    double t2 = omp_get_wtime();
    cout<<endl<<t2-t1;
    cout<<endl<<q << " " << w;
    return 0;
}