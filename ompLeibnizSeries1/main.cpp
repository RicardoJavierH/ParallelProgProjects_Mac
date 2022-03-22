#include <iostream>
#include "omp.h"
#include <chrono>

int main(){
    
    double respuestaSerial = 0.0;
    long numeroIteraciones = 1000000000;
    
    //******* Serial mode
    auto beginTimerSerial = std::chrono::high_resolution_clock::now();

    for(long indice = 0; indice < numeroIteraciones; indice++){
        if(indice % 2 == 0){
            respuestaSerial += 4.0 / (2.0 * indice + 1.0);
        }else{
            respuestaSerial -= 4.0 / (2.0 * indice + 1.0);
        }
    }
    
    auto endTimerSerial = std::chrono::high_resolution_clock::now();
    auto elapsedSerial = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimerSerial - beginTimerSerial);
    unsigned long int durationSerial = static_cast<unsigned long int>(elapsedSerial.count());
    std::cout << " Serial mode: \n"<< "duration: " << durationSerial*1E-9 << " seconds" << std::endl;
    printf("La respuesta es: %.8f\n\n", respuestaSerial);
    
    //Otimized serial mode **********
    double respuestaSerialOpt = 0.0;
    bool esIndicePar = true;
    
    auto beginTimerSerialOpt = std::chrono::high_resolution_clock::now();

    for(long indice = 0; indice <= numeroIteraciones; indice++){
        if(esIndicePar == true){
          respuestaSerialOpt += 4.0 / (2.0 * indice + 1.0);
        }else{
          respuestaSerialOpt -= 4.0 / (2.0 * indice + 1.0);
        }
        esIndicePar = !esIndicePar;
    }
    auto endTimerSerialOpt = std::chrono::high_resolution_clock::now();
    auto elapsedSerialOpt = std::chrono::duration_cast<std::chrono::nanoseconds>(endTimerSerialOpt - beginTimerSerialOpt);
    unsigned long int durationSerialOpt = static_cast<unsigned long int>(elapsedSerialOpt.count());
    std::cout << "Optimized Serial mode: \n"<< "duration: " << durationSerialOpt*1E-9 << " seconds" << std::endl;
    printf("La respuesta es: %.8f\n\n", respuestaSerialOpt);
    
    //******* End serial mode
    
    //****** Pallelized mode ********
    int numeroHilos = 2, idHilo;
    omp_set_num_threads(numeroHilos);
    double respuesta = 0.0, sumasParciales[numeroHilos];
    
    auto beginTimer = std::chrono::high_resolution_clock::now();

    #pragma omp parallel private(idHilo) shared(sumasParciales)
    {
        int idHilo = omp_get_thread_num();
        sumasParciales[idHilo] = 0.0;
        
        for(long indice = 0; indice < numeroIteraciones; indice += numeroHilos){
            if(indice % 2 == 0){
                sumasParciales[idHilo] += 4.0 / (2.0 * indice + 1.0);
            }else{
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
    
    std::cout << " Parallel mode :\n" << "number of threads: " << numeroHilos <<std::endl;
    std::cout << "Duration: " << duration*1E-9 << " seconds" << std::endl;
    printf("La respuesta es: %.8f\n", respuesta);
    
    return 0;
    
}
