#include <stdlib.h>

#include "abb.h"

#define ERROR -1
#define EXITO 0

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor) {

    if (!comparador)
        return NULL;

    abb_t* arbol = calloc(1, sizeof(abb_t));

    if (!arbol)
        return NULL;

    arbol->comparador = comparador;
    arbol->destructor = destructor;

    return arbol;
}

int arbol_insertar(abb_t* arbol, void* elemento) {

    if (!arbol)
        return ERROR;

    if (!arbol->nodo_raiz) {
        nodo_abb_t* nodo = calloc(1, sizeof(nodo_abb_t));

        if (!nodo) return ERROR;

        nodo->elemento = elemento;
        arbol->nodo_raiz = nodo;
        return EXITO;
    }

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;
    int comparacion = arbol->comparador(elemento, arbol_raiz(arbol));

    arbol->nodo_raiz = comparacion > 0 ? arbol->nodo_raiz->derecha : arbol->nodo_raiz->izquierda;

    int valor = arbol_insertar(arbol, elemento);

    if (valor == ERROR) return ERROR;

    if (comparacion > 0)
        nodo_actual->derecha = arbol->nodo_raiz;
    else nodo_actual->izquierda = arbol->nodo_raiz;

    arbol->nodo_raiz = nodo_actual;

    return EXITO;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    return 0;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {

    if(!arbol)
        return NULL;

    if (!arbol->nodo_raiz)
        return NULL;

    int comparacion = arbol->comparador(elemento, arbol_raiz(arbol));

    if (comparacion == 0)
        return arbol_raiz(arbol);

    arbol->nodo_raiz = comparacion > 0 ? arbol->nodo_raiz->derecha : arbol->nodo_raiz->izquierda;

    return arbol_buscar(arbol, elemento);
}

void* arbol_raiz(abb_t* arbol) {
    if (!arbol)
        return NULL;

    if (arbol_vacio(arbol))
        return NULL;

    return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol) {
    if (!arbol)
        return true;

    if (!arbol->nodo_raiz)
        return true;

    return false;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array) {
/*    if (!arbol)
        return 0;

    if (!tamanio_array)
        return 0;

    if (arbol_vacio(arbol))
        return 0;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    arbol->nodo_raiz = nodo_actual->izquierda;
    int valor_izquierda = arbol_recorrido_inorden(arbol, array, tamanio_array - 1);

    if (valor_izquierda != 0)
        tamanio_array--;

    if (!tamanio_array) return 1 + valor_izquierda;

    *(array+valor_izquierda) = arbol_raiz(arbol);

    tamanio_array--;
    if (!tamanio_array) return 2 +valor_izquierda;

    arbol->nodo_raiz = nodo_actual->derecha;
    int valor_derecha = arbol_recorrido_inorden(arbol, array, tamanio_array - 1);

    if (valor_derecha)
        tamanio_array--;

    return 1 + valor_izquierda + valor_derecha; */
    return 0;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array) {
    return 0;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array) {
    return 0;
}

void arbol_destruir_hojas(abb_t* arbol) {
    if (!arbol)
        return;

    if (arbol_vacio(arbol))
        return;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    arbol->nodo_raiz = nodo_actual->izquierda;
    arbol_destruir_hojas(arbol);

    arbol->nodo_raiz = nodo_actual->derecha;
    arbol_destruir_hojas(arbol);

    arbol->nodo_raiz = nodo_actual;

    if (arbol->destructor)
        arbol->destructor(arbol_raiz(arbol));

    free(arbol->nodo_raiz);
}

void arbol_destruir(abb_t* arbol) {
    if (!arbol)
        return;

    if (!arbol_vacio(arbol))
        arbol_destruir_hojas(arbol);

    free(arbol);
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra) {
    return 0;
}
