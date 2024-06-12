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
        puts("               Pokern't  ♥♠♣♦");
        puts("========================================");
        printf("          ───▄█▄▄▄▄▄▄▄───▄──\n");
        printf("          ──█▀██▀▄▄▀███▄▐─▌─\n");
        printf("          ─████▌█▌▐█▐███▄▀▄─\n");
        printf("          ──████▄▀▀▄████────\n");
        printf("          ───▀█▀▀▀▀▀▀█▀─────\n\n");
      
        puts("1) Jugar");
        puts("2) Tutorial");
        puts("3) Configuración");
        puts("4) Salir");
    
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
        
        switch (opcion) {
        case '1':
          break;
        case '2':
          break;
        case '3':
          break;
        case '4':
           printf("\nSaliendo del juego.\n");
           break;
        default:
            printf("\nOpción inválida. Por favor, ingrese una opción válida.\n");
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != '4');

  return 0;
}
