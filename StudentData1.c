#include <stdio.h>

int main() {
    char estudiante1_nombre[50] = "Ana";
    int estudiante1_edad = 20;
    float estudiante1_promedio = 8.5;

    char estudiante2_nombre[50] = "Luis";
    int estudiante2_edad = 22;
    float estudiante2_promedio = 7.8;

    char estudiante3_nombre[50] = "Marta";
    int estudiante3_edad = 21;
    float estudiante3_promedio = 9.0;

// Mostrar los datos de los estudiantes
printf("Estudiante 1:%s, Edad %d, Promedio %.2f\n", estudiante1_nombre, estudiante1_edad, estudiante1_promedio);
printf("Estudiante 2:%s, Edad %d, Promedio %.2f\n", estudiante2_nombre, estudiante2_edad, estudiante2_promedio);
printf("Estudiante 3:%s, Edad %d, Promedio %.2f\n", estudiante3_nombre, estudiante3_edad, estudiante3_promedio);

return 0;
}