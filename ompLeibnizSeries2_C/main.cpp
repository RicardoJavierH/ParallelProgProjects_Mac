//Parallel implementation with optimized for loops

#include <stdio.h>
#include "omp.h"
#include <iostream>
using namespace std;

int main(){
    int numeroHilos = 2, idHilo;
    omp_set_num_threads(numeroHilos);
    double respuesta = 0.0;
    long numeroIteraciones=1000000000;
    
    auto beginTimer = std::chrono::high_resolution_clock::now();
        
#pragma omp parallel for reduction(+:respuesta)
    {
        for(long indice = 0; indice < numeroIteraciones; indice++){
            if(indice % 2 == 0){
                respuesta += 4.0 / (2.0 * indice + 1.0);
            }
            else{
                respuesta += -4.0 / (2.0 * indice + 1.0);
            }
        }
    }

    auto endTimer = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimer - beginTimer);
    unsigned long int duration = static_cast<unsigned long int>(elapsed.count());
    std::cout << " Duration = " << duration*1E-9 << " seconds" << std::endl;
    printf("La respuesta es: %.8f\n", respuesta);
    
        
    return 0;
}
