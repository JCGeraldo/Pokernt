#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/stack.h"
#include "tdas/queue.h"

typedef struct{
  char numero;
  char palo;
  int puntaje;
}Carta;



// ==================== OPCIÓN 1 ====================


// ==================== OPCIÓN 2 ====================



// ==================== OPCIÓN 3 ====================


// ==================== MAIN ====================

int main() {

    
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
        
        switch (opcion) {
        case '1':
          //dfs(opcion);
          break;
        case '2':
          //bfs(opcion);
          break;
        case '3':
          //best_first(opcion);
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
