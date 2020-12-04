#include <stdlib.h>

#include "abb.h"
#include "pa2mm.h"

#define ERROR -1
#define EXITO 0

typedef struct estructura_contador {
    int key;
    int contador;
} contador_t;

typedef struct estructura_orden {
    int* array;
    int contador;
} orden_t;

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
        borrar_correcta = arbol_borrar(arbol, orden+contador);
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

int comparador_contador (void* elemento_uno, void* elemento_dos) {

    if (((contador_t*)elemento_uno)->key > ((contador_t*)elemento_dos)->key)
        return 1;
    else if (((contador_t*)elemento_uno)->key < ((contador_t*)elemento_dos)->key)
        return -1;
    return 0;
}

void destructor_contador (void* dato) {
    ((contador_t*)dato)->contador++;
}

void probar_arbol_destruir_funcion_destructor_un_nodo () {
    abb_comparador comparador = comparador_contador;
    abb_liberar_elemento destructor = destructor_contador;
    abb_t* arbol = arbol_crear(comparador, destructor);

    contador_t datos[1];

    datos[0].key = 4;
    datos[0].contador = 0;

    arbol_insertar(arbol, datos);
    arbol_destruir(arbol);

    pa2m_afirmar(datos[0].contador > 0,
                 "Se destruye el elemento del arbol con un nodo");

    pa2m_afirmar(datos[0].contador == 1,
                 "Se destruye el elemento del arbol solo una vez\n");
}

void probar_arbol_destruir_funcion_destructor_varios_nodos () {
    abb_comparador comparador = comparador_prueba;
    abb_liberar_elemento destructor = destructor_contador;
    abb_t* arbol = arbol_crear(comparador, destructor);

    contador_t datos[4];

    datos[0].key = 4;
    datos[0].contador = 0;
    datos[1].key = 2;
    datos[1].contador = 0;
    datos[2].key = 6;
    datos[2].contador = 0;
    datos[3].key = 1;
    datos[3].contador = 0;

    for (int i = 0; i < 4; i++)
        arbol_insertar(arbol, datos+i);

    arbol_destruir(arbol);

    bool destruccion_correcta = true;
    int contador = 0;

    while (contador < 4 && destruccion_correcta) {
        destruccion_correcta = datos[contador].contador > 0 ? true : false;
        contador++;
    }

    pa2m_afirmar(destruccion_correcta,
                 "Se destruye todos los elementos del arbol con varios nodos");

    contador = 0;
    while (contador < 4 && destruccion_correcta) {
        destruccion_correcta = datos[contador].contador == 1 ? true : false;
        contador++;
    }

    pa2m_afirmar(destruccion_correcta,
                 "Se destruyelos elementos del arbol con varios nodos una sola vez\n");
}

void probar_arbol_destruir () {

    probar_arbol_destruir_funcion_destructor_un_nodo();
    probar_arbol_destruir_funcion_destructor_varios_nodos();

}

size_t insertar_n_valores (abb_t* arbol, int array[], size_t cantidad) {
    size_t insertados = 0;
    for (size_t i = 0; i < cantidad; i++) {
        int resultado = arbol_insertar(arbol, array+i);
        if (resultado == EXITO)
            insertados++;
    }
    return insertados;
}

