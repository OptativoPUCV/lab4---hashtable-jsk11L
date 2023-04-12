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
  long index = hash(key,map->capacity);
  long primerIndex = index;

  while(1){
    Pair *current = map->buckets[index];
    
    if(current == NULL) return NULL;
    
    if(strcmp(current->key,key) == 0){
      map->current = index;
      return current;
    }
    
    index = (index + 1) % map->capacity;
    
    if(index == primerIndex) return NULL;
  }

  return NULL;
}

void eraseMap(HashMap * map,  char * key) {
  long index = hash(key,map->capacity);
  long primerIndex = index;

  while(1){
    Pair *current = map->buckets[index];
    
    if(current == NULL) return;
    
    if(strcmp(current->key,key) == 0){
      current->key = NULL;
      map->size -= 1;
      return;
    }
    
    index = (index + 1) % map->capacity;
    
    if(index == primerIndex) return;
  }

  return;
}

Pair * firstMap(HashMap * map) {
  long index = 0;
  long primerIndex = index;
  Pair *current = map->buckets[index];

  while(1){
    current = map->buckets[index];
    
    if(current != NULL || current->key != NULL){
      break;
    }
    
    index = (index+1) % map->capacity; 
    if(index == primerIndex) return NULL;
  }
  
  map->current = index;
  return current;
}

Pair * nextMap(HashMap * map) {
  
  long index = map->capacity+1;
  long primerIndex = index;
  Pair *current = map->buckets[index];

  while(1){
    current = map->buckets[index];
    
    if(current != NULL){
      break;
    }
    
    index = (index+1) % map->capacity; 
    if(index == primerIndex) return NULL;
  }
  
  map->current = index;
  return current;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
}