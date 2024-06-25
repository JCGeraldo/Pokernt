#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

#define phi 0.61803398875
int enlarge_called = 1;
typedef struct HashMap HashMap;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( int* key,  int * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( int * key, long capacity) {
    double fractionalPart = *(int*)key * phi - (int)(*(int*)key * phi);
    return (long)(capacity * fractionalPart);
}

int is_equal(int* key1, int* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(*key1 == *key2) return 1;
    return 0;
}


void insertMap(HashMap * map, int* key, int * value) {
    if(map==NULL || key==NULL) return;
    unsigned long posicion = hash(key,map->capacity);
    unsigned long posicionFija = posicion;
    
    if(!map->buckets[posicion]){
        map->buckets[posicion]=createPair(key,value);
        map->size++;
        map->current = posicion;
        return;
    }
    else{
        do{
            posicion++;
            if(posicion == map->capacity){
                posicion = 0;
            }
            if(!map->buckets[posicion]){
                map->buckets[posicion]=createPair(key,value);
                map->size++;
                map->current = posicion;
                return;
            }
        }while(map->buckets[posicion] && posicion != posicionFija);
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair ** aux = map->buckets;
    unsigned long oldSize = map->size;
    map->capacity *= 2;
    map->buckets = (Pair **)malloc(map->capacity*sizeof(Pair*));
    map->size = 0;

    for(int i=0;i<oldSize;i++){
        if(aux[i]){
            insertMap(map,aux[i]->key,aux[i]->value);
        }
    }
    free(aux);
}


HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  int * key) { 
    if(map==NULL || key==NULL) return;
    unsigned long posicion = hash(key,map->capacity);
    unsigned long posicionFija = posicion;
    if(map->buckets[posicion] && is_equal(map->buckets[posicion]->key,key)){
        map->buckets[posicion]->key = NULL;
        map->size--;
        return;
    }
    else{
        do{
            posicion++;
            if(posicion == map->capacity) posicion = 0;
            if(map->buckets[posicion] && is_equal(map->buckets[posicion]->key,key)){
                map->buckets[posicion]->key = NULL;
                map->size--;
                return;
            }
            
        }while(map->buckets[posicion] && posicion != posicionFija);
    }
    return;
    
}

Pair * searchMap(HashMap * map,  int * key) {   
    unsigned long posicion = hash(key,map->capacity);
    unsigned long posicionFija = posicion;
    if(!map->buckets[posicion])return NULL;
    if(is_equal(map->buckets[posicion]->key,key)){
        map->current = posicion;
        return map->buckets[posicion];
    }
    else{
        do{
            posicion++;
            if(posicion == map->capacity) posicion = 0;
            if(map->buckets[posicion] == NULL) return NULL;
            if(is_equal(map->buckets[posicion]->key,key)){
                map->current = posicion;
                return map->buckets[posicion];
            }
        }while(map->buckets[posicion] && posicion != posicionFija);
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {
    if(map==NULL) return NULL;
    for(unsigned long i=0;i<map->capacity;i++){
        if(map->buckets[i]!=NULL && map->buckets[i]-> key != NULL){
            map->current = i;
            return map->buckets[i];
        }  
    }
    return NULL;
}

Pair * nextMap(HashMap * map) {
    if(map==NULL) return NULL;
    if(map->current == -1) return NULL;
    for(unsigned long i=map->current+1 ; i < map->capacity ; i++){
        if(map->buckets[i]!=NULL && map->buckets[i]->key!=NULL){
            map->current = i;
            return map->buckets[i];
        }
    }
    return NULL;
}
