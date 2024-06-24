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

void mostrarTitulo(){
  puts("========================================");
  puts("         ♠♣♦♥  Pokern't  ♥♦♣♠");
  puts("========================================\n");
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
  printf("1. Selecciona hasta 5 cartas para jugar.\n");
  printf("2. Ordena tu mano por valores o por palo. Así es más fácil ver las combinaciones!\n");
  printf("3. Descarta cartas de tu mano que no te sirvan ahora.\n\n");

  limpiarPantalla();
  printf("Mesa de Juego:\n");

  puts("============================================================\n");
  puts("Puntaje = 0                              Pozo = 100\n\n");
  puts("                                         Jugadas: 0 / 5\n");
  puts("Mano:                                    Descartes: 0 / 3\n");
  puts(".-------.-------.-------.-------.-------.-------.-------.-------.");
  puts("|7♠     |5♥     |6♦     |6♠     |Q♥     |9♦     |10♣  ♣ |8♦     |");
  puts("|  ♠ ♠  |  ♥ ♥  |  ♦ ♦  |  ♠ ♠  |       | ♦ ♦ ♦ | ♣ ♣ ♣ | ♦ ♦ ♦ |");
  puts("| ♠ ♠ ♠ |   ♥   |  ♦ ♦  |  ♠ ♠  |       | ♦ ♦ ♦ |  ♣ ♣  |  ♦ ♦  |");
  puts("|  ♠ ♠  |  ♥ ♥  |  ♦ ♦  |  ♠ ♠  |       | ♦ ♦ ♦ | ♣ ♣ ♣ | ♦ ♦ ♦ |");
  puts("|     ♠7|     ♥5|     ♦6|     ♠6|     ♥Q|     ♦9| ♣  ♣10|     ♦8|");
  puts("`-------^-------^-------^-------^-------^-------^-------^-------´");
  puts("    1       2       3       4       5       6       7       8");

  puts("============================================================\n");

  puts("Elija una opcion: ");
  puts("  1) Elegir cartas");
  puts("  2) Ordenar mano por palo");
  puts("  3) Ordenar mano por valor");
  puts("  4) Descartar cartas\n\n");
  puts("============================================================\n\n");

  printf("1. La mano del jugador muestra las cartas que tienes.\n");
  printf("2. La mesa de juego muestra cuantas jugadas y descartes te quedan.\n");
  printf("3. Puntaje muestra cuántos puntos has acumulado en el nivel actual.\n");
  puts("4. El pozo indica tu meta de puntaje.\n");
  getchar();

  printf("Estrategia Básica:\n");
  printf("1. Intenta formar combinaciones ganadoras como pares o tríos.\n");
  printf("2. Prioriza cartas altas para ganar más puntos.\n");
  puts("3. Tienes jugadas limitadas. Haz que cuenten!\n");

  printf("¡Buena suerte y diviértete jugando!\n");
}