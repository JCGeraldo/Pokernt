#define CARTAS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

const char* palo_to_char(int palo) {
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

void mostrar_cartas(Carta *cartas, int cantidad) {

    printf(".------.------.------.------.------.------.------.------.\n");

    // Línea 1
    for (int i = 0 ; i < cantidad; i++) {
        printf("|%s%-2s    ", numero_to_char(cartas[i].numero), palo_to_char(cartas[i].palo));
    }
    printf("|\n");

    // Línea 2
    for (int i = 0 ; i < cantidad ; i++) {
        printf("|  %s%s  ", palo_to_char(cartas[i].palo), palo_to_char(cartas[i].palo));
    }
    printf("|\n");

    // Línea 3
    for (int i = 0 ; i < cantidad ; i++) {
        printf("|  %s%s  ", palo_to_char(cartas[i].palo), palo_to_char(cartas[i].palo));
    }
    printf("|\n");

    // Línea 4
    for (int i = 0 ; i < cantidad ; i++) {
        printf("|    %s%s", palo_to_char(cartas[i].palo), numero_to_char(cartas[i].numero));
    }
    printf("|\n");

    printf("`------^------^------^------^------^------^------^------´\n");
    for (int i = 1 ; i <= cantidad ; i++){
        if (i == 1)printf("%5d", i);
        else printf("%7d", i);
    }
    printf("\n\n");
}