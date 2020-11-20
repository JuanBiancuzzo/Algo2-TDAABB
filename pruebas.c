#include <stdlib.h>

#include "abb.h"
#include "pa2mm.h"

#define ERROR -1
#define EXITO 0

int comparador_prueba (void* elemento_uno, void* elemento_dos) {
    return *(int*) elemento_uno > *(int*) elemento_dos ? 1 : *(int*) elemento_uno < *(int*) elemento_dos ? -1 : 0;
}

void destructor_prueba (void* arbol) {
    arbol = arbol;
}

abb_t* inicializar_arbol() {
    abb_comparador comparador = comparador_prueba;
    abb_liberar_elemento destructor = destructor_prueba;
    return arbol_crear(comparador, destructor);
}

void probar_arbol_crear_valores_invalidos () {
    abb_comparador comparador = comparador_prueba;
    abb_liberar_elemento destructor = destructor_prueba;
    abb_t* arbol = NULL;

    pa2m_afirmar((arbol = arbol_crear(NULL, destructor)) == NULL,
                 "Detecta correctamente que el comparador es invalido");

    pa2m_afirmar((arbol = arbol_crear(comparador, NULL)) != NULL,
                 "Detecta correctamente que no es necesario el destructor\n");

    arbol_destruir(arbol);
}

void probar_arbol_crear_inicializacion () {
    abb_comparador comparador = comparador_prueba;
    abb_liberar_elemento destructor = destructor_prueba;
    abb_t* arbol = NULL;

    pa2m_afirmar((arbol = arbol_crear(comparador, destructor)) != NULL,
                 "Mensaje de creacion correcta al crear el arbol");

    pa2m_afirmar(!arbol->nodo_raiz && arbol->comparador == comparador && arbol->destructor == destructor,
                 "La estructura del arbol se inicializa de forma correcta\n");

    arbol_destruir(arbol);
}

void probar_arbol_crear () {

    probar_arbol_crear_valores_invalidos();
    probar_arbol_crear_inicializacion();

}

void probar_arbol_insertar_valores_invalidos () {
    int elemento = 11;

    pa2m_afirmar(arbol_insertar(NULL, &elemento) == ERROR,
                 "Detecta correctamente que el arbol es invalido\n");

}

