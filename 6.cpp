#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

int atom(vector<int> v1, vector<int> v2){
    int m = 0,sum = 0;
    #pragma omp parallel private(m)
    {
        #pragma omp for
        for(int i = 0;i<v1.size();i++){
            m = v1[i] * v2[i];
        #pragma omp atomic
            sum += m;
        }
    }
    return sum;
}

int crit(vector<int> v1, vector<int> v2){
    int m = 0,sum = 0;
    #pragma omp parallel private(m)
    {
        #pragma omp for
        for(int i = 0;i<v1.size();i++){
            m = v1[i] * v2[i];
        #pragma omp critical
        sum += m;
        }
    }
    return sum;
}

int lock(vector<int> v1, vector<int> v2){
    int m = 0,sum = 0;
    omp_lock_t lock;
    omp_init_lock(&lock);
    #pragma omp parallel private(m)
    {
        #pragma omp for
        for(int i = 0;i<v1.size();i++){
            m = v1[i] * v2[i];
        omp_set_lock (&lock);
        sum += m;
        omp_unset_lock (&lock);
        }
    }
    return sum;
}

int reduc(vector<int> v1, vector<int> v2){
    int m = 0,sum = 0;
    #pragma omp parallel 
    {
        #pragma omp for private(m) reduction(+:sum)
        for(int i = 0;i<v1.size();i++){
            m = v1[i] * v2[i];
            sum = sum + m;
        }
    }
    return sum;
}

int main(){
    int n = 100000000;
    auto v1 = create_vec(n,1);
    auto v2 = create_vec(n,5);

    double t1 = omp_get_wtime();
    atom(v1,v2);
    double t2 = omp_get_wtime();
    cout<<t2-t1<<" time"<<endl;

    t1 = omp_get_wtime();
    crit(v1,v2);
    t2 = omp_get_wtime();
    cout<<t2-t1<<" time"<<endl;

    // t1 = omp_get_wtime();
    // lock(v1,v2);
    // t2 = omp_get_wtime();
    // cout<<t2-t1<<" time"<<endl;

    t1 = omp_get_wtime();
    reduc(v1,v2);
    t2 = omp_get_wtime();
    cout<<t2-t1<<" time"<<endl;
}