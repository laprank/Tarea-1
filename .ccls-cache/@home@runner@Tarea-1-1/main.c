#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tdas/list.h"
#include <stdbool.h>
typedef struct {
    char nombre[50];
    int edad;
    char sintoma[50];
    char prioridad[50];
    char hora[50];
} Persona;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

// Función para pausar hasta que el usuario presione una tecla
void presioneTeclaParaContinuar() {
    puts("Presione una tecla para continuar...");
    getchar(); // Consume el '\n' del buffer de entrada
    getchar(); // Espera a que el usuario presione una tecla
}

// Función para mostrar el menú principal
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("     Sistema de Gestión Hospitalaria");
    puts("========================================");

    puts("1) Registrar paciente");
    puts("2) Asignar prioridad a paciente");
    puts("3) Mostrar lista de espera");
    puts("4) Atender al siguiente paciente");
    puts("5) Mostrar pacientes por prioridad");
    puts("6) Salir");
}

// Función para registrar un paciente
// Función para registrar un paciente
void registrar_paciente(List *pacientes) {
    Persona *paciente = (Persona*)malloc(sizeof(Persona)); 
    if (paciente == NULL) {
        printf("Error: No se pudo asignar memoria para el paciente.\n");
        return;
    }
    strcpy(paciente->prioridad,"Bajo");
    printf("Registrar nuevo paciente escriba su nombre\n");
    scanf(" %[^\n]",paciente->nombre);
    printf("Escriba su edad\n");
    scanf("%d",&(paciente->edad));
    getchar(); 
    printf("Escriba su sintoma\n");
    scanf(" %[^\n]",paciente->sintoma);
    time_t hora_actual = time(NULL);
    struct tm *tm_hora_actual = localtime(&hora_actual);
    strftime(paciente->hora, sizeof(paciente->hora), "%H:%M:", tm_hora_actual);
    list_pushBack(pacientes, paciente);
    printf("Paciente registrado con éxito.\n");
}




// Función para mostrar la lista de pacientes en espera
void mostrar_lista_pacientes(List *pacientes) {
    printf("Pacientes en espera: \n");
    // Implementación de la lógica para recorrer y mostrar los pacientes
}

int main() {
    char opcion;
    List *pacientes = list_create(); // Lista para gestionar los pacientes

    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Consumir el newline anterior

    while (opcion != '6') {
        switch (opcion) {
            case '1':
                registrar_paciente(pacientes);
                break;
            case '2':
              if(pacientes->head == NULL)  {
                printf("No hay pacientes registrados.\n");
                  break;
              }
              bool pacienteEncontrado = false;
              printf("Escriba el nombre del paciente al que le quiere asignar prioridad\n");
              char nombre[50];
              scanf("%s",nombre);
              pacientes->current = pacientes->head;
              if (strcmp(((Persona*)(pacientes->current->data))->nombre, nombre) == 0){
                printf("Escriba la prioridad que le quiere asignar al paciente\n");
                scanf("%s",((Persona*)(pacientes->current->data))->prioridad);
                printf("Prioridad asignada con éxito.\n");
                pacienteEncontrado = true;
                break;
              }

              while(pacientes->current->next != NULL){
                  if(strcmp(((Persona*)pacientes->current->data)->nombre,nombre) == 0){
                    printf("escriba el nivel de prioridad que le quiere asignar al paciente entre Baja, Media, Alta\n");
                    scanf("%s",((Persona*)pacientes->current->data)->prioridad);
                    printf("Prioridad asignada con éxito.\n");
                    pacienteEncontrado = true;
                    break;
                  }
                
                pacientes->current = pacientes->current->next;
                  
              }
              if(!pacienteEncontrado){
                printf("el paciente %s no se encuentra en nuestra base de datos por favor registrelo\n",nombre);
              }
                // Lógica para asignar prioridad
                break;
            case '3':
                mostrar_lista_pacientes(pacientes);
                break;
            case '4':
                // Lógica para atender al siguiente paciente
                break;
            case '5':
                // Lógica para mostrar pacientes por prioridad
                break;
            default:
                puts("Opción no válida. Por favor, intente de nuevo.");
        }
        presioneTeclaParaContinuar();

        limpiarPantalla();
        mostrarMenuPrincipal();
        printf("Ingrese su opción: ");
        scanf(" %c", &opcion); // Consumir el newline anterior
    }

    puts("Saliendo del sistema de gestión hospitalaria...");

    // Liberar recursos
    list_clean(pacientes);

    return 0;
}
