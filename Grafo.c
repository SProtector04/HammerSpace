#include <stdio.h>
#include <stdlib.h>

// Estructura para un nodo de la lista de adyacencia
struct NodoAdyacente {
    int destino;
    struct NodoAdyacente* siguiente;
};

// Estructura para la lista de adyacencia
struct ListaAdyacencia {
    struct NodoAdyacente* cabeza;
};

// Estructura del grafo
struct Grafo {
    int numVertices;
    struct ListaAdyacencia* array;
};

// Función para crear un nuevo nodo
struct NodoAdyacente* crearNodo(int destino) {
    struct NodoAdyacente* nuevoNodo = (struct NodoAdyacente*)malloc(sizeof(struct NodoAdyacente));
    nuevoNodo->destino = destino;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

// Función para crear un grafo de V vértices
struct Grafo* crearGrafo(int V) {
    struct Grafo* grafo = (struct Grafo*)malloc(sizeof(struct Grafo));
    grafo->numVertices = V;

    grafo->array = (struct ListaAdyacencia*)malloc(V * sizeof(struct ListaAdyacencia));

    for (int i = 0; i < V; ++i)
        grafo->array[i].cabeza = NULL;

    return grafo;
}

// Agrega una arista al grafo (no dirigido)
void agregarArista(struct Grafo* grafo, int origen, int destino) {
    // Agregar destino al origen
    struct NodoAdyacente* nuevoNodo = crearNodo(destino);
    nuevoNodo->siguiente = grafo->array[origen].cabeza;
    grafo->array[origen].cabeza = nuevoNodo;

    // Agregar origen al destino (porque es no dirigido)
    nuevoNodo = crearNodo(origen);
    nuevoNodo->siguiente = grafo->array[destino].cabeza;
    grafo->array[destino].cabeza = nuevoNodo;
}

// Función para imprimir el grafo
void imprimirGrafo(struct Grafo* grafo) {
    for (int v = 0; v < grafo->numVertices; ++v) {
        struct NodoAdyacente* temp = grafo->array[v].cabeza;
        printf("Lista de adyacencia del vértice %d: ", v);
        while (temp) {
            printf("-> %d ", temp->destino);
            temp = temp->siguiente;
        }
        printf("\n");
    }
}

// Función principal
int main() {
    int V = 5;
    struct Grafo* grafo = crearGrafo(V);

    agregarArista(grafo, 0, 1);
    agregarArista(grafo, 0, 4);
    agregarArista(grafo, 1, 2);
    agregarArista(grafo, 1, 3);
    agregarArista(grafo, 1, 4);
    agregarArista(grafo, 2, 3);
    agregarArista(grafo, 3, 4);

    imprimirGrafo(grafo);

    return 0;
}
