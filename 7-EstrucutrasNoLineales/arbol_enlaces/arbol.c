#include "arbol.h"
#include <stdio.h>
#include <stdlib.h>

// Definir la estructura del tipo de dato
typedef struct nodo {
    TipoDato dato;

    struct nodo * izquierdo;
    struct nodo * derecho;
} Nodo;

 Nodo * crearNodo(TipoDato dato) {
    Nodo * nuevo = RESERVAR(1, Nodo);

    if (nuevo == NULL) {
        fputs("Error. Sin memoria disponible", stderr);
        exit(EXIT_FAILURE);
    }

    *nuevo = (Nodo) { .dato = dato, .izquierdo = NULL, .derecho = NULL };
    return nuevo;
}

struct arbol {
    Nodo * raiz;
    int num_elementos;
};

// Funciones para crear y destruir el árbol
Arbol * Arbol_Nuevo(void)
{
    Arbol * nuevo = RESERVAR(1, Arbol);
    if (nuevo == NULL) {
        return NULL;
    }
    *nuevo = (Arbol) { .raiz = NULL, .num_elementos = 0 };
    return nuevo;
}

 void auxLiberar(Nodo * subraiz) {
    if (subraiz != NULL) {
        auxLiberar(subraiz->izquierdo);
        auxLiberar(subraiz->derecho);
        free(subraiz);
    }
}

#undef Arbol_Liberar
void    Arbol_Liberar(Arbol ** arbol)
{
    auxLiberar((*arbol)->raiz);
    free(*arbol);
    *arbol = NULL;
}

// Funciones que modifican la estructura del árbol
 bool auxInsertar(Nodo ** subraiz, TipoDato dato) {
    if ((*subraiz) == NULL) {
        (*subraiz) = crearNodo(dato);
        return true;
    }

    int comparacion = compararDato(&dato, &(*subraiz)->dato);
    if (comparacion == 0) {
        return false;
    }

    if (comparacion < 0) {
        return auxInsertar(&(*subraiz)->izquierdo, dato);
    } else {
        return auxInsertar(&(*subraiz)->derecho, dato);
    }
}
bool Arbol_Insertar(Arbol * arbol, TipoDato dato)
{
    if (auxInsertar(&arbol->raiz, dato)) {
        arbol->num_elementos++;
        return true;
    }
    return false;
}

 int cantidadHijos(const Nodo * subraiz)
{
    int cantidad = 0;
    if (subraiz->derecho != NULL) { cantidad++; }
    if (subraiz->izquierdo != NULL) { cantidad++; }
    return cantidad;
}

 Nodo * encontrarPadreRemplazo(Nodo * subraiz)
{
    if (subraiz->derecho == NULL)
        while (subraiz->izquierdo != NULL)
            subraiz = subraiz->izquierdo;

    Nodo * padre_mayor = NULL;

    while (subraiz->derecho != NULL) {
        padre_mayor = subraiz;
        subraiz = subraiz->derecho;
    }
    return padre_mayor;
}

 bool auxEliminar(Nodo ** subraiz, Nodo * padre, TipoDato elim)
{
    if ((*subraiz) == NULL) {
        return false;
    }

    int comparacion = compararDato(&elim, &(*subraiz)->dato);

    if (comparacion > 0) {
        return auxEliminar(&(*subraiz)->derecho, *subraiz, elim);
    } else if (comparacion < 0) {
        return auxEliminar(&(*subraiz)->izquierdo, *subraiz, elim);
    }

    int hijos = cantidadHijos(*subraiz);

    if (hijos == 0) {
        if (padre != NULL) {
            if (padre->izquierdo == *subraiz) {
                padre->izquierdo = NULL;
            } else {
                padre->derecho = NULL;
            }
        }
        free(*subraiz);
        *subraiz = NULL;
    } else if (hijos == 1) {
        Nodo * unico_hijo = ((*subraiz)->derecho != NULL) ?
                            (*subraiz)->derecho : (*subraiz)->izquierdo;
        if (padre != NULL) {
            Nodo * aux = *subraiz;
            if (padre->derecho == aux) {
                padre->derecho = unico_hijo;
            } else {
                padre->izquierdo = unico_hijo;
            }
            free(aux);
        } else {
            Nodo * aux = *subraiz;
            *subraiz = unico_hijo;
            free(aux);
        }
    } else {
        Nodo * aux = encontrarPadreRemplazo((*subraiz)->izquierdo);
        Nodo * sustituto = (aux == NULL) ? (*subraiz)->izquierdo : aux->derecho;

        (*subraiz)->dato = sustituto->dato;

        if (aux == NULL)
            (*subraiz)->izquierdo = sustituto->izquierdo;
        else
            aux->derecho = sustituto->izquierdo;
        free(sustituto);
    }

    return true;
}
bool Arbol_Eliminar(Arbol * arbol, TipoDato a_eliminar)
{
    if (auxEliminar(&arbol->raiz, NULL, a_eliminar)) {
        arbol->num_elementos--;
        return true;
    }
    return false;
}

