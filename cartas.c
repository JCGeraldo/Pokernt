#define CARTAS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char numero; // 1 a 13
  int palo;  // 0-3 (0 es Corazones, 1 es Diamantes, 2 es Tréboles, 3 es Picas)
  int puntaje;
} Carta;

//       .------.------.------.------.
//       |A♥  ♥ |A /\  |A _   |A .   |
//       |♥ ♥♥ ♥| /  \ | ( )  | / \  |
//       | ♥  ♥ | \  / |(_x_) |(_,_) |
//       |  ♥♥ A|  \/ A|  Y  A|  I  A|  
//       `------^------^------'------'
//       .------.------.------.------.------.------.------.------.
//       |A_  _ |A_  _ |A /\  |A /\  |A _   |A _   |A .   |A .   |
//       |( \/ )|( \/ )| /  \ | /  \ | ( )  | ( )  | / \  | / \  |
//       | \  / | \  / | \  / | \  / |(_x_) |(_x_) |(_,_) |(_,_) |
//       |  \/ A|  \/ A|  \/ A|  \/ A|  Y  A|  Y  A|  I  A|  I  A| 
//       `------^------^------^------^------^------^------^------´

//cora1 = "♥";
//diam1 = "♦";
//treb1 = "♣";
//pic1 = "♠";

char* palo_to_char(int palo) {
  switch(palo) {
    case 0: return "♥";
    case 1: return "♦";
    case 2: return "♣";
    case 3: return "♠";
    default: return " ";
  }
}

const char* numero_to_char(char numero) {
  switch(numero) {
    case 1: return "A";
    case 11: return "J";
    case 12: return "Q";
    case 13: return "K";
    default: {
      static char num[6];
      snprintf(num, sizeof(num), "%d", numero);
      return num;
    }
  }
}

void linea1(Carta *cartas, int cantidad) {
  printf(".-------.-------.-------.-------.-------.-------.-------.-------.\n");
  for (int i = 0 ; i < cantidad; i++) {
    if (cartas[i].numero == 10) {
      printf("|%s%-2s  %s ", numero_to_char(cartas[i].numero), palo_to_char(cartas[i].palo) , palo_to_char(cartas[i].palo));
    } else {
      printf("|%s%-2s     ", numero_to_char(cartas[i].numero), palo_to_char(cartas[i].palo));
    }
  }
  printf("|\n");
}

void linea2(Carta *cartas, int cantidad) {
  for (int i = 0 ; i < cantidad ; i++) {
    char *figura = palo_to_char(cartas[i].palo);
    if (cartas[i].numero == 1) {
      printf("|       ");
    } else if (cartas[i].numero == 2) {
      printf("|   %s   ", figura);
    } else if (cartas[i].numero == 3) {
      printf("|   %s   ", figura);
    } else if (cartas[i].numero == 4) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 5) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 6) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 7) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 8) {
      printf("| %s %s %s ", figura, figura, figura);
    } else if (cartas[i].numero == 9) {
      printf("| %s %s %s ", figura, figura, figura);
    } else if (cartas[i].numero == 10) {
      printf("| %s %s %s ", figura, figura, figura);
    } else {
      printf("|       ");
    }
  }
  printf("|\n");
}

void linea3(Carta *cartas, int cantidad) {
  for (int i = 0 ; i < cantidad ; i++) {
    char *figura = palo_to_char(cartas[i].palo);
    if (cartas[i].numero == 1) {
      printf("|       ");
    } else if (cartas[i].numero == 2) {
      printf("|       ");
    } else if (cartas[i].numero == 3) {
      printf("|   %s   ", figura);
    } else if (cartas[i].numero == 4) {
      printf("|       ");
    } else if (cartas[i].numero == 5) {
      printf("|   %s   ", figura);
    } else if (cartas[i].numero == 6) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 7) {
      printf("| %s %s %s ", figura, figura, figura);
    } else if (cartas[i].numero == 8) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 9) {
      printf("| %s %s %s ", figura, figura, figura);
    } else if (cartas[i].numero == 10) {
      printf("|  %s %s  ", figura, figura);
    } else {
      printf("|       ");
    }
  }
  printf("|\n");
}

