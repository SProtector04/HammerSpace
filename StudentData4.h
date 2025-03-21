#ifndef STUDENTDATA_H
#define STUDENTDATA_H

typedef struct {

    char nombre[50];

    int edad;

    float promedio;

} Estudiante;

//Funciones
void AsignarMemoria(Estudiante **clase, int numEstudiantes);
void InicializarEstudiante (Estudiante *est, const char *nombre, int edad, float promedio);
void MostrarEstudiante (const Estudiante *est);
void MostrarClase (const Estudiante clase[], int numEstudiantes);


#endif
