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

HashMap * createMap(long capacity) {
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  map->buckets = (Pair **)calloc(capacity,sizeof(Pair *));
  return map;
}

void insertMap(HashMap * map, char * key, void * value) {
  long index = hash(key,map->capacity);
  long primerIndex = index;

  while(1){

    Pair *current = map->buckets[index];

    if(current == NULL || current->key == NULL){
      Pair* nuevoPar = (Pair *)malloc(sizeof(Pair));
      nuevoPar->key = strdup(key);
      nuevoPar->value = value;
      map->buckets[index] = nuevoPar;
      map->size++;
      map->current = index;
      return;
    }

    index = (index+1) % map->capacity;

    if(index == primerIndex){
      return;
    }
  }
}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

void eraseMap(HashMap * map,  char * key) {
  long index = hash(key,map->capacity);
  long primerIndex = index;

  while(1){
    Pair *current = map->buckets[index];
    
    if(current == NULL) return NULL;
    
    if(strcmp(current->key,key) == 0){
      map->current = index;
      return;
    }
    
    index = (index + 1) % map->capacity;
    
    if(index == primerIndex) return;
  }
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
}