#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <atomic>
#include "CargarArchivos.hpp"
#include <thread> 

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        // Completar (Ejercicio 4)
      hashMap.incrementar(palabraActual);
      cant++;
    }

    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();

    return cant;
}

void cargador_archivos_threaded(HashMapConcurrente &hashMap,std::vector<std::string> filepaths,std::atomic<int> &contador_files) {
  while(contador_files>0){
    int filePathIndex = contador_files;
    contador_files--;
    cargarArchivo(hashMap,filepaths[filePathIndex-1]);
  }
}

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
) {
    std::atomic<int> contador_files;
    contador_files = filePaths.size();
    std::vector<std::thread> threads;

  for(unsigned int i =0; i<cantThreads;i++){

    threads.emplace_back(std::thread(cargador_archivos_threaded,std::ref(hashMap),filePaths, std::ref(contador_files)));

    // Otra forma de ejecutar threads
    //
    // std::thread threadArchivo(cargador_archivos_threaded,filePaths);
    // threads.push_back(move(threadArchivo));
    
  } 

  for(auto &t : threads){
    t.join();
  }
}

#endif
