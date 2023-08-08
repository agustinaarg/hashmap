#ifndef HMC_HPP
#define HMC_HPP

#include <atomic>
#include <string>
#include <vector>
#include <semaphore.h> 
#include "ListaAtomica.hpp"
#include <string> 

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static const unsigned int cantLetras = 26;

    HashMapConcurrente();
    /*
     * Incrementa concurrentemente el valor de la clave pasada por parametro.
     * En caso de no existir la clave genera un nuevo hashMapPair y la inserta en la lista
     * @param clave: clave que se desea incrementar en el hashMap
    */
    void incrementar(std::string clave);
    /*
     * Retorna todas las claves existentes en el hashmap.
     */
    std::vector<std::string> claves();
    /*
     * Retorna el numero de veces que se incremento la clave pasada por parametro.
     * @param clave: Clave a la que se desea buscar el valor asociado.
     */
    unsigned int valor(std::string clave);

    /*
     * Busca el maximo valor que se encuentra en el hasMap sin concurrencia.
     */
    hashMapPair maximo();
   //  hashMapPair maximoFila(unsigned int fila);
   /*
    *  Busca el maximo de forma concurrente con varios threads
    *  @param cantThreads: numero de threads que se ejecutaran para la busqueda del maximo
    */
    hashMapPair maximoParalelo(unsigned int cantThreads);

 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];
    bool hayFilaParaBuscarMaximo();
    std::atomic<int> buckets_procesados; 
    //std::mutex check_fila;
    //std::mutex check_ultima_fila;
    std::mutex seccion_cargar_maximo;
    std::mutex check_fila;
    sem_t permisos_buckets[26];
    void  buscarMaximoThreaded(std::string &claveMax,unsigned int &valorMax, int i);
    static unsigned int hashIndex(std::string clave);
};

#endif  /* HMC_HPP */
