#include "monticulo.h"

#include <stdio.h>
#include <stdlib.h>

// Definir la estructura del tipo de dato
struct monticulo {
    int tamanio;
    int num_elementos;

    enum tipo_prioridad tipo_prioridad;

    TipoDato * contenido;
};

// Funciones para crear y liberar el montículo
Monticulo * Monticulo_Nuevo(enum tipo_prioridad tipo_prioridad)
{
    Monticulo * nuevo = RESERVAR(1, Monticulo);
    *nuevo = (Monticulo) { .tamanio = 16,
                           .contenido = RESERVAR(16, TipoDato),
                           .tipo_prioridad = tipo_prioridad };
    return nuevo;
}

#undef Monticulo_Liberar
void   Monticulo_Liberar(Monticulo ** monticulo)
{
    free((*monticulo)->contenido);
    free(*monticulo);
    *monticulo = NULL;
}

bool Monticulo_Insertar(Monticulo * monticulo, TipoDato dato)
{
    if (monticulo->num_elementos == monticulo->tamanio) {
        monticulo->tamanio *= 2;
        TipoDato * tmp = REDIM(monticulo->contenido, monticulo->tamanio, TipoDato);
        if (tmp == NULL) {
            monticulo->tamanio /= 2;
            return false;
        }
        monticulo->contenido = tmp;
    }

    int n = monticulo->num_elementos;

    while (n != 0) {
        int padre = (n - n % 2) / 2;
        int comp = compararDato(&dato, &monticulo->contenido[padre]);
        if (monticulo->tipo_prioridad == MAYOR_ES_PRIMERO) {
            comp *= -1;
        }

        if (comp >= 0) {
            break;
        } else if (comp < 0) {
            monticulo->contenido[n] = monticulo->contenido[padre];
            n = padre;
        }
    }
    monticulo->contenido[n] = dato;
    monticulo->num_elementos++;
    return true;
}

bool Monticulo_Eliminar(Monticulo * monticulo, TipoDato * sacado)
{
    if (Monticulo_Vacio(monticulo)) {
        return false;
    }
    TipoDato * cnt = monticulo->contenido;
    *sacado = cnt[0];
    monticulo->num_elementos--;
    int sustituto = cnt[monticulo->num_elementos];

    int n = 0;
    while ((n * 2 + 1) < monticulo->num_elementos) {
        int ind_hijo_izq = n * 2 + 1;
        int ind_hijo_der = ind_hijo_izq + 1;

        int cmp_hijos = compararDato(&cnt[ind_hijo_izq], &cnt[ind_hijo_der]);
        if (monticulo->tipo_prioridad == MAYOR_ES_PRIMERO) {
            cmp_hijos *= -1;
        }

        if (cmp_hijos < 0) {
            int cmp_dato = compararDato(&sustituto, &cnt[ind_hijo_izq]);
            if (monticulo->tipo_prioridad == MAYOR_ES_PRIMERO) {
                cmp_dato *= -1;
            }
            if (cmp_dato > 0) {
                cnt[n] = cnt[ind_hijo_izq];
                n = ind_hijo_izq;
            } else {
                break;
            }
        } else {
            int cmp_dato = compararDato(&sustituto, &cnt[ind_hijo_der]);
            if (monticulo->tipo_prioridad == MAYOR_ES_PRIMERO) {
                cmp_dato *= -1;
            }
            if (cmp_dato > 0) {
                cnt[n] = cnt[ind_hijo_der];
                n = ind_hijo_der;
            } else {
                break;
            }
        }

    }
    cnt[n] = sustituto;

    return true;
}

TipoDato Monticulo_ChecarPrimero(const Monticulo * monticulo)
{
    if (Monticulo_Vacio(monticulo)) {
        fputs("Error. Montículo vacío", stderr);
        exit(EXIT_FAILURE);
    }
    return monticulo->contenido[0];
}

bool Monticulo_Vacio(const Monticulo * monticulo)
{
    return monticulo->num_elementos == 0;
}

int  Monticulo_NumeroElementos(const Monticulo * monticulo)
{
    return monticulo->num_elementos;
}

void Monticulo_Imprimir(const Monticulo * monticulo)
{
    unsigned nivel = 1;
    for (int i = 0; i < monticulo->num_elementos; ++i) {
        if (i == (1 << nivel) - 1) {
            nivel++;
        }
        for (unsigned j = 1; j < nivel; ++j) {
            printf(".   ");
        }
        imprimirDato(&monticulo->contenido[i]);
        printf("\n");
    }
}
