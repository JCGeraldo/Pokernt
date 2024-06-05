#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <string.h>

typedef struct nodo{
   void* data;
   int priority;
} heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions; //Secuencia de movimientos para llegar al estado
} State;

int distancia_L1(State* state) {
    int ev = 0;
    for(int i = 0 ; i < 3 ; i++)
        for(int j = 0 ; j < 3 ; j++){
            int val = state->square[i][j];
            if (val == 0) continue;
            int ii = (val) / 3;
            int jj = (val) % 3;
            ev += abs(ii - i) + abs(jj - j);
        }
    return ev;
}

// Función para calcular el número de inversiones en el estado del puzzle
int contar_inversiones(State* state) {
    int inv_count = 0;
    int arr[8]; // Array temporal para almacenar los valores del puzzle
    int k = 0;

    // Convertir la matriz en un array unidimensional, ignorando el espacio vacío (0)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state->square[i][j] != 0) {
                arr[k++] = state->square[i][j];
            }
        }
    }
    // Contar el número de inversiones
    for (int i = 0; i < 8 - 1; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (arr[i] > arr[j]) {
                inv_count++;
            }
        }
    }
    return inv_count;
}

// Función para verificar si un estado es resoluble
bool es_resoluble(State* state) {
    int inv_count = contar_inversiones(state);
    return (inv_count % 2 == 0);
}

// Función para imprimir el estado del puzzle
void imprimirEstado(const State *estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0)
                printf("x "); // Imprime un espacio en blanco para el espacio vacío
            else
                printf("%d ", estado->square[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Función para verificar si un estado es igual a otro estado
bool comparar_estados(const State *a, const State *b) {
    for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
            if (a->square[i][j] != b->square[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Función para verificar si un estado es el estado objetivo
bool is_final_state(State* state) {
    // Estado final del puzzle
    State estado_final = {
        {{0, 1, 2}, // Primera fila (0 representa espacio vacío)
         {3, 4, 5}, // Segunda fila
         {6, 7, 8}, // Tercera fila
         },  
        0, 0   // Posición del espacio vacío (fila 0, columna 0)
    };
    return comparar_estados(state, &estado_final);
}

// Función para obtener los estados adyacentes a un estado
List* get_adj_states(State* state){
    List* adj_states = list_create();
    int x = state->x;
    int y = state->y;
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};
    
    int inversos[] = {2, 3, 0, 1};
    int *previousAction = (int*)list_last(state->actions);
    
    for (int i = 0 ; i < 4 ; i++) {
        //Se verifica si la nueva accion revierte la accion anterior.
        if(previousAction != NULL && i == inversos[*previousAction]) continue;
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        // Verificar si la nueva posición está dentro de los límites del tablero
        if (new_x >= 0 && new_x < 3 && new_y >= 0 && new_y < 3){
            State* new_state = (State*) malloc(sizeof(State));
            memcpy(new_state, state, sizeof(State));
            int temp = new_state->square[x][y];
            new_state->square[x][y] = new_state->square[new_x][new_y];
            new_state->square[new_x][new_y] = temp;
            new_state->x = new_x;
            new_state->y = new_y;
            new_state->actions = list_create();

            int *action = list_first(state->actions);
            while(action) {
                list_pushBack(new_state->actions, action);
                action = list_next(state->actions);
            }

            int *lastAction = (int*)malloc(sizeof(int));
            *lastAction = i;
            list_pushBack(new_state->actions, lastAction);
            list_pushBack(adj_states, new_state);
        }
    }
    return adj_states;
}

// Función para mostrar los pasos realizados para llegar al estado objetivo
void mostrarPasos(State* estadoInicial, List* pasos) {
    int cont = 1;
    int *paso= (int*)list_first(pasos);
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, -1, 0, 1};
    int size = list_size(pasos);
    while(paso){
        int x = estadoInicial->x;
        int y = estadoInicial->y;
        int new_x = x + dx[*paso];
        int new_y = y + dy[*paso];
        estadoInicial->square[x][y] = estadoInicial->square[new_x][new_y];
        estadoInicial->square[new_x][new_y] = 0;
        estadoInicial->x = new_x;
        estadoInicial->y = new_y;
        printf("Paso %d:\n", cont);
        imprimirEstado(estadoInicial);
        paso = (int*)list_next(pasos);
        cont++;
    }
}

// ==================== OPCIÓN 1 ====================

void dfs(State *estado) {
    Stack* stack = stack_create(stack);
    stack_push(stack, estado);
    int contador = 0;
    
    while (stack_top(stack)) {
        contador++;
        State* actual = (State*) stack_top(stack);
        stack_pop(stack);
        if (is_final_state(actual)) {
            printf("\nEstado final encontrado.\n");
            printf("Número de estados visitados: %d\n", contador);
            printf("Movimientos: %d\n\n", list_size(actual->actions));
            printf("Estado inicial:\n");
            imprimirEstado(estado);
            mostrarPasos(estado, actual->actions);
            list_clean(actual->actions);
            
            State* elem = (State*)stack_pop(stack);
            while(elem){
                list_clean(elem->actions);
                int *action = (int*)list_first(elem->actions);
                while (action) {
                    free(action);
                    action = (int*)list_next(elem->actions);
                }
                free(elem);
                elem = (State*)stack_pop(stack);
            }
            stack_clean(stack);
            return;
        }
        if(list_size(actual->actions) > 20){
            list_clean(actual->actions);
            continue;
        }
        
        List* adj_states = get_adj_states(actual);
        State* adj_state = (State*) list_first(adj_states);
        while(adj_state) {
            stack_push(stack, adj_state);
            adj_state = (State*) list_next(adj_states);
        }
        list_clean(adj_states);
        list_clean(actual->actions);
    }
    printf("\nNo se encontró un estado final.\n");
    printf("Iteraciones: %d\n", contador);
}

// ==================== OPCIÓN 2 ====================

void bfs(State *estado) {
    Queue* queue = queue_create(queue);
    queue_insert(queue, estado);
    int contador = 0;
    
    while (queue_front(queue)) {
        contador++;
        State* actual = (State*) queue_front(queue);
        queue_remove(queue);
        if (is_final_state(actual)) {
            printf("\nEstado final encontrado.\n");
            printf("Número de estados visitados: %d\n", contador);
            printf("Movimientos: %d\n\n", list_size(actual->actions));
            printf("Estado inicial:\n");
            imprimirEstado(estado);
            mostrarPasos(estado, actual->actions);
            list_clean(actual->actions);

            State* elem = (State*)queue_remove(queue);
            while(elem){
                list_clean(elem->actions);
                int *action = (int*)list_first(elem->actions);
                while (action) {
                    free(action);
                    action = (int*)list_next(elem->actions);
                }
                free(elem);
                elem = (State*)queue_remove(queue);
            }
            queue_clean(queue);
            return;
        }
        if(list_size(actual->actions) > 20){
            list_clean(actual->actions);
            continue;
        }
        List* adj_states = get_adj_states(actual);
        State* adj_state = (State*) list_first(adj_states);
        while(adj_state){
            queue_insert(queue, adj_state);
            adj_state = (State*) list_next(adj_states);
        }   
        list_clean(adj_states);
        list_clean(actual->actions);
    }
    printf("\nNo se encontró un estado final, requiere más de 20 movimientos\n");
    printf("Iteraciones: %d\n", contador);
}

// ==================== OPCIÓN 3 ====================

void best_first(State* estado) {
    Heap* heap = heap_create();
    heap_push(heap, estado, -(distancia_L1(estado)));
    int contador = 0;

    while (heap_top(heap)) {
        contador++;
        State* actual = (State*) heap_top(heap);
        heap_pop(heap);
        if (is_final_state(actual)) {
            printf("\nEstado final encontrado.\n");
            printf("Número de estados visitados: %d\n", contador);
            printf("Movimientos: %d\n\n", list_size(actual->actions));
            printf("Estado inicial:\n");
            imprimirEstado(estado);
            mostrarPasos(estado, actual->actions);
            State* elem = (State*)heap_top(heap);
            heap_pop(heap);
            while(elem) {
                list_clean(elem->actions);
                int *action = (int*)list_first(elem->actions);
                while (action) {
                    free(action);
                    action = (int*)list_next(elem->actions);
                }
                free(elem);
                elem = (State*)heap_top(heap);
                heap_pop(heap);
            }
            list_clean(actual->actions);
            heap_clean(heap);
            return;
        }
        List* adj_states = get_adj_states(actual);
        State* adj_state = (State*) list_first(adj_states);
        while(adj_state) {
            heap_push(heap, adj_state, -(list_size(adj_state->actions) + distancia_L1(adj_state)));
            adj_state = (State*) list_next(adj_states);
        }
        list_clean(adj_states);
        list_clean(actual->actions);
    }
    printf("\nNo se encontró un estado final.\n");
    printf("Iteraciones: %d\n", contador);
}

// ==================== MAIN ====================

int main() {
    // Estado inicial del puzzle
    ///*
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0   // Posición del espacio vacío (fila 0, columna 0)
    };
    //*/
    /*
    State estado_inicial = {
        {{8, 0, 6}, // Primera fila (0 representa espacio vacío)
         {5, 4, 7}, // Segunda fila
         {2, 3, 1}, // Tercera fila
         },  
        0, 1   // Posición del espacio vacío (fila 0, columna 0)
    };
    */
    // Verificar si el estado inicial es resoluble
    if (!es_resoluble(&estado_inicial)) {
        printf("El estado inicial del puzzle no es resoluble.\n");
        return 1;
    }
    
    // Imprime el estado inicial
    printf("Estado inicial del puzzle:\n");
    imprimirEstado(&estado_inicial);

    printf("Distancia L1:%d\n", distancia_L1(&estado_inicial));

    char opcion;
    do {
        puts("\n========================================");
        puts("     Escoge método de búsqueda");
        puts("========================================");
        
        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Buscar Mejor Primero");
        puts("4) Salir");
    
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);

        State *copia = (State*) malloc(sizeof(State));
        
        switch (opcion) {
        case '1':
          memcpy(copia, &estado_inicial, sizeof(State));
          copia->actions = list_create();
          dfs(copia);
          break;
        case '2':
          memcpy(copia, &estado_inicial, sizeof(State));
          copia->actions = list_create();
          bfs(copia);
          break;
        case '3':
          memcpy(copia, &estado_inicial, sizeof(State));
          copia->actions = list_create();
          best_first(copia);
          break;
        case '4':
           printf("\nSaliendo del programa.\n");
           break;
        default:
            printf("\nOpción inválida. Por favor, ingrese una opción válida.\n");
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != '4');

  return 0;
}
