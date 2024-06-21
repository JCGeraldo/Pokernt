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
#include "tdas/extra.h"

typedef struct {
  char numero; // 1 a 13
  int palo;  // 0-3 (0 es Corazones, 1 es Diamantes, 2 es Tréboles, 3 es Picas)
  int puntaje;
} Carta;

typedef struct {
  Carta cartas[8]; // Cartas que tiene el jugador
  int puntaje;
  int comodin;
  // Puntaje del jugador
  // Falta definir el comodín seleccionado
} Jugador;

typedef struct{
  int etapa;
  int pozo;
}Nivel;

void inicializarMazo(Carta *mazo) {
  int index = 0;
  for (int palo = 0 ; palo <= 3 ; palo++) {
    for (int valor = 1 ; valor <= 13 ; valor++) {
      mazo[index].numero = valor;
      mazo[index].palo = palo;
      index++;
    }
  }
}

void barajarMazo(Carta *mazo, int tamano, Stack *mazoBarajado) {
  srand(time(NULL));
  for (int i = 0 ; i < tamano ; i++) {
    int j = rand() % tamano;
    Carta temp = mazo[i];
    mazo[i] = mazo[j];
    mazo[j] = temp;
  }
  for (int i = 0 ; i < tamano ; i++)
    stack_push(mazoBarajado, mazo+i);
}



void repartirMano(Jugador* jugador, Stack* mazoBarajado){
  for(int i = 0; i < 8; i++)
    jugador->cartas[i] = *(Carta*)stack_pop(mazoBarajado);
}

void  mostrarMano(Jugador jugador){
  for(int i = 0; i < 8; i++)
    printf("|%d %d|  ", jugador.cartas[i].numero, jugador.cartas[i].palo);
  printf("\n\n");
}


// ==================== OPCIÓN 1 ====================

void jugar() {
  limpiarPantalla();
  // Inicializar el mazo
  Carta mazo[52];
  Carta cartasElegidas[5];
  Nivel nivel;
  nivel.etapa = 1;
  nivel.pozo = 100;
  
  inicializarMazo(mazo);
  // Barajar el mazo
  Stack *mazoBarajado = stack_create(mazoBarajado); 
  barajarMazo(mazo, 52, mazoBarajado);
  Jugador jugador;
  jugador.puntaje = 0;
  repartirMano(&jugador, mazoBarajado);
  mostrarMano(jugador);
  // Pedir cartas al jugador
  int carta;
  printf("Ingrese el número de la carta que desea pedir (1-5): ");
  do{
    scanf("%d", &carta);
  }while(carta!=0);
  
  
  
}

// ==================== OPCIÓN 2 ====================


// ==================== OPCIÓN 3 ====================


// ==================== MAIN ====================

int main() {

    puts("\n========================================");
    puts("               Pokern't  ♥♠♣♦");
    puts("========================================");
    printf("          ───▄█▄▄▄▄▄▄▄───▄──\n");
    printf("          ──█▀██▀▄▄▀███▄▐─▌─\n");
    printf("          ─████▌█▌▐█▐███▄▀▄─\n");
    printf("          ──████▄▀▀▄████────\n");
    printf("          ───▀█▀▀▀▀▀▀█▀─────\n\n");
    puts("\nPresione una tecla para jugar...");
    getchar();
    limpiarPantalla();// Consume el '\n' del buffer de entrada
    char opcion;
    do {
        puts("1) Jugar");
        puts("2) Tutorial");
        puts("3) Configuración");
        puts("4) Salir");
    
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion);
        
        switch (opcion) {
        case '1':
          jugar();
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
