  #define CARTAS_C

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdbool.h>

  #define RESET "\033[0m"
  #define BLACK "\033[0;30m"
  #define RED "\033[0;31m"
  #define GREEN "\033[0;32m"
  #define YELLOW "\033[0;33m"
  #define BLUE "\033[0;34m"
  #define MAGENTA "\033[0;35m"
  #define CYAN "\033[0;36m"
  #define WHITE "\033[0;37m"
  #define BLACK_B "\033[1;30m"
  #define RED_B "\033[1;31m"
  #define GREEN_B "\033[1;32m"
  #define YELLOW_B "\033[1;33m"
  #define BLUE_B "\033[1;34m"
  #define MAGENTA_B "\033[1;35m"
  #define CYAN_B "\033[1;36m"
  #define WHITE_B "\033[1;37m"
  #define BLACK_BG "\033[40m"
  #define RED_BG "\033[41m"
  #define GREEN_BG "\033[42m"
  #define YELLOW_BG "\033[43m"
  #define BLUE_BG "\033[44m"
  #define MAGENTA_BG "\033[45m"
  #define CYAN_BG "\033[46m"
  #define WHITE_BG "\033[47m"
  #define BOLD "\033[1m"
  #define UNDERLINE "\033[4m"





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

  // ============================================================
  // ========================= CARTAS ===========================
  // ============================================================

  char* palo_to_char(int palo) {
    switch(palo) {
      case 0: return "♥";
      case 1: return "♦";
      case 2: return "♣";
      case 3: return "♠";
      default: return " ";
    }
  }

  char* numero_to_char(char numero) {
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

  void mostrarComodin(Jugador jugador) {
    printf(BLUE"  -----------------------------------------------------------------\n"RESET);
    switch(jugador.comodin) {
      case 1:
        printf(BLUE"  │"RESET);
        printf("                  Sir Jester, the Knight of Misrule              ");
        printf(BLUE"│\n"RESET);
        break;
      case 2:
        printf(BLUE"  │"RESET);
        printf("                 Amenhotep, the king of the desert               ");
        printf(BLUE"│\n"RESET);
        break;
      case 3:
        printf(BLUE"  │"RESET);
        printf("                             Joker C                             ");
        printf(BLUE"│\n"RESET);
        break;
      default:
        printf(BLUE"  │"RESET);
        printf("                     !Sin comodín activo!                      ");
        printf(BLUE"│\n"RESET);
        break;
    }                      
    printf(BLUE"  -----------------------------------------------------------------\n"RESET);
  }

  void linea1(Carta *cartas, int cantidad) {
    printf("  ");
    for(int i = 0; i < cantidad; i++){
      i == cantidad - 1? printf(".-------.\n  "):printf(".-------");
    }
    for (int i = 0 ; i < cantidad; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      char *numero = numero_to_char(cartas[i].numero);
      if (cartas[i].numero == 1) {
        if (cartas[i].palo == 0) {
          printf("|%s%-2s     ", numero, figura);
        } else if (cartas[i].palo == 1) {
          printf("|%s%-2s ∧   ", numero, figura);
        } else if (cartas[i].palo == 2) {
          printf("|%s%-2s _   ", numero, figura);
        } else {
          printf("|%s%-2s .   ", numero, figura);
        }
      } else if (cartas[i].numero == 10) {
        printf("|%s%-2s  %s ", numero, figura , figura);
      } else if (cartas[i].numero == 11) {
        if (cartas[i].palo == 0) {
          printf("|%s /~|_ ", numero);
        } else if (cartas[i].palo == 1) {
          printf("|%s |≡\\_ ", numero);
        } else if (cartas[i].palo == 2) {
          printf("|%s (-)_ ", numero);
        } else {
          printf("|%s {╬}_ ", numero);
        }
      } else if (cartas[i].numero == 12) {
        if (cartas[i].palo == 0) {
          printf("|%s |~~~|", numero);
        } else if (cartas[i].palo == 1) {
          printf("|%s |≡≡≡|", numero);
        } else if (cartas[i].palo == 2) {
          printf("|%s (---)", numero);
        } else {
          printf("|%s {║║║}", numero);
        }
      } else if (cartas[i].numero == 13) {
        if (cartas[i].palo == 0) {
          printf("|%s |%%°%%|", numero);
        } else if (cartas[i].palo == 1) {
          printf("|%s /\\|/\\", numero);
        } else if (cartas[i].palo == 2) {
          printf("|%s ()·()", numero);
        } else {
          printf("|%s [╠╦╣]", numero);
        }
      } else {
        printf("|%s%-2s     ", numero, figura);
      }
    }
    printf("|\n");
  }

  void linea2(Carta *cartas, int cantidad) {
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      if (cartas[i].numero == 1) {
        if (cartas[i].palo == 0) {
          printf("| /\\ /\\ ");
        } else if (cartas[i].palo == 1) {
          printf("|  / \\  ");
        } else if (cartas[i].palo == 2) {
          printf("|  ( )  ");
        } else {
          printf("|  / \\  ");
        }
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
      } else if (cartas[i].numero == 11) {
        if (cartas[i].palo == 0) {
          printf("|%s %%*\\`.", figura);
        } else if (cartas[i].palo == 1) {
          printf("|%s (o\\  ", figura);
        } else if (cartas[i].palo == 2) {
          printf("|%s |o`, ", figura);
        } else {
          printf("|%s ! -\\ ", figura);
        }
      } else if (cartas[i].numero == 12) {
        if (cartas[i].palo == 0) {
          printf("|%s %%*,*%%", figura);
        } else if (cartas[i].palo == 1) {
          printf("|%s |o.o|", figura);
        } else if (cartas[i].palo == 2) {
          printf("|%s /o,o\\", figura);
        } else {
          printf("|%s \\- -/", figura);
        }
      } else if (cartas[i].numero == 13) {
        if (cartas[i].palo == 0) {
          printf("|%s #*.*#", figura);
        } else if (cartas[i].palo == 1) {
          printf("|%s │0,0│", figura);
        } else if (cartas[i].palo == 2) {
          printf("|%s /°-°\\", figura);
        } else {
          printf("|%s \\· ·/", figura);
        }
      } else {
        printf("|       ");
      }
    }
    printf("|\n");
  }

  void linea3(Carta *cartas, int cantidad) {
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      if (cartas[i].numero == 1) {
        if (cartas[i].palo == 0) {
          printf("| \\ ˇ / ");
        } else if (cartas[i].palo == 1) {
          printf("| (   ) ");
        } else if (cartas[i].palo == 2) {
          printf("| (_X_) ");
        } else {
          printf("| (_,_) ");
        }
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
      } else if (cartas[i].numero == 11) {
        if (cartas[i].palo == 0) {
          printf("| %% <~  ");
        } else if (cartas[i].palo == 1) {
          printf("|  ! \\l ");
        } else if (cartas[i].palo == 2) {
          printf("|  | -| ");
        } else {
          printf("|  \\ -! ");
        }
      } else if (cartas[i].numero == 12) {
        if (cartas[i].palo == 0) {
          printf("|  \\_o_/");
        } else if (cartas[i].palo == 1) {
          printf("|   \\v/ ");
        } else if (cartas[i].palo == 2) {
          printf("|  \\_-_/");
        } else {
          printf("|   |-| ");
        }
      } else if (cartas[i].numero == 13) {
        if (cartas[i].palo == 0) {
          printf("|  └┬-┬┘");
        } else if (cartas[i].palo == 1) {
          printf("|   \\¤/ ");
        } else if (cartas[i].palo == 2) {
          printf("|  \\-~-/");
        } else {
          printf("|   ├-┤ ");
        }
      } else {
        printf("|       ");
      }
    }
    printf("|\n");
  }

  void linea4(Carta *cartas, int cantidad) {
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      if (cartas[i].numero == 1) {
        if (cartas[i].palo == 0) {
          printf("|  \\ /  ");
        } else if (cartas[i].palo == 1) {
          printf("|  \\ /  ");
        } else if (cartas[i].palo == 2) {
          printf("|   Y   ");
        } else {
          printf("|   I   ");
        }
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
      } else if (cartas[i].numero == 11) {
        if (cartas[i].palo == 0) {
          printf("| %%%%/%%%% ");
        } else if (cartas[i].palo == 1) {
          printf("| ^^Xvv ");
        } else if (cartas[i].palo == 2) {
          printf("|=~)+(_=");
        } else {
          printf("| ',\\', ");
        }
      } else if (cartas[i].numero == 12) {
        if (cartas[i].palo == 0) {
          printf("|  =<*>=");
        } else if (cartas[i].palo == 1) {
          printf("|  XXOXX");
        } else if (cartas[i].palo == 2) {
          printf("|  ~+_-~");
        } else {
          printf("|  I %% I");
        }
      } else if (cartas[i].numero == 13) {
        if (cartas[i].palo == 0) {
          printf("|  *<=>*");
        } else if (cartas[i].palo == 1) {
          printf("|  xXxXx");
        } else if (cartas[i].palo == 2) {
          printf("|  «×_×»");
        } else {
          printf("|  j ┼ i");
        }
      } else {
        printf("|       ");
      }
    }
    printf("|\n");
  }

  void linea5(Carta *cartas, int cantidad) {
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      char *numero = numero_to_char(cartas[i].numero);
      if (cartas[i].numero == 1) {
        if (cartas[i].palo == 0) {
          printf("|   ˇ %s%s", figura, numero);
        } else if (cartas[i].palo == 1) {
          printf("|   v %s%s", figura, numero);
        } else if (cartas[i].palo == 2) {
          printf("|     %s%s", figura, numero);
        } else {
          printf("|     %s%s", figura, numero);
        }
      } else if (cartas[i].numero == 10) {
        printf("| %s  %s%s", figura, figura, numero);
      } else if (cartas[i].numero == 11) {
        if (cartas[i].palo == 0) {
          printf("|  _> %s%s", figura, numero);
        } else if (cartas[i].palo == 1) {
          printf("| l\\I %s%s", figura, numero);
        } else if (cartas[i].palo == 2) {
          printf("|  |- %s%s", figura, numero);
        } else {
          printf("| I-\\ %s%s", figura, numero);
        }
      } else if (cartas[i].numero == 12) {
        if (cartas[i].palo == 0) {
          printf("| /~o %s%s", figura, numero);
        } else if (cartas[i].palo == 1) {
          printf("|  /^ %s%s", figura, numero);
        } else if (cartas[i].palo == 2) {
          printf("| /~- %s%s", figura, numero);
        } else {
          printf("|  |- %s%s", figura, numero);
        }
      } else if (cartas[i].numero == 13) {
        if (cartas[i].palo == 0) {
          printf("| |~o %s%s", figura, numero);
        } else if (cartas[i].palo == 1) {
          printf("|  (^ %s%s", figura, numero);
        } else if (cartas[i].palo == 2) {
          printf("| /~+ %s%s", figura, numero);
        } else {
          printf("|  ¦─ %s%s", figura, numero);
        }
      } else {
        printf("|     %s%s", figura, numero);
      }
    }
    printf("|\n");

    printf("  `");
    for(int i = 0; i < cantidad; i++){
      i == cantidad - 1?printf("-------´\n  "):printf("-------^");
    }
  }

  void mostrar_cartas(Carta *cartas, int cantidad) {

    linea1(cartas, cantidad);

    linea2(cartas, cantidad);

    linea3(cartas, cantidad);

    linea4(cartas, cantidad);

    linea5(cartas, cantidad);

    for (int i = 1 ; i <= cantidad ; i++){
      if (i == 1) printf("%5d", i);
      else printf("%8d", i);
    }
    printf("\n\n");
  }

  void mostrar_cartas_dos(Carta *cartas, int cantidad) {

    printf(BLUE"  ");
    for(int i = 0 ; i < cantidad ; i++)
      printf(".-------");
    // Línea 1
    printf(".\n  ");
    for (int i = 0 ; i < cantidad; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      char *numero = numero_to_char(cartas[i].numero);
      printf(BLUE"|"RESET);
      printf("%-2s  ", numero);
      if (figura == "♥" || figura == "♦") {
        printf(RED"%-2s  "RESET, figura);
      } else if (figura == "♠" || figura == "♣") {
        printf(BLACK"%-2s  "RESET, figura);
      }
    }
    printf(BLUE"|\n"RESET);

    // Línea 2
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      printf(BLUE"|"RESET);
        if (figura == "♥" || figura == "♦") {
          printf(RED"   %s%s  "RESET, figura, figura);
        } else if (figura == "♠" || figura == "♣") {
          printf(BLACK"   %s%s  "RESET, figura, figura);
      }
    }
    printf(BLUE"|\n"RESET);

    // Línea 3
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      printf(BLUE"|"RESET);
      if (figura == "♥" || figura == "♦") {
        printf(RED"  %s%s%s  "RESET, figura, figura, figura);
      } else if (figura == "♠" || figura == "♣") {
        printf(BLACK"  %s%s%s  "RESET, figura, figura, figura);
      }
    }
    printf(BLUE"|\n"RESET);

    // Línea 4 
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      printf(BLUE"|"RESET);
      if (figura == "♥" || figura == "♦") {
        printf(RED"  %s%s   "RESET, figura, figura);
      } else if (figura == "♠" || figura == "♣") {
        printf(BLACK"  %s%s   "RESET, figura, figura);
      }
    }
    printf(BLUE"|\n"RESET);

    // Línea 5
    printf("  ");
    for (int i = 0 ; i < cantidad ; i++) {
      char *figura = palo_to_char(cartas[i].palo);
      char *numero = numero_to_char(cartas[i].numero);
      printf(BLUE"|"RESET);
      if (figura == "♥" || figura == "♦") {
        printf(RED"  %s  "RESET, figura);
      } else if (figura == "♠" || figura == "♣") {
        printf(BLACK"  %s  "RESET, figura);
      }
      printf("%-2s", numero);
    }
    printf(BLUE"|\n"RESET);

    printf(BLUE"  `");
    for(int i  = 0; i < cantidad; i++){
      i == cantidad - 1?printf("-------´\n  "RESET):printf("-------^");
    }
    for (int i = 1 ; i <= cantidad ; i++) {
        if (i == 1) printf("%5d", i);
        else printf("%8d", i);
    }
    printf("\n\n");
  }

  // ============================================================
  // ========================== JOKERS ==========================
  // ============================================================

  void joker1(Jugador *jugador) {
    limpiarPantalla();
    printf("\n");
    printf("   ================= Sir Jester, the Knight of Misrule =================\n\n");
    printf("  En la era moderna, tener a Sir Jester activo otorga un total de 99 puntos\n");
    printf(" adicionales, recordando siempre que la alegría y el valor pueden cambiar el\n");
    printf("   destino, tal como lo hizo el caballero del desorden en tiempos antiguos.\n\n");

    printf("                     ____________________________\n");
    printf("                     |                          |\n");
    printf("                     |   ,^.                    |\n");
    printf("                     |   |||                    |\n");
    printf("                     |   |||       _T_          |\n");
    printf("                     |   |||   .-.[:|:].-.      |\n");
    printf("                     |   ===_ /\\|  '\"'  |/      |\n");
    printf("                     |    E]_|\\/ \\--|-|'''''|   |\n");
    printf("                     |    O  `'  '=[:]| A   |   |\n");
    printf("                     |           /\"\"\"\"|   P |   |\n");
    printf("                     |          /\"\"\"\"\".`.__.'   |\n");
    printf("                     |         []\"/\"\"\\[]        |\n");
    printf("                     |         | \\     / |      |\n");
    printf("                     |         | |     | |      |\n");
    printf("                     |       <\\\\\\)     (///>    |\n");
    printf("                     |                          |\n");
    printf("                     |__________________________|\n\n");

    // CONDICIÓN LOGICA PARA PREGUNTAR SI ESTÁ DESBLOQUEADO O NO:
    printf("\n   Para desbloquear a Sir Jester, el Caballero del Desorden...\n");

    char opcion[50];
    printf("\n   ¿Desea activar a Sir Jester? ");
    printf(GREEN"(S/N): "RESET);
    scanf(" %[^\n]s", opcion);
    if (strcmp(opcion, "S") == 0 || strcmp(opcion, "s") == 0) {
      printf("\n   ¡Has activado a Sir Jester!\n");
      jugador->comodin = 1;
    } else if (strcmp(opcion, "N") == 0 || strcmp(opcion, "n") == 0) {
      printf("\n   ¡No has activado a Sir Jester!\n\n");
      return;
    } else {
      printf("\n   Opción inválida.\n");
    }
    printf("\n");
  }

  void joker2(Jugador *jugador) {
    limpiarPantalla();
    printf("\n");
    printf("  ================= Amenhotep, the king of the desert =================\n\n");
    printf("    Aquellos que tienen la suerte de obtener a Amenhotep en su mazo,\n");
    printf("   se les permitirá realizar dos jugadas adicionales durante cada nivel,\n");
    printf("replicando el poder del faraón y potencialmente cambiando el curso del juego.\n\n");

    printf("                     ____________________________\n");
    printf("                     |                          |\n");
    printf("                     |                      ..  |\n");
    printf("                     |   ..                 /\\. |\n");
    printf("                     |   /\\.    _-_        /:_\\/|\n");
    printf("                     |  /:_\\/ /'. .'\\ ___ /__:_\\|\n");
    printf("                     |       /(|`/ !)\\  /:__:___|\n");
    printf("                     |      |  \\ = /  |/ / /\\   |\n");
    printf("                     |       `  ---  ./ / / /\\  |\n");
    printf("                     |      /--- -----\\/ / / /  |\n");
    printf("                     |     /---  ----- `/ / /   |\n");
    printf("                     |   _/--- __ _/  ' `/ /    |\n");
    printf("                     | /     /XXX/     ! `/     |\n");
    printf("                     ||_|_|_|XXX|_|_|_'|_/      |\n");
    printf("                     |                          |\n");
    printf("                     |                          |\n");
    printf("                     |__________________________|\n\n");

    // CONDICIÓN LOGICA PARA PREGUNTAR SI ESTÁ DESBLOQUEADO O NO:
    printf("\n   Para desbloquear a Amenhotep, el rey del decierto...\n");

    char opcion[50];
    printf("\n   ¿Desea activar a Amenhotep? ");
    printf(GREEN"(S/N): "RESET);
    scanf(" %[^\n]s", opcion);
    if (strcmp(opcion, "S") == 0 || strcmp(opcion, "s") == 0) {
      printf("\n   ¡Has activado a Amenhotep!\n");
      jugador->comodin = 2;
    } else if (strcmp(opcion, "N") == 0 || strcmp(opcion, "n") == 0) {
      printf("\n   ¡No has activado a Amenhotep!\n\n");
      return;
    } else {
      printf("\n   Opción inválida.\n");
    }
    printf("\n");
  }

  void joker3(Jugador *jugador) {

  }



  // ============================================================
  // ============================================================
  // ============================================================

  void mostrarTitulo(){
    puts(BLUE"\n========================================");
    printf(BLACK"           ♠♣");
    printf(RED"♦♥ "RESET); 
    printf("Pokern't ");
    printf(RED"♥♦");
    printf(BLACK"♣♠ \n");
    puts(BLUE"======================================== \n"RESET);
  }

  void mostrarChancho(){
    printf(RED_B"              ▄█▄▄▄▄▄▄▄   ▄  \n");
    printf("             █▀██▀▄▄▀███▄▐ ▌ \n");
    printf("            ████▌█▌▐█▐███▄▀▄ \n");
    printf("             ████▄▀▀▄████    \n");
    printf("              ▀█▀▀▀▀▀▀█▀     \n");
    printf(CYAN_B"          ▀█████████████████▀\n");
    printf("           █               █ \n");
    printf("           █               █ \n");
    printf("           █               █ \n"RESET);
  }

  void mensajeVictoria(){
    puts(BLUE"========================================");
    printf(BLACK"           ♠♣");
    printf(RED"♦♥ "RESET);
    printf("VICTORIA ");
    printf(RED"♥♦");
    printf(BLACK"♣♠ \n");
    puts(BLUE"========================================"RESET);
    mostrarChancho();
    puts("\nDesea continuar al siguiente nivel? (s/n)");
  }

  void mensajeFinal(){
    puts(BLUE"==========================================================");
    printf(BLACK"                   ♠♣");
    printf(RED"♦♥ "RESET);
    printf("FIN DEL JUEGO");
    printf(RED"♥♦");
    printf(BLACK"♣♠ \n");
    puts(BLUE"=========================================================="RESET);
  }

  void mensajeEstrategias(Jugador jugador_tutorial , int mazo){
    printf("Controles Básicos:\n");
    printf("1. Selecciona hasta 5 cartas para jugar.\n");
    printf("2. Ordena tu mano por valores o por palo. Así es más fácil ver las combinaciones!\n");
    printf("3. Descarta cartas de tu mano que no te sirvan ahora.\n\n");

    limpiarPantalla();
    printf("Mesa de Juego:\n");

    printf(BLUE"================================================================\n"RESET);
    puts("Puntaje = 0                              Pozo = 100\n");
    puts("                                         Jugadas: 0 / 5\n");
    puts("Mano:                                    Descartes: 0 / 3\n");
    if (mazo == 1) mostrar_cartas(jugador_tutorial.cartas, 8);
    else if (mazo == 2) mostrar_cartas_dos(jugador_tutorial.cartas, 8);
    
    //puts(".-------.-------.-------.-------.-------.-------.-------.-------.");
    //puts("|7♠     |5♥     |6♦     |6♠     |Q♥     |9♦     |10♣  ♣ |8♦     |");
    //puts("|  ♠ ♠  |  ♥ ♥  |  ♦ ♦  |  ♠ ♠  |       | ♦ ♦ ♦ | ♣ ♣ ♣ | ♦ ♦ ♦ |");
    //puts("| ♠ ♠ ♠ |   ♥   |  ♦ ♦  |  ♠ ♠  |       | ♦ ♦ ♦ |  ♣ ♣  |  ♦ ♦  |");
    //puts("|  ♠ ♠  |  ♥ ♥  |  ♦ ♦  |  ♠ ♠  |       | ♦ ♦ ♦ | ♣ ♣ ♣ | ♦ ♦ ♦ |");
    //puts("|     ♠7|     ♥5|     ♦6|     ♠6|     ♥Q|     ♦9| ♣  ♣10|     ♦8|");
    //puts("`-------^-------^-------^-------^-------^-------^-------^-------´");
    //puts("    1       2       3       4       5       6       7       8");

    printf(BLUE"================================================================\n"RESET);

    puts(" Elija una opcion: ");
    puts("  1) Elegir cartas");
    puts("  2) Ordenar mano por palo");
    puts("  3) Ordenar mano por valor");
    puts("  4) Descartar cartas\n\n");
    puts(BLUE"==================================================================\n"RESET);

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