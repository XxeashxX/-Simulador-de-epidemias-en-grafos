#include "epidemias.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para simular la propagación de la Gripe
void simularGripe(int dias, int filas, int columnas, int porcentajeDeInfectadosIniciales) {
    int CantidadNodos = filas * columnas;
    int **matrizDeDatos;
    matrizDeDatos = (int **)malloc(((filas * columnas)) * sizeof(int *));
    for (int i = 0; i < (filas * columnas); i++) {
        matrizDeDatos[i] = (int *)malloc(dias * sizeof(int));
    }

    for (int i = 0; i < (filas * columnas); i++) {
        for (int j = 0; j < dias; j++) {
            matrizDeDatos[i][j] = Susceptible;
        }
    }

    struct nodo
    {
        struct Gripe epidemia; // La estructura de la epidemia se incluye directamente en el nodo
    };

    // Crear una matriz bidimensional de nodos utilizando un puntero
    struct nodo **matrizNodos = (struct nodo **)malloc(filas * sizeof(struct nodo *));
    for (int i = 0; i < filas; i++)
    {
        matrizNodos[i] = (struct nodo *)malloc(columnas * sizeof(struct nodo));
    }
    //inicializa tipo de nodo
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            int random = rand() % 2;
            // Inicializar el estado inicial de los nodos
            if (random == 0)
            {
                matrizNodos[i][j].epidemia.TipoDeNodo.TipoNodo = persona;
            }
            else
            {
                matrizNodos[i][j].epidemia.TipoDeNodo.TipoNodo = Objeto;
            }
        }
    }
    //inicializar nodos infectados
    int cont = 0;
    while (cont < porcentajeDeInfectadosIniciales)
    {
        int filaAleatoria = rand() % filas;
        int columnaAleatoria = rand() % columnas;
        if (matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado != Infectado)
        {
            matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado = Infectado;
            matrizDeDatos[0][filaAleatoria * columnas + columnaAleatoria] = Infectado;
            cont += 1;
        }
    }
    //iniciar los nodos suceptibles
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (matrizNodos[i][j].epidemia.Estado != Infectado)
            {
                matrizNodos[i][j].epidemia.Estado = Susceptible;
                matrizDeDatos[0][i * columnas + j] = Susceptible;
            }
        }
    }

    // Simular la propagación durante un cierto número de días
    bool confirmacion = false;
    for (int dia = 0; dia < dias; dia++)
    {
        //ciclo para recorrer cada nodo
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                int indice = (i * columnas + j);
                //repite el estado del dia anterior
                if (dia - 1 >= 0){
                    if (matrizDeDatos[indice][dia - 1] == 2){
                        matrizNodos[i][j].epidemia.Estado = Recuperado;
                        matrizDeDatos[indice][dia] = Recuperado;
                    }
                    else{
                        if (matrizDeDatos[indice][dia - 1] == 1){
                            matrizNodos[i][j].epidemia.Estado = Infectado;
                            matrizDeDatos[indice][dia] = Infectado;
                        }
                    }
                }

                int interacciones = rand() % (CantidadNodos); // con cuántos nodos va a interactuar en el día este nodo
                //ciclo de interacciones que va a tener el nodo durante el día
                for (int interaccion = 0; interaccion < interacciones; interaccion++){
                    confirmacion = false;
                    //interacción si el nodo está infectado con un nodo random no infectado
                    int filaAleatoria = rand() % filas;
                    int columnaAleatoria = rand() % columnas;
                    int indiceAleatorio = (filaAleatoria * columnas + columnaAleatoria);

                    // consulta si el estado del nodo en el momento es infectado, si el día anterior estaba infectado y si no está recuperado
                    if (matrizNodos[i][j].epidemia.Estado == Infectado && matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado != Recuperado){
                        // Simulación simple: la persona infectada aleatoriamente
                        if (rand() % 100 < 5)
                        {
                            matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado = Infectado;
                            matrizDeDatos[indiceAleatorio][dia] = Infectado;
                            confirmacion = true;
                        }
                    }
                    else{
                        //si el nodo no está infectado pero interactúa con uno infectado
                        if (rand() % 100 < 5 && matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado == Infectado && matrizNodos[i][j].epidemia.Estado != Recuperado)
                        {
                            matrizNodos[i][j].epidemia.Estado = Infectado;
                            matrizDeDatos[indice][dia] = Infectado;
                            confirmacion = true;
                        }
                    }
                    // Simulación simple: el nodo se recupera aleatoriamente
                    if (matrizNodos[i][j].epidemia.Estado == Infectado && matrizDeDatos[indice][dia] == Infectado){
                        if (rand() % 100 < 0.25)
                        {
                            matrizNodos[i][j].epidemia.Estado = Recuperado;
                            matrizDeDatos[indice][dia] = Recuperado;
                        }
                    }
                    if (confirmacion == true && dia - 1 >= 0 && matrizDeDatos[indice][dia - 1] == Infectado)
                    {
                        matrizNodos[i][j].epidemia.Estado = Infectado;
                        matrizDeDatos[indice][dia] = Infectado;
                    }
                    else{
                        if (confirmacion == true && dia - 1 >= 0 && matrizDeDatos[indice][dia - 1] == Recuperado)
                        {
                            matrizNodos[i][j].epidemia.Estado = Recuperado;
                            matrizDeDatos[indice][dia] = Recuperado;
                        }
                        else{
                            if (confirmacion == true && dia - 1 >= 0 && matrizDeDatos[indice][dia - 1] == Susceptible)
                            {
                                matrizNodos[i][j].epidemia.Estado = Susceptible;
                                matrizDeDatos[indice][dia] = Susceptible;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < filas; i++)
    {
        free(matrizNodos[i]); //libera memoria asignada a matrizNodos
    }
    //escribir los datos obtenidos en archivo csv
    FILE *file = fopen("GripeSimulacion.csv", "w");
    if (file == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    for (int i = 1; i <= dias; i++){
        if (i < dias){
        fprintf(file, "dia%d,", i);
        }
        else{
            fprintf(file, "dia%d", i);
        }
        
    }
    fprintf(file, "\n");
    //fprintf(file, "dia1\tdia2\tdia3\tdia4\tdia5\tdia6\tdia7\tdia8\tdia9\tdia10\n");
    for (int i = 0; i < (filas * columnas); i++)
    {
        for (int j = 0; j < dias; j++){
            if (j == dias-1){
                fprintf(file, "%d", matrizDeDatos[i][j]);
            }else {
                fprintf(file, "%d,", matrizDeDatos[i][j]);
            }
            
        }
        fprintf(file, "\n");
    }
    fclose(file);
    for (int i = 0; i < dias + 1; i++)
    {
        free(matrizDeDatos[i]);
    }
    free(matrizDeDatos);
}