void linea4(Carta *cartas, int cantidad) {
  for (int i = 0 ; i < cantidad ; i++) {
    char *figura = palo_to_char(cartas[i].palo);
    if (cartas[i].numero == 1) {
      printf("|       ");
    } else if (cartas[i].numero == 2) {
      printf("|   %s   ", figura);
    } else if (cartas[i].numero == 3) {
      printf("|   %s   ", figura);
    } else if (cartas[i].numero == 4) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 5) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 6) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 7) {
      printf("|  %s %s  ", figura, figura);
    } else if (cartas[i].numero == 8) {
      printf("| %s %s %s ", figura, figura, figura);
    } else if (cartas[i].numero == 9) {
      printf("| %s %s %s ", figura, figura, figura);
    } else if (cartas[i].numero == 10) {
      printf("| %s %s %s ", figura, figura, figura);
    } else {
      printf("|       ");
    }
  }
  printf("|\n");
}

void linea5(Carta *cartas, int cantidad) {
  for (int i = 0 ; i < cantidad ; i++) {
    if (cartas[i].numero == 10) {
      printf("| %s  %s%s", palo_to_char(cartas[i].palo), palo_to_char(cartas[i].palo), numero_to_char(cartas[i].numero));
    } else {
      printf("|     %s%s", palo_to_char(cartas[i].palo), numero_to_char(cartas[i].numero));
    }
  }
  printf("|\n");

  printf("`-------^-------^-------^-------^-------^-------^-------^-------´\n");
}

void mostrar_cartas(Carta *cartas, int cantidad) {

  linea1(cartas, cantidad);

  linea2(cartas, cantidad);

  linea3(cartas, cantidad);

  linea4(cartas, cantidad);

  linea5(cartas, cantidad);
    
  for (int i = 1 ; i <= cantidad ; i++){
    if (i == 1)printf("%5d", i);
    else printf("%8d", i);
  }
  printf("\n\n");
}

void mostrarChancho(){
  printf("          ───▄█▄▄▄▄▄▄▄───▄──\n");
  printf("          ──█▀██▀▄▄▀███▄▐─▌─\n");
  printf("          ─████▌█▌▐█▐███▄▀▄─\n");
  printf("          ──████▄▀▀▄████────\n");
  printf("          ───▀█▀▀▀▀▀▀█▀─────\n");
  printf("         ▀█████████████████▀\n");
  printf("          █               █ \n");
  printf("          █               █ \n");
  printf("          █               █ \n");
}
void mensajeVictoria(){
  puts("====================================");
  puts("         ♠♣♦♥  VICTORIA  ♥♦♣♠");
  puts("====================================");
  mostrarChancho();
  puts("\nPresione para continuar al siguiente nivel...");
  getchar();
  limpiarPantalla();
}
void mensajeFinal(){
  puts("==========================================================");
  puts("                   ♠♣♦♥  FIN DEL JUEGO  ♥♦♣♠");
  puts("==========================================================");
}

void mensajeEstrategias(){
  printf("Controles Básicos:\n");
  printf("1. Selecciona una carta para jugar.\n");
  printf("2. Juega una carta seleccionada para formar combinaciones.\n");
  printf("3. Pasa el turno cuando no puedes jugar una carta.\n\n");

  printf("Interfaz de Usuario:\n");
  printf("1. La mano del jugador muestra las cartas que tienes.\n");
  printf("2. La mesa de juego muestra las cartas jugadas.\n");
  printf("3. Los puntajes muestran cuántos puntos tiene cada jugador.\n\n");

  printf("Estrategia Básica:\n");
  printf("1. Intenta formar combinaciones ganadoras como pares o tríos.\n");
  printf("2. Prioriza cartas altas para ganar más puntos.\n\n");

  printf("¡Buena suerte y diviértete jugando!\n");
}