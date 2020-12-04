# TDA Árbol binario de búsqueda (ABB)

Este tipo de dato abstracto es un árbol binario de búsqueda (ABB), con sus operaciones administrativas (creary destruir), e insertar, eliminar, buscar, mostrar la raiz y si el árbol esta vacio. También tenemos funciones para recorrer el árbol, de forma inorden, preorden o postorden.

Por último tenemos un iterador interno, donde se puede especificar que tipo de recorrido se quiere usar.

## Compilación y ejecucion

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

