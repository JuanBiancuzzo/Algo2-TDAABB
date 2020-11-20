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

    int comparacion = arbol->comparador(elemento, arbol_raiz(arbol));
    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    arbol->nodo_raiz = comparacion > 0 ? arbol->nodo_raiz->derecha : arbol->nodo_raiz->izquierda;

    int valor = arbol_insertar(arbol, elemento);

    if (valor == ERROR) return ERROR;

    if (comparacion > 0)
        nodo_actual->derecha = arbol->nodo_raiz;
    else nodo_actual->izquierda = arbol->nodo_raiz;

    arbol->nodo_raiz = nodo_actual;

    return EXITO;
}

/*
 * Devuelve las ramas combinadas, colocando la rama izquierda en el de
 * la rama derecha
 */
nodo_abb_t* combinar_hijos(nodo_abb_t* izquierda, nodo_abb_t* derecha) {

    if (!izquierda) return derecha;

    if (!derecha) return izquierda;

    derecha->izquierda = combinar_hijos(izquierda, derecha->izquierda);

    return derecha;
}

int arbol_borrar(abb_t* arbol, void* elemento) {

    if (!arbol)
        return ERROR;

    if (arbol_vacio(arbol))
        return ERROR;

    int comparacion = arbol->comparador(elemento, arbol_raiz(arbol));
    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    if (comparacion == 0) {

        if (arbol->destructor) arbol->destructor(nodo_actual->elemento);

        arbol->nodo_raiz = combinar_hijos(arbol->nodo_raiz->izquierda, arbol->nodo_raiz->derecha);
        free(nodo_actual);

        return EXITO;
    }

    arbol->nodo_raiz = comparacion > 0 ? arbol->nodo_raiz->derecha : arbol->nodo_raiz->izquierda;

    int valor = arbol_borrar(arbol, elemento);

    if (valor == ERROR) return ERROR;

    if (comparacion > 0)
        nodo_actual->derecha = arbol->nodo_raiz;
    else nodo_actual->izquierda = arbol->nodo_raiz;

    arbol->nodo_raiz = nodo_actual;

    return EXITO;
}

void* arbol_buscar(abb_t* arbol, void* elemento) {

    if(!arbol)
        return NULL;

    if (!arbol->nodo_raiz)
        return NULL;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;
    int comparacion = arbol->comparador(elemento, arbol_raiz(arbol));

    if (comparacion == 0)
        return arbol_raiz(arbol);

    arbol->nodo_raiz = comparacion > 0 ? arbol->nodo_raiz->derecha : arbol->nodo_raiz->izquierda;

    void* valor = arbol_buscar(arbol, elemento);
    arbol->nodo_raiz = nodo_actual;

    return valor;
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
    if (!arbol || !array) return 0;

    if (arbol_vacio(arbol)) return 0;

    if(tamanio_array == 0) return 0;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    arbol->nodo_raiz = nodo_actual->izquierda;
    size_t valor = arbol_recorrido_inorden(arbol, array, tamanio_array-1);

    arbol->nodo_raiz = nodo_actual;
    *(array+valor) = arbol_raiz(arbol);

    if (tamanio_array - valor < 1)
        return tamanio_array;
    else tamanio_array -= valor;

    arbol->nodo_raiz = nodo_actual->derecha;
    size_t valor_dos = arbol_recorrido_inorden(arbol, array+(valor+1), tamanio_array-1);

    arbol->nodo_raiz = nodo_actual;
    return 1 + valor + valor_dos;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array) {
    if (!arbol || !array) return 0;

    if (arbol_vacio(arbol)) return 0;

    if(tamanio_array == 0) return 0;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    *array = arbol_raiz(arbol);

    arbol->nodo_raiz = nodo_actual->izquierda;
    size_t valor = arbol_recorrido_preorden(arbol, array+1, tamanio_array-1);

    if (tamanio_array - valor < 1)
        return tamanio_array;
    else tamanio_array -= valor;

    arbol->nodo_raiz = nodo_actual->derecha;
    size_t valor_dos = arbol_recorrido_preorden(arbol, array+1, tamanio_array-1);

    arbol->nodo_raiz = nodo_actual;
    return 1 + valor + valor_dos;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array) {
    if (!arbol || !array) return 0;

    if (arbol_vacio(arbol)) return 0;

    if(tamanio_array == 0) return 0;

    nodo_abb_t* nodo_actual = arbol->nodo_raiz;

    arbol->nodo_raiz = nodo_actual->izquierda;
    size_t valor = arbol_recorrido_postorden(arbol, array, tamanio_array-1);

    if (tamanio_array - valor < 1)
        return tamanio_array;
    else tamanio_array -= valor;

    arbol->nodo_raiz = nodo_actual->derecha;
    size_t valor_dos = arbol_recorrido_postorden(arbol, array+valor, tamanio_array-1);

    arbol->nodo_raiz = nodo_actual;
    *(array+(valor+valor_dos)) = arbol_raiz(arbol);

    return 1 + valor + valor_dos;
}

/*
 * Dado un arbol lo recorre de abajo hacia arriba destruyendo (si tiene destructor)
 * cada hoja y liberandola, hasta dejar el arbol vacio
 */
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

    if (arbol->destructor) arbol->destructor(arbol_raiz(arbol));
    free(arbol->nodo_raiz);
}

void arbol_destruir(abb_t* arbol) {
    if (!arbol)
        return;

    if (!arbol_vacio(arbol))
        arbol_destruir_hojas(arbol);

    free(arbol);
}

/*
 * Itera todo el arbol, de la forma voy a la izquierda, después en el que estoy y
 * por ultimo a la derecha
 */
size_t abb_iterador_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra) {
    if (!nodo || !funcion) return 0;

    size_t valor = abb_iterador_inorden(nodo->izquierda, funcion, extra);

    if (funcion(nodo->elemento, extra)) return 0;

    size_t valor_dos = abb_iterador_inorden(nodo->derecha, funcion, extra);
    
    return 1 + valor + valor_dos;
}

/*
 * Itera todo el arbol, de la forma primero en el que estoy, después voy a la
 * izquierda y por ultimo a la derecha
 */
size_t abb_iterador_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra) {
    if (!nodo || !funcion) return 0;

    if (funcion(nodo->elemento, extra)) return 0;

    size_t valor = abb_iterador_preorden(nodo->izquierda, funcion, extra);

    size_t valor_dos = abb_iterador_preorden(nodo->derecha, funcion, extra);

    return 1 + valor + valor_dos;
}

/*
 * Itera todo el arbol, de la forma voy a la izquierda, después a la derecha y
 * por ultimo en el que estoy
 */
size_t abb_iterador_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra) {
    if (!nodo || !funcion) return 0;

    size_t valor = 0, valor_dos = 0;

    if (nodo->izquierda)
        valor = abb_iterador_postorden(nodo->izquierda, funcion, extra);

    if (nodo->derecha)
        valor_dos = abb_iterador_postorden(nodo->derecha, funcion, extra);

    if (funcion(nodo->elemento, extra)) return 0;

    return 1 + valor + valor_dos;
}

size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra) {

    if (!arbol || !funcion) return 0;

    if (recorrido == ABB_RECORRER_INORDEN)
        return abb_iterador_inorden(arbol->nodo_raiz, funcion, extra);

    if (recorrido == ABB_RECORRER_PREORDEN)
        return abb_iterador_preorden(arbol->nodo_raiz, funcion, extra);

    if (recorrido == ABB_RECORRER_POSTORDEN)
        return abb_iterador_postorden(arbol->nodo_raiz, funcion, extra);

    return 0;
}
