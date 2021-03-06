//Simple parallel implementation

#include "omp.h"
#include <iostream>
using namespace std;

int main(){
    int numeroHilos = 4, idHilo;
    omp_set_num_threads(numeroHilos);
    double respuesta = 0.0, sumasParciales[numeroHilos];
    long numeroIteraciones=1000000000;
    
    auto beginTimer = std::chrono::high_resolution_clock::now();

    #pragma omp parallel private(idHilo) shared(sumasParciales)
    {
        int idHilo = omp_get_thread_num();
        sumasParciales[idHilo] = 0.0;

        for(long indice = idHilo; indice < numeroIteraciones; indice += numeroHilos){
            if(indice % 2 == 0){
                sumasParciales[idHilo] += 4.0 / (2.0 * indice + 1.0);
            }
            else{
                sumasParciales[idHilo] -= 4.0 / (2.0 * indice + 1.0);
            }
        }
    }

    for(int indice = 0; indice < numeroHilos; indice++){
        respuesta += sumasParciales[indice];
    }

    auto endTimer = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimer - beginTimer);
    unsigned long int duration = static_cast<unsigned long int>(elapsed.count());
    
    std::cout << " Duration = " << duration*1E-9 << " seconds" << std::endl;
    printf("Respuesta: %.8f\n", respuesta);
    
        
    return 0;
}
