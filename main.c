#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"  // Incluye el archivo de encabezado grafo.h

int main() {
    srand(time(NULL));  // Inicializar la semilla del generador de números aleatorios

    // Definir los parámetros de la simulación
    int dias = 10;
    int CantidadNodos = 25;
    int porcentajeDeInfectadosIniciales = int(2);

    // Llama a la función para simular la propagación de la Gripe
    simularGripe(dias, CantidadNodos, porcentajeDeInfectadosIniciales);

    return 0;
}
