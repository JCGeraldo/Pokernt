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
void limpiarBuffer(){
  while(getchar() != '\n');
}
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
    *puntaje += valorCarta(cartas[i]);
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

  

  qsort(cartas, largo, sizeof(Carta), compararNumerico);

  bool tieneTrio = false;
  bool tienePareja = false;

  // Buscar el trío
  for (int i = 0 ; i < largo - 2 ; i++) {
    if (cartas[i].numero == cartas[i+1].numero && 
        cartas[i].numero == cartas[i+2].numero) {
      tieneTrio = true;
      // Quitar el trío encontrado y seguir buscando la pareja
      i += 2; // Saltar las cartas del trío
      break;
    }
  }

  // Buscar la pareja
  for (int i = 0; i < largo - 1; i++) {
    if (cartas[i].numero == cartas[i+1].numero) {
      // Si el trío ya fue encontrado, asegurarse de no contar las mismas cartas como pareja
      if (tieneTrio && (i > 1 && cartas[i].numero == cartas[i-1].numero && cartas[i].numero == cartas[i-2].numero)) {
        continue;
      }
      tienePareja = true;
      break;
    }
  }
  return tieneTrio && tienePareja;
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
      do{
        limpiarBuffer();
        if(!scanf("%d", &carta) || carta < 0 || carta > 8 ){
          puts("Ingrese un número válido: ");
        }
      }while(carta < 0 || carta > 8);
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
    
    asignacionPuntaje(&jugador, cartasElegidas, cont); // IAN 
    presioneTeclaParaContinuar();
    
    //asignar puntaje a la mano jugada, mostrar puntaje total

    //comprobar si se cumple la condicion de victoria

    //quitar de la mano las cartas elegidas, vaciar la lista de cartas elegidas y rellenar la mano con cartas del mazo.
    for(int i = 0 ; i < 5 ; i++) { // Aqui se reemplazan las cartas de la mano con otras del mazo
      jugador.cartas[cartasElegidas[i] - 1] = *(Carta*)stack_pop(mazoBarajado);
      cartasElegidas[i] = 0;
    }
    
        
    //Repetir hasta que se cumpla la condicion de victoria o de derrota
    printf("\n\n");
    limpiarPantalla();
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
