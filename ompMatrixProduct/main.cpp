#include <iostream>
#include "omp.h"
#include <chrono>
#include <cmath>
const int n = 1000;
double A[n][n], B[n][n], C1[n][n], C2[n][n];

void generatesMatrices(int m);
void printMatrix(int m);
void serialProduct(int m);
void parallelProduct(int m);
 

int main(){

    //Serial mode product *******
    auto beginTimerSerial = std::chrono::high_resolution_clock::now();

    serialProduct(n);
            
    auto endTimerSerial = std::chrono::high_resolution_clock::now();
    auto elapsedSerial = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimerSerial - beginTimerSerial);
    unsigned long int durationSerial = static_cast<unsigned long int>(elapsedSerial.count());
    
    std::cout << "Serial mode product duration = " << durationSerial*1E-9 << " seconds" << std::endl;

    
    // Parallel mode product *******
    
    for(int nthreads =1; nthreads <=6; nthreads++){
        omp_set_num_threads(nthreads);
        
        auto beginTimer = std::chrono::high_resolution_clock::now();

        parallelProduct(n);
        
        auto endTimer = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimer - beginTimer);
        unsigned long int duration = static_cast<unsigned long int>(elapsed.count());
        
        std::cout << "Parallel mode product duration = " << duration*1E-9 << " seconds" << " with nthreads = " << nthreads << std::endl;
    }

    
return 0;
    
}

void serialProduct(int m){
    for(int i=0; i<m; i++)
        for(int j=0; j<m; j++)
            for(int k=0; k<m; k++)
                C1[i][j] += A[i][k]*B[k][j];
}

void parallelProduct(int m){
    int i,j,k;
//#pragma omp parallel for schedule(static,50) collapse(2) private(i,j,k) shared(A,B,C2) ////Static Scheduler
//#pragma omp parallel for schedule(dynamic,50) collapse(2) private(i,j,k) shared(A,B,C2) ////Dynamic Scheduler
#pragma omp parallel for private(i,j,k) shared(A,B,C2)
    for(i=0; i<m; i++)
        for(j=0; j<m; j++)
            for(k=0; k<m; k++)
                C2[i][j] += A[i][k]*B[k][j];
}


void generatesMatrices(int m){
    for(int i=0; i<m; i++)
        for(int j=0; j<m; j++){
            A[i][j]=1;
            B[i][j]=1;
            C1[i][j]=0;
            C2[i][j]=0;
        }
}

void printMatrix(int m){
    //printf("Result: \n");
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++)
            printf("%.2f\t",C1[i][j]);
        printf("\n");
    }
}
