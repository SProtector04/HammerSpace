#include <stdio.h>
#include <stdlib.h>

// Definición del nodo
struct Nodo {
    int dato;
    struct Nodo* siguiente;
};

// Función para crear un nuevo nodo
struct Nodo* crearNodo(int valor) {
    struct Nodo* nuevo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevo->dato = valor;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Función para agregar un nodo al final de la lista
void agregarAlFinal(struct Nodo** cabeza, int valor) {
    struct Nodo* nuevo = crearNodo(valor);
    if (*cabeza == NULL) {
        *cabeza = nuevo;
        return;
    }
    struct Nodo* actual = *cabeza;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
}

// Función para imprimir la lista
void imprimirLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("%d -> ", actual->dato);
        actual = actual->siguiente;
    }
    printf("NULL\n");
}

// Función principal
int main() {
    struct Nodo* lista = NULL;

    agregarAlFinal(&lista, 10);
    agregarAlFinal(&lista, 20);
    agregarAlFinal(&lista, 30);

    imprimirLista(lista);

    return 0;
}

  