//Peter Pacheco
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <chrono>


const int thread_count = 2;

const int m = 10000, n = 10000;
double A[m][n], x[n], y1[n], y2[n];

void generatesMatrices(int m, int n);
void printMatrix(int m, int n);
void printVect(int m);
void serialProduct(int m,int n);

void* Pth_mat_vect(void* rank){
    int my_rank = *((int*)rank);
    std::cout<<"my_rank ="<<my_rank<<"thread_count ="<<thread_count<<std::endl;
    int i,j;
    int local_m = m/thread_count;
    int my_first_row = my_rank*local_m;
    int my_last_row = (my_rank+1)*local_m-1;
    
    for (i = my_first_row; i<= my_last_row; i++){
        y2[i] = 0.;
        for (j = 0; j < n; j++)
            y2[i] += A[i][j]*x[j];
    }
    
    return NULL;
}

int main(){
    generatesMatrices(m,n);
    
    //Parallel mode product *******
    auto beginTimer = std::chrono::high_resolution_clock::now();

    pthread_t threads[thread_count];
    int thread_args[thread_count];
    int i = 0;
    int result_code;
    
    for (i = 0; i < thread_count; i++){
        thread_args[i] = i;
        std::cout<<"thread_args[i]= "<< thread_args[i] << " i= " <<i<<std::endl;

        result_code = pthread_create(&threads[i], NULL, Pth_mat_vect, &thread_args[i]);
        assert(!result_code);
    }
    
    for (i = 0; i < thread_count; i++){
        result_code = pthread_join(threads[i],NULL);
        assert(!result_code);
    }
    
    auto endTimer = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimer - beginTimer);
    unsigned long int duration = static_cast<unsigned long int>(elapsed.count());
    
    std::cout << "Parallel mode product duration = " << duration*1E-9 << " seconds" << std::endl;

    
    //Serial mode product *******
    auto beginTimerSerial = std::chrono::high_resolution_clock::now();

    serialProduct(m,n);
            
    auto endTimerSerial = std::chrono::high_resolution_clock::now();
    auto elapsedSerial = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimerSerial - beginTimerSerial);
    unsigned long int durationSerial = static_cast<unsigned long int>(elapsedSerial.count());
    
    std::cout << "Serial mode product duration = " << durationSerial*1E-9 << " seconds" << std::endl;

    //printMatrix(m,n);
    //printVect(m);
}//end main

void generatesMatrices(int m, int n){
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++){
            A[i][j]=1;
        }
    
    for (int i = 0; i < n; i++)
        x[i]=1.;
    
    for (int j = 0; j < m; j++){
        y1[j] = 0.;
        y2[j] = 0.;
    }
}

void printMatrix(int m, int n){
    //printf("Result: \n");
    for(int i=m-1; i<m; i++){
        for(int j=0; j<n; j++)
            printf("%.2f\t",A[i][j]);
        printf("\n");
    }
}

void printVect(int m){
    //printf("Result: \n");
    int count=0;
    for(int i=0; i<m; i++){
        /*if(y2[i] != 100.){
            
            printf("\n%.2d\t\n\n",count);
            return;
        }*/
            printf("%.2f\t",y2[i]);
        printf("\n");
        count++;
    }
}

void serialProduct(int m,int n){
    for (int i = 0; i < m; i++){
        y1[i] = 0.;
        for (int j = 0; j < n; j++)
            y1[i] += A[i][j]*x[j];
    }
}
