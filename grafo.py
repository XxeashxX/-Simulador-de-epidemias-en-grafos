import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D

# Leer los archivos CSV
matrices_de_adyacencia = pd.read_csv('matrices_de_adyacencia.csv', header=None)
GripeSimulacion = pd.read_csv('GripeSimulacion.csv', header=None)
InformeDeEstado = pd.read_csv('InformeDeEstado.csv', header=None, names=['Infectado', 'Recuperado', 'Susceptible'])

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
    matriz_dia = matrices_de_adyacencia.iloc[dia * len(GripeSimulacion):(dia + 1) * len(GripeSimulacion)]
    for i in range(len(matriz_dia) - 1):
        for j in range(len(matriz_dia.columns)):
            if matriz_dia.iloc[i, j] == 1:  # Si hay una arista entre los nodos i y j
                G.add_edge(i, j)

    # Dibujar el grafo
    plt.figure(dia)
    colores = ['red' if G.nodes[nodo]['estado'] == 1 else 'yellow' if G.nodes[nodo]['estado'] == 0 else 'green' for nodo in G.nodes()]
    nx.draw(G, with_labels=True, node_color=colores)

    # Agregar la leyenda con información del InformeDeEstado para el día actual
    infectados = InformeDeEstado.iloc[dia, 0]
    recuperados = InformeDeEstado.iloc[dia, 1]
    susceptibles = InformeDeEstado.iloc[dia, 2]
    legend_text = f'Día {dia+1} - Infectados: {infectados}, Recuperados: {recuperados}, Susceptibles: {susceptibles}'
    legend_elements = [Line2D([0], [0], marker='o', color='w', label=legend_text, markerfacecolor='red', markersize=10)]
    plt.legend(handles=legend_elements, loc='upper right')

    # Guardar la imagen en un archivo
    plt.savefig(f'grafo_dia_{dia+1}.png')

plt.close('all')  # Cerrar todas las figuras
