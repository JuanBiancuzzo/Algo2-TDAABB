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

#### Recorrido inorden 

#### Recorrido preorden 

#### Recorrido postorden 

### Funcion destruir

### Funcion iterador interno
