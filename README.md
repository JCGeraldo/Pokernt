
## Pokern´t
## Descripción:

 “Pokern´t” es un juego en solitario, donde el objetivo del jugador es superar cada nivel alcanzando ciertas cuotas mediante la formación de manos de poker. Cada mano de poker otorgará una cierta cantidad de puntaje según la dificultad de la formación, de esta manera, el jugador tendrá que jugar estratégicamente para definir cuál es la mejor combinación para alcanzar dicha cuota. Finalmente, cada nivel será más exigente que el anterior, el puntaje requerido irá aumentando a medida que el jugador vaya ganando experiencia, lo cual, se traduce en un mayor desafío.

## Cómo compilar y ejecutar
Para mayor simplicidad al momento de probar y ejecutar el juego se utilizará la plataforma [Repl.it](http://repl.it/), los pasos a seguir son:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "Create Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/JCGeraldo/Pokernt`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Configure el comando de compilación con `gcc tdas/*.c Pokernt.c -Wno-unused-result -o Pokernt` y el comando run con `./Pokernt`.
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades
## Funcionando correctamente:
* `Iniciar Juego`: Esta opción permite al jugador comenzar una nueva partida. Al seleccionarla, el juego iniciará el primer nivel para así progresar a niveles más avanzados. Este modo es el núcleo de la experiencia de juego, diseñado para ofrecer desafíos crecientes en un entorno solitario.
* `Guardar Partida`: Esta opción permite al jugador guardar su partida y así no perder sus avances en el juego. Cada vez que inicie el juego, se va a cargar su última partida.
* `Tutorial`: El tutorial está diseñado para introducir a los nuevos jugadores a las mecánicas básicas del juego. Aquí, se explican las reglas del póker que son relevantes para "Pokern't", así como las estrategias básicas para formar manos ganadoras. 
* `Configuración`: Esta opción permite al jugador seleccionar el nivel de dificultad del juego. La configuración de la dificultad ajusta parámetros como la cantidad de puntos necesarios para superar un nivel o la disponibilidad de descartes.
* `Comodín`: Desde esta opción se puede seleccionar una carta comodín la cual otorgará una ventaja al jugador durante la partida, esta carta especial puede proporcionar ventajas específicas, como aumentar la puntuación de una mano particular, permitir más descartes,  entre otras.
* `Salir`: La opción "Salir" permite al jugador finalizar la aplicación.

## Problemas conocidos:
* El programa no es capaz de soportar ingresos inválidos en las opciones que superen los 50 caracteres.

## A mejorar:
* Darle la posibilidad al jugador de cancelar una opcion luego de ser elegida durante la partida.
* Mejorar la interacción exclusiva a través del teclado.

## Ejemplo de uso:
**Paso 1: Jugar**
Se comienza a través de la primera opción, jugar!!
````
Opción seleccionada: 1) Jugar

  -----------------------------------------------------------------
  │                     !Sin comodín activo!                      │
  -----------------------------------------------------------------

  Puntaje = 0                              Pozo = 100

  Nivel 1                                  Jugadas: 0 / 5

  Mano:                                    Descartes: 0 / 3

  .-------.-------.-------.-------.-------.-------.-------.-------.
  |Q   ♥  |3   ♥  |Q   ♦  |3   ♦  |J   ♣  |9   ♠  |5   ♣  |J   ♥  |
  |   ♥♥  |   ♥♥  |   ♦♦  |   ♦♦  |   ♣♣  |   ♠♠  |   ♣♣  |   ♥♥  |
  |  ♥♥♥  |  ♥♥♥  |  ♦♦♦  |  ♦♦♦  |  ♣♣♣  |  ♠♠♠  |  ♣♣♣  |  ♥♥♥  |
  |  ♥♥   |  ♥♥   |  ♦♦   |  ♦♦   |  ♣♣   |  ♠♠   |  ♣♣   |  ♥♥   |
  |  ♥  Q |  ♥  3 |  ♦  Q |  ♦  3 |  ♣  J |  ♠  9 |  ♣  5 |  ♥  J |
  `-------^-------^-------^-------^-------^-------^-------^-------
      1       2       3       4       5       6       7       8

 ==================================================================

  Elija una opcion: 
  1) Elegir cartas
  2) Ordenar mano por palo
  3) Ordenar mano por valor
  4) Descartar cartas
````
En el momento de que se selecccione, el jugador comenzará en el nivel 1, se le mostraran las cartas elegidas al azar y luego se le presentaran las opciones.

**Paso 2: Seleccion cartas**

Luego de observar las cartas, el jugador puede elegir tanto jugar una combinación, ordenar mano por palo, ordenar mano por valor o finalmente, descartar cartas.
El jugador puede elegir hasta 5 cartas para jugar, o puede ingresar un cero para terminar la selección con menos cartas.
En este caso el jugador puede jugar un doble pareja!!
````
Opción seleccionada: 1) Elegir cartas

Ingrese el número de la carta que desea jugar (1-8): 1 
3
5
8
0
Cartas seleccionadas:
  .-------.-------.-------.-------.
  |J   ♥  |J   ♣  |Q   ♥  |Q   ♦  |
  |   ♥♥  |   ♣♣  |   ♥♥  |   ♦♦  |
  |  ♥♥♥  |  ♣♣♣  |  ♥♥♥  |  ♦♦♦  |
  |  ♥♥   |  ♣♣   |  ♥♥   |  ♦♦   |
  |  ♥  J |  ♣  J |  ♥  Q |  ♦  Q |
  `-------^-------^-------^-------´
      1       2       3       4

