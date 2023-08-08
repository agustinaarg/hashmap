#include <iostream>

#include "HashMapConcurrente.hpp"
#include "CargarArchivos.hpp"
#include <time.h>
#include <cmath>
#include <sys/time.h>
#include <stdio.h>
#include <fstream>

long obtenerTiempo(){
    struct timeval inicio;
    // gettimeofdat devuelve el tiempo del reloj de la computadora
    gettimeofday(&inicio, NULL);
    // Retornamos el tiempo en segundo multiplicado por un millon que será 00:00:00 + el tiempo en microsegundos
    return inicio.tv_sec*1000000+inicio.tv_usec;
}


int main(int argc, char **argv) {

    std::ofstream fsout;

    fsout.open("./resultados.csv",std::ios_base::app);
    if(fsout.eof()){
        fsout << "Threads Archivos , Threads Maximo , Tiempo En Cargar Archivos, Tiempo en buscar Maximo, Tiempo de Programa, cantidad de archivos" << std::endl; 
    } 
    

    // std::cout << "Threads Archivos , Threads Maximo , Tiempo En Cargar Archivos, Tiempo en buscar Maximo, Tiempo de Programa, cantidad de archivos" << std::endl; 
    long inicio = obtenerTiempo();
    if (argc < 4) {
        std::cout << "Error: faltan argumentos." << std::endl;
        std::cout << std::endl;
        std::cout << "Modo de uso: " << argv[0] << " <threads_lectura> <threads_maximo>" << std::endl;
        std::cout << "    " << "<archivo1> [<archivo2>...]" << std::endl;
        std::cout << std::endl;
        std::cout << "    threads_lectura: "
            << "Cantidad de threads a usar para leer archivos." << std::endl;
        std::cout << "    threads_maximo: "
            << "Cantidad de threads a usar para computar máximo." << std::endl;
        std::cout << "    archivo1, archivo2...: "
            << "Archivos a procesar." << std::endl;
        return 1;
    }
    int cantThreadsLectura = std::stoi(argv[1]);
    int cantThreadsMaximo = std::stoi(argv[2]);

    std::vector<std::string> filePaths = {};
    for (int i = 3; i < argc; i++) {
        filePaths.push_back(argv[i]);
    }
    long inicioArchivos = obtenerTiempo();

    HashMapConcurrente hashMap = HashMapConcurrente();
    long finArchivos = obtenerTiempo();
    
    cargarMultiplesArchivos(hashMap, cantThreadsLectura, filePaths);
    long inicioMaximo = obtenerTiempo();
    hashMapPair maximo = hashMap.maximoParalelo(cantThreadsMaximo);
    long finMaximo = obtenerTiempo();

 
    fsout << " " << (cantThreadsLectura)<< ", " << cantThreadsMaximo <<  ", "  << ((finArchivos - inicioArchivos) * pow(10, -3)) << "ms, " <<  ((finMaximo - inicioMaximo) * pow(10, -3)) << "ms, " << ((finMaximo - inicio) * pow(10, -3)) << "ms, " << filePaths.size() << std::endl;
    

    return 0;
}