// Funciones que no modifican la estructura del árbol
 TipoDato * auxConsultar(Nodo * subraiz, TipoDato buscado)
{
    if (subraiz == NULL) {
        return NULL;
    }

    int comparacion = compararDato(&buscado, &subraiz->dato);
    if (comparacion == 0) {
        return &subraiz->dato;
    } else if (comparacion < 0) {
        return auxConsultar(subraiz->izquierdo, buscado);
    } else {
        return auxConsultar(subraiz->derecho, buscado);
    }
}
TipoDato * Arbol_Consultar(const Arbol * arbol, TipoDato buscado)
{
    return auxConsultar(arbol->raiz, buscado);
}

bool Arbol_Vacio(const Arbol * arbol)
{
    return arbol->num_elementos == 0;
}
int  Arbol_NumeroElementos(const Arbol * arbol)
{
    return arbol->num_elementos;
}

 void auxImprimir(Nodo * subraiz, int niveles)
{
    for (int i = 0; i < niveles; ++i) {
        printf(".    ");
    }
    if (subraiz != NULL) {
        printf("Dato: ");
        imprimirDato(&subraiz->dato);
        printf("\n");
        auxImprimir(subraiz->izquierdo, niveles + 1);
        auxImprimir(subraiz->derecho, niveles + 1);
    } else {
        printf("(nil)\n");
    }
}

// Funciones que implican recorridos del árbol
void Arbol_Imprimir(const Arbol * arbol)
{
    putchar('\n');
    auxImprimir(arbol->raiz, 0);
}

 void auxRecorrerInOrd(Nodo * sr, FunDato operacion)
{
    if (sr != NULL) {
        auxRecorrerInOrd(sr->izquierdo, operacion);
        operacion(&sr->dato);
        auxRecorrerInOrd(sr->derecho, operacion);
    }
}

 void auxRecorrerPreOrd(Nodo * sr, FunDato operacion)
{
    if (sr != NULL) {
        operacion(&sr->dato);
        auxRecorrerInOrd(sr->izquierdo, operacion);
        auxRecorrerInOrd(sr->derecho, operacion);
    }
}

 void auxRecorrerPosOrd(Nodo * sr, FunDato operacion)
{
    if (sr != NULL) {
        auxRecorrerInOrd(sr->izquierdo, operacion);
        auxRecorrerInOrd(sr->derecho, operacion);
        operacion(&sr->dato);
    }
}
 void (* const funcionRecorrido[])(Nodo *, FunDato) = {
    [IN_ORDER]  = auxRecorrerInOrd,
    [PRE_ORDER] = auxRecorrerPreOrd,
    [POS_ORDER] = auxRecorrerPosOrd
};
void Arbol_Recorrer(const Arbol * arbol, FunDato operacion, enum tipo_recorrido tipo)
{
    funcionRecorrido[tipo](arbol->raiz, operacion);
}
