# Sistema de gestión de atención de pacientes

Este programa se encarga de gestionar la lista de espera y atencion de los pacientes en un hospital. Este usa un sistema de cola, el cual se basa en el orden de llega y de prioridad de los pacientes.

A cada paciente se le registra un nivel de prioridad y hora de atencion para determinar el orden en que seran atendidos. Ademas, en los datos del paciente se incluye el nombre, edad, síntoma, nivel de prioridad (Alto, Medio, Bajo) y hora de registro. Esta aplicación tambien permite registrar nuevos pacientes, modificar su nivel de prioridad, atender al siguiente paciente según la prioridad, y mostrar una lista de espera por prioridad o general de los pacientes.

## Funcionalidades

1. **Registrar nuevo paciente**: El programa registrara un nuevo paciente en la lista de espera con sus datos correspondientes como nombre, edad, sintomas y hora en que fue registrado.
2. **Modificar prioridad de paciente**: El usuario ingresa el nombre de un paciente al cual desea cambiar su prioridad y cual sera su nueva prioridad.
3. **Mostrar lista de espera**: La aplicacion muestra a todos los pacientes registrados en la lista de espera, ordenados por prioridad y hora en la que fueron registrados.
4. **Atender al siguiente paciente**: Una vez atendido al primer paciente en la lista de espera, el programa elimina al primer paciente en la lista y muestra sus datos.
5. **Mostrar lista de espera por prioridad**: El usuario ingresa una prioridad, y el programa muestra a todos los pacientes en la lista de espera registrados con esa prioridad, ordenados por su hora de registro.

## Uso

### Registrar un nuevo paciente

Para registrar un nuevo paciente en el sistema, se utiliza la función `registrarPaciente`. Esta función usa como argumento una lista de espera y realiza las siguientes operaciones:

1. Se solicita al usuario que ingrese el nombre del paciente. Los caracteres del nombre se convierten a mayúsculas para mantener consistencia en los datos.
2. Se solicita al usuario que ingrese la edad del paciente. Se verifica que se haya ingresado solo dígitos, en caso contrario se volverá a consultar hasta ingresar un valor válido.
3. Se solicita al usuario que ingrese los síntomas del paciente. Los síntomas se convierten a mayúsculas para mantener la consistencia en los datos.
4. El programa asigna una prioridad "BAJA" al paciente por defecto.
5. El programa registra la hora local de ingreso del paciente.
6. Se verifica que el paciente no esté registrado en la lista de espera. Si el paciente ya está en la lista, se libera la memoria asignada al nuevo paciente y se termina la función. En el caso contrario, se agrega a la lista de espera y se muestra un mensaje de éxito.

Ejemplo:
```c
List *listaDeEspera = list_create();
registrar_paciente(listaDeEspera);
```

### Asignar prioridad

Para poder realizar un cambio en la prioridad de un paciente, se utiliza la función `asignarPrioridad`. Esta función usa como argumento una lista de pacientes en espera y realiza las siguientes operaciones:

1. Verifica si la lista está vacía. En caso de estarlo, se muestra un aviso indicando que no hay pacientes registrados y finaliza la función.
2. Se solicita al usuario que ingrese el nombre del paciente al que se desea cambiar de prioridad. Este nombre se convierte a mayúsculas para mantener la consistencia en los datos.
3. Se solicita al usuario que ingrese la nueva prioridad. Se convierte a mayúsculas la nueva prioridad para mantener la consistencia en los datos, y se verifica que la prioridad ingresada sea válida. En caso de no ingresarse una prioridad válida (Alta, Media o Baja), se vuelve a solicitar al usuario que ingrese la prioridad.
4. Se busca al paciente en la lista de espera. Si se encuentra al paciente, se cambia su prioridad, se muestra un mensaje de éxito y se ordena la lista de pacientes. En caso contrario, se muestra un mensaje indicando que el paciente no se encuentra en la lista.


Ejemplo:
```c
List *listaDeEspera = list_create();
registrar_paciente(listaDeEspera);
asignarPrioridad(listaDeEspera);
```

### Mostrar lista de espera

Para poder mostrar los pacientes registrados en la lista de espera, se utiliza la función `mostrarListaPacientes`. Esta función usa como argumento una lista de espera y realiza las siguientes operaciones:

1. Se verifica si la lista está vacía. En caso de estarlo, se muestra un aviso indicando que no hay pacientes registrados y finaliza la función.
2. Se recorre la lista y se muestra la información de cada paciente.

Ejemplo:
```c
List *listaDeEspera = list_create();
registrar_paciente(listaDeEspera);
mostrarListaPacientes(listaDeEspera);
```

### Atender al siguiente paciente

Para poder atender al siguiente paciente en la lista de espera, se utiliza la función `AtenderSiguientePaciente`. Esta función usa como argumento una lista de espera y realiza las siguientes operaciones:

1. Verifica si la lista está vacía. En caso de estarlo, se muestra un aviso indicando que no hay pacientes registrados y finaliza la función.
2. Se elimina al primer paciente de la lista de espera y almacena su información en una variable temporal.
3. Muestra la información del paciente que acaba de ser atendido.
4. Se verifica si la lista de espera está vacía tras haber atendido al paciente. En caso de estarlo, se muestra un aviso indicando que no quedan pacientes registrados y se termina la función.

Ejemplo:
```c
List *listaDeEspera = list_create();
registrar_paciente(listaDeEspera);
AtenderSiguientePaciente(listaDeEspera);
```
### Mostrar pacientes por prioridad

Para poder mostrar los pacientes registrados con cierta prioridad en la lista de espera, se utiliza la función `mostrarPacientesPorPrioridad`. Esta función usa como argumento una lista de espera y realiza las siguientes operaciones:

1. Verifica si la lista está vacía. En caso de estarlo, se muestra un aviso indicando que no hay pacientes registrados y finaliza la función.
2. Se solicita al usuario que ingrese la prioridad de los pacientes que desea ver. Se convierte a mayúsculas la nueva prioridad para mantener la consistencia en los datos, y se verifica que la prioridad ingresada sea válida. En caso de no ingresarse una prioridad válida (Alta, Media o Baja), se vuelve a solicitar al usuario que ingrese la prioridad.
3. Se recorre la lista mostrando solo a los pacientes que tengan la prioridad indicada por el usuario.
4. En caso de no encontrarse pacientes con la prioridad indicada, se muestra un aviso de que no hay pacientes con esa prioridad.

Ejemplo:
```c
List *listaDeEspera = list_create();
registrar_paciente(listaDeEspera);
mostrarPacientesPorPrioridad(listaDeEspera);
```

## Como ejecutar el programa (main)
Para poder ejecutar el programa, tendremos que iniciar la consola e ir la la carpeta raíz, y tendremos que compilar el archivo main con el siguiente comando:
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Una vez compilado el programa, lo ejecutamos con el comando:
````
./main
````
