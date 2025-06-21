#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SERVICIO 11
#define MAX_APELLIDO 16
#define ARCHIVO "turnos_julio2025.txt"

struct Turno {
    char apellido[MAX_APELLIDO];
    char nombre[16];
    int dni;
    char telefono[11];
    int dia;
    int hora;
    char servicio[MAX_SERVICIO];
    struct Turno* siguiente;
};
// Funciones
void menu(struct Turno** lista);
void reservarTurno(struct Turno** lista);
int esFinDeSemana(int dia);
int turnoOcupado(struct Turno* lista, int dia, int hora);
int main() {
    struct Turno* lista = NULL;
    menu(&lista);
    return 0;
}
void menu(struct Turno** lista) {
    int opcion;
    do {
        printf("\n----- SISTEMA DE TURNOS JULIO 2025 -----\n");
        printf("1. Reservar turno\n");
        printf("2. Listar turnos del mes\n");
        printf("3. Listar turnos por dia\n");
        printf("4. Buscar turno por DNI\n");
        printf("5. Cancelar turno\n");
        printf("6. Modificar turno\n");
        printf("0. Salir\n");
        printf("Seleccione opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: reservarTurno(lista); break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 0: break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 0);
}
int esFinDeSemana(int dia) {
    return dia == 5 || dia == 6 || dia == 12 || dia == 13 || dia == 19 || dia == 20 || dia == 26 || dia == 27;
}
int turnoOcupado(struct Turno* lista, int dia, int hora) {
    while (lista) {
        if (lista->dia == dia && lista->hora == hora) return 1;
        lista = lista->siguiente;
    }
    return 0;
}
void reservarTurno(struct Turno** lista) {
    struct Turno* nuevo = malloc(sizeof(struct Turno));
    if (!nuevo) return;

    printf("Apellido (máx 15): ");
    scanf("%15s", nuevo->apellido);

    printf("Nombre (máx 15): ");
    scanf("%15s", nuevo->nombre);

    do {
        printf("DNI (7 u 8 dígitos): ");
        scanf("%d", &nuevo->dni);
        int cant = 0, aux = nuevo->dni;
        while (aux) { cant++; aux /= 10; }
        if (cant != 7 && cant != 8) printf("ERROR: DNI inválido.\n");
        else break;
    } while (1);

    do {
        printf("Teléfono (10 dígitos): ");
        scanf("%s", nuevo->telefono);
        int valido = 1;
        if (strlen(nuevo->telefono) != 10) valido = 0;
        else {
            for (int i = 0; i < 10; i++) {
                if (!isdigit(nuevo->telefono[i])) {valido = 0; break;}
            }
        }
        if (!valido) printf("ERROR: El teléfono debe tener 10 dígitos numéricos.\n");
        else break;
    } while (1);

    do {
        printf("Día (1-31): ");
        scanf("%d", &nuevo->dia);
        if (nuevo->dia < 1 || nuevo->dia > 31 || esFinDeSemana(nuevo->dia))
            printf("ERROR: Día inválido o fin de semana.\n");
        else break;
    } while (1);

    int horaDisponible = 0;
do {
    // Mostrar horarios ya ocupados para ese día
    printf("\nHorarios ocupados el día %d: ", nuevo->dia);
    int ocupado = 0;
    for (int h = 8; h <= 15; h++) {
        if (turnoOcupado(*lista, nuevo->dia, h)) {
            printf("%d:00\n", h);
            ocupado++;
        }
    }
    if (ocupado == 8) {
        printf("\nNo hay horarios disponibles para este día.\n");
        printf("¿Desea elegir otro día? (S/N): ");
        char opcion;
        scanf(" %c", &opcion);
        if (opcion == 'S' || opcion == 's') {
            do {
                printf("Ingrese otro día (1-31): ");
                scanf("%d", &nuevo->dia);
                if (nuevo->dia < 1 || nuevo->dia > 31 || esFinDeSemana(nuevo->dia))
                    printf("ERROR: Día inválido o fin de semana.\n");
                else break;
            } while (1);
            continue; // volver a verificar horarios del nuevo día
        } else {
            printf("Cancelando reserva...\n");
            free(nuevo);
            printf("Presione ENTER para continuar..."); getchar(); getchar();
            return;
        }
    }

    printf("\nIngrese la hora del turno (entre 8 y 15): ");
    scanf("%d", &nuevo->hora);
    if (nuevo->hora < 8 || nuevo->hora > 15)
        printf("ERROR: Horario inválido.\n");
    else if (turnoOcupado(*lista, nuevo->dia, nuevo->hora))
        printf("ERROR: Turno ya ocupado.\n");
    else {
        horaDisponible = 1;
    }

} while (!horaDisponible);


    printf("Servicio (máx 10): ");
    scanf("%10s", nuevo->servicio);

    nuevo->siguiente = *lista;
    *lista = nuevo;

    printf("\nTurno reservado con éxito.\n");
    printf("Presione ENTER para continuar..."); getchar(); getchar();
}