#ifndef CHM_CPP
#define CHM_CPP

#include <iostream>
#include <fstream>
#include <pthread.h> 
#include <thread> 
#include <semaphore.h>
#include "HashMapConcurrente.hpp"
#include <vector> 
#include <string> 

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
        sem_init(&this->permisos_buckets[i],1,1);
    }
    this->buckets_procesados=0;
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    // Completar (Ejercicio 2)
  
	unsigned int index = this->hashIndex(clave);

    sem_wait(& this->permisos_buckets[index]);
	auto it = this->tabla[index]->crearIt();

	bool estaEnTabla = false;

	while(it.haySiguiente()){
		if(it.siguiente().first == clave){
	        estaEnTabla = true;
            it.siguiente().second++;

		}
	  it.avanzar(); 
	}

	if(!estaEnTabla){
        this->tabla[index]->insertar(hashMapPair(clave,1));
	}

    sem_post(&this->permisos_buckets[index]);
}

std::vector<std::string> HashMapConcurrente::claves() {
    std::vector<std::string> res;
    for(unsigned int i=0;i<this->cantLetras;i++){
        // sem_wait(&this->permisos_buckets[i]);
        auto it = this->tabla[i]->crearIt();

        while(it.haySiguiente()){
            res.push_back(it.siguiente().first);
            it.avanzar();
        }

        // sem_post(&this->permisos_buckets[i]);
	}
  return res;
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    // Completar (Ejercicio 2)
    unsigned int res = 0;
    for(unsigned int i=0;i<this->cantLetras;i++){
    //   sem_wait(&this->permisos_buckets[i]);

      auto it = this->tabla[i]->crearIt();
      while(it.haySiguiente()) {
        if(it.siguiente().first == clave){
            res = it.siguiente().second;
        }

        it.avanzar();
      }

    //   sem_post(&this->permisos_buckets[i]);
    }

    return res;
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;
    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        sem_wait(&this->permisos_buckets[index]);
    }

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (
            auto it = tabla[index]->crearIt();
            it.haySiguiente();
            it.avanzar()
        ) {
            if (it.siguiente().second > max->second) {
                max->first = it.siguiente().first;
                max->second = it.siguiente().second;
            }
        }
        sem_post(&this->permisos_buckets[index]);
    }

    return *max;
}

/*
 *  Metodo que ejecuta cada thread para la busqueda del maximo por fila en el hashMap
 *  @param claveMax: referencia a la clave del maximo encontrado hasta el momento en la busqueda
 *  @param valorMax: refencia a la clave del maximo valor encontrado hasta el momento en la busqueda
 */

 void HashMapConcurrente:: buscarMaximoThreaded(std::string &claveMax,unsigned int &valorMax, int i){
    unsigned int maximo_fila_valor = 0;
    std::string maximo_fila_clave = "";
    int fila = i;
    while(fila < this->cantLetras){

        //this->check_fila.lock();
        //int fila = this->buckets_procesados;

       // std::cout<< fila <<" "<< i << std::endl;
        /* if (buckets_procesados >= cantLetras) {
             //this->check_fila.unlock();
             break;
         } */
        //this->check_fila.unlock();

        auto it = this->tabla[fila]->crearIt();

        while(it.haySiguiente()) {
            if(it.siguiente().second > maximo_fila_valor){
                maximo_fila_clave = it.siguiente().first;
                maximo_fila_valor = it.siguiente().second;
            }

            it.avanzar();
        }

        sem_post(&this->permisos_buckets[fila]);
        this->check_fila.lock();
        fila = this->buckets_procesados;
        buckets_procesados++;
        this->check_fila.unlock();
    }

    this->seccion_cargar_maximo.lock();
    if(valorMax < maximo_fila_valor){
        claveMax = maximo_fila_clave;
        valorMax = maximo_fila_valor;
    }
    this->seccion_cargar_maximo.unlock();

    return;
}



hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cantThreads){
    this->buckets_procesados = cantThreads;
    std::string claveMax;
    claveMax ="";
    unsigned int valorMax;
    valorMax= 0;

    for(unsigned int i =0; i<this->cantLetras; i++){
        sem_wait(&this->permisos_buckets[i]);
    }

    std::vector<std::thread> threads;
    for(int i=0;i<cantThreads;i++){
    threads.emplace_back(std::thread(&HashMapConcurrente::buscarMaximoThreaded,this,std::ref(claveMax),std::ref(valorMax), i)); //al momento de colocarlo lo crea
    }

    for(auto &t : threads){
        t.join();
    }

    hashMapPair res = hashMapPair(claveMax,valorMax);
    return res;
}

#endif

