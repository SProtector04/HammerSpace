#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de estructuras
typedef struct {
    int id;
    int estado;
    char nickname[20];
    char password[10]; // Se podría mejorar con una encriptación
} Usuario;

typedef struct {
    int id;
    char time[10]; // Formato HH:MM:SS
    char message[140];
    Usuario user;
} Mensaje;

typedef struct {
    int id;
    Usuario *users;
    Mensaje *chats;
} SalaDeChat;

// Declaraciones de funciones
SalaDeChat* crearSala(int id);
Usuario* crearUsuario(int id, const char *nick, const char *pass);
void Loggin(Usuario *user);
void SignUp(Usuario *user);
void UnirseASala(Usuario *user, int id);
void EnviarMensaje(int id, const char *message, const char *time, Usuario *user);
void MostrarChat(SalaDeChat *sala);
void MostrarMensaje(Mensaje *msm);
int mostrarMenu();

// Implementaciones de funciones
SalaDeChat* crearSala(int id) {
    SalaDeChat *sala = (SalaDeChat*)malloc(sizeof(SalaDeChat));
    if (sala == NULL) {
        printf("Error al asignar memoria para la sala.\n");
        return NULL;
    }
    sala->id = id;
    sala->users = NULL;
    sala->chats = NULL;
    return sala;
}

Usuario* crearUsuario(int id, const char *nick, const char *pass) {
    Usuario *user = (Usuario*)malloc(sizeof(Usuario));
    if (user == NULL) {
        printf("Error al asignar memoria para el usuario.\n");
        return NULL;
    }
    user->id = id;
    strncpy(user->nickname, nick, sizeof(user->nickname) - 1);
    user->nickname[sizeof(user->nickname) - 1] = '\0'; // Asegurar el nulo al final

    strncpy(user->password, pass, sizeof(user->password) - 1);
    user->password[sizeof(user->password) - 1] = '\0'; // Evitar buffer overflow

    user->estado = 0;
    return user;
}

int main() {
    SalaDeChat *sala1 = crearSala(1);
    if (sala1) {
        printf("Sala de chat creada con ID: %d\n", sala1->id);
    }

    Usuario *usuario1 = crearUsuario(1, "Juan", "12345");
    if (usuario1) {
        printf("Usuario creado: %s\n", usuario1->nickname);
    }

    // Liberar memoria antes de salir
    free(sala1);
    free(usuario1);

    return 0;
}

