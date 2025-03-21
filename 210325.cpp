#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct {
    char nickname[20];
    char password[9];
} Usuario;

typedef struct {
    char hora[6];
    char contenido[140];
    Usuario *user;
} Mensaje;

Usuario* registrarUsuario() {
    Usuario *user = (Usuario*)malloc(sizeof(Usuario));
    printf("Username: ");
    scanf("%s", user->nickname);

    printf("Enter a password (Max 8 characters): ");
    int i = 0;
    char c;
    while (i < 8) {
        c = getch();
        if (c == '\r') break;  // Enter finaliza la entrada
        if (c == 8 && i > 0) { // Manejo de backspace
            printf("\b \b");
            i--;
            continue;
        }
        if (c != 8) {
            user->password[i++] = c;
            printf("*");
        }
    }
    user->password[i] = '\0';

    printf("\nSuccessful Login!\n");
    return user;
}

void obtenerHora(char *hora) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(hora, 6, "%H:%M", tm_info);
}

void enviarMensaje(Usuario *user) {
    Mensaje msg;
    msg.user = user;

    while (1) {
        obtenerHora(msg.hora);
        printf("\n%s, Enter a message (or type 'exit' to quit): ", user->nickname);
        fflush(stdin);
        fgets(msg.contenido, 140, stdin);
        msg.contenido[strcspn(msg.contenido, "\n")] = 0; // Eliminar el salto de línea

        if (strcmp(msg.contenido, "exit") == 0) break;

        printf("[%s] %s: %s\n", msg.hora, msg.user->nickname, msg.contenido);
    }
}

int main() {
    Usuario *user1 = registrarUsuario();
    enviarMensaje(user1);
    free(user1);
    return 0;
}

