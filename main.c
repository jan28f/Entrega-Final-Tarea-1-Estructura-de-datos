#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAXCHAR 101

typedef struct
{
  char nombre[MAXCHAR];
  short edad;
  char sintoma[MAXCHAR];
  char prioridad[MAXCHAR];
  struct tm *info_tiempo;
} paciente;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Funcion encargada de mostrar la informacion de un paciente
void mostrarInfoPaciente(paciente *infoPaciente)
{
  printf("  Nombre: %s\n", infoPaciente->nombre);
  printf("  Edad: %hd\n", infoPaciente->edad);
  printf("  Sintomas: %s\n", infoPaciente->sintoma);
  printf("  Prioridad: %s\n", infoPaciente->prioridad);
  printf("  Hora de ingreso %2d:%2d:%2d\n\n", infoPaciente->info_tiempo->tm_hour, 
                                              infoPaciente->info_tiempo->tm_min,
                                              infoPaciente->info_tiempo->tm_sec);
}

// Funcioin encargada de convertir todos los caracteres de una cadena en mayusculas
void convertirMayusculas(char *cadena)
{
  char *caracter = cadena; // Apunta a la primera posicion de la cadena
  while (*caracter != '\0') // Recorre la cadena
  {
    *caracter = toupper(*caracter); // Convierte la letra en mayuscula
    caracter++; // Avanza al siguiente elemento en la lista
  }
}

// Funcion encargada de leer y validar la prioridad ingresada por el usuario
void leerPrioridad(char *prioridad)
{
  do
    {
      printf("Ingrese la nueva prioridad (Alta, Media, Baja): ");
      scanf("%100[^\n]s", prioridad); // El usuario ingresa la prioridad
      convertirMayusculas(prioridad);
    } while ((strcmp(prioridad, "ALTA") != 0) &&
             (strcmp(prioridad, "MEDIA") != 0) &&
             (strcmp(prioridad, "BAJA") != 0));
             // Verifica que se haya ingresado una prioridad valida
}

// Funcion encargada de leer y validar la edad ingresada por el usuario
int tieneSoloDigitos(char *cadena)
{
  char *caracter = cadena;
  while (*caracter != '\0') // Recorre la cadena
  {
    if (!isdigit(*caracter))
      return 0; // Si el caracter no es un digito, devuelve 0
    caracter++; // Avanza al siguiente caracter
  }
  return 1; // Devolvera 1 si la cadena contiene solo digitos
}

// Funcion encargada de encontrar, eliminar y retornar los datos de paciente con menor hora de ingreso
paciente *eliminarPacienteMenorHora(List *listaDeEspera)
{
  if (listaDeEspera == NULL || list_first(listaDeEspera) == NULL) return NULL;
  // Verifica si la lista esta vacia

  paciente *menor = (paciente *)list_first(listaDeEspera);
  paciente *pacienteActual = menor;
  while (pacienteActual != NULL) // Recorre la lista
  {
    //Compara hora de ingreso
    if (pacienteActual->info_tiempo->tm_hour < menor->info_tiempo->tm_hour) menor = pacienteActual;
    else if (pacienteActual->info_tiempo->tm_hour == menor->info_tiempo->tm_hour)
    {
      //Compara minutos de ingreso si las horas son iguales
      if (pacienteActual->info_tiempo->tm_min < menor->info_tiempo->tm_min) menor = pacienteActual;
      else if (pacienteActual->info_tiempo->tm_min == menor->info_tiempo->tm_min)
        //Compara segundos si los minutos son iguales
        if (pacienteActual->info_tiempo->tm_sec < menor->info_tiempo->tm_sec) menor = pacienteActual;
    }
    //Avanza al siguiente elemento de la lista
    pacienteActual = (paciente *)list_next(listaDeEspera);
  }

  pacienteActual = (paciente *)list_first(listaDeEspera);
  while (pacienteActual != NULL) // Recorre la lista
    // Busca y elimina al paciente con menor hora de ingreso y retorna sus datos
    if (pacienteActual == menor) return (paciente *)list_popCurrent(listaDeEspera);
    else pacienteActual = (paciente *)list_next(listaDeEspera);
}

