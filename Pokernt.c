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
#include "tdas/map.h"
#include "cartas.c"

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
void limpiarBuffer(){
  while(getchar() != '\n');
}
int is_equal(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2;
}

void inicializarMapa(Map *mapa){
  for(int i = 1; i <= 13; i++){
    int *numero = malloc(sizeof(int));
    *numero = i;
    int *puntaje = malloc(sizeof(int));
    if(i == 1)
      *puntaje = 15;
    else if (i > 10)
      *puntaje = 10;
    else
      *puntaje = i;
    map_insert(mapa, numero, puntaje);
  }
}
// ----------------------------------------------------------------

void inicializarMazo(Carta *mazo, Map *mapa) {
  int index = 0;
  for (int palo = 0 ; palo <= 3 ; palo++) {
    for (int valor = 1 ; valor <= 13 ; valor++) {
      mazo[index].numero = valor;
      mazo[index].palo = palo;
      mazo[index].puntaje = *(int*)map_search(mapa, &valor)->value;;
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

void  mostrarMano(Jugador jugador, int majosJugadas, int contadorDescartes) { 
  char *jugadas = {"Jugadas:"};
  char *descartes = {"Descartes:"};
  printf("%49s %d / 5\n\n", jugadas, majosJugadas);
  printf("Mano: %45s %d / 3\n\n", descartes, contadorDescartes);
  mostrar_cartas(jugador.cartas, 8);
}

// ----------------------------------------------------------------

int compararCartas(const void *a, const void *b) {
  Carta *cartaA = (Carta *)a;
  Carta *cartaB = (Carta *)b;

  if (cartaA->numero != cartaB->numero)
      return cartaA->numero - cartaB->numero;
  return cartaA->palo - cartaB->palo;
}

int compararCartasPalo(const void *a, const void *b) {
  Carta *cartaA = (Carta *)a;
  Carta *cartaB = (Carta *)b;

  if (cartaA->palo != cartaB->palo)
      return cartaA->palo - cartaB->palo;
  return cartaA->numero - cartaB->numero;
}

// ----------------------------------------------------------------

void ordenarCartas(Carta* cartas, int largo) {
  if (largo < 2) return;
  qsort(cartas, largo, sizeof(Carta), compararCartas);
}

void ordenarCartasPalo(Carta* cartas, int largo) {
  if (largo < 2) return;
  qsort(cartas, largo, sizeof(Carta), compararCartasPalo);
}

// ----------------------------------------------------------------

int compararNumerico(const void *a, const void *b) {
  Carta *cartaA = (Carta *)a;
  Carta *cartaB = (Carta *)b;
  return cartaA->numero - cartaB->numero;
}

// ----------------------------------------------------------------

// Prototipo de funciones
bool esEscaleraDeColor(Carta* cartas, int largo);
bool esPoker(Carta* cartas, int largo);
bool esFull(Carta* cartas, int largo);
bool esColor(Carta* cartas, int largo);
bool esEscalera(Carta* cartas, int largo);
bool esTrio(Carta* cartas, int largo);
bool esDoblePareja(Carta* cartas, int largo);
bool esPareja(Carta* cartas, int largo);

// ----------------------------------------------------------------

void mejorJugada(Carta* cartas, int largo, int* puntaje) {
  int multiplo = 1;
  
  if (esEscaleraDeColor(cartas, largo)) {
    printf("Escalera de color!\n");
    *puntaje = 100;
    multiplo = 8;
  } else if (esPoker(cartas, largo)) {
    printf("Poker!\n");
    *puntaje = 60;
    multiplo = 7;
  } else if (esFull(cartas, largo)) {
    printf("Full!\n");
    *puntaje = 40;
    multiplo = 4;
  } else if (esColor(cartas, largo)) {
    printf("Color!\n");
    *puntaje = 35;
    multiplo = 4;
  } else if (esEscalera(cartas, largo)) {
    printf("Escalera!\n");
    *puntaje = 30;
    multiplo = 4;
  } else if (esTrio(cartas, largo)) {
    printf("Trio!\n");
    *puntaje = 30;
    multiplo = 3;
  } else if (esDoblePareja(cartas, largo)) {
    printf("Doble pareja!\n");
    *puntaje = 20;
    multiplo = 2;
  } else if (esPareja(cartas, largo)) {
    printf("Pareja!\n");
    *puntaje = 10;
    multiplo = 2;
  } else {
    printf("Carta más alta!\n");
    *puntaje = 5;
    multiplo = 1;
  }
  
  for (int i = 0 ; i < largo ; i++) {
    printf("%d ", cartas[i].puntaje);
    *puntaje += cartas[i].puntaje;
  }
  printf("\n");
  printf("Puntaje: %d\n", *puntaje);
  *puntaje *= multiplo;
  printf("Multiplo: %d\n", multiplo);
  return;
}

// ----------------------------------------------------------------

bool esEscaleraDeColor(Carta* cartas, int largo) {
  if (largo < 5) return false;
  if (esEscalera(cartas, largo) && esColor(cartas, largo)) return true;
  return false;
}

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

bool esFull(Carta* cartas, int largo) {
  if (largo < 5) return false;
  
  int numerosDistintos = 1;

  for(int i = 0; i < largo - 1; i++)
    if(cartas[i].numero != cartas[i+1].numero) numerosDistintos++;
  return numerosDistintos == 2;
}

bool esColor(Carta* cartas, int largo) {
  if (largo < 5) return false;
  int pinta = cartas[0].palo;
  for (int i = 1 ; i < largo ; i++) {
    if (cartas[i].palo != pinta) {
      return false;
    }
  }
  return true;
}

bool esEscalera(Carta* cartas, int largo) {
  if (largo < 5) return false;
  
  // Ordenar las cartas
  qsort(cartas, largo, sizeof(Carta), compararNumerico);

  // Contar número de cartas consecutivas
  int consecutivas = 1;
  for (int i = 1; i < largo; i++) {
    if (cartas[i].numero == cartas[i-1].numero) {
      continue; // Ignorar cartas duplicadas
    }
    if (cartas[i].numero == cartas[i-1].numero + 1) {
      consecutivas++;
      if (consecutivas == 5) return true;
    } else {
      consecutivas = 1; // Resetear la cuenta si no son consecutivas
    }
  }

  // Considerar caso especial para escalera con As alto (ejemplo: 10, J, Q, K, A)
  if (cartas[largo-1].numero == 13 && 
      cartas[largo-2].numero == 12 &&
      cartas[largo-3].numero == 11 &&
      cartas[largo-4].numero == 10 &&
      cartas[0].numero == 1) {
    return true;
  }
  return false;
}

bool esTrio(Carta* cartas, int largo) {
  if (largo < 3) return false;
  for (int i = 0 ; i < largo - 2 ; i++) {
    if (cartas[i].numero == cartas[i+1].numero &&
        cartas[i].numero == cartas[i+2].numero) {
      return true;
    }
  }
  return false;
}

bool esDoblePareja(Carta* cartas, int largo) {
  if (largo < 4) return false;
  int parejas = 0;

  for (int i = 0 ; i < largo - 1 ; i++) {
    if (cartas[i].numero == cartas[i+1].numero) {
      parejas++;
      i++; // Saltar la siguiente carta para evitar contarla de nuevo
      if (parejas == 2) return true;
    }
  }
  return false;
}

bool esPareja(Carta* cartas, int largo) {
  if (largo < 2) return false;
  for (int i = 0 ; i < largo - 1 ; i++) {
    if (cartas[i].numero == cartas[i+1].numero) {
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
    int posicion = listaPosicion[i];
    cartasSeleccionadas[i] = jugador->cartas[posicion-1];
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

void descartarCartas(Jugador *jugador, Stack *mazoBarajado, int *contadorDescartes) {
  if (*contadorDescartes >= 3) {
      limpiarPantalla();
      printf("Has alcanzado el máximo número de descartes permitidos.");
      return;
  }

  int carta;
  int cont = 0;
  int cartasElegidas[5] = {0, 0, 0, 0, 0};

  do {
    printf("Ingrese el número de la carta que desea descartar (1-8): ");
    if (!scanf("%d", &carta) || carta < 1 || carta > 8) {
      puts("Ingrese un número válido !! ");
      limpiarBuffer();
    } else if (noExiste(carta, cartasElegidas)) {
      cartasElegidas[cont] = carta;
      cont++;
    } else {
      printf("\nLa carta ya fue elegida, ingrese otra!!\n ");
      limpiarBuffer();
    }
  } while (cont < 5 && carta != 0);

  for (int i = 0; i < cont; i++) {
    jugador->cartas[cartasElegidas[i] - 1] = *(Carta*)stack_pop(mazoBarajado);
  }

  (*contadorDescartes)++;
  limpiarPantalla();
}

// ==================== OPCIÓN 1 ====================

bool jugar(Jugador jugador, Nivel nivel, Map *mapa) {
  limpiarPantalla();
  // Inicializar variables y el mazo
  Carta mazo[52];
  int cartasElegidas[5] = {0,0,0,0,0};

  int manosJugadas = 0; //Limite de manos, condición de derrota.
  int contadorDescartes = 0;

  inicializarMazo(mazo, mapa);

  Stack *mazoBarajado = stack_create(mazoBarajado); // Barajar el mazo
  barajarMazo(mazo, 52, mazoBarajado);

  jugador.puntaje = 0;
  repartirMano(&jugador, mazoBarajado); // Repartir mano al jugador
  // Pedir cartas al jugador
  int carta;
  char opcion;
  do{
    int cont = 0;

    //Eleccion de cartas.
    do{
      printf("Puntaje = %-30d Pozo = %d\n\n\n", jugador.puntaje, nivel.pozo);
      mostrarMano(jugador, manosJugadas, contadorDescartes);
      puts("============================================================\n");
      puts("Elija una opcion: ");
      puts("  1) Elegir cartas");
      puts("  2) Ordenar mano por palo");
      puts("  3) Ordenar mano por valor");
      if (contadorDescartes < 3) {
          puts("  4) Descartar cartas");
      }

      scanf(" %c", &opcion);
      switch(opcion){
        case '1':
          printf("Ingrese el número de la carta que desea jugar (1-8): ");
          do{
            do{
              if(!scanf("%d", &carta) || carta < 0 || carta > 8 ){
                puts("Ingrese un número válido: ");
                limpiarBuffer();
              }
            }while(carta < 0 || carta > 8);
            if(!carta && cont == 0){
              puts("Elija al menos una carta");
              continue;
            }
            if(!carta) break;
            if(noExiste(carta,cartasElegidas)) {
              cartasElegidas[cont] = carta;
              cont++;
            }
            else printf("La carta ya fue elegida, ingrese otra: ");
          }while(cont < 5);
          break;
        case '2':
          ordenarCartasPalo(jugador.cartas, 8);
          limpiarPantalla();
          break;
        case '3':
          ordenarCartas(jugador.cartas, 8);
          limpiarPantalla();
          break;
        case '4':
          if (contadorDescartes < 3) {
            descartarCartas(&jugador, mazoBarajado, &contadorDescartes);
          }
          limpiarPantalla();
        break;
        default:
          puts("Ingrese una opción válida: ");
          break;
      }
    }while(opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4');

    if (opcion == '4') continue;
    if(cont == 0)continue;
    manosJugadas++;
    //Mostrar cartas elegidas y pedir confirmacion(opcional)
    printf("Cartas elegidas: \n");
    for(int i = 0; i < cont; i++){
      if(jugador.cartas[cartasElegidas[i] - 1].numero == 0) break;
      printf("|%d %d|  ", jugador.cartas[cartasElegidas[i] - 1].numero, jugador.cartas[cartasElegidas[i] - 1].palo);
    }
    printf("\n");

    asignacionPuntaje(&jugador, cartasElegidas, cont);
    presioneTeclaParaContinuar();

    if(jugador.puntaje >= nivel.pozo)//Condición de victoria
      return false;

    //se reemplazan las cartas usadas por otras del mazo y se vacia la lista de cartas elegidas.
    for(int i = 0 ; i < 5 ; i++) {
      jugador.cartas[cartasElegidas[i] - 1] = *(Carta*)stack_pop(mazoBarajado);
      cartasElegidas[i] = 0;
    }

    //Repetir hasta que se cumpla la condicion de victoria o de derrota
    printf("\n\n");
    limpiarPantalla();
  } while(manosJugadas < 5);
  stack_clean(mazoBarajado);
  return true;
}

// ==================== OPCIÓN 2 ====================

void mostrar_tutorial(Jugador jugador_tutorial) {
  printf("Bienvenido al juego de cartas!\n\n");

  printf("Objetivo del juego:\n");
  printf("El objetivo es ganar puntos formando combinaciones de cartas.\n\n");
  printf("...");

  presioneTeclaParaContinuar();
  printf("Mecánicas Básicas del Juego:\n");
  printf("1. Cada jugador recibe 8 cartas.\n");
  printf("2. Las cartas tienen un número (1 a 13) y un palo (Corazones, Diamantes, Tréboles, Picas).\n\n");
  mostrar_cartas(jugador_tutorial.cartas, 8);
  mensajeEstrategias();
}


// ==================== OPCIÓN 3 ====================



// ==================== OPCIÓN 4 ====================

void seleccionarComodin(Jugador jugador) {
  
}


// ==================== MAIN ====================

int main() {
  Map *mapa = map_create(is_equal);
  inicializarMapa(mapa);
  Jugador jugador_tutorial = {
      .cartas = {
          {1, 0, 0}, {13, 1, 0}, {11, 1, 0}, {12, 1, 0},
          {5, 1, 0}, {9, 0, 0}, {3, 3, 0}, {10, 1, 0}
      },
      .puntaje = 0,
      .comodin = 0
  };

  puts("\n========================================");
  puts("         ♠♣♦♥  Pokern't  ♥♦♣♠");
  puts("========================================");

  mostrarChancho();
  puts("\nPresione una tecla para jugar...");
  getchar();
  limpiarPantalla();
  
  Jugador jugador;  
  char opcion;
  bool derrota = false;
  do {
      Nivel nivel;
      nivel.etapa = 1;
      nivel.pozo = 100;
      puts("1) Jugar");
      puts("2) Tutorial");
      puts("3) Configuración");
      puts("4) Comodín");
      puts("5) Salir");
      printf("Ingrese su opción: ");
      scanf(" %c", &opcion);
      switch (opcion) {
      case '1':
        do{
          derrota = jugar(jugador, nivel, mapa); 
          if(derrota) break;
          nivel.etapa++;
          nivel.pozo *= 1.5;
          limpiarPantalla();
          mensajeVictoria();
          
        } while(!derrota);
        mensajeFinal();
        printf("\nFelicitaciones, alcanzaste el nivel %d.\n\n", nivel.etapa);
        break;
      case '2':
        mostrar_tutorial(jugador_tutorial);
        break;
      case '3':
        break;
      case '4':
        seleccionarComodin(jugador);
        break;
      case '5':
         printf("\nSaliendo del juego.\n");
         break;
      default:
          printf("\nOpción inválida. Por favor, ingrese una opción válida.\n");
      }
      presioneTeclaParaContinuar();
      limpiarPantalla();

  } while (opcion != '5');

  return 0;
}
