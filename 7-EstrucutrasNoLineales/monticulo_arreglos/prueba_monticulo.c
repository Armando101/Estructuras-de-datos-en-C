#include "monticulo.h"

#if MONTICULO_EN_PRUEBAS == true
#undef NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
    // Probando un montículo donde los menores elementos salen primero
    Monticulo * m = Monticulo_Nuevo(MENOR_ES_PRIMERO);

    // Al principio la lista debe estar vacía
    assert(Monticulo_Vacio(m) == true);
    assert(Monticulo_NumeroElementos(m) == 0);

    // Insertando elementos en desorden
    assert(Monticulo_Insertar(m, 6) == true);
    assert(Monticulo_Insertar(m, 3) == true);
    assert(Monticulo_Insertar(m, 1) == true);
    assert(Monticulo_Insertar(m, 8) == true);
    assert(Monticulo_Insertar(m, 2) == true);
    assert(Monticulo_Insertar(m, 5) == true);
    assert(Monticulo_Insertar(m, 9) == true);
    assert(Monticulo_Insertar(m, 4) == true);
    assert(Monticulo_Insertar(m, 7) == true);
    assert(Monticulo_Insertar(m, 10) == true);

    // El primer elementos tiene que ser el menor insertado
    assert(Monticulo_ChecarPrimero(m) == 1);

    // El número de elementos debe ser 10
    assert(Monticulo_NumeroElementos(m) == 10);

    puts("Montículo de menores a mayores:");
    Monticulo_Imprimir(m);

    // Eliminando elementos
    TipoDato sacado;
    for (int i = 1; i <= 10; ++i) {
        assert(Monticulo_Eliminar(m, &sacado) == true);
        assert(sacado == i);
    }

    assert(Monticulo_Eliminar(m, &sacado) == false);
    assert(Monticulo_NumeroElementos(m) == 0);
    assert(Monticulo_Vacio(m) == true);

    Monticulo_Liberar(m);

    // Probando un montículo donde los mayor es elementos salen primero
    m = Monticulo_Nuevo(MAYOR_ES_PRIMERO);

    // Al principio la lista debe estar vacía
    assert(Monticulo_Vacio(m) == true);
    assert(Monticulo_NumeroElementos(m) == 0);

    // Insertando elementos en desorden
    assert(Monticulo_Insertar(m, 6) == true);
    assert(Monticulo_Insertar(m, 3) == true);
    assert(Monticulo_Insertar(m, 1) == true);
    assert(Monticulo_Insertar(m, 8) == true);
    assert(Monticulo_Insertar(m, 2) == true);
    assert(Monticulo_Insertar(m, 5) == true);
    assert(Monticulo_Insertar(m, 9) == true);
    assert(Monticulo_Insertar(m, 4) == true);
    assert(Monticulo_Insertar(m, 7) == true);
    assert(Monticulo_Insertar(m, 10) == true);

    // El primer elementos tiene que ser el mayor insertado
    assert(Monticulo_ChecarPrimero(m) == 10);

    // El número de elementos debe ser 10
    assert(Monticulo_NumeroElementos(m) == 10);

    puts("Montículo de mayores a menores");
    Monticulo_Imprimir(m);

    // Eliminando elementos
    for (int i = 1; i <= 10; ++i) {
        assert(Monticulo_Eliminar(m, &sacado) == true);
        assert(sacado == 10 - i + 1);
    }

    assert(Monticulo_Eliminar(m, &sacado) == false);
    assert(Monticulo_NumeroElementos(m) == 0);
    assert(Monticulo_Vacio(m) == true);

    Monticulo_Liberar(m);
}
#endif // LISTA_EN_PRUEBAS
