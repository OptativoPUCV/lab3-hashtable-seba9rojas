#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

//===========================================
// Función para insertar un nuevo dato en el mapa
//===========================================
void insertMap(HashMap * map, char * key, void * value) {
  Pair* newPair= (Pair*)malloc(sizeof(Pair));
  newPair->key = key;
  newPair->value = value;

  long i=hash(key,map->capacity);
  long copia=i;
  while(1){
    Pair* newAux=map->buckets[i];
    if(newAux==NULL || newAux->key==NULL){
      map->buckets[i]=newPair;
      map->size++;
      return;
    }
    i=(i+1)%map->capacity;
    if(i==copia){
      return;
    }
  }    
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}

//===========================================
// Función crear Mapa
//===========================================
HashMap * createMap(long capacity) {
  HashMap *mapa = malloc(sizeof(HashMap));
    if (mapa == NULL) {
        return NULL;
    }

    mapa->buckets=malloc(sizeof(Pair *) * capacity);
    if(mapa->buckets==NULL){
      free(mapa);
      return NULL;
    }

    mapa->capacity = capacity;
    mapa->size = 0;
    mapa->current = -1; 

    // Inicializar los buckets
    for (long i = 0; i < capacity; i++) {
        mapa->buckets[i] = NULL;
    }
    return mapa;
}

//===========================================
// Función para eliminar un dato correspondiente al mapa
//===========================================
void eraseMap(HashMap * map,  char * key) {
  long i=hash(key,map->capacity);
  long copia=i;
  while(1){
    Pair* newAux=map->buckets[i];
    if(newAux!=NULL && strcmp(newAux->key,key)==0){
      map->size--;
      map->buckets[i]->key=NULL;
      return;
    }
    i=(i+1)%map->capacity;
    if(i==copia){
      return;
    }
  }
}

Pair *searchMap(HashMap * map,  char * key) {
  long i=hash(key,map->capacity);

  while(1){
    Pair* current=map->buckets[i];

    if(current==NULL){
      return NULL;
    }
    
    if(strcmp(current->key,key)==0){
      map->current=i;
      return current;
    }

    i=(i+1)%map->capacity;

    if(i==map->current){
      break;
    }
  }
  return NULL;
}

Pair *firstMap(HashMap * map) {

    return NULL;
}

Pair *nextMap(HashMap * map) {

    return NULL;
}
