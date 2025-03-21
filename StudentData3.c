#include <stdio.h>
#include <string.h>

typedef struct {

    char nombre[50];

    int edad;

    float promedio;

} Estudiante;

void InicializarEstudiante (Estudiante *est, const char *nombre, int edad, float promedio);
void MostrarEstudiante (const Estudiante *est);
void MostrarClase (const Estudiante clase[], int numEstudiantes);

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

    for ( i = 0; i < numEstudiantes; i++) {
        printf("Estudiante %d: ", i +1);
        MostrarEstudiante(&clase[i]);
}
}

int main () {
    int numEstudiantes = 3;
    Estudiante clase[numEstudiantes];

//Inicializacion de los estudiantes
InicializarEstudiante(&clase[0], "Ana", 20, 8.5);
InicializarEstudiante(&clase[1], "Luis", 22, 7.8);
InicializarEstudiante(&clase[2], "Juan", 21, 9.0);


    // Mostrar los datos de los estudiantes
    MostrarClase(clase, numEstudiantes);
}