// Funcion encargada de ordenar los pacientes por su prioridad y hora de ingreso
void ordenarPacientes(List *listaDeEspera)
{
  if (listaDeEspera == NULL || list_first(listaDeEspera) == NULL)
  {
    printf("No hay pacientes en la lista.\n");
    return;
  } //Verifica si la lista esta vacia

  List *alta = list_create();
  List *media = list_create();
  List *baja = list_create();
  paciente *pacienteActual = (paciente *)list_first(listaDeEspera);

  // Separa los pacientes segun su prioridad
  while (list_first(listaDeEspera) != NULL)
  {
    if (strcmp(pacienteActual->prioridad, "ALTA") == 0)
      list_pushBack(alta, pacienteActual);
    else if (strcmp(pacienteActual->prioridad, "MEDIA") == 0)
      list_pushBack(media, pacienteActual);
    else
      list_pushBack(baja, pacienteActual);

    pacienteActual = (paciente *)list_next(listaDeEspera);
    list_popFront(listaDeEspera);
  }

  // Reincorpora los pacientes a la lista de forma ordenada
  while (list_first(alta) != NULL)
    list_pushBack(listaDeEspera, eliminarPacienteMenorHora(alta));
  while (list_first(media) != NULL)
    list_pushBack(listaDeEspera, eliminarPacienteMenorHora(media));
  while (list_first(baja) != NULL)
    list_pushBack(listaDeEspera, eliminarPacienteMenorHora(baja));
}

// Menú principal
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

// Funcion encargada de registrar un paciente nuevo a la lista de espera
void registrarPaciente(List *listaDeEspera)
{
  limpiarPantalla();
  printf("========================================\n");
  printf("       Registrar nuevo paciente\n");
  printf("========================================\n\n");

  paciente *pacienteNuevo = (paciente *)malloc(sizeof(paciente));
  if (pacienteNuevo == NULL) // Avisa y termina el programa si no hay memoria
  {
    printf("No hay suficiente memoria disponiblen\n");
    printf("Finalizando ejecucion del programa");
    exit(EXIT_FAILURE);
  }

  getchar(); // Consume el '\n' del buffer
  // Se regisrta el nombre del paciente
  printf("Ingrese el nombre del paciente: ");
  scanf("%100[^\n]s", pacienteNuevo->nombre);
  convertirMayusculas(pacienteNuevo->nombre);
  getchar(); // Consume el '\n' del buffer

  // Se registra la edad del paciente
  char edad[MAXCHAR];
  do
  {
    printf("Ingrese la edad del paciente: ");
    scanf("%100[^\n]s", edad);
    getchar(); // Consume el '\n' del buffer
  } while (tieneSoloDigitos(edad) != 1);
  // Se verifica que se haya ingresado solo numeros
  pacienteNuevo->edad = atoi(edad);

  // Se registra los sintoma del paciente
  printf("Ingrese el síntoma del paciente: ");
  scanf("%100[^\n]s", pacienteNuevo->sintoma);
  convertirMayusculas(pacienteNuevo->sintoma);

  //Se registra prioridad BAJA por defecto al paciente
  printf("Prioridad asignada por defecto: BAJA\n");
  strcpy(pacienteNuevo->prioridad, "BAJA");

  //Se registra la hora local de ingreso del paciente
  time_t tiempo = time(NULL); // Obtiene la hora UTC
  struct tm *tiempoLocal = localtime(&tiempo); // Convierte la hora UTC a la hora local
  pacienteNuevo->info_tiempo = malloc(sizeof(struct tm));
  memcpy(pacienteNuevo->info_tiempo, tiempoLocal, sizeof(struct tm)); // Registra la hora de ingreso del paciente
  printf("Hora de ingreso: %2d:%2d:%2d\n\n", pacienteNuevo->info_tiempo->tm_hour, 
                                             pacienteNuevo->info_tiempo->tm_min,
                                             pacienteNuevo->info_tiempo->tm_sec);

  paciente *actual = (paciente *)list_first(listaDeEspera);
  while (actual != NULL) // Recorre la lista para verificar que no se repita el paciente
  {
    if (strcmp(pacienteNuevo->nombre, actual->nombre) == 0)
    {
      // Si esta en la lista, no almacena al paciente y libera la memoria
      printf("El paciente ya se encuentra registrado\n");
      free(pacienteNuevo);
      return;
    }
    actual = (paciente *)list_next(listaDeEspera);
  }
  list_pushBack(listaDeEspera, pacienteNuevo); // Se agrega el paciente a la lista si no esta repetido
  printf("***Paciente registrado con exito***\n");
}

