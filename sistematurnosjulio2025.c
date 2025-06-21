#include <stdio.h>
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
void menu(struct Turno** lista);
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
            case 1: break;
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