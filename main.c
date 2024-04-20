#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tdas/list.h"
#include "tdas/map.h"
#include "tdas/queue.h"
#include "tdas/priority_queue.h"
#include <stdbool.h>
#include <ctype.h>
typedef struct {
    char nombre[50];
    int edad;
    char sintoma[50];
    char prioridad[50];
    char hora[50];
} Persona;
// Función para mostrar la lista de pacientes en espera
void str_to_lower(char str[50]) {
    for (int i = 0; i < 50 && str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void str_to_upper(char str[50]) {
    for (int i = 0; i < 50 && str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

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
    strcpy(paciente->prioridad, "BAJA");

    printf("Registrar nuevo paciente escriba su nombre\n");
    scanf(" %[^\n]", paciente->nombre);
    str_to_upper(paciente->nombre); // Convertir el nombre a mayúsculas

    printf("Escriba su edad\n");
    scanf("%d", &(paciente->edad));
    getchar(); 

    printf("Escriba su síntoma\n");
    scanf(" %[^\n]", paciente->sintoma);
    str_to_upper(paciente->sintoma); // Convertir el síntoma a mayúsculas

    time_t hora_actual = time(NULL);
    struct tm *tm_hora_actual = localtime(&hora_actual);
    strftime(paciente->hora, sizeof(paciente->hora), "%H:%M:", tm_hora_actual);

    list_pushBack(pacientes, paciente);

    printf("Paciente registrado con éxito.\n");
}


// Función para mostrar la lista de pacientes en espera
void mostrar_lista_pacientes(List *pacientes, Queue *cola_prioridad) {
    // Mostrar la lista de pacientes en espera
    printf("Lista de pacientes en espera:\n");
    while (cola_prioridad->head != NULL){
        Persona *paciente = (Persona *)cola_prioridad->head->data;
        printf("Nombre: %s\n", paciente->nombre);
        printf("Edad: %d\n", paciente->edad);
        printf("Sintoma: %s\n", paciente->sintoma);
        printf("Prioridad: %s\n", paciente->prioridad);
        printf("Hora: %s\n", paciente->hora);
        printf("------------------------\n");
        cola_prioridad->head = cola_prioridad->head->next;
    }
    queue_clean(cola_prioridad);
}

void list_remover(List *lista, void *data) {
    Node *current = lista->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                lista->head = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}




int main() {
    char opcion;
    List *pacientes = list_create();// Lista para gestionar los pacientes
    Queue *cola_prioridad = queue_create(cola_prioridad);
    char prioridad[10];

    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Consumir el newline anterior

    while (opcion != '6') {
        switch (opcion) {
            case '1':
                registrar_paciente(pacientes);
                break;
            case '2':
              if (pacientes->head == NULL) {
                printf("No hay pacientes registrados.\n");
                break;
              }

              printf("Escriba el nombre del paciente al que le quiere asignar prioridad\n");
              char nombre[50];
              scanf("%s", nombre);
              str_to_upper(nombre);

              pacientes->current = pacientes->head;
              bool pacienteEncontrado = false;

              while (pacientes->current != NULL) {
                if (strcmp(((Persona*)(pacientes->current->data))->nombre, nombre) == 0) {
                    printf("Escriba el nivel de prioridad que le quiere asignar al paciente entre Baja, Media, Alta\n");
                    scanf("%s", ((Persona*)(pacientes->current->data))->prioridad);
                    str_to_upper(((Persona*)(pacientes->current->data))->prioridad);
                    printf("Prioridad asignada con éxito.\n");
                    pacienteEncontrado = true;
                    break;
                }
                pacientes->current = pacientes->current->next;
              }

              if (!pacienteEncontrado) {
                printf("El paciente %s no se encuentra en nuestra base de datos. Por favor, regístrelo.\n", nombre);
              }

              break;
            case '3':
              pacientes->current = pacientes->head; // Asegurar que el puntero current esté al principio de la lista
              while (pacientes->current != NULL) {
                  // Verificar si la prioridad del paciente es "Alta"
                  if (strcmp(((Persona *)pacientes->current->data)->prioridad, "ALTA") == 0) {
                      // Agregar el paciente a la cola de prioridad
                      queue_insert(cola_prioridad,pacientes->current->data);
                  }
                  pacientes->current = pacientes->current->next; // Avanzar al siguiente nodo
              }
              pacientes->current = pacientes->head;
              while (pacientes->current != NULL){
                  // Verificar si la prioridad del paciente es "Media"
                  if (strcmp(((Persona *)pacientes->current->data)->prioridad, "MEDIA") == 0){
                      // Agregar el paciente a la cola de prioridad
                      queue_insert(cola_prioridad,pacientes->current->data);
                  }
                  pacientes->current = pacientes->current->next;
              }
              pacientes->current = pacientes->head;
              while (pacientes->current != NULL){
                  // Verificar si la prioridad del paciente es "Bajo"
                  if (strcmp(((Persona *)pacientes->current->data)->prioridad, "BAJA") == 0){
                      // Agregar el paciente a la cola de prioridad
                      queue_insert(cola_prioridad,pacientes->current->data);
                  }
                  pacientes->current = pacientes->current->next;
              }
                mostrar_lista_pacientes(pacientes,cola_prioridad);
                break;
            case '4':
                pacientes->current = pacientes->head; // Asegurar que el puntero current esté al principio de la lista
                while (pacientes->current != NULL) {
                    // Verificar si la prioridad del paciente es "Alta"
                    if (strcmp(((Persona *)pacientes->current->data)->prioridad, "ALTA") == 0) {
                        // Agregar el paciente a la cola de prioridad
                        queue_insert(cola_prioridad,pacientes->current->data);
                    }
                    pacientes->current = pacientes->current->next; // Avanzar al siguiente nodo
                }
                pacientes->current = pacientes->head;
                while (pacientes->current != NULL){
                    // Verificar si la prioridad del paciente es "Media"
                    if (strcmp(((Persona *)pacientes->current->data)->prioridad, "MEDIA") == 0){
                        // Agregar el paciente a la cola de prioridad
                        queue_insert(cola_prioridad,pacientes->current->data);
                    }
                    pacientes->current = pacientes->current->next;
                }
                pacientes->current = pacientes->head;
                while (pacientes->current != NULL){
                    // Verificar si la prioridad del paciente es "Bajo"
                    if (strcmp(((Persona *)pacientes->current->data)->prioridad, "BAJA") == 0){
                        // Agregar el paciente a la cola de prioridad
                        queue_insert(cola_prioridad,pacientes->current->data);
                    }
                    pacientes->current = pacientes->current->next;
                }
                if (cola_prioridad->head == NULL){
                    printf("No hay pacientes en espera.\n");
                }
                else{
                    Persona *paciente = (Persona *)cola_prioridad->head->data;
                    printf("Atendiendo al paciente %s\n", paciente->nombre);
                    list_remover(pacientes, paciente);
                    queue_clean(cola_prioridad);
                }
                // Lógica para atender al siguiente paciente
                break;
            case '5':
                printf("ingrese la prioridad que desea ver\n");
                scanf("%s",prioridad);
                str_to_upper(prioridad);
                if (strcmp(prioridad,"BAJA") == 0){
                  pacientes->current = pacientes->head;
                  while (pacientes->current != NULL){
                      // Verificar si la prioridad del paciente es "Bajo"
                      if (strcmp(((Persona *)pacientes->current->data)->prioridad, "BAJA") == 0){
                          // Agregar el paciente a la cola de prioridad
                          queue_insert(cola_prioridad,pacientes->current->data);
                      }
                      pacientes->current = pacientes->current->next;
                  }
                    mostrar_lista_pacientes(pacientes,cola_prioridad);
                    queue_clean(cola_prioridad);
                }
                else if(strcmp(prioridad,"MEDIA") == 0){
                  pacientes->current = pacientes->head;
                  while (pacientes->current != NULL){
                      // Verificar si la prioridad del paciente es "Media"
                      if (strcmp(((Persona *)pacientes->current->data)->prioridad, "MEDIA") == 0){
                          // Agregar el paciente a la cola de prioridad
                          queue_insert(cola_prioridad,pacientes->current->data);
                      }
                      pacientes->current = pacientes->current->next;
                    }
                    mostrar_lista_pacientes(pacientes,cola_prioridad);
                    queue_clean(cola_prioridad);
                }
                else if(strcmp(prioridad,"ALTA") == 0){
                  pacientes->current = pacientes->head; // Asegurar que el puntero current esté al principio de la lista
                  while (pacientes->current != NULL) {
                      // Verificar si la prioridad del paciente es "Alta"
                      if (strcmp(((Persona *)pacientes->current->data)->prioridad, "ALTA") == 0) {
                          // Agregar el paciente a la cola de prioridad
                          queue_insert(cola_prioridad,pacientes->current->data);
                      }
                      pacientes->current = pacientes->current->next; // Avanzar al siguiente nodo
                  }
                    mostrar_lista_pacientes(pacientes,cola_prioridad);
                    queue_clean(cola_prioridad);
                 }
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
