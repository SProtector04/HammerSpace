#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#define MAXTAMCAD 1000 

/*Definición del dato que contiene un nodo*/
typedef struct { 
    int clave; 
} Item; 

/*Definición de un nodo del árbol*/
typedef struct Elemento { 
    Item dato; 
    struct Elemento *padre, *izq, *der; 
} Nodo;

/*Definición del árbol. Nota: También podía emplearse directamente un nodo que 
represente a la raíz del árbol.*/
typedef struct { 
    Nodo *raiz; 
} ArbolBin;

/*Reserva el espacio en memoria para un nodo, cargándole el Item x. 
La función devuelve la dirección de ese nodo.*/
Nodo* crearNodo(Item x) { 
    Nodo *a = malloc(sizeof(Nodo)); 
    a->dato = x; 
    a->padre = NULL; 
    a->izq = NULL; 
    a->der = NULL; 
    return a; 
} 

/*Asigna un valor NULL a la raíz del árbol binario*/
void inicializarArbolBin(ArbolBin *arb) { 
    arb->raiz = NULL; 
} 

/*Muestra la información de un nodo*/
void mostrarNodo(Nodo *v) { 
    printf("Nodo %d ---> ", v->dato.clave); 
    if (v->padre != NULL) 
        printf("padre: %d\t", v->padre->dato.clave); 
    else 
        printf("padre: ninguno\t");
    if (v->izq != NULL) 
        printf("h_izq: %d\t", v->izq->dato.clave); 
    else 
        printf("h_izq: ninguno\t"); 
    if (v->der != NULL) 
        printf("h_der: %d\n", v->der->dato.clave); 
    else 
        printf("h_der: ninguno\n"); 
} 

/*Función recursiva para mostrar los elementos de un árbol*/
void mostrarArbolBinRec(Nodo *nodo, char cad[]) { 
    printf("%d\n", nodo->dato.clave);
    // Para el hijo izquierdo 
    if (nodo->izq != NULL) {
        char cad2[MAXTAMCAD]; 
        strcpy(cad2, cad); 
        if (nodo->der != NULL) { 
            printf("%s%c%c%c%c%c", cad, 195, 196, 196, 196, 196); 
            char simb = 179, aux[2]; 
            aux[0] = simb; aux[1] = '\0'; 
            strcat(cad2, aux); 
            strcat(cad2, " "); 
            mostrarArbolBinRec(nodo->izq, cad2); 
        } else { 
            printf("%s%c%c%c%c%c", cad, 192, 196, 196, 196, 196); 
            strcat(cad2, " "); 
            mostrarArbolBinRec(nodo->izq, cad2); 
        }
    } 
    // Para el hijo derecho 
    if (nodo->der != NULL) { 
        char cad3[MAXTAMCAD]; 
        strcpy(cad3, cad); 
        printf("%s%c%c%c%c%c", cad, 192, 196, 196, 196, 196); 
        strcat(cad3, " "); 
        mostrarArbolBinRec(nodo->der, cad3); 
    } 
}

/*Función que permite visualizar la estructura de un árbol binario*/
void mostrarArbolBin(ArbolBin arb) { 
    if (arb.raiz == NULL) 
        printf("El arbol esta vacio!!\n"); 
    else 
        mostrarArbolBinRec(arb.raiz, ""); 
} 

int main() { 
    ArbolBin arbol; 
    inicializarArbolBin(&arbol); 
    // Construcción del árbol
    Item x; 
    Nodo *nodo1, *nodo2, *nodo3, *nodo4, *nodo5, *nodo6, *nodo7, *nodo8, *nodo9, *nodo10, *nodo11; 

    x.clave = 51; 
    nodo1 = crearNodo(x); 
    arbol.raiz = nodo1; 

    x.clave = 100; 
    nodo2 = crearNodo(x); 
    nodo1->izq = nodo2; 
    nodo2->padre = nodo1; 

    x.clave = 3; 
    nodo3 = crearNodo(x); 
    nodo3->padre = nodo1; 
    nodo1->der = nodo3; 

    x.clave = 20; 
    nodo4 = crearNodo(x); 
    nodo4->padre = nodo2; 
    nodo2->izq = nodo4; 

    x.clave = 10; 
    nodo5 = crearNodo(x); 
    nodo5->padre = nodo2; 
    nodo2->der = nodo5;

    x.clave = 7; 
    nodo6 = crearNodo(x); 
    nodo6->padre = nodo4; 
    nodo4->izq = nodo6;

    x.clave = 4; 
    nodo7 = crearNodo(x); 
    nodo7->padre = nodo4; 
    nodo4->der = nodo7; 

    x.clave = 64; 
    nodo8 = crearNodo(x); 
    nodo8->padre = nodo6; 
    nodo6->der = nodo8; 

    x.clave = 2; 
    nodo9 = crearNodo(x); 
    nodo9->padre = nodo3; 
    nodo3->izq = nodo9; 

    x.clave = 34; 
    nodo10 = crearNodo(x); 
    nodo10->padre = nodo5; 
    nodo5->izq = nodo10; 

    x.clave = 12; 
    nodo11 = crearNodo(x); 
    nodo11->padre = nodo3; 
    nodo3->der = nodo11; 

    // Test Mostrar info de un nodo 
    mostrarNodo(nodo4);

    // Test Mostrar árbol
    printf("\nEl arbol es: \n"); 
    mostrarArbolBin(arbol); 

    return 0; 
}
