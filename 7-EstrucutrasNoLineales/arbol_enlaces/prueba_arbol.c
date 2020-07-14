#include "arbol.h"

#if ARBOL_EN_PRUEBAS == true
#undef NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum { CANTIDAD_INSERTAR = 5 };
_Static_assert(CANTIDAD_INSERTAR <= 100, "Solo valores de 1 al 100");

int main(void)
{
    Arbol * a = Arbol_Nuevo();
    TipoDato insertados[CANTIDAD_INSERTAR];

    // Al principio la lista debe estar vacía
    assert(Arbol_Vacio(a) == true);
    assert(Arbol_NumeroElementos(a) == 0);

    // Insertando elementos
    for (int i = 1; i <= CANTIDAD_INSERTAR; ++i) {
        int a_insertar;

        bool continuar;
        do {
            continuar = false;
            a_insertar = rand() % 100;
            for (int j = 0; j < i; ++j) {
                if (insertados[j] == a_insertar) {
                    continuar = true;
                    break;
                }
            }
        } while (continuar);

        insertados[i - 1] = a_insertar;
        assert(Arbol_Insertar(a, a_insertar));
        assert(Arbol_NumeroElementos(a) == i);
    }

    // Revisamos que los elementos insertados se encuentren ahí
    for (int i = 0; i < CANTIDAD_INSERTAR; ++i) {
        int * consultado = Arbol_Consultar(a, insertados[i]);
        assert(consultado != NULL);
        assert(*consultado == insertados[i]);
    }

    // Recorridos para imprimir
    printf("Árbol en orden normal: ");  Arbol_Imprimir(a);

    Arbol_Recorrer(a, multiplicar5, IN_ORDER);
    puts("Tras multiplicar por 5:");
    printf("Árbol en orden normal: ");  Arbol_Imprimir(a);

    Arbol_Recorrer(a, dividir5, PRE_ORDER);

    puts("Tras dividir por 5:");
    printf("Árbol en orden normal: ");  Arbol_Imprimir(a);

    // Sacamos los elementos de la lista
    for (int i = 0; i < CANTIDAD_INSERTAR; ++i) {
        assert(Arbol_Eliminar(a, insertados[i]) == true);
        assert(Arbol_Consultar(a, insertados[i]) == NULL);
        assert(Arbol_NumeroElementos(a) == CANTIDAD_INSERTAR - i - 1);
    }

    // La lista nuevamente debe estar vacía
    assert(Arbol_Vacio(a) == true);

    Arbol_Liberar(a);
}
#endif // LISTA_EN_PRUEBAS
