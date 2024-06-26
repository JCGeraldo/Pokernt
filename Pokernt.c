#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/stack.h"
#include "tdas/hashmap.h"
#include "cartas.c"

// Estructura Save File: nivel, pozo, dificultad, comodin, estilo
typedef struct {
  int etapa; // Nivel de juego
  int pozo; // Pozo del nivel
} Nivel;

// ----------------------------------------------------------------
void limpiarBuffer(){
  while(getchar() != '\n');
}

/*int is_equal(void *key1, void *key2) {
  return *(int *)key1 == *(int *)key2;
}*/

void inicializarMapa(HashMap *mapa){
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
    insertMap(mapa, numero, puntaje);
  }
}

// ----------------------------------------------------------------

void inicializarMazo(Carta *mazo, HashMap *mapa) {
  int index = 0;
  for (int palo = 0 ; palo <= 3 ; palo++) {
    for (int valor = 1 ; valor <= 13 ; valor++) {
      mazo[index].numero = valor;
      mazo[index].palo = palo;
      mazo[index].puntaje = *(int*)searchMap(mapa, &valor)->value;;
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

void  mostrarMano(Jugador jugador, int manosJugadas, int contadorDescartes, int estiloMazo) { 
  char *jugadas = {"Jugadas:"};
  char *descartes = {"Descartes:"};
  if (jugador.comodin == 2){ 
    printf("%42s %d / 7\n\n", jugadas, manosJugadas);
    printf("  Mano: %45s %d / 2\n\n", descartes, contadorDescartes);// COMODÍN 2
  }
  else {
    printf("%42s %d / 5\n\n", jugadas, manosJugadas);
    printf("  Mano: %45s %d / 3\n\n", descartes, contadorDescartes);
  }
  if (estiloMazo == 1) {
  mostrar_cartas(jugador.cartas, 8);
  } else { //if (estiloMazo == 2) {
    mostrar_cartas_dos(jugador.cartas, 8);
  }
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

void ordenarCartas(Carta* cartas, int largo) {
  if (largo < 2) return;
  qsort(cartas, largo, sizeof(Carta), compararCartas);
}

void ordenarCartasPalo(Carta* cartas, int largo) {
  if (largo < 2) return;
  qsort(cartas, largo, sizeof(Carta), compararCartasPalo);
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

void asignacionPuntaje(Jugador* jugador, int* listaPosicion, int largo, int estilo) {
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

  printf("Cartas seleccionadas:\n");
  ordenarCartas(cartasSeleccionadas, largo);
  estilo == 1? mostrar_cartas(cartasSeleccionadas, largo):mostrar_cartas_dos(cartasSeleccionadas, largo);
  // Calcular el puntaje basado en las cartas seleccionadas
  int puntaje = 0;
  mejorJugada(cartasSeleccionadas, largo, &puntaje); 
  jugador->puntaje += puntaje; // Agregar el puntaje calculado al puntaje total del jugador
  free(cartasSeleccionadas);  

}

void descartarCartas(Jugador *jugador, Stack *mazoBarajado, int *contadorDescartes, int sumaDescartes) {
  if (*contadorDescartes >= 3 + sumaDescartes) {
      limpiarPantalla();
      printf("Has alcanzado el máximo número de descartes permitidos.");
      return;
  }

  int carta;
  int cont = 0;
  int cartasElegidas[5] = {0, 0, 0, 0, 0};

  printf("Ingrese el número de la carta que desea descartar (1-8): ");
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
    else puts("La carta ya fue elegida, ingrese otra: ");
  } while(cont < 5);

  for (int i = 0; i < cont; i++) {
    jugador->cartas[cartasElegidas[i] - 1] = *(Carta*)stack_pop(mazoBarajado);
  }

  (*contadorDescartes)++;
  limpiarPantalla();
}

// ==================== OPCIÓN 1 ====================

bool jugar(Jugador jugador, Nivel nivel, HashMap *mapa, int estiloMazo) {
  limpiarPantalla();
  // Inicializar variables y el mazo
  Carta mazo[52];
  int cartasElegidas[5] = {0,0,0,0,0};

  //Limite de manos, condición de derrota.
  int manosJugadas = 0;
  int sumaComodin2 = 0;
  int sumaDescartes = 0;
  int contadorDescartes = 0;

  inicializarMazo(mazo, mapa);

   // Barajar el mazo
  Stack *mazoBarajado = stack_create(mazoBarajado);
  barajarMazo(mazo, 52, mazoBarajado);

  // COMODÍN 1
  if (jugador.comodin == 1) jugador.puntaje = 99;
  else jugador.puntaje = 0;

  // COMODÍN 2
  if (jugador.comodin == 2) {
    sumaComodin2 += 2;
    sumaDescartes = -1;
  }

  repartirMano(&jugador, mazoBarajado); // Repartir mano al jugador
  // Pedir cartas al jugador
  int carta;
  char opcion;
  do {
    int cont = 0;

    //Eleccion de cartas.
    do {
      mostrarComodin(jugador);
      printf("\n  Puntaje = %-30d Pozo = %d\n\n", jugador.puntaje, nivel.pozo);
      printf(MAGENTA_B"  Nivel %d"RESET , nivel.etapa);
      mostrarMano(jugador, manosJugadas, contadorDescartes, estiloMazo);
      puts(BLUE" ==================================================================\n"RESET);
      puts("  Elija una opcion: ");
      puts("  1) Elegir cartas");
      puts("  2) Ordenar mano por palo");
      puts("  3) Ordenar mano por valor");
      if (contadorDescartes < 3 + sumaDescartes) {
          puts("  4) Descartar cartas");
      }

      scanf(" %c", &opcion);
      switch(opcion) {
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
          } while(cont < 5);
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
          if (contadorDescartes < 3 + sumaDescartes) {
            descartarCartas(&jugador, mazoBarajado, &contadorDescartes, sumaDescartes);
          }
          limpiarPantalla();
          break;
        default:
          puts("Ingrese una opción válida: ");
          limpiarBuffer();
          limpiarPantalla();
          break;
      }
    } while(opcion != '1' && opcion != '2' && opcion != '3' && opcion != '4');

    if (opcion != '1') continue;
    manosJugadas++;
    //Mostrar cartas elegidas y pedir confirmacion(opcional)
    
    asignacionPuntaje(&jugador, cartasElegidas, cont, estiloMazo);
    presioneTeclaParaContinuar();

    if(jugador.puntaje >= nivel.pozo){//Condición de victoria
      stack_clean(mazoBarajado);
      free(mazoBarajado);
      return false;
    }
    //se reemplazan las cartas usadas por otras del mazo y se vacia la lista de cartas elegidas.

    if(manosJugadas >= 5 + sumaComodin2)
      break;
    for(int i = 0 ; i < cont ; i++) {
      jugador.cartas[cartasElegidas[i] - 1] = *(Carta*)stack_pop(mazoBarajado);
      cartasElegidas[i] = 0;
    }

    //Repetir hasta que se cumpla la condicion de victoria o de derrota
    limpiarPantalla();
  } while(manosJugadas < 5 + sumaComodin2);
  stack_clean(mazoBarajado);
  free(mazoBarajado);
  return true;
}

void guardarPartida(Nivel nivel, float factor, Jugador jugador, int estilo){
  FILE *archivo;
  archivo = fopen("SaveFile.txt", "w");
  if (archivo == NULL) {
    puts("Error al abrir el archivo");
    return;
  }
  fprintf(archivo, "%d, %d, %f, %d, %d", nivel.etapa, nivel.pozo, factor, jugador.comodin, estilo);
  fclose(archivo);
  puts("Partida guardada");
}

void reiniciarGuardado(Nivel *nivel, float factor, int estiloMazo) {
  printf("\nFelicitaciones, alcanzaste el nivel %d.\n\n", nivel->etapa);
  nivel->etapa = 1;
  nivel->pozo = 100;
  FILE *archivo;
  archivo = fopen("SaveFile.txt", "w");
  if (archivo == NULL) return;
  fprintf(archivo, "%d, %d, %f, %d, %d", 1, 100, factor, 0, estiloMazo);   
  fclose(archivo);
}

// ==================== OPCIÓN 2 ====================

void cargarPartida(Nivel *nivel, Jugador* jugador,float* factor, int* estilo ){
  FILE *archivo;
  archivo = fopen("SaveFile.txt", "r");
  if (archivo == NULL){
    puts("No se pudo abrir el archivo");
    return;
  }
  fscanf(archivo, "%d, %d, %f, %d, %d", &nivel->etapa, &nivel->pozo, factor, &jugador->comodin,estilo);
  fclose(archivo);
  if(nivel->etapa == 1) {
    puts("No hay partida en curso");
    return;
  }
  puts("Partida cargada exitosamente.");
  puts("Seleccione la opción 1 para continuar su partida.");
}

// ==================== OPCIÓN 3 ====================

void mostrar_tutorial(Jugador jugador_tutorial , int *mazo) {
  limpiarPantalla();
  mostrarTitulo();
  printf("Bienvenido al juego de cartas Pokern't!\n\n");

  printf("Objetivo del juego:\n");
  printf("El objetivo es ganar puntos formando combinaciones de cartas.\n\n");

  presioneTeclaParaContinuar();
  printf("Mecánicas Básicas del Juego:\n");
  printf("1. Recibes 8 cartas del mazo.\n");
  printf("2. Las cartas tienen un número (1 a 13) y un palo (Corazones, Diamantes, Tréboles, Picas).\n\n");

  if (*mazo == 1) mostrar_cartas(jugador_tutorial.cartas, 8);
  else if (*mazo == 2) mostrar_cartas_dos(jugador_tutorial.cartas, 8);

  puts("3. Puedes elegir hasta 5 cartas para jugar.");
  puts("4. Cada jugada suma puntos basados en las cartas elegidas y la combinación que forman.");
  puts("5. Puedes descartar cartas para obtener nuevas cartas.");
  puts("6. Ganas cuando alcanzas el puntaje objetivo, indicado como pozo");
  puts("7. Pierdes si se agotan las jugadas y no logras alcanzar el pozo");
  getchar();
  mensajeEstrategias(jugador_tutorial , *mazo);
}

// ==================== OPCIÓN 4 ====================

void seleccionarDificultad(float *factor, Nivel* nivel) {
  limpiarPantalla();
  mostrarTitulo();
  puts("\nSeleccionar una nueva dificultad lo obligará a comenzar en el nivel 1");
  puts("\nSeleccione la dificultad del juego:");
  puts("1. Fácil");
  puts("2. Medio");
  puts("3. Difícil");
  puts("4. Imposible");
  puts("5. Volver al menú principal");
  int opcion;
  float temp;
  do {
    printf("Ingrese una opción (1 - 5): ");
    if(!scanf("%d", &opcion) || opcion < 1 || opcion > 5) {
      puts("Ingrese una opción válida !!");
      limpiarBuffer();
    if(opcion == 5) return;
    }
  } while(opcion < 1 || opcion > 5);
  switch (opcion){
    case 1:
      temp = 1.2;
      break;
    case 2:
      temp = 1.5;
      break;
    case 3:
      temp = 1.8;
      break;
    case 4:
      temp = 2.4;
      break;
    case 5:
      break;
  }
  if(*factor != temp) {
    nivel->etapa = 1;
    nivel->pozo = 100;
  } 
  *factor = temp;
}

bool mazoValida(char *cadena, int *ptrOpcion) {
  for (int i = 0 ; cadena[i] != '\0' ; i++) {
    if (!isdigit(cadena[i])) return false;
  }
  *ptrOpcion = atoi(cadena);
  if (*ptrOpcion < 1 || *ptrOpcion > 3) return false;
  return true;
}

void seleccionarMazo(int *mazo) {
  limpiarPantalla();
  mostrarTitulo();
  puts("Seleccione el mazo de cartas:\n");
  puts("1. Mazo clásico inglés\n");
  puts("2. Mazo minimalista\n");
  puts("3. Volver al menú principal\n");
  char opcionAux[50];
  int opcion;
  scanf(" %[^\n]s", opcionAux);
  if (mazoValida(opcionAux, &opcion)) {
    switch (opcion) {
      case 1:
        *mazo = 1;
        printf("\nHa seleccionado el mazo clásico inglés.\n\n");
        break;
      case 2:
        printf("\nHa seleccionado el mazo minimalista.\n\n");
        *mazo = 2;
        break;
      case 3:
        return;
    }
  } else {
    puts("Opción inválida. Intente nuevamente.");
  }
}

void cargarEstiloMazo(int *estilo){
  FILE* archivo;
  int etapa,pozo, comodin;
  float factor;

  archivo = fopen("SaveFile.txt", "r");
  if (archivo == NULL)
    return;
  fscanf(archivo, "%d, %d, %f, %d, %d", &etapa, &pozo, &factor, &comodin,estilo);
  fclose(archivo);
  return;
}

bool configuracionValida(char *cadena, int *ptrOpcion) {
  for (int i = 0 ; cadena[i] != '\0' ; i++) {
    if (!isdigit(cadena[i])) return false;
  }
  *ptrOpcion = atoi(cadena);
  if (*ptrOpcion < 1 || *ptrOpcion > 3) return false;
  return true;
}

void configuracion(float *factor, Nivel* nivel, int *mazo) {
  limpiarPantalla();
  mostrarTitulo();
  puts("Configuración del juego:\n");
  puts("1. Elegir dificultad\n");
  puts("2. Elegir mazo\n");
  puts("3. Volver al menú principal\n");
  char opcionAux[50];
  int opcion;
  scanf(" %[^\n]s", opcionAux);
  if (configuracionValida(opcionAux, &opcion)) {
    switch (opcion) {
      case 1:
        seleccionarDificultad(factor, nivel);
        break;
      case 2:
        seleccionarMazo(mazo);
        break;
      case 3:
        return;
    }
  } else {
    puts("Opción inválida. Intente nuevamente.");
  }
}

// ==================== OPCIÓN 5 ====================

bool comodinValido(char *cadena, int *ptrOpcion) {
  if (strcmp(cadena, "n") == 0 || strcmp(cadena, "N") == 0) return true;
  for (int i = 0 ; cadena[i] != '\0' ; i++) {
    if (!isdigit(cadena[i])) return false;
  }
  *ptrOpcion = atoi(cadena);
  if (*ptrOpcion < 0 || *ptrOpcion > 3) return false;
  return true;
}

void seleccionarComodin(Jugador *jugador) {
  limpiarPantalla();
  char opcionAux[50];
  int opcion;

  printf(BLUE"\n     =============== "RESET);
  printf("Listado de Comodines ");
  printf(BLUE"===============\n\n"RESET);
  printf(GREEN"     .--------------------------------------------------.");
  printf(GREEN"\n     │ "RESET);
  printf("1. Sir Jester, the Knight of Misrule             ");
  printf(GREEN"│\n");
  printf("     ----------------------------------------------------");
  printf("\n     │ "RESET);
  printf("2. Amenhotep, the king of the desert             ");
  printf(GREEN"│\n");
  printf("     ----------------------------------------------------");
  printf(GREEN"\n     │ "RESET);
  printf("3. Proximamente...                               ");
  printf(GREEN"│\n");
  printf("     '--------------------------------------------------'"RESET);
  printf("\n\n     Ingrese el número del comodín que desea ver\n");
  printf("     Para salir ingrese 0\n");
  printf("     Para quitar comodin ingrese 'N'\n");
  printf("\n     Opción: ");

  scanf(" %[^\n]s", opcionAux);
  if (comodinValido(opcionAux, &opcion)) {
    if (strcmp(opcionAux, "n") == 0 || strcmp(opcionAux, "N") == 0) {
      jugador->comodin = 0;
      printf("\nHas desequipado el comodín.\n\n");
    } else {
      switch (opcion) {
        case 0:
          return;
        case 1:
          joker1(jugador);
          break;
        case 2:
          joker2(jugador);
          break;
        case 3:
          joker3(jugador);
          break;
      }
    }
  } else {
    puts("\nOpción inválida. Intente nuevamente.\n");
    presioneTeclaParaContinuar();
    seleccionarComodin(jugador);
    return;
  }
}

// ==================== MAIN ====================

int main() {

  HashMap *mapa = createMap(29);
  inicializarMapa(mapa);
  Jugador jugador_tutorial = {
      .cartas = {
          {1, 0, 0}, {13, 1, 0}, {11, 1, 0}, {12, 1, 0},
          {5, 1, 0}, {9, 0, 0}, {3, 3, 0}, {10, 1, 0}
      },
      .puntaje = 0,
      .comodin = 0
  };

  int estiloMazo = 1;
  cargarEstiloMazo(&estiloMazo);

  mostrarTitulo();
  mostrarChancho();
  puts("\n     Presione una tecla para jugar...");
  getchar();
  limpiarPantalla();

  float factor = 1.5;
  Nivel nivel;
  nivel.etapa = 1;
  nivel.pozo = 100;
  Jugador jugador;  
  jugador.comodin = 0;
  char opcion, opcion2, opcion3;
  bool derrota = false;
  do {
    mostrarMenu();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);
    switch (opcion) {
      case '1':
        do{
          derrota = jugar(jugador, nivel, mapa, estiloMazo);
          if(derrota) break;
          nivel.etapa++;
          nivel.pozo *= factor;
          limpiarPantalla();
          mensajeVictoria();
          scanf(" %c", &opcion2);
          if(opcion2 == 'n'){
            puts("Desea guardar la partida? (s/n)");
            scanf(" %c", &opcion3);
            if(opcion3 == 's')
              guardarPartida(nivel, factor, jugador, estiloMazo);
            nivel.etapa = 1;
            nivel.pozo = 100;
            break;
          }
        } while(!derrota);
        if(derrota){
          limpiarPantalla();
          mensajeFinal();
          reiniciarGuardado(&nivel, factor, estiloMazo);       
        }
        break;
      case '2':
        cargarPartida(&nivel, &jugador, &factor, &estiloMazo);
        break;
      case '3':
        mostrar_tutorial(jugador_tutorial, &estiloMazo);
        break;
      case '4':
        limpiarPantalla();
        configuracion(&factor, &nivel, &estiloMazo);
        break;
      case '5':
        seleccionarComodin(&jugador);
        break;
      case '6':
         printf("\nSaliendo del juego.\n");
         break;
      default:
          printf("\nOpción inválida. Por favor, ingrese una opción válida.\n");
      }
      presioneTeclaParaContinuar();
      limpiarPantalla();

  } while (opcion != '6');

  return 0;
}
