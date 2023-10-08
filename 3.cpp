#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

double func(double x){
    return x*x;
}

template<typename Func>
double integrity(Func f, double a, double b, int n){
    double sum = 0;
    double h = (b-a)/n;
    // #pragma omp for
    for(int i = 0; i<=n; i++){
        sum += f(a + i*h);
    };
    return h*sum;
}

int main(){
    double t1 = omp_get_wtime();
    double sum = integrity(func,0,100000,10000000);
    double t2 = omp_get_wtime();
    cout<<t2-t1;
    cout<<endl<<sum<<endl;
    return 0;
}