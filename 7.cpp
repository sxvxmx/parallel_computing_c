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
            print_vec(vec);
            cout<<endl;
        }
    }
    return v;
}

int reduc(vector<int> v1, vector<int> v2){
    int m = 0, sum = 0;
    #pragma omp parallel private(m) reduction(+:sum)
    {
        #pragma omp for
        for(int i = 0;i<v1.size();i++){
            m = v1[i] * v2[i];
        sum += m;
        }
    }
    return sum;
}

int main(){
    int s = 0;
    vector<vector<int>> v;
    double t1 = omp_get_wtime();
    #pragma omp parallel reduction(+:s)
    {
    #pragma omp sections
    {
        #pragma omp section
            v = read();
    }
    #pragma omp for
    for(int i = 1;i < v.size();i++){
            s += reduc(v[i],v[i-1]);
        }
    }
    cout<<s<<endl;
    double t2 = omp_get_wtime();
    cout<<t2-t1<<" time"<<endl;
}