#include "epidemias.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Función para simular la propagación de la Gripe
void simularGripe(int dias, int CantidadNodos, int porcentajeDeInfectadosIniciales) {
    int filas = 5; // Número de filas
    int columnas = 5; // Número de columnas
    int **matrizDeDatos;
    matrizDeDatos = (int**) malloc((dias+1) * sizeof(int *));
    for(int i = 0; i < dias+1; i++) {
        matrizDeDatos[i] = (int*) malloc((filas*columnas+1) * sizeof(int));
    }


    for (int i = 0; i < dias+1; i++) {
        for (int j = 0; j <(filas*columnas)+1; j++) {
            matrizDeDatos[i][j] = 7;
        }
    }

    struct nodo{
        struct Gripe epidemia;  // La estructura de la epidemia se incluye directamente en el nodo
    };

    // Crear una matriz bidimensional de nodos utilizando un puntero
    struct nodo** matrizNodos = (struct nodo**)malloc(filas * sizeof(struct nodo*));
    for(int i = 0; i < filas; i++) {
    matrizNodos[i] = (struct nodo*)malloc(columnas * sizeof(struct nodo));
    }  
    //inicializa tipo de nodo
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){    
            int random = rand() % 2;
            // Inicializar el estado inicial de los nodos
            if (random == 0){
                matrizNodos[i][j].epidemia.TipoDeNodo.TipoNodo = persona;
            }
            else{
                matrizNodos[i][j].epidemia.TipoDeNodo.TipoNodo = Objeto;
            }
        }
    }
    //inicializar nodos infectados
    int cont=0;
    while (cont < porcentajeDeInfectadosIniciales){
        printf(" contador %d\n", cont);
        int filaAleatoria = rand() % filas;
        int columnaAleatoria = rand() % columnas;
        if(matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado != Infectado){
            matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado = Infectado;
            matrizDeDatos[0][filaAleatoria*columnas+ columnaAleatoria] = 1;
            cont +=1;
        }
    }    
    
    

    printf("tipo de nodos iniciados\n");
    
    //iniciar los nodos suceptibles
    for (int i = 0; i < filas; i++){
        for (int j = 0; j < columnas; j++){
            if (matrizNodos[i][j].epidemia.Estado != Infectado){
                matrizNodos[i][j].epidemia.Estado = Susceptible;
                matrizDeDatos[0][i*columnas+j] = 0;

            }               
        }
    }

    // Simular la propagación durante un cierto número de días
    bool confirmacion = false;
    for (int dia = 0; dia < dias; dia++) {
        //ciclo para recorrer cada nodo
        for (int i = 0; i <filas; i++){
            for (int j = 0; j < columnas; j++){         
                int indice = (i*columnas+ j);
                int interacciones = rand() % (CantidadNodos + 1);// con cuantos nodos va a interactuar en el dia este nodo
                //ciclo de interacciones que va a tener el nodo durante el dia
                for (int interaccion = 0; interaccion < interacciones; interaccion++){
                    confirmacion = false;
                    //interaccion si el nodo esta infectado con un nodo random no infectado
                    int filaAleatoria = rand() % filas;
                    int columnaAleatoria = rand() % columnas;
                    int indiceAleatorio = (filaAleatoria*columnas+columnaAleatoria);
                    if(matrizNodos[i][j].epidemia.Estado == Infectado){
                        if (matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado != Infectado){
                            // Simulación simple: la persona se vuelve infectada aleatoriamente
                            if (rand() % 100 < 30) {
                                matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado = Infectado;
                                matrizDeDatos[dia][indiceAleatorio] = 1;
                                printf("nodo[%d]: 1", indice);
                                printf("\n");
                                confirmacion = true;
                            }
                        }
                    }
                    else{
                        //si el nodo no esta infectado pero interactua con uno infectado 
                       if (rand() % 100 < 30 && matrizNodos[filaAleatoria][columnaAleatoria].epidemia.Estado == Infectado){
                            matrizNodos[i][j].epidemia.Estado = Infectado;
                            matrizDeDatos[dia][indice] = 1;
                            printf("nodo[%d]: 1", indice);
                                    printf("\n");

                            confirmacion = true;

                        }
                    }
                    if (confirmacion==true && matrizDeDatos[dia][(i*columnas+j)] == 2){  
                        matrizDeDatos[dia][(i*columnas+j)] = 2;
                        printf("nodo[%d] %d",(i * columnas + j),matrizDeDatos[dia][(i * columnas + j)]);
                        printf("\n");
                    }

                }
                 // Simulación simple: el nodo se recupera aleatoriamente
                if (matrizNodos[i][j].epidemia.Estado == Infectado && rand() % 100 < 20) {
                    matrizNodos[i][j].epidemia.Estado = Recuperado;
                    matrizDeDatos[dia][indice] = 2;
                            printf("nodo[%d]: 2", indice);
                            printf("\n");
                }
            }
        }
    }
    for (int i = 0; i < filas; i++){
        free(matrizNodos[i]); //libera memoria asignada a matrizNodos
    }
    //escribir los datos obtenidos en archivo csv
    FILE *file = fopen("GripeSimulacion.csv", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        exit(1);
    }
    fprintf(file, "dia1\tdia2\tdia3\tdia4\tdia5\tdia6\tdia7\tdia8\tdia9\tdia10\n");  
      
    for (int i = 0; i < (dias); i++) {
        for (int j = 0; j <(filas*columnas); j++) {
            fprintf(file, "%d", matrizDeDatos[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    for(int i = 0; i < dias+1; i++) {
        free(matrizDeDatos[i]);
    }
    free(matrizDeDatos);

}