#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/heap.h"
#include "tdas/stack.h"
#include "tdas/queue.h"

typedef struct{
  char numero; // 1 a 13
  int palo;  // 0-3 (0 es Corazones, 1 es Diamantes, 2 es Tréboles, 3 es Picas)
  int puntaje;
}Carta;

void inicializarMazo(Carta *mazo) {
    int index = 0;
    for (int palo = 0; palo < 3; palo++) {
        for (int valor = 1; valor <= 13; valor++) {
            mazo[index].numero = valor;
            mazo[index].palo = palo;
            index++;
        }
    }
}

void barajarMazo(Carta *mazo, int tamano,Stack *mazoBarajado) {
  srand(time(NULL));
  for (int i = 0; i < tamano; i++) {
      int j = rand() % tamano;
      Carta temp = mazo[i];
      mazo[i] = mazo[j];
      mazo[j] = temp;
  }
  for (int i = 0; i < tamano; i++)
    stack_push(mazoBarajado,mazo+i);
}




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
