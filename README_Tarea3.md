# Solución "El 8-puzzle"
Este código implementa un solucionador para el 8-puzzle utilizando diferentes métodos de búsqueda: 
* búsqueda en profundidad (DFS) 
* búsqueda en anchura (BFS)
* búsqueda de mejor primero (Best-First Search)

## Ejecución

Para probar este código siga estos pasos:
* Importe el repositorio desde su cuenta en repl.it
* Presione el botón **RUN** para ejecutar el código.

## Utilizando el programa

Al ejecutar el programa usted verá un menú como el siguiente:
```
========================================
     Escoge método de búsqueda
========================================
1) Búsqueda en Profundidad
2) Buscar en Anchura
3) Buscar Mejor Primero
4) Salir
Ingrese su opción: 
```
Ahora usted debe ingresar el número correspondiente al método de resolución que desea utilizar.

A continuación se detallan cada una de estas opciones.

## Ejemplos de Uso

<details>
<summary>Opción 1 - Búsqueda en Profundidad:</summary>
Esta opción realiza una búsqueda en profundidad para encontrar el estado objetivo, explora el espacio de búsqueda del 8-puzzle profundizando lo más posible en cada rama antes de retroceder y explorar otras ramas. Utiliza una pila para gestionar los estados pendientes de exploración, y busca de manera exhaustiva hasta encontrar el estado objetivo o hasta que se determinen que no hay más movimientos posibles dentro del límite de profundidad especificado.
     
Si selecciona esta opción, verá la resolución paso a paso de la siguiente forma:

```
Ingrese su opción: 1

Estado final encontrado.
Número de estados visitados: 176008
Movimientos: 20

Estado inicial:
x 1 2 
3 4 8 
6 5 7 

Paso 1:
1 x 2 
3 4 8 
6 5 7 

Paso 2:
1 4 2 
3 x 8 
6 5 7

...

Paso 20:
x 1 2 
3 4 5 
6 7 8 
```

**Es una técnica simple pero puede ser ineficiente en términos de tiempo y espacio, especialmente si el espacio de búsqueda es grande y las soluciones están profundamente anidadas.**

Para un estado inicial de mayor complejidad, esta opción no será capaz de obtener una solución como vemos en este ejemplo:

```
Estado inicial del puzzle:
8 x 6 
5 4 7 
2 3 1 

Ingrese su opción: 1

No se encontró un estado final.
Iteraciones: 424945

```
</details>

<details>
<summary>Opción 2 - Buscar en Anchura:</summary>
Esta opción realiza una búsqueda en anchura para encontrar el estado objetivo, explora el espacio de búsqueda del 8-puzzle nivel por nivel, utilizando una cola para gestionar los estados pendientes de exploración. Se empieza con el estado inicial y se exploran todos los estados adyacentes antes de pasar al siguiente nivel de estados. Este enfoque garantiza que la solución encontrada, si existe, es la de menor profundidad (el menor número de movimientos).

Si selecciona esta opción, verá la resolución paso a paso de la siguiente forma:

```
Ingrese su opción: 2

Estado final encontrado.
Número de estados visitados: 1962
Movimientos: 12

Estado inicial:
x 2 8 
1 3 4 
6 5 7 

Paso 1:
1 2 8 
x 3 4 
6 5 7 

Paso 2:
1 2 8 
3 x 4 
6 5 7

...

Paso 12:
x 1 2 
3 4 5 
6 7 8 
``` 
**Es una técnica completa y óptima, pero puede ser ineficiente en términos de memoria, ya que puede requerir almacenar un gran número de estados en la cola, especialmente en puzzles con soluciones profundas.**

Para un estado inicial con mayor complejidad, esta opción no será capaz de encontrar una solución en caso de que no se pueda llegar a ella en menos de 20 movimientos (niveles):

``` 
Estado inicial del puzzle:
8 x 6 
5 4 7 
2 3 1 

Ingrese su opción: 2

No se encontró un estado final, requiere más de 20 movimientos
Iteraciones: 424945
``` 
</details>

<details>
<summary>Opción 3 - Buscar Mejor Primero:</summary>
Esta opción realiza una búsqueda del mejor primero para encontrar el estado objetivo, explora el espacio de búsqueda del 8-puzzle seleccionando los estados basándose en una función de evaluación que estima cuán cerca está un estado del objetivo. Utiliza una cola de prioridad (Heap) para gestionar los estados, priorizando aquellos que parecen más prometedores.
     
Si selecciona esta opción, verá la resolución paso a paso de la siguiente forma:

```
Ingrese su opción: 3

Estado final encontrado.
Número de estados visitados: 25
Movimientos: 12

Estado inicial:
x 2 8 
1 3 4 
6 5 7 

Paso 1:
1 2 8 
x 3 4 
6 5 7 

Paso 2:
1 2 8 
3 x 4 
6 5 7

...

Paso 12:
x 1 2 
3 4 5 
6 7 8
```

**Este enfoque es más eficiente que las otras búsquedas a "ciegas" como lo son DFS y BFS debido a que este sigue un patron de búsqueda mejor establecido para guiar su búsqueda**

Al ser un metodo de gran consistencia, este no tiene un límite de pasos establecidos y es capaz de encontrar una solución para cualquier estado inicial (siempre que exista):

```
Ingrese su opción: 3

Estado final encontrado.
Número de estados visitados: 24278
Movimientos: 31

Estado inicial:
8 x 6 
5 4 7 
2 3 1 

Paso 1:
8 6 x 
5 4 7 
2 3 1 

Paso 2:
8 6 7 
5 4 x 
2 3 1 

...

Paso 31:
x 1 2 
3 4 5 
6 7 8 
```
</details>

<details>
<summary>Opción 4 - Salir:</summary>
Esta opción finaliza la ejecución del programa.
  
</details>


## Contribuciones
### Juan Geraldo:
* Diseño README.
* Implementación lógica de las siguientes funciones:
  - es_resoluble
  - get_adj_states
  - mostrarPasos
  - DSF
  - BSF
* Ajustes en carpetas tdas

### Ian Guerrero:
* Redacción README.
* Implementación lógica de las siguientes funciones:
  - is_final_state
  - best_first
* Comentarios y visualización de código

## Observaciones y Errores Conocidos
* La Función de Búsqueda en Profundidad es la más propensa a entregar resultados con alguna serie de bucles entre los pasos realizados.
