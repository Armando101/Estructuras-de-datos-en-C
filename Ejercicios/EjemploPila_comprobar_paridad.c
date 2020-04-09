#include "pila.h"

#include <stdio.h>

int main(void)
{
    Pila * p = Pila_Nueva(-1);
    static const char parejas[] = {
        ['('] = ')', [')'] = '(',
        ['{'] = '}', ['}'] = '{',
        ['['] = ']', [']'] = '[',
    };

    puts("Comprobar paridad de símbolos [], {} y ()");

    enum { SIN_ERROR, CHAR_INESPERADO, CIERRE_SIN_APERTURA } error = SIN_ERROR;
    printf("Ingrese una expresión de varias líneas (presione %s para terminar): ",
#ifdef _WIN32
            "Control + Z"
#else
            "Control + D"
#endif
            );

    int c;
    while ((c = getchar()) && c != EOF) {
        if (c == '(' || c == '[' || c == '{') {
            Pila_Insertar(p, c);
        }

        if (c == ')' || c == ']' || c == '}') {
            if (Pila_Vacia(p)) {
                error = CIERRE_SIN_APERTURA; break;
            }
            int tope = Pila_ChecarTope(p);

            if (tope != parejas[c]) {
                // El tope se conserva para futuras referencias
                error = CHAR_INESPERADO; break;
            } else {
                Pila_Eliminar(p, &tope);
            }
        }
    }

    if (!Pila_Vacia(p)) {
        printf("Se encontró EOF mientras se esperaba: '%c'\n",
                parejas[Pila_ChecarTope(p)]);
    } else if (error == CHAR_INESPERADO) {
        printf("Se esperaba '%c' antes de '%c'\n", parejas[Pila_ChecarTope(p)], c);
    } else if (error == CIERRE_SIN_APERTURA) {
        printf("Se ha encontrado un '%c' sin un '%c' previo\n", c, parejas[c]);
    } else {
        printf("La expresión esta balanceada :D\n");
    }
}
