#include <stdlib.h>

#include "abb.h"
#include "pa2mm.h"

int comparador_prueba (void* elemento_uno, void* elemento_dos) {
    elemento_uno = elemento_uno;
    elemento_dos = elemento_dos;
    return 0;
}

void destructor_prueba (void* arbol) {
    arbol = arbol;
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

int main() {

    pa2m_nuevo_grupo("Pruebas crear árbol");
    probar_arbol_crear();



    pa2m_mostrar_reporte();
    return 0;
}
