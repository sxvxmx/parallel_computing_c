#include <bits/stdc++.h>
#include <omp.h>
#include "help.h"

using namespace std;

vector<vector<int>> read(){
    ifstream file;
    vector<vector<int>> v;
    file.open("files/vectors.txt");
    for(;file;){
        string s;
        vector<int> vec;
        getline(file,s);
        if(!s.empty()){
            for(int i = 0;i<s.size();i++){
                if(s[i] != ' ')
                    vec.push_back(s[i] - '0');
            }
            v.push_back(vec);
        }
    }
    return v;
}

int reduc(vector<int> v1, vector<int> v2){
    int m = 0, sum = 0;
    // #pragma omp parallel private(m) reduction(+:sum)
    // {
        // #pragma omp for
        for(int i = 0;i<v1.size();i++){
            m = v1[i] * v2[i];
        sum += m;
        }
    //}
    return sum;
}

int main(){
    int s = 0;
    int n = 2000000;
    int q = n-1;
    vector<vector<int>> v(n);
    vector<int> v1(n,0);
    double t1 = omp_get_wtime();
    // #pragma omp parallel
    {
    // #pragma omp sections
    {
        // #pragma omp section
            v = read();

        // #pragma omp section
        {
            while(q > 0){
            // #pragma omp parallel for
            for(int i = 1;i < n;i++){
                    if(v[i].size() == 5 & v[i-1].size() == 5 & v1[i] == 0){
                        // #pragma omp atomic
                        s += reduc(v[i], v[i-1]);
                        // #pragma omp atomic 
                        q--;
                        v1[i] = 1;
                    }
                }
            }
        }
        }
    }
    cout<<s<<endl;
    double t2 = omp_get_wtime();
    cout<<t2-t1<<" time"<<endl;
    return 0;
}