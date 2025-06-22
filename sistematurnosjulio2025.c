#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SERVICIO 11
#define MAX_APELLIDO 16
#define ARCHIVO "turnos_julio2025.txt"
// Estructura de un turno con todos los datos necesarios
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
// Declaracion de Funciones
void menu(struct Turno** lista);
void reservarTurno(struct Turno** lista);
void listarTurnos(struct Turno* lista);
void listarPorDia(struct Turno* lista);
int esFinDeSemana(int dia);
int turnoOcupado(struct Turno* lista, int dia, int hora);
void cancelarTurno(struct Turno** lista);
void modificarTurno(struct Turno* lista);
void ordenarLista(struct Turno** lista);
void buscarPorDNI(struct Turno* lista);
void guardarEnArchivo(struct Turno* lista);
void cargarDesdeArchivo(struct Turno** lista);
// Funcion principal
int main() {
    struct Turno* lista = NULL;
     cargarDesdeArchivo(&lista);
    ordenarLista(&lista);
    menu(&lista);
    guardarEnArchivo(lista);
    return 0;
}
// Implementacion de Funciones
// Muestra el menú principal y gestiona las opciones del usuario
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
            case 1: reservarTurno(lista);ordenarLista(lista);guardarEnArchivo(*lista); break; // Guarda automáticamente después de realizar una acción importante
            case 2: listarTurnos(*lista); break;
            case 3: listarPorDia(*lista); break;
            case 4: buscarPorDNI(*lista); break;
            case 5: cancelarTurno(lista);guardarEnArchivo(*lista); break; // Guarda automáticamente después de realizar una acción importante
            case 6: modificarTurno(*lista);ordenarLista(lista);guardarEnArchivo(*lista); break; // Guarda automáticamente después de realizar una acción importante
            case 0: break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 0);
}
// Verifica si un día ingresado es fin de semana (no se atiende)
int esFinDeSemana(int dia) {
    return dia == 5 || dia == 6 || dia == 12 || dia == 13 || dia == 19 || dia == 20 || dia == 26 || dia == 27;
}
// Verifica si un horario ya está ocupado para un día específico
int turnoOcupado(struct Turno* lista, int dia, int hora) {
    while (lista) {
        if (lista->dia == dia && lista->hora == hora) return 1;
        lista = lista->siguiente;
    }
    return 0;
}
// Reserva un nuevo turno validando los datos ingresados
void reservarTurno(struct Turno** lista) {
    struct Turno* nuevo = malloc(sizeof(struct Turno));
    if (!nuevo) return;

    printf("Apellido (máx 15): ");
    scanf("%15s", nuevo->apellido);

    printf("Nombre (máx 15): ");
    scanf("%15s", nuevo->nombre);
// Validación de DNI: debe tener 7 u 8 dígitos
    do {
        printf("DNI (7 u 8 dígitos): ");
        scanf("%d", &nuevo->dni);
        int cant = 0, aux = nuevo->dni;
        while (aux) { cant++; aux /= 10; }
        if (cant != 7 && cant != 8) printf("ERROR: DNI inválido.\n");
        else break;
    } while (1);
// Validación de teléfono: exactamente 10 dígitos numéricos
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
// Validación de día: debe estar entre 1 y 31 y no ser fin de semana
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
    // Verifica si hay turnos disponibles antes de seguir
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
// Validación de hora: entre 8 y 15, y que no esté ocupada
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
// Lista todos los turnos cargados en el sistema
void listarTurnos(struct Turno* lista) {
    if (!lista) {
        printf("No hay turnos reservados.\n");
    } else {
        printf("\nTurnos del mes:\n");
        while (lista) {
            printf("Día %2d - %2d:00hs | %s %s | DNI: %d | Tel: %s | Servicio: %s\n",
                   lista->dia, lista->hora, lista->apellido, lista->nombre,
                   lista->dni, lista->telefono, lista->servicio);
            lista = lista->siguiente;
        }
    }
    printf("Presione ENTER para continuar..."); getchar(); getchar();
}
// Lista los turnos de un día específico
void listarPorDia(struct Turno* lista) {
    int dia;
    do {
        printf("Ingrese el día (1-31): ");
        scanf("%d", &dia);
        if (dia < 1 || dia > 31 || esFinDeSemana(dia))
            printf("ERROR: Día inválido o fin de semana.\n");
        else break;
    } while (1);

    int hay = 0;
    while (lista) {
        if (lista->dia == dia) {
            if (!hay) {
                printf("Turnos para el día %d:\n", dia);
                hay = 1;
            }
            printf("%2d:00hs | %s %s | DNI: %d | Tel: %s | Servicio: %s\n",
                   lista->hora, lista->apellido, lista->nombre,
                   lista->dni, lista->telefono, lista->servicio);
        }
        lista = lista->siguiente;
    }
    if (!hay) printf("No hay turnos para ese día.\n");
    printf("Presione ENTER para continuar..."); getchar(); getchar();
}
// Cancela un turno según DNI, día y hora
void cancelarTurno(struct Turno** lista) {
    if (!*lista) {
        printf("No hay turnos cargados.\n");
        printf("Presione ENTER para continuar..."); getchar(); getchar();
        return;
    }

    int dni, hora, dia;
    printf("Ingrese DNI: ");
    scanf("%d", &dni);
    printf("Ingrese día (1-31): ");
    scanf("%d", &dia);
    printf("Ingrese hora (8 a 15): ");
    scanf("%d", &hora);

    struct Turno *actual = *lista, *anterior = NULL;

    while (actual) {
        if (actual->dni == dni && actual->dia == dia && actual->hora == hora) {
            if (anterior) anterior->siguiente = actual->siguiente;
            else *lista = actual->siguiente;
            free(actual);
            printf("Turno cancelado exitosamente.\n");
            printf("Presione ENTER para continuar..."); getchar(); getchar();
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    printf("No se encontró el turno para cancelar.\n");
    printf("Presione ENTER para continuar..."); getchar(); getchar();
}
// Modifica los datos de un turno ya existente
void modificarTurno(struct Turno* lista) {
    if (!lista) {
        printf("No hay turnos cargados.\n");
        printf("Presione ENTER para continuar..."); getchar(); getchar();
        return;
    }

    int dni, dia, hora;
    printf("Ingrese el DNI del turno a modificar: ");
    scanf("%d", &dni);

    // Mostrar todos los turnos que coincidan con ese DNI
    struct Turno* actual = lista;
    int encontrados = 0;
    while (actual) {
        if (actual->dni == dni) {
            printf("Día %2d - %2d:00hs | %s %s | Tel: %s | Servicio: %s\n",
                   actual->dia, actual->hora, actual->apellido, actual->nombre,
                   actual->telefono, actual->servicio);
            encontrados++;
        }
        actual = actual->siguiente;
    }

    if (!encontrados) {
        printf("No se encontró un turno con ese DNI.\n");
        printf("Presione ENTER para continuar..."); getchar(); getchar();
        return;
    }

    // Pedir día y hora del turno específico a modificar
    printf("Ingrese el día del turno a modificar: ");
    scanf("%d", &dia);
    printf("Ingrese la hora del turno a modificar (entre 8 y 15): ");
    scanf("%d", &hora);

    actual = lista;
    while (actual) {
        if (actual->dni == dni && actual->dia == dia && actual->hora == hora) {
            printf("\n--- Modificar Turno ---\n");

            printf("Nuevo apellido (máx 15): ");
            scanf("%15s", actual->apellido);

            printf("Nuevo nombre: ");
            scanf("%15s", actual->nombre);

            do {
                printf("Nuevo teléfono (10 dígitos): ");
                scanf("%s", actual->telefono);
                int valido = 1;
                if (strlen(actual->telefono) != 10) valido = 0;
                else {
                    for (int i = 0; i < 10; i++) {
                        if (!isdigit(actual->telefono[i])) {valido = 0; break;}
                    }
                }
                if (!valido) printf("ERROR: El teléfono debe tener 10 dígitos numéricos.\n");
                else break;
            } while (1);

            int nuevoDia, nuevaHora;
            do {
                printf("Nuevo día (1-31): ");
                scanf("%d", &nuevoDia);
                if (nuevoDia < 1 || nuevoDia > 31 || esFinDeSemana(nuevoDia))
                    printf("ERROR: Día inválido o fin de semana.\n");
                else break;
            } while (1);

            do {
                printf("Nueva hora (entre 8 y 15): ");
                scanf("%d", &nuevaHora);
                if (nuevaHora < 8 || nuevaHora > 15)
                    printf("ERROR: Horario inválido.\n");
                else if (turnoOcupado(lista, nuevoDia, nuevaHora) &&
                         !(nuevoDia == actual->dia && nuevaHora == actual->hora))
                    printf("ERROR: Turno ya ocupado.\n");
                else break;
            } while (1);

            actual->dia = nuevoDia;
            actual->hora = nuevaHora;

            printf("Nuevo servicio (máx 10): ");
            scanf("%10s", actual->servicio);

            printf("\nTurno modificado con éxito.\n");
            printf("Presione ENTER para continuar..."); getchar(); getchar();
            return;
        }
        actual = actual->siguiente;
    }

    printf("No se encontró ese turno con ese día y hora.\n");
    printf("Presione ENTER para continuar..."); getchar(); getchar();
}
// Ordena la lista enlazada por día y hora de menor a mayor
void ordenarLista(struct Turno** lista) {
    if (!*lista || !(*lista)->siguiente) return;
    struct Turno *i, *j;
    for (i = *lista; i != NULL; i = i->siguiente) {
        for (j = i->siguiente; j != NULL; j = j->siguiente) {
            if (i->dia > j->dia || (i->dia == j->dia && i->hora > j->hora)) {
                struct Turno temp = *i;
                *i = *j;
                *j = temp;
                struct Turno* aux = i->siguiente;
                i->siguiente = j->siguiente;
                j->siguiente = aux;
            }
        }
    }
}
// Busca turnos por número de DNI
void buscarPorDNI(struct Turno* lista) {
    int dni, encontrados = 0;
    printf("Ingrese DNI a buscar: ");
    scanf("%d", &dni);

    while (lista) {
        if (lista->dni == dni) {
            printf("Día %2d - %2d:00hs | %s %s | Tel: %s | Servicio: %s\n",
                   lista->dia, lista->hora, lista->apellido, lista->nombre,
                   lista->telefono, lista->servicio);
            encontrados = 1;
        }
        lista = lista->siguiente;
    }

    if (!encontrados)
        printf("No se encontraron turnos con ese DNI.\n");

    printf("Presione ENTER para continuar..."); getchar(); getchar();
}
// Guarda todos los turnos en el archivo de texto
void guardarEnArchivo(struct Turno* lista) {
    FILE* f = fopen(ARCHIVO, "w");
    if (!f) {
        printf("Error al guardar archivo.\n");
        return;
    }
    while (lista) {
        fprintf(f, "%s %s %d %s %d %d %s\n", lista->apellido, lista->nombre, lista->dni,
                lista->telefono, lista->dia, lista->hora, lista->servicio);
        lista = lista->siguiente;
    }
    fclose(f);
}
// Carga los turnos desde el archivo al iniciar el programa
void cargarDesdeArchivo(struct Turno** lista) {
    FILE* f = fopen(ARCHIVO, "r");
    if (!f) return;
    while (!feof(f)) {
        struct Turno* nuevo = malloc(sizeof(struct Turno));
        if (fscanf(f, "%15s %15s %d %10s %d %d %10s", nuevo->apellido, &nuevo->nombre,
                   &nuevo->dni, nuevo->telefono, &nuevo->dia, &nuevo->hora, nuevo->servicio) == 7) {
            nuevo->siguiente = *lista;
            *lista = nuevo;
        } else {
            free(nuevo);
            break;
        }
    }
    fclose(f);
}