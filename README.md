# TDA Árbol binario de búsqueda (ABB)

Este tipo de dato abstracto es un árbol binario de búsqueda (ABB), con sus operaciones administrativas (creary destruir), e insertar, eliminar, buscar, mostrar la raiz y si el árbol esta vacio. También tenemos funciones para recorrer el árbol, de forma inorden, preorden o postorden.

Por último tenemos un iterador interno, donde se puede especificar que tipo de recorrido se quiere usar.

## Compilación y ejecución

### Compilar
    
Para poder ejecutarlo primero tenemos que compilarlo, esto lo hacemos con la siguiente linea
``` bash
gcc -g -Wall -Wconversion -Wtype-limits -pedantic -Werror -std=c99 -O0 *.c -o abb 
```
De esta manera todos los archivos .c se compilan con este TDA. También esta con la ayuda del makefile se puede compilar con la linea
``` bash
make build
```
    
### Ejecutar

Para ejecutarlo vamos a usar valgrind, esto lo hacemos con la siguiente linea
``` bash
valgrind --leak-check==full --track-origins=yes --show-reachable=yes ./abb
```
También con makefile podemos hacer lo mismo con la linea
``` bash
make valgrind
```


## Detalles de la implementación

### Funcion crear
Lo primero que hacemos es comprobar que la función de comparación que se nos pasa como parametro sea valida, no es necesario comprobar si la función de destrucción sea valida porque esta puede no existir, por lo que no es un problema que sea NULL.
Luego reservamos memoria en el heap y comprobamos que no haya dado un puntero valido, después asignamos las funciones al arbol creado y lo devolvemos.

### Funcion insertar
Lo primero que hacemos es comprobar que el árbol sea valido. Teniendo en cuenta que siempre se inserta una hoja en un árbol binario de búsqueda, entonces lo que hacemos es ir recorriendo el árbol, usando la función comparación vamos eligiendo si vamos para la rama izquierda o la rama derecha. Cuando ya no haya una rama para ir, esé será donde va a ir la hoja.

Reservamos memoria para crear un nodo más del árbol, le asignamos el elemento que va a guardar, y devolvemos el puntero de la nueva hoja.

### Funcion borrar
Lo primero que hacemos es comprobar que el árbol sea valido. Después de eso buscamos el elemento que queremos eliminar, si no esta el elemento podemos no hacer nada. En el caso de que lo encontremos, tenemos 3 posibilidades en las que nos podemos encontrar:

En el primer caso es que no tenga hijos el elemento a eliminar, entonces usamos el destructor (si lo tenemos) y lo reemplazamos por NULL en la rama que vinimos a buscarlo.
El segundo caso es que tenga un lo hijo el elemento a eliminar, entonces usamos el destructor (si lo tenemos) y lo reemplazamos con el hijo que tenía.
En el tercer caso es que tenga los dos hijo el elemento a eliminar, entonces usamos el destructor (si lo tenemos) y buscamos su reemplazo, en este caso, usamos el predecesor inorden, que es el mayor de la rama izquierda del elemento a eliminar y al predecesor le agregamos a su rama derecha, la rama derecha del elemento a eliminar.

### Funcion buscar
Lo primero que hacemos es comprobar que el árbol sea valido. Después comprobamos si el elemento en el que estamos es el que estamos búscando, si lo es devolvemos ese, sino vemos si el elemento que estamos buscando, usando la función de comparación, vamos a la rama derecha o la rama izquierda, y repetimos el proceso hasta llegar al elemento que buscamos o recorrer todo el árbol, y en ese caso devolvemos NULL que es la forma de indicar que no encontramos el elemento.

### Funcion recorrido
Lo primero, explicando que hacen, recorrer el árbol de forma inorden, preorden o postorden, y van guardando en un array los elementos que va encontrando dependiendo de la forma de recorrer.

En cualquier recorrido lo primero que hacemos es comprobar que el árbol sea valido y que el array sea valido

#### Recorrido inorden 
Lo principal es entender que el recorrido inorden, es la forma de recorrer el árbol primero yendo por la rama izquierda, después (en este caso) guardando el elemento actual y por último ir por la rama derecha.

Lo hacemos de forma recursiva, entonces primero llamamos a la función mandando la rama izquierda, después guardamos en el array el valor que tenemos en el nodo actual, en el caso de que lleguemos al tome del array devolvemos ahí, sino llamamos a la función mandando la rama derecha.

#### Recorrido preorden 
De nuevo, lo primero es entender que el recorrido preorden, es la forma de recorrer el árbol primero (en este caso) guardando el elemento actual, después yendo por la rama izquierda y por último vamos por la rama derecha.

El procedimiento es igual que el recorrido inorden pero cambiando el orden en el que se hacen las llamadas recursivas.

#### Recorrido postorden 
Sorpresa sorpresa, lo primero es entender que el recorrido postorden, es la forma de recorrer el árbol primero yendo por la rama izquierda, después yendo por la rama derecha y por último (en este caso) guardando el elemento actual.

El procedimiento es igual que el recorrido inorden pero cambiando el orden en el que se hacen las llamadas recursivas.

### Funcion destruir
Lo primero que hacemos es comprobar que el árbol sea valido. Después si el árbol esta vacio liberamos la memoria reservada y lista. En el caso que no este vacia, vamos hasta las hojas y si tenemos destructor, lo usamos y después vamos subien por el árbol hasta llegar a la raíz.

### Funcion iterador interno
Lo primero que hacemos es comprobar que el árbol y la función sean validas. Después dependiendo el recorrido, el orden en el que se llama con la rama izquierda, la derecha o la función que se nos pasa. 

## Conceptos teóricos

### Árbol binario de búsqueda y árbol binario

#### Que es un árbol binario de búsqueda
El árbol binario de búsqueda es un tipo de dato que aprovecha la busqueda binaria. Este árbol tiene la estructura de que cada nodo se divide en dos con la propiedad de los menores al nodo actual se situan a la izquierda, y los mayores a la derecha, por eso decimos que aprovecha la busqueda binaria.

#### Diferencia con un árbol binario
La diferencia principal es la propiedad con la que se ubican los elementos, donde los menores a la izquierda y los mayores a la derecha.

### La función destrucción 
Como el árbol esta pensando para que el usuario pueda guardar lo que quiera; en el caso de que guarde dato que necesita una forma especifica para destruirse, este tda le permite al usuario decidir como se destruye ese dato.

En el caso de que no dieramos esta posibilidades, tendríamos que limitar los datos que podría guardar, y por lo tanto el usuario no va a poder guardar lo que quiera. 

Demos un ejemplo para entender mejor esto: si yo creo un puntero al heap, e inserto ese puntero en el árbol, si eliminara el nodo que contiene ese puntero al heal, tendría perdidas de memoria ya que ese puntero al heap se perdio. Entonces si tengo una función destrucción puedo hacer que cuando se elimine ese nodo, libere el puntero al heap, así solucionando el problema. En el caso de no tenerlo no tendría opción de usar un puntero al heap, porque sin la función destrucción siempre se perdería memoría cuando usamos un puntero al heap.

### Complejidades

