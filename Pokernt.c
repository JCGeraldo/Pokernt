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

bool jugar() {
  limpiarPantalla();
  // Inicializar variables y el mazo
  bool derrota = true;
  Carta mazo[52];
  int cartasElegidas[5] ={0};
  Nivel nivel;  
  nivel.etapa = 1;
  nivel.pozo = 100; //Puntaje requerido, condición de victoria.
  int manosJugadas = 0; //Limite de manos, condición de derrota.
  
  inicializarMazo(mazo);
  // Barajar el mazo
  Stack *mazoBarajado = stack_create(mazoBarajado); 
  barajarMazo(mazo, 52, mazoBarajado);
  Jugador jugador;
  jugador.puntaje = 0;
  repartirMano(&jugador, mazoBarajado);
  // Pedir cartas al jugador
  int carta;
  do{
    int cont = 0;
    mostrarMano(jugador);
    //Eleccion de cartas, falta filtrar elecciones repetidas.
    printf("Ingrese el número de la carta que desea pedir (1-8): ");
    do{
      scanf("%d", &carta);
      if(!carta) break;
      cartasElegidas[cont] = carta - 1;
      cont++;
    }while(cont<5);
    manosJugadas++;
  
    //Mostrar cartas elegidas y pedir confirmacion(opcional)
    printf("Cartas elegidas: \n");
    for(int i = 0; i < cont; i++){
      if(jugador.cartas[cartasElegidas[i]].numero!=0)
        printf("|%d %d|  ", jugador.cartas[cartasElegidas[i]].numero, jugador.cartas[cartasElegidas[i]].palo);
    }
    printf("\n");
    //asignar puntaje a la mano jugada, mostrar puntaje total

    //comprobar si se cumple la condicion de victoria

    //quitar de la mano las cartas elegidas, vaciar la lista de cartas elegidas y rellenar la mano con cartas del mazo.
    for(int i = 0; i < 5; i++){ // Aqui se reemplazan las cartas de la mano con otras del mazo
      jugador.cartas[cartasElegidas[i]] = *(Carta*)stack_pop(mazoBarajado);
      cartasElegidas[i] = 0;
    }
    
        
    //Repetir hasta que se cumpla la condicion de victoria o de derrota

    limpiarPantalla();
  } while(manosJugadas < 5);

  return derrota;
}

// ==================== OPCIÓN 2 ====================


// ==================== OPCIÓN 3 ====================


// ==================== MAIN ====================

int main() {

  puts("\n========================================");
  puts("         ♠♣♦♥  Pokern't  ♥♦♣♠");
  puts("========================================");
  printf("          ───▄█▄▄▄▄▄▄▄───▄──\n");
  printf("          ──█▀██▀▄▄▀███▄▐─▌─\n");
  printf("          ─████▌█▌▐█▐███▄▀▄─\n");
  printf("          ──████▄▀▀▄████────\n");
  printf("          ───▀█▀▀▀▀▀▀█▀─────\n\n");
  puts("\nPresione una tecla para jugar...");
  getchar();
  limpiarPantalla();
  char opcion;
  bool derrota = false;
  do {
      puts("1) Jugar");
      puts("2) Tutorial");
      puts("3) Configuración");
      puts("4) Salir");
  
      printf("Ingrese su opción: ");
      scanf(" %c", &opcion);
      
      switch (opcion) {
      case '1':
        do{
          derrota = jugar(); //Agregar argumento del nivel?
          //Actualizar el nivel y el pozo
        }while(!derrota);
        break;
      case '2':
        //mostrarTutorial();
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