Doble pareja!
10 10 10 10 
Puntaje: 60
Multiplo: 2
Presione una tecla para continuar...

````
Una vez jugado la combinación, al jugador se le desplegará la combinacion jugada, su puntaje y el multiplo de este. Ya que el jugador obtuvo el puntaje necesario para pasar al siguiente nivel, se le desplegará un mensaje de victoria y se pregunta si el jugador desea pasar al siguiente nivel. En caso de que la respuesta sea negativa, se le pregunta al jugador si desea guardar la partida.

````
========================================
           ♠♣♦♥ VICTORIA ♥♦♣♠ 
========================================
              ▄█▄▄▄▄▄▄▄   ▄  
             █▀██▀▄▄▀███▄▐ ▌ 
            ████▌█▌▐█▐███▄▀▄ 
             ████▄▀▀▄████    
              ▀█▀▀▀▀▀▀█▀     
          ▀█████████████████▀
           █               █ 
           █               █ 
           █               █ 

Desea continuar al siguiente nivel? (s/n)
n
Desea guardar la partida? (s/n)
````
**Bonus: Descartar cartas**
El jugador durante la partida, tambien se le entrega la opción de descartar cartas. Las cartas elegidas serán eliminadas del mazo del jugador y se reemplazaran por nuevas elegidas al azar.

````
  -----------------------------------------------------------------
  │                     !Sin comodín activo!                      │
  -----------------------------------------------------------------

  Puntaje = 0                              Pozo = 100

  Nivel 1                                  Jugadas: 0 / 5

  Mano:                                    Descartes: 0 / 3

  .-------.-------.-------.-------.-------.-------.-------.-------.
  |3   ♦  |6   ♦  |7   ♠  |8   ♦  |2   ♥  |A   ♣  |J   ♦  |5   ♣  |
  |   ♦♦  |   ♦♦  |   ♠♠  |   ♦♦  |   ♥♥  |   ♣♣  |   ♦♦  |   ♣♣  |
  |  ♦♦♦  |  ♦♦♦  |  ♠♠♠  |  ♦♦♦  |  ♥♥♥  |  ♣♣♣  |  ♦♦♦  |  ♣♣♣  |
  |  ♦♦   |  ♦♦   |  ♠♠   |  ♦♦   |  ♥♥   |  ♣♣   |  ♦♦   |  ♣♣   |
  |  ♦  3 |  ♦  6 |  ♠  7 |  ♦  8 |  ♥  2 |  ♣  A |  ♦  J |  ♣  5 |
  `-------^-------^-------^-------^-------^-------^-------^-------´
      1       2       3       4       5       6       7       8

 ==================================================================

  Elija una opcion: 
  1) Elegir cartas
  2) Ordenar mano por palo
  3) Ordenar mano por valor
  4) Descartar cartas
4
Ingrese el número de la carta que desea descartar (1-8): 1
2
3
4
5
````
Una vez descartadas las cartas, se actualizara el contador y las cartas.

````
  -----------------------------------------------------------------
  │                     !Sin comodín activo!                      │
  -----------------------------------------------------------------

  Puntaje = 0                              Pozo = 100

  Nivel 1                                  Jugadas: 0 / 5

  Mano:                                    Descartes: 1 / 3

  .-------.-------.-------.-------.-------.-------.-------.-------.
  |4   ♣  |J   ♣  |6   ♥  |Q   ♠  |A   ♦  |A   ♣  |J   ♦  |5   ♣  |
  |   ♣♣  |   ♣♣  |   ♥♥  |   ♠♠  |   ♦♦  |   ♣♣  |   ♦♦  |   ♣♣  |
  |  ♣♣♣  |  ♣♣♣  |  ♥♥♥  |  ♠♠♠  |  ♦♦♦  |  ♣♣♣  |  ♦♦♦  |  ♣♣♣  |
  |  ♣♣   |  ♣♣   |  ♥♥   |  ♠♠   |  ♦♦   |  ♣♣   |  ♦♦   |  ♣♣   |
  |  ♣  4 |  ♣  J |  ♥  6 |  ♠  Q |  ♦  A |  ♣  A |  ♦  J |  ♣  5 |
  `-------^-------^-------^-------^-------^-------^-------^-------´
      1       2       3       4       5       6       7       8

 ==================================================================

  Elija una opcion: 
  1) Elegir cartas
  2) Ordenar mano por palo
  3) Ordenar mano por valor
  4) Descartar cartas
````


