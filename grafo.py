import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt

# Leer los archivos CSV
matrices_de_adyacencia = pd.read_csv('matrices_de_adyacencia.csv', header=None)
GripeSimulacion = pd.read_csv('GripeSimulacion.csv', header=None)

# Calcular el número de días
num_dias = (len(GripeSimulacion.columns))
print(num_dias)
# Crear un grafo para cada día
grafos = []
for dia in range(num_dias):
    # Crear un grafo vacío
    G = nx.DiGraph()
    # Añadir nodos al grafo
    for i in range(len(GripeSimulacion)):
        nodo = i
        estado = GripeSimulacion.iloc[i, dia]  # El estado del nodo en el día actual
        G.add_node(nodo, estado=estado)

    # Añadir aristas al grafo
    matriz_dia = matrices_de_adyacencia.iloc[dia*len(GripeSimulacion):(dia+1)*len(GripeSimulacion)]
    for i in range(len(matriz_dia)-1):
        for j in range(len(matriz_dia.columns)):
            if matriz_dia.iloc[i, j] == 1:  # Si hay una arista entre los nodos i y j
                G.add_edge(i, j)


    # Añadir el grafo a la lista de grafos
    grafos.append(G)

# Dibujar el grafo para cada día
for i, G in enumerate(grafos):
    plt.figure(i)
    nx.draw(G, with_labels=True)
    


plt.show()
