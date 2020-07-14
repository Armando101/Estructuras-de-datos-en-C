#ifndef MONTICULO_H
#define MONTICULO_H

// Cabeceras públicas
#include <stdbool.h>

// Definiciones
#include "tipo_entero.h"
#include "definiciones.h"
typedef struct monticulo Monticulo;

#define MONTICULO_EN_PRUEBAS true

enum tipo_prioridad { MAYOR_ES_PRIMERO, MENOR_ES_PRIMERO };

// Prototipos de función
Monticulo * Monticulo_Nuevo(enum tipo_prioridad tipo_prioridad);
void        Monticulo_Liberar(Monticulo ** monticulo);
#define     Monticulo_Liberar(l) Monticulo_Liberar(&l)

bool Monticulo_Insertar(Monticulo * monticulo, TipoDato dato);
bool Monticulo_Eliminar(Monticulo * monticulo, TipoDato * sacado);

TipoDato Monticulo_ChecarPrimero(const Monticulo * monticulo);

bool Monticulo_Vacio(const Monticulo * monticulo);
int  Monticulo_NumeroElementos(const Monticulo * monticulo);

void Monticulo_Imprimir(const Monticulo * monticulo);

#endif // MONTICULO_H
