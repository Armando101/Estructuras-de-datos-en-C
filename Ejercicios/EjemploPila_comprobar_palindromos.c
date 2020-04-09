#include "pila.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    enum { TAM_CADENA = 100 };
    char cadena[TAM_CADENA];

    puts("----- Comprobar si una cadena es un palíndromo -----\n");
    printf("Ingresa una cadena: ");
    fgets(cadena, TAM_CADENA, stdin);

    int largo = strlen(cadena) - 1;

    Pila * inversor = Pila_Nueva(largo);

    for (int i = 0; i < largo; ++i)
        Pila_Insertar(inversor, cadena[i]);

    _Bool palindromo = 1;

    for (int i = 0; i < largo; ++i) {
        int sacado;
        Pila_Eliminar(inversor, &sacado);
        if (sacado != cadena[i]) {
            palindromo = false;
            break;
        }
    }

    Pila_Liberar(inversor);

    printf("La cadena %s es un palíndromo\n", palindromo ? "si" : "no");
}
