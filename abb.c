#include <stdlib.h>

#include "abb.h"


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
    return 0;
}

int arbol_borrar(abb_t* arbol, void* elemento) {
    return 0;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {
    return NULL;
}

void* arbol_raiz(abb_t* arbol) {
    return NULL;
}

bool arbol_vacio(abb_t* arbol) {
    return true;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array) {
    return 0;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array) {
    return 0;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array) {
    return 0;
}

void arbol_destruir(abb_t* arbol) {
    return;
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra) {
    return 0;
}