// Funcion encargada de asignar una nueva prioridad a un paciente
void asignarPrioridad(List *listaDeEspera)
{
  limpiarPantalla();
  printf("========================================\n");
  printf("    Cambio de prioridad de paciente\n");
  printf("========================================\n\n");

  // Declaracion de variables temporales
  char nombre[MAXCHAR];
  char prioridad[MAXCHAR];
  paciente *pacienteActual = list_first(listaDeEspera);

  if (pacienteActual == NULL) // Aviso si la lista esta vacia
  {
    printf("No se han registrado pacientes en la lista de espera\n");
    return;
  }

  getchar(); // Consume el '\n' del buffer
  //Se registra el nombre del paciente a cambiar de prioridad
  printf("Ingrese el nombre del paciente a cambiar prioridad: ");
  scanf("%100[^\n]s", nombre);
  convertirMayusculas(nombre);

  getchar(); // Consume el '\n' del buffer
  // Se registra la nueva prioridad del paciente a cambiar
  leerPrioridad(prioridad);

  while (pacienteActual != NULL) //Se recorre la lista para encontrar el paciente
  {
    if (strcmp(pacienteActual->nombre, nombre) == 0)
    {
      //Si se encuentra el paciente, se cambia su prioridad y se ordena la lista
      strcpy(pacienteActual->prioridad, prioridad);
      printf("\nSe ha cambiado exitosamente la prioridad de %s\n", pacienteActual->nombre);
      ordenarPacientes(listaDeEspera); // Se ordena la lista de pacientes
      return;
    }
    pacienteActual = (paciente *)list_next(listaDeEspera); // Avanza al siguiente paciente
  }

  // Aviso en caso de no encontrar el paciente
  printf("\nNo se ha encontrado paciente en la lista de espera\n");
}

// Funcion encaragada de mostrar la lista de espera de pacientes
void mostrarListaPacientes(List *listaDeEspera)
{
  limpiarPantalla();
  printf("========================================\n");
  printf("          Lista de pacientes\n");
  printf("========================================\n\n");

  paciente *pacienteActual = list_first(listaDeEspera);
  if (pacienteActual == NULL) // Avisa si la lista esta vacia
  {
    printf("No se han registrado pacientes en la lista de espera\n");
    return;
  }

  printf("Pacientes en espera: \n");
  while (pacienteActual != NULL) // Recorre la lista mostrando la inforamcion de cada paciente
  {
    mostrarInfoPaciente(pacienteActual);
    pacienteActual = list_next(listaDeEspera); // Avanza al siguiente paciente
  }
}

// Funcion encargada de atender al siguiente paciente en la lista
void AtenderSiguientePaciente(List *listaDeEspera)
{
  //Se elimina el primer paciente de la lista y se almacena en una variable temporal
  paciente *infoPaciente = list_popFront(listaDeEspera);
  if (infoPaciente == NULL) //Aviso si la lista esta vacia
  {
    printf("\nNo se han registrado pacientes en la lista de espera\n");
    return;
  }

  //Se muestra la informacion del paciente eliminado
  printf("\n\nSe ha atendido a: \n");
  mostrarInfoPaciente(infoPaciente);

  if (list_first(listaDeEspera) == NULL) //Aviso si se vacio la lista
    printf("Se han atentido todos los pacientes registro en la lista de espera");
}

// Funcion encargada de mostrar los pacientes con cierta prioridad de la lista de espera
void mostrarPacientesPorPrioridad(List *listaDeEspera)
{
  limpiarPantalla();
  printf("========================================\n");
  printf("      Ver pacientes por prioridad\n");
  printf("========================================\n\n");

  // Declaracion de variables temporales
  paciente *pacienteActual = (paciente *)list_first(listaDeEspera);
  char prioridad[MAXCHAR];
  size_t contador = 0;

  if (pacienteActual == NULL) // Aviso si la lista esta vacia
  {
    printf("No se han registrado pacientes a la lista de espera\n");
    return;
  }

  getchar(); // Consume el '\n' del buffer
  leerPrioridad(prioridad); // Registra la prioridad a mostrar
  
  printf("\nPacientes de prioridad %s en espera: \n", prioridad);
  while (pacienteActual != NULL) // Se comienza a recorrer la lista
  {
    if (strcmp(pacienteActual->prioridad, prioridad) == 0)
    {
      //Si el paciente tiene la prioridad buscada, se muestra su informacion
      mostrarInfoPaciente(pacienteActual);
      contador++;
    }
    pacienteActual = list_next(listaDeEspera);
  }

  if (contador == 0) //Aviso si no se encuentra pacientes con la prioridad buscada
    printf("\nNo se han encontrado pacientes con la prioridad %s\n", prioridad);
}

int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes
  if (pacientes == NULL)
  {
    printf("No hay memoria disponible para iniciar la lista de espera\n");
    printf("Se finalizara el programa");
    exit(EXIT_FAILURE);
  } // Verifica si hay memoria disponible

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrarPaciente(pacientes);
      break;
    case '2':
      // Lógica para asignar prioridad
      asignarPrioridad(pacientes);
      break;
    case '3':
      mostrarListaPacientes(pacientes);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      AtenderSiguientePaciente(pacientes);
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
      mostrarPacientesPorPrioridad(pacientes);
      break;
    case '6':
      puts("\nSaliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("\nOpción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}