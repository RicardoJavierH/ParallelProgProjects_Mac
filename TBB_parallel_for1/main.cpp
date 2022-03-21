#include <iostream>
#include <vector>
#include <tbb/tbb.h>

void f(int v){
    std::cout<< v <<std::endl;
}

void sidebar_pfor_lambda(int N, const std::vector<int> &a){
    tbb::parallel_for(0,N,1,[&a](int j){
            f(a[j]);
        }
    );
}

int main(){
    int n=10;
    std::vector<int> vect(n);
  //std::cout << vect.size() << std::endl;
    for(int i = 0; i < vect.size(); i++){
        vect[i]=i;
        //std::cout << vect[i] << ", ";
    }
    std::cout << std::endl;
    
    sidebar_pfor_lambda(n,vect);

    
return 0;
}

