//Parallel implementation with general critical sections

#include <iostream>
#include "omp.h"

int main(){
    int numeroHilos = 4;
    omp_set_num_threads(numeroHilos);
    double respuesta = 0.0;
    long numeroIteraciones = 1000000000;

    auto beginTimer = std::chrono::high_resolution_clock::now();
    
#pragma omp parallel
    {
        int idHilo = omp_get_thread_num();
        double sumaParcial = 0.0;
        for(long indice = idHilo; indice < numeroIteraciones; indice += numeroHilos){
            if(indice % 2 == 0){
                sumaParcial += 4.0 / (2.0 * indice + 1.0);
            }else{
                sumaParcial -= 4.0 / (2.0 * indice + 1.0);
            }
        }

    #pragma omp critical
        {
          //printf("El hilo %d esta entrando en la seccion critica\n", idHilo);
          respuesta += sumaParcial;
        }
    }

    auto endTimer = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimer - beginTimer);
    unsigned long int duration = static_cast<unsigned long int>(elapsed.count());
    std::cout << " Duration = " << duration*1E-9 << " seconds" << std::endl;
    
    std::cout<<"Respuesta: " << respuesta << std::endl;
    return 0;
}