void probar_arbol_insertar_un_elemento () {
    abb_t* arbol = inicializar_arbol();
    int elemento = 11;

    pa2m_afirmar(arbol_insertar(arbol, &elemento) == EXITO,
                 "Mensaje de exito al insertar el elemento");

    pa2m_afirmar(elemento == *(int*)arbol->nodo_raiz->elemento ,
                 "Se inserta correctamente el elemenento en el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_insertar_varios_elementos () {
    abb_t* arbol = inicializar_arbol();
    int elemento_uno = 22, mensaje_uno, elemento_dos = 11, mensaje_dos, elemento_tres = 33, mensaje_tres;
    bool posicion_uno, posicion_dos, posicion_tres;

    mensaje_uno = arbol_insertar(arbol, &elemento_uno);
    mensaje_dos = arbol_insertar(arbol, &elemento_dos);
    mensaje_tres = arbol_insertar(arbol, &elemento_tres);

    pa2m_afirmar(mensaje_uno == EXITO && mensaje_dos == EXITO && mensaje_tres == EXITO,
                 "Mensaje de exito al insertar varios elementos");

    posicion_uno = elemento_uno == *(int*) arbol->nodo_raiz->elemento;
    posicion_dos = elemento_dos == *(int*) arbol->nodo_raiz->izquierda->elemento;
    posicion_tres = elemento_tres == *(int*) arbol->nodo_raiz->derecha->elemento;

    pa2m_afirmar(posicion_uno && posicion_dos && posicion_tres,
                "Se inserta correctamente los elementos en el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_insertar () {

    probar_arbol_insertar_valores_invalidos();
    probar_arbol_insertar_un_elemento();
    probar_arbol_insertar_varios_elementos();

}

void probar_arbol_borrar_valores_invalidos () {
    abb_t* arbol = inicializar_arbol();
    int elemento = 11;

    pa2m_afirmar(arbol_borrar(NULL, &elemento) == ERROR,
                 "Detecta correctamente que el arbol es invalido");

    pa2m_afirmar(arbol_borrar(arbol, &elemento) == ERROR,
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_borrar_un_elemento () {
    abb_t* arbol = inicializar_arbol();
    int elemento = 11;

    arbol_insertar(arbol, &elemento);

    pa2m_afirmar(arbol_borrar(arbol, &elemento) == EXITO,
                 "Mensaje de exito al intentar borrar un elemento de un arbol con un elemento");

    pa2m_afirmar(!arbol->nodo_raiz && arbol_vacio(arbol),
                 "Se borra correctamente el elemento en un arbol con un elemento\n");

    arbol_destruir(arbol);
}

void probar_arbol_borrar_varios_elementos () {
    abb_t* arbol = inicializar_arbol();
    int contador = 0, cantidad = 7;

    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    int insertar_correcta = EXITO;

    while (contador < cantidad && insertar_correcta == EXITO) {
        insertar_correcta = arbol_insertar(arbol, elementos+contador);
        contador++;
    }

    int orden[7] = {7, 6, 2, 4, 3, 1, 5};
    int borrar_correcta = EXITO;
    contador = 0;

    while (contador < cantidad && borrar_correcta == EXITO) {
        // printf("eliminar %i, raiz %i - ", orden[contador], *(int*)arbol->nodo_raiz->elemento);
        borrar_correcta = arbol_borrar(arbol, orden+contador);
        // printf("return %i\n", borrar_correcta);
        contador++;
    }

    pa2m_afirmar(borrar_correcta == EXITO,
                 "Mensaje de exito al borrar todos los elementos del arbol con varios elementos");

    pa2m_afirmar(contador == cantidad && arbol_vacio(arbol),
                 "Se borra correctamente todos elementos en un arbol con varios elementos\n");

    arbol_destruir(arbol);
}

void probar_arbol_borrar () {

    probar_arbol_borrar_valores_invalidos();
    probar_arbol_borrar_un_elemento();
    probar_arbol_borrar_varios_elementos();

}

void probar_arbol_recorrido_inorden_valores_invalidos () {
    abb_t* arbol = inicializar_arbol();
    int array[10];
    size_t cantidad = 10;

    pa2m_afirmar(arbol_recorrido_inorden(NULL, (void**)&array, cantidad) == 0,
                 "Detecta correctamente que el arbol es invalido");

    pa2m_afirmar(arbol_recorrido_inorden(arbol, NULL, cantidad) == 0,
                 "Detecta correctamente que el array es invalido");

    pa2m_afirmar(arbol_recorrido_inorden(arbol, (void**)&array, cantidad) == 0,
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_inorden_array_mayor_arbol () {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    int cantidad = 7;

    for (int i = 0; i < cantidad; i++)
        arbol_insertar(arbol, elementos+i);

    int* array[9];
    size_t tamanio_array = 9;

    size_t recorridos = arbol_recorrido_inorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar((int)recorridos == cantidad,
                 "Devuelve la cantidad correcta de elementos");

    size_t contador = 0;
    bool inorden = true;

    while (contador+1  < recorridos && inorden) {

        if (*(int*)(array[contador])+1 != *(int*)(array[contador+1]))
            inorden = false;
        contador++;
    }

    pa2m_afirmar(inorden,
                 "Se recorre correctamente el arbol con un array mayor que el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_inorden () {

    probar_arbol_recorrido_inorden_valores_invalidos();
    probar_arbol_recorrido_inorden_array_mayor_arbol();
    // probar_arbol_recorrido_inorden_array_menor_arbol();

}

void probar_arbol_recorrido_preorden_valores_invalidos () {
    abb_t* arbol = inicializar_arbol();
    int array[10];
    size_t cantidad = 10;

    pa2m_afirmar(arbol_recorrido_preorden(NULL, (void**)&array, cantidad) == 0,
                 "Detecta correctamente que el arbol es invalido");

    pa2m_afirmar(arbol_recorrido_preorden(arbol, NULL, cantidad) == 0,
                 "Detecta correctamente que el array es invalido");

    pa2m_afirmar(arbol_recorrido_preorden(arbol, (void**)&array, cantidad) == 0,
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_preorden_array_mayor_arbol () {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {1, 2, 3, 4, 5, 6, 7};
    int cantidad = 7;

    for (int i = 0; i < cantidad; i++)
        arbol_insertar(arbol, elementos+i);

    int* array[9];
    size_t tamanio_array = 11;

    size_t recorridos = arbol_recorrido_preorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar((int)recorridos == cantidad,
                 "Devuelve la cantidad correcta de elementos");

    size_t contador = 0;
    bool preorden = true;

    while (contador+1  < recorridos && preorden) {

        if (*(int*)(array[contador])+1 != *(int*)(array[contador+1]))
            preorden = false;
        contador++;
    }

    pa2m_afirmar(preorden,
                 "Se recorre correctamente el arbol con un array mayor que el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_preorden () {

    probar_arbol_recorrido_preorden_valores_invalidos();
    probar_arbol_recorrido_preorden_array_mayor_arbol();
    // probar_arbol_recorrido_preorden_array_menor_arbol();

}

void probar_arbol_recorrido_postorden_valores_invalidos () {
    abb_t* arbol = inicializar_arbol();
    int array[10];
    size_t cantidad = 10;

    pa2m_afirmar(arbol_recorrido_postorden(NULL, (void**)&array, cantidad) == 0,
                 "Detecta correctamente que el arbol es invalido");

    pa2m_afirmar(arbol_recorrido_postorden(arbol, NULL, cantidad) == 0,
                 "Detecta correctamente que el array es invalido");

    pa2m_afirmar(arbol_recorrido_postorden(arbol, (void**)&array, cantidad) == 0,
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_postorden_array_mayor_arbol () {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    int cantidad = 7;

    for (int i = 0; i < cantidad; i++)
        arbol_insertar(arbol, elementos+i);

    int* array[9];
    size_t tamanio_array = 9;

    size_t recorridos = arbol_recorrido_postorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar((int)recorridos == cantidad,
                 "Devuelve la cantidad correcta de elementos");

    int elementos_esperados[7] = {1, 3, 2, 5, 7, 6, 4};
    bool postorden = true;
    size_t contador = 0;

    while (contador < recorridos && postorden) {

        if (*(int*)array[contador] != elementos_esperados[contador])
            postorden = false;
        contador++;
    }

    pa2m_afirmar(postorden,
                 "Se recorre correctamente el arbol con un array mayor que el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_postorden () {

    probar_arbol_recorrido_postorden_valores_invalidos();
    probar_arbol_recorrido_postorden_array_mayor_arbol();
    // probar_arbol_recorrido_postorden_array_menor_arbol();

}

int main() {

    pa2m_nuevo_grupo("Pruebas crear árbol");
    printf(" * Arbol_crear:\n");
    probar_arbol_crear();

    pa2m_nuevo_grupo("Pruebas insertar y borrar");
    printf(" * Arbol_insertar:\n");
    probar_arbol_insertar();
    printf("\n * Arbol_borrar:\n");
    probar_arbol_borrar();

    //pa2m_nuevo_grupo("Pruebas herramientas");
    //printf(" * Arbol_insertar:\n");

    pa2m_nuevo_grupo("Pruebas Recorridos");
    printf(" * Arbol_recorrido_inorden:\n");
    probar_arbol_recorrido_inorden();
    printf("\n * Arbol_recorrido_preorden:\n");
    probar_arbol_recorrido_preorden();
    printf("\n * Arbol_recorrido_postorden:\n");
    probar_arbol_recorrido_postorden();

    pa2m_mostrar_reporte();
    return 0;
}