void probar_arbol_buscar_valores_invalidos () {
    abb_t* arbol = inicializar_arbol();
    int key = 4;

    pa2m_afirmar(arbol_buscar(NULL, &key) == NULL,
                 "Detecta correctamente que el arbol es invalido");

    pa2m_afirmar(arbol_buscar(arbol, &key) == NULL,
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_buscar_key_en_arbol () {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    insertar_n_valores(arbol, elementos, 7);

    int key = 4;
    pa2m_afirmar(*(int*)arbol_buscar(arbol, &key) == 4,
                 "Encuentra correctamente la raiz del arbol");

    key = 7;
    pa2m_afirmar(*(int*)arbol_buscar(arbol, &key) == 7,
                 "Encuentra correctamente una hoja del arbol");

    key = 2;
    pa2m_afirmar(*(int*)arbol_buscar(arbol, &key) == 2,
                 "Encuentra correctamente un nodo que no es raiz, ni hoja\n");

    arbol_destruir(arbol);
}

void probar_arbol_buscar_key_invalido () {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    insertar_n_valores(arbol, elementos, 7);

    int key = 8;
    pa2m_afirmar(arbol_buscar(arbol, &key) == NULL,
                 "Reconoce correctamente que no hay elemento que no esta en el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_buscar () {

    probar_arbol_buscar_valores_invalidos();
    probar_arbol_buscar_key_en_arbol();
    probar_arbol_buscar_key_invalido();

}

void probar_arbol_raiz_valores_invalidos () {
    abb_t* arbol = inicializar_arbol();

    pa2m_afirmar(arbol_raiz(NULL) == NULL,
                 "Detecta correctamente que el arbol es invalido");

    pa2m_afirmar(arbol_raiz(arbol) == NULL,
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_raiz_arbol_un_nodo() {
    abb_t* arbol = inicializar_arbol();
    int elemento = 11;

    arbol_insertar(arbol, &elemento);

    pa2m_afirmar(*(int*)arbol_raiz(arbol) == elemento,
                 "Reconoce correctamente la raiz con un arbol de un nodo\n");

    arbol_destruir(arbol);
}

void probar_arbol_raiz_arbol_varios_nodos() {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    insertar_n_valores(arbol, elementos, 7);

    pa2m_afirmar(*(int*)arbol_raiz(arbol) == elementos[0],
                 "Reconoce correctamente la raiz con un arbol de varios nodos\n");

    arbol_destruir(arbol);
}

void probar_arbol_raiz () {

    probar_arbol_raiz_valores_invalidos();
    probar_arbol_raiz_arbol_un_nodo();
    probar_arbol_raiz_arbol_varios_nodos();

}

void probar_arbol_vacio_valores_invalidos () {
    abb_t* arbol = inicializar_arbol();

    pa2m_afirmar(arbol_vacio(NULL),
                 "Detecta correctamente que el arbol es invalido y por ende vacio");

    pa2m_afirmar(arbol_vacio(arbol),
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_vacio_arbol_varios_nodos() {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    insertar_n_valores(arbol, elementos, 7);

    pa2m_afirmar(!arbol_vacio(arbol),
                 "Detecta correctamente que el arbol no esta vacio\n");

    arbol_destruir(arbol);
}

void probar_arbol_vacio () {

    probar_arbol_vacio_valores_invalidos();
    probar_arbol_vacio_arbol_varios_nodos();

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
    int elementos [7] = {4, 2, 6, 1, 3, 5, 7};
    size_t cantidad = insertar_n_valores (arbol, elementos, 7);

    int* array[9];
    size_t tamanio_array = 9;

    size_t recorridos = arbol_recorrido_inorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar(recorridos == cantidad,
                 "Devuelve la cantidad correcta de elementos en un recorrido más largo que el arbol");

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

void probar_arbol_recorrido_inorden_array_menor_arbol () {
    abb_t* arbol = inicializar_arbol();
    int elementos [7] = {4, 2, 6, 1, 3, 5, 7};
    insertar_n_valores (arbol, elementos, 7);

    int* array[9];
    size_t tamanio_array = 4;

    size_t recorridos = arbol_recorrido_inorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar(recorridos == tamanio_array,
                    "Devuelve la cantidad correcta de elementos en un recorrido más corto que el arbol");

    size_t contador = 0;
    bool inorden = true;

    while (contador+1  < recorridos && inorden) {

        if (*(int*)(array[contador])+1 != *(int*)(array[contador+1]))
            inorden = false;
        contador++;
    }

    pa2m_afirmar(inorden,
                    "Se recorre correctamente el arbol con un array menor que el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_inorden () {

    probar_arbol_recorrido_inorden_valores_invalidos();
    probar_arbol_recorrido_inorden_array_mayor_arbol();
    probar_arbol_recorrido_inorden_array_menor_arbol();

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
    size_t cantidad = insertar_n_valores (arbol, elementos, 7);

    int* array[9];
    size_t tamanio_array = 11;

    size_t recorridos = arbol_recorrido_preorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar(recorridos == cantidad,
                 "Devuelve la cantidad correcta de elementos en un recorrido más largo que el arbol");

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

void probar_arbol_recorrido_preorden_array_menor_arbol () {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {1, 2, 3, 4, 5, 6, 7};
    insertar_n_valores (arbol, elementos, 7);

    int* array[9];
    size_t tamanio_array = 4;

    size_t recorridos = arbol_recorrido_preorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar(recorridos == tamanio_array,
                 "Devuelve la cantidad correcta de elementos en un recorrido más corto que el arbol");

    size_t contador = 0;
    bool preorden = true;

    while (contador+1  < recorridos && preorden) {

        if (*(int*)(array[contador])+1 != *(int*)(array[contador+1]))
            preorden = false;
        contador++;
    }

    pa2m_afirmar(preorden,
                 "Se recorre correctamente el arbol con un array menor que el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_preorden () {

    probar_arbol_recorrido_preorden_valores_invalidos();
    probar_arbol_recorrido_preorden_array_mayor_arbol();
    probar_arbol_recorrido_preorden_array_menor_arbol();

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
    size_t cantidad = insertar_n_valores (arbol, elementos, 7);

    int* array[9];
    size_t tamanio_array = 9;

    size_t recorridos = arbol_recorrido_postorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar(recorridos == cantidad,
                 "Devuelve la cantidad correcta de elementos en un recorrido más largo que el arbol");

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

void probar_arbol_recorrido_postorden_array_menor_arbol () {
    abb_t* arbol = inicializar_arbol();
    int elementos[7] = {4, 2, 6, 1, 3, 5, 7};
    insertar_n_valores (arbol, elementos, 7);

    int* array[5];
    size_t tamanio_array = 5;

    size_t recorridos = arbol_recorrido_postorden(arbol, (void**)array, tamanio_array);

    pa2m_afirmar(recorridos == tamanio_array,
                 "Devuelve la cantidad correcta de elementos en un recorrido más corto que el arbol");

    int elementos_esperados[7] = {1, 3, 2, 5, 7, 6, 4};
    bool postorden = true;
    size_t contador = 0;

    while (contador < recorridos && postorden) {
        if (*(int*)array[contador] != elementos_esperados[contador])
            postorden = false;
        contador++;
    }

    pa2m_afirmar(postorden,
                 "Se recorre correctamente el arbol con un array menor que el arbol\n");

    arbol_destruir(arbol);
}

void probar_arbol_recorrido_postorden () {

    probar_arbol_recorrido_postorden_valores_invalidos();
    probar_arbol_recorrido_postorden_array_mayor_arbol();
    probar_arbol_recorrido_postorden_array_menor_arbol();

}

bool iterador_avanzar (void* elemento, void* extra) {
    ((contador_t*)elemento)->contador++;
    extra = extra;
    return false;
}

bool iterador_avanzar_dos (void* elemento, void* extra) {
    (((orden_t*)extra)->array)[((orden_t*)extra)->contador] = *(int*)elemento;
    ((orden_t*)extra)->contador++;
    return false;
}

void probar_iterador_interno_valores_invalidos () {

    abb_t* arbol = inicializar_arbol();
    bool (*funcion) (void*, void*) = iterador_avanzar;

    pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_INORDEN, funcion, NULL) == 0,
                 "Detecta correctamente que el arbol es invalido");

    pa2m_afirmar(abb_con_cada_elemento(arbol, 3, funcion, NULL) == 0,
                 "Detecta correctamente que el recorrido es invalido");

    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, NULL, NULL) == 0,
                 "Detecta correctamente que la funcion es invalida");

    pa2m_afirmar(abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, funcion, NULL) == 0,
                 "Detecta correctamente que el arbol esta vacio\n");

    arbol_destruir(arbol);
}

void probar_iterador_interno_recorrido_inorden_cada_nodo () {

    abb_comparador comparador = comparador_contador;
    abb_liberar_elemento destructor = destructor_prueba;
    abb_t* arbol = arbol_crear(comparador, destructor);

    bool (*funcion) (void*, void*) = iterador_avanzar;
    contador_t datos[5];

    int elementos[5] = {4, 2, 6, 1, 7};
    bool recorrido_correcto = true;
    int cantidad = 5;

    for (int i = 0; i < cantidad; i++) {
        datos[i].key = *(elementos+i);
        datos[i].contador = 0;
        arbol_insertar(arbol, datos+i);
    }

    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, funcion, NULL);

    for (int i = 0; i < cantidad && recorrido_correcto; i++)
        recorrido_correcto = datos[i].contador > 0 ? true : false;

    pa2m_afirmar(recorrido_correcto, "Se recorren todos los elementos del arbol por lo menos una vez");

    for (int i = 0; i < cantidad && recorrido_correcto; i++)
        recorrido_correcto = datos[i].contador == 1 ? true : false;

    pa2m_afirmar(recorrido_correcto, "Se recorren todos los elementos del arbol solo una vez\n");

    arbol_destruir(arbol);
}

void probar_iterador_interno_recorrido_inorden_orden () {
    abb_t* arbol = inicializar_arbol();
    int datos[5] = {4, 2, 6, 1, 7};
    int valor_esperado[5] = {1, 2, 4, 6, 7};

    int resultado[5];
    int cantidad = 5;
    orden_t orden = {resultado, 0};

    bool (*funcion) (void*, void*) = iterador_avanzar_dos;

    bool recorrido_correcto = true;

    for (int i = 0; i < cantidad; i++)
        arbol_insertar(arbol, datos+i);

    abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, funcion, &orden);

    for (int i = 0; i < cantidad && recorrido_correcto; i++)
        recorrido_correcto = valor_esperado[i] == resultado[i] ? true : false;

    pa2m_afirmar(recorrido_correcto, "Se recorre el arbol de forma inorden de forma correcta\n");

    arbol_destruir(arbol);
}

void probar_iterador_interno_recorrido_preorden_cada_nodo () {

    abb_comparador comparador = comparador_contador;
    abb_liberar_elemento destructor = destructor_prueba;
    abb_t* arbol = arbol_crear(comparador, destructor);

    bool (*funcion) (void*, void*) = iterador_avanzar;
    contador_t datos[5];

    int elementos[5] = {4, 2, 6, 1, 7};
    bool recorrido_correcto = true;
    int cantidad = 5;

    for (int i = 0; i < cantidad; i++) {
        datos[i].key = *(elementos+i);
        datos[i].contador = 0;
        arbol_insertar(arbol, datos+i);
    }

    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, funcion, NULL);

    for (int i = 0; i < cantidad && recorrido_correcto; i++)
        recorrido_correcto = datos[i].contador > 0 ? true : false;

    pa2m_afirmar(recorrido_correcto, "Se recorren todos los elementos del arbol por lo menos una vez");

    for (int i = 0; i < cantidad && recorrido_correcto; i++)
        recorrido_correcto = datos[i].contador == 1 ? true : false;

    pa2m_afirmar(recorrido_correcto, "Se recorren todos los elementos del arbol solo una vez\n");

    arbol_destruir(arbol);
}

void probar_iterador_interno_recorrido_preorden_orden () {
    abb_t* arbol = inicializar_arbol();
    int datos[5] = {4, 2, 6, 1, 7};
    int valor_esperado[5] = {4, 2, 1, 6, 7};

    int resultado[5];
    int cantidad = 5;
    orden_t orden = {resultado, 0};

    bool (*funcion) (void*, void*) = iterador_avanzar_dos;

    bool recorrido_correcto = true;

    for (int i = 0; i < cantidad; i++)
        arbol_insertar(arbol, datos+i);

    abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, funcion, &orden);

    for (int i = 0; i < cantidad && recorrido_correcto; i++)
        recorrido_correcto = valor_esperado[i] == resultado[i] ? true : false;

    pa2m_afirmar(recorrido_correcto, "Se recorre el arbol de forma preorden de forma correcta\n");

    arbol_destruir(arbol);
}

    arbol_destruir(arbol);
}

void probar_iterador_interno () {

    probar_iterador_interno_valores_invalidos();

    printf("  · Recorrido inorden:\n");
    probar_iterador_interno_recorrido_inorden_cada_nodo();
    probar_iterador_interno_recorrido_inorden_orden();
    printf("  · Recorrido preorden:\n");
    probar_iterador_interno_recorrido_preorden_cada_nodo();
    probar_iterador_interno_recorrido_preorden_orden();

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
    printf("\n * Arbol_destruir:\n");
    probar_arbol_destruir();

    pa2m_nuevo_grupo("Pruebas herramientas");
    printf(" * Arbol_buscar:\n");
    probar_arbol_buscar();
    printf("\n * Arbol_raiz:\n");
    probar_arbol_raiz();
    printf("\n * Arbol_vacio:\n");
    probar_arbol_vacio();

    pa2m_nuevo_grupo("Pruebas Recorridos");
    printf(" * Arbol_recorrido_inorden:\n");
    probar_arbol_recorrido_inorden();
    printf("\n * Arbol_recorrido_preorden:\n");
    probar_arbol_recorrido_preorden();
    printf("\n * Arbol_recorrido_postorden:\n");
    probar_arbol_recorrido_postorden();

    pa2m_nuevo_grupo("Pruebas iterador interno");
    printf(" * Arbol_con_cada_elemento:\n");
    probar_iterador_interno();


    pa2m_mostrar_reporte();
    return 0;
}
