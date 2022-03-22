#include <iostream>
#include "omp.h"
#include <chrono>

int main(){
 
    int n=500, i,j,k;
    double A[n][n], B[n][n], C1[n][n], C2[n][n];
    
    for(i=0; i<n; i++)
        for(j=0; j<n; j++){
            A[i][j]=1;
            B[i][j]=1;
            C1[i][j]=0;
            C2[i][j]=0;
        }
    
//Serial mode product *******
    auto beginTimerSerial = std::chrono::high_resolution_clock::now();

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            for(k=0; k<n; k++)
                C1[i][j] += A[i][k]*B[k][j];
            
    auto endTimerSerial = std::chrono::high_resolution_clock::now();
    auto elapsedSerial = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimerSerial - beginTimerSerial);
    unsigned long int durationSerial = static_cast<unsigned long int>(elapsedSerial.count());
    
    std::cout << "Serial mode product duration = " << durationSerial*1E-9 << " seconds" << std::endl;

    
    // Parallel mode product *******
    int nthreads =6;
    omp_set_num_threads(nthreads);
    auto beginTimer = std::chrono::high_resolution_clock::now();
#pragma omp parallel for private(i,j,k) shared(A,B,C2)
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            for(k=0; k<n; k++)
                C2[i][j] += A[i][k]*B[k][j];

 
    auto endTimer = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimer - beginTimer);
    unsigned long int duration = static_cast<unsigned long int>(elapsed.count());
    
    std::cout << "Parallel mode product duration = " << duration*1E-9 << " seconds" << std::endl;
    std::cout << " with nthreads =" << nthreads << std::endl;
    
//    printf("Result: \n");
//    for(int i=0; i<n; i++){
//        for(int j=0; j<n; j++)
//            printf("%.2f\t",C2[i][j]);
//        printf("\n");
//    }
    
return 0;
    
}
