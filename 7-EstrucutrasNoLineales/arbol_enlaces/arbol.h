#ifndef ARBOL_H
#define ARBOL_H

// Cabeceras públicas
#include <stdbool.h>

// Definiciones
#include "tipo_entero.h"
#include "definiciones.h"
typedef struct arbol Arbol;

#define ARBOL_EN_PRUEBAS true

enum tipo_recorrido { IN_ORDER, PRE_ORDER, POS_ORDER };

// Prototipos de función
Arbol * Arbol_Nuevo(void);
void    Arbol_Liberar(Arbol ** arbol);
#define Arbol_Liberar(l) Arbol_Liberar(&l)

bool Arbol_Insertar(Arbol * arbol, TipoDato dato);
bool Arbol_Eliminar(Arbol * arbol, TipoDato a_eliminar);

TipoDato * Arbol_Consultar(const Arbol * arbol, TipoDato buscado);

bool Arbol_Vacio(const Arbol * arbol);
int  Arbol_NumeroElementos(const Arbol * arbol);

void Arbol_Imprimir(const Arbol * arbol);
void Arbol_Recorrer(const Arbol * arbol, FunDato operacion,
                    enum tipo_recorrido tipo);

#endif // ARBOL_H
