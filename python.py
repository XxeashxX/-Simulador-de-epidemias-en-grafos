import pandas as pd
import matplotlib.pyplot as plt


GripeSimulacion = open("GripeSimulacion.csv")

linea = GripeSimulacion.readline()
linea.replace("\n", "")

lista = []

while linea != "":
    lista.append(linea.split(","))    
    linea = GripeSimulacion.readline()
    linea.replace("\n", "")
GripeSimulacion.close()

for fila in lista:
    for elemento in fila:
        print(elemento, end=" ")  # El argumento end=" " evita que se añada un salto de línea después de cada elemento
    print()  # Agrega un salto de línea al final de cada fila