#include <stdio.h>
#include "StudentData4.h"

void AsignarMemoria(Estudiante **clase, int numEstudiantes) {
    *clase = (Estudiante *)malloc(numEstudiantes * sizeof(Estudiante));
    if (*clase == NULL) {
        printf("Error al asignar memoria.\n");
        return 1; // Salir del programa si no se puede asignar memoria
    }
}

void InicializarEstudiante (Estudiante *est, const char *nombre, int edad, float promedio) {
    strcpy(est->nombre, nombre);
    est->edad = edad;
    est->promedio = promedio;
}

void MostrarEstudiante (const Estudiante *est)
{
    printf("Nombre: %s, Edad: %d, Promedio: %.2f\n", est->nombre, est->edad, est->promedio);
}

void MostrarClase (const Estudiante clase[], int numEstudiantes) {

	int i;
    for (i = 0; i < numEstudiantes; i++) {
        printf("Estudiante %d: ", i +1);
        MostrarEstudiante(&clase[i]);
}
}

