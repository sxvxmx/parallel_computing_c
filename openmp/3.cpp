#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

double func(double x){
    return x*x - 30 * x;
}

template<typename Func>
double integrity(Func f, double a, double b, long long n){
    double sum = 0;
    double h = (b-a)/n;
    double m;
    #pragma omp parallel 
    { 
        #pragma omp for private(m) reduction(+:sum)
        for(int i = 0; i<=n; i++){
            m = f(a + i*h);
            sum = sum + m;
        };
    }
    return h*sum;
}

int main(){
    for(int k = 0;k<=14; k+=2){
    omp_set_num_threads(k);
    long long n = 1000000000;
    for(long long i = n;i<=n;i*=10){
    double t1 = omp_get_wtime();
    double sum = integrity(func,0,1000000000,i);
    double t2 = omp_get_wtime();
    cout<<t2-t1<<",";
    }
    }
}