#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

#define newline cout<<endl

using namespace std;

int main(){
    // omp_set_num_threads(14);
    omp_set_nested(10);
    int n = 100000000;
    auto v1 = create_vec(n,1);
    auto v2 = create_vec(n,1);
    // print_vec(v1);
    // newline;
    // print_vec(v2);
    int sum = 0;

    double t1 = omp_get_wtime();
    #pragma omp for
    for(int i = 0;i<v1.size();i++){
            sum += v1[i]*v2[i];
    };
    double t2 = omp_get_wtime();
    cout<<endl<<t2-t1;
    cout<<endl<<sum<<endl;
    return 0;
}