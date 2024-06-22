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
  int puntaje; // Puntaje del jugador
  int comodin;
} Jugador;

typedef struct {
  int etapa; // Nivel de juego
  int pozo; // Pozo del nivel
} Nivel;

// ----------------------------------------------------------------

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

// ----------------------------------------------------------------

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

// ----------------------------------------------------------------
bool noExiste(int carta,int *cartasElegidas){
  for(int i =0; i <5; i++){
    if(cartasElegidas[i] == carta) return false;
  }
  return true;
}
void repartirMano(Jugador* jugador, Stack* mazoBarajado) {
  for(int i = 0; i < 8; i++)
    jugador->cartas[i] = *(Carta*)stack_pop(mazoBarajado);
}

// ----------------------------------------------------------------

void  mostrarMano(Jugador jugador) {
  printf("Mano:\n\n");
  for(int i = 0; i < 8; i++)
    printf("|%d %d|  ", jugador.cartas[i].numero, jugador.cartas[i].palo);
  printf("\n\n");
}

// ----------------------------------------------------------------

int compararCartas(const void *a, const void *b) {
  Carta *cartaA = (Carta *)a;
  Carta *cartaB = (Carta *)b;

  if (cartaA->numero != cartaB->numero)
      return cartaA->numero - cartaB->numero;
  return cartaA->palo - cartaB->palo;
}

// ----------------------------------------------------------------

void ordenarCartas(Carta* cartas, int largo) {
  if (largo < 2) return;
  qsort(cartas, largo, sizeof(Carta), compararCartas);
}

// ----------------------------------------------------------------

bool mismaPinta(Carta* cartas, int largo) {
  int pinta = cartas[0].palo;
  for(int i = 1 ; i < largo ; i++) {
    if(cartas[i].palo != pinta) return false;
  }
  return true;
}
// ----------------------------------------------------------------

int valorCarta(Carta carta) {
  // Falta el caso del comodín
  int puntaje;
  switch (carta.numero) {
    case 1: // As
      puntaje = 15;
        break;
    case 11: // Jota
    case 12: // Reina
    case 13: // Rey
      puntaje = 10;
        break;
    default:
      puntaje = carta.numero; // Los valores 2-10 se asignan directamente
        break;
  }
  printf("%d ", puntaje);
  return puntaje;
}

// ----------------------------------------------------------------

bool esPoker(Carta* cartas, int largo);

/*
// Prototipo de funciones
bool esEscaleraDeColor(Carta* cartas, int largo);
bool esPoker(Carta* cartas, int largo);
bool esFull(Carta* cartas, int largo);
bool esColor(Carta* cartas, int largo);
bool esEscalera(Carta* cartas, int largo);
bool esTrio(Carta* cartas, int largo);
bool esDoblePareja(Carta* cartas, int largo);
bool esPareja(Carta* cartas, int largo);
void cartaMasAlta(Carta* cartas, int largo);
*/
// ----------------------------------------------------------------

void mejorJugada(Carta* cartas, int largo, int* puntaje) {
  int multiplo = 1;
  if (esPoker(cartas, largo)) {
    printf("Poker\n");
    *puntaje = 60;
    multiplo = 7;
  }
  printf("No es Poker\n");
  /*
  if (esEscaleraDeColor(cartas, largo) {
    *puntaje = 100;
    multiplo = 8;
  } else if (esPoker(cartas, largo)) {
    *puntaje = 60;
    multiplo = 7;
  } else if (esFull(cartas, largo)) {
    *puntaje = 40;
    multiplo = 4;
  } else if (esColor(cartas, largo)) {
    *puntaje = 35;
    multiplo = 4;
  } else if (esEscalera(cartas, largo)) {
    *puntaje = 30;
    multiplo = 4;
  } else if (esTrio(cartas, largo)) {
    *puntaje = 30;
    multiplo = 3;
  } else if (esDoblePareja(cartas, largo)) {
    *puntaje = 20;
    multiplo = 2;
  } else if (esPareja(cartas, largo)) {
    *puntaje = 10;
    multiplo = 2;
  } else { 
    cartaMasAlta(cartas, largo);
    *puntaje = 5;
    multiplo = 1;
  }
  */
  for (int i = 0 ; i < largo ; i++) {
    *puntaje += valorCarta(cartas[i]);
  }
  printf("\n");
  printf("Puntaje: %d\n", *puntaje);
  *puntaje *= multiplo;
  printf("Multiplo: %d\n", multiplo);
  return;
}

// ----------------------------------------------------------------

bool esPoker(Carta* cartas, int largo) {
  if (largo < 4) return false;
  for (int i = 0 ; i < largo - 3 ; i++) {
    if (cartas[i].numero == cartas[i+1].numero && 
        cartas[i].numero == cartas[i+2].numero && 
        cartas[i].numero == cartas[i+3].numero) {
      return true;
    }
  }
  return false;
}

// ----------------------------------------------------------------

void asignacionPuntaje(Jugador* jugador, int* listaPosicion, int largo) {
  if (largo == 0) return;

  // Crear un arreglo de cartas seleccionadas
  Carta* cartasSeleccionadas = (Carta*)malloc(largo * sizeof(Carta));
  if (cartasSeleccionadas == NULL) {
    printf("Error al asignar memoria para cartas seleccionadas.\n");
    return;
  }

  // Copiar las cartas seleccionadas al nuevo arreglo
  for (int i = 0 ; i < largo ; i++) {
    int posicion = listaPosicion[i-1];
    cartasSeleccionadas[i] = jugador->cartas[posicion];
  }

  printf("Cartas seleccionadas en orden:\n");
  ordenarCartas(cartasSeleccionadas, largo);
  for (int i = 0 ; i < largo ; i++) {
    printf("|%d %d|  ", cartasSeleccionadas[i].numero, cartasSeleccionadas[i].palo);
  }
  printf("\n");

  // Calcular el puntaje basado en las cartas seleccionadas
  int puntaje = 0;
  mejorJugada(cartasSeleccionadas, largo, &puntaje); 
  jugador->puntaje += puntaje; // Agregar el puntaje calculado al puntaje total del jugador
  free(cartasSeleccionadas);  

}

// ==================== OPCIÓN 1 ====================

bool jugar() {
  limpiarPantalla();
  // Inicializar variables y el mazo
  bool derrota = true;
  Carta mazo[52];
  int cartasElegidas[5] = {0,0,0,0,0};
  
  Nivel nivel;  
  nivel.etapa = 1;
  nivel.pozo = 100; //Puntaje requerido, condición de victoria.
  int manosJugadas = 0; //Limite de manos, condición de derrota.
  
  inicializarMazo(mazo);
  Stack *mazoBarajado = stack_create(mazoBarajado); // Barajar el mazo
  barajarMazo(mazo, 52, mazoBarajado);

  Jugador jugador; 
  jugador.puntaje = 0;
  repartirMano(&jugador, mazoBarajado); // Repartir mano al jugador
  // Pedir cartas al jugador
  int carta;
  
  do{
    int cont = 0;
    printf("Puntaje = %d                    Pozo = %d\n\n\n", jugador.puntaje, nivel.pozo);
    mostrarMano(jugador);
    //Eleccion de cartas, falta filtrar elecciones repetidas.
    printf("Ingrese el número de la carta que desea pedir (1-8): ");
    do{
      scanf("%d", &carta);
      if(!carta) break;
      if(noExiste(carta,cartasElegidas)) {
        cartasElegidas[cont] = carta;
        cont++;
      }
      else printf("La carta ya fue elegida, ingrese otra: ");
    } while(cont < 5);
    manosJugadas++;
  
    //Mostrar cartas elegidas y pedir confirmacion(opcional)
    printf("Cartas elegidas: \n");
    for(int i = 0; i < cont; i++){
      if(jugador.cartas[cartasElegidas[i] - 1].numero == 0) break;
      printf("|%d %d|  ", jugador.cartas[cartasElegidas[i] - 1].numero, jugador.cartas[cartasElegidas[i] - 1].palo);
    }
    printf("\n");

    //presioneTeclaParaContinuar();

    asignacionPuntaje(&jugador, cartasElegidas, cont); // IAN 
    
    //asignar puntaje a la mano jugada, mostrar puntaje total

    //comprobar si se cumple la condicion de victoria

    //quitar de la mano las cartas elegidas, vaciar la lista de cartas elegidas y rellenar la mano con cartas del mazo.
    for(int i = 0 ; i < 5 ; i++) { // Aqui se reemplazan las cartas de la mano con otras del mazo
      jugador.cartas[cartasElegidas[i] - 1] = *(Carta*)stack_pop(mazoBarajado);
      cartasElegidas[i] = 0;
    }
    
        
    //Repetir hasta que se cumpla la condicion de victoria o de derrota
    printf("\n\n");
    //limpiarPantalla();
  } while(manosJugadas < 20);

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
