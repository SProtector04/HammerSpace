#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int edad;
    float promedio;
    } Estudiante;

    int main() {
        Estudiante clase[3];
        strcpy(clase[0].nombre,"Ana");
        clase[0].edad = 20;
        clase[0].promedio = 8.5;

        strcpy(clase[1].nombre,"Luis");
        clase[1].edad = 22;
        clase[1].promedio = 7.8;

        strcpy(clase[2].nombre, "Juan");
        clase[2].edad = 21;
        clase[2].promedio = 9.0;

        //Mostrar los datos de los estudiantes
        int i;
		for ( i = 0; i < 3; i++) {
            printf("Estudiante: %d: %s, Edad: %d, Promedio: %.2f\n", i+1, clase[i].nombre, clase[i].edad, clase[i].promedio);
        }

        return 0;
    }
        
