#include <stdio.h>
#include <stdlib.h>
#include "StudentData4.h"

int main() {
    const int numEstudiantes = 3;
    Estudiante *clase = NULL;

    // Asignar memoria dinámicamente
    AsignarMemoria(&clase, numEstudiantes);

    // Inicialización de los estudiantes
    InicializarEstudiante(&clase[0], "Ana", 20, 8.5);
    InicializarEstudiante(&clase[1], "Luis", 22, 7.8);
    InicializarEstudiante(&clase[2], "Juan", 21, 9.0);

    // Mostrar los datos de los estudiantes
    MostrarClase(clase, numEstudiantes);

    free(clase);

    return 0;
}
