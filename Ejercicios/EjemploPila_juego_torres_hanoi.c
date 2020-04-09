#include "pila.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const char * lado_torre[] = {
    "##",
    "###",
    "####",
    "#####",
    "######"
};

enum mov { ORIGEN, DESTINO };

void imprimirTorres(Pila * torres[3]);
bool movimientoValido(Pila * torres[3], int origen, int destino);
void actualizarJuego(Pila * torres[3], int origen, int destino);

int leerNumTorre(enum mov m);
void limpiarPantalla(void);
void limpiarBuffer(void);

int main(void)
{
    puts("+---------------------------+\n"
         "| Torres de hanoi: El juego |\n"
         "+---------------------------+\n");

    printf("Presione cualquier tecla para continuar . . . \n");
    limpiarBuffer();

    // Preparando el juego
    bool ganado = false;
    Pila * torres[3] = { Pila_Nueva(5), Pila_Nueva(5), Pila_Nueva(5) };
    for (int i = 4; i >= 0; --i) {
        Pila_Insertar(torres[0], i);
    }

    while (!ganado) {
        limpiarPantalla();
        imprimirTorres(torres);

        int torre_origen, torre_desino;
        bool seguirPreguntando;
        do {
            torre_origen = leerNumTorre(ORIGEN);
            torre_desino = leerNumTorre(DESTINO);
            if (!movimientoValido(torres, torre_origen, torre_desino)) {
                seguirPreguntando = true;
                printf("No se puede realizar ese movimiento\n");
            } else {
                seguirPreguntando = false;
            }

        } while(seguirPreguntando);

        actualizarJuego(torres, torre_origen, torre_desino);

        ganado = Pila_NumeroElementos(torres[2]) == 5;
    }

    limpiarPantalla();
    imprimirTorres(torres);
    printf("\n\n"
           "****** Felicidades, Has ganado *****\n");
}

void imprimirTorres(Pila * torres[3])
{
    for (int i = 5; i >= 1; --i) {
        for (int j = 0; j < 3; ++j) {
            int n = Pila_NumeroElementos(torres[j]);
            if (n >= i) {
                int valor = Pila_ChecarPosN(torres[j], n - i);
                printf("\t\t%7s%-7s", lado_torre[valor], lado_torre[valor]);
            } else {
                printf("\t\t%14s", "");
            }
        }
        putchar('\n');
    }
    printf("\t\t   Torre 1   \t\t   Torre 2   \t\t   Torre 2   \n");
}
bool movimientoValido(Pila * torres[3], int origen, int destino)
{
    if (Pila_Vacia(torres[origen])) {
        return false;
    }
    if (Pila_Vacia(torres[destino])) {
        return true;
    }
    if (Pila_ChecarTope(torres[origen]) > Pila_ChecarTope(torres[destino])) {
        return false;
    }
    return true;
}
void actualizarJuego(Pila * torres[3], int origen, int destino)
{
    int sacado;
    Pila_Eliminar(torres[origen], &sacado);
    Pila_Insertar(torres[destino], sacado);
}

int leerNumTorre(enum mov m)
{
    int torre;
    bool es_valida;

    do {
        printf("Ingresa el número de torre de %s (1-3): ",
                m == ORIGEN ? "origen" : "destino");
        es_valida = scanf("%d", &torre) && torre >= 1 && torre <= 3;

        if (!es_valida) {
            puts("Esa torre no existe");
            limpiarBuffer();
        }
    } while (!es_valida);
    return torre - 1; // Para contar desde 0
}

void limpiarPantalla(void)
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limpiarBuffer(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}
