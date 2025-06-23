# 📅 Sistema de Gestión de Turnos - Julio 2025

## 👨‍💻 Integrantes

- **Barrios Cristian Martin**
- **Stabile Maximiliano**
- **Sánchez Oliva Iván Nicolás**
  
##  🛗  Roles del equipo
  
Todos los integrantes participaron de forma colaborativa y compartida en las siguientes tareas:
-Análisis y diseño del sistema.
-Implementación del código y validaciones.
-Pruebas y corrección de errores.
-Documentación y armado de archivos de prueba.

El trabajo fue realizado en equipo, dividiendo las tareas por secciones según necesidad, y validando en conjunto cada parte del desarrollo.

## 📋 Descripción

Sistema de gestión de turnos desarrollado en C que permite administrar citas médicas, servicios profesionales o cualquier tipo de reserva por horarios durante el mes de julio de 2025. El sistema utiliza una lista enlazada para almacenar los datos en memoria y persiste la información en un archivo de texto.

## ✨ Características Principales

- **Gestión completa de turnos**: Crear, modificar, cancelar y consultar
- **Validación de datos**: Verificación de DNI, teléfono, horarios y fechas
- **Persistencia de datos**: Guardado automático en archivo
- **Ordenamiento automático**: Los turnos se muestran ordenados por día y hora
- **Control de disponibilidad**: Evita solapamiento de horarios
- **Exclusión de fines de semana**: Solo permite turnos en días hábiles

## 🏗️ Estructura del Proyecto

```
📦 sistema-turnos/
├── 📄 main.c                    # Código fuente principal
├── 📄 turnos_julio2025.txt      # Archivo de datos (generado automáticamente)
└── 📖 README.md                 # Documentación
```

## 🔧 Compilación y Ejecución

### Requisitos

- Compilador GCC
- Sistema operativo compatible con C estándar

### Compilar

```bash
gcc -o sistema_turnos main.c
```

### Ejecutar

```bash
./sistema_turnos
```

## 📊 Estructura de Datos

### Estructura `Turno`

```c
struct Turno {
    char apellido[16];      // Apellido del cliente (máx 15 caracteres)
    char nombre[16];        // Nombre del cliente (máx 15 caracteres)
    int dni;               // DNI (7 u 8 dígitos)
    char telefono[11];     // Teléfono (10 dígitos numéricos)
    int dia;               // Día del mes (1-31, excluyendo fines de semana)
    int hora;              // Hora del turno (8-15)
    char servicio[11];     // Tipo de servicio (máx 10 caracteres)
    struct Turno* siguiente; // Puntero al siguiente turno
};
```

## 🎯 Funcionalidades Detalladas

### 1. **Reservar Turno**

- **Función**: `reservarTurno()`
- **Descripción**: Permite crear un nuevo turno solicitando todos los datos del cliente
- **Validaciones**:
  - DNI: Debe tener 7 u 8 dígitos
  - Teléfono: Exactamente 10 dígitos numéricos
  - Día: Entre 1-31, excluyendo fines de semana
  - Hora: Entre 8:00 y 15:00, sin superposiciones
- **Características especiales**:
  - Muestra horarios ocupados del día seleccionado
  - Ofrece cambiar de día si no hay horarios disponibles
  - Permite cancelar la reserva en cualquier momento

### 2. **Listar Turnos del Mes**

- **Función**: `listarTurnos()`
- **Descripción**: Muestra todos los turnos ordenados cronológicamente
- **Formato de salida**:
  ```
  Día 15 - 10:00hs | García Juan | DNI: 12345678 | Tel: 1234567890 | Servicio: Consulta
  ```

### 3. **Listar Turnos por Día**

- **Función**: `listarPorDia()`
- **Descripción**: Filtra y muestra turnos de un día específico
- **Validación**: Solo acepta días válidos (no fines de semana)

### 4. **Buscar por DNI**

- **Función**: `buscarPorDNI()`
- **Descripción**: Encuentra todos los turnos asociados a un DNI específico
- **Utilidad**: Ideal para clientes con múltiples turnos

### 5. **Cancelar Turno**

- **Función**: `cancelarTurno()`
- **Descripción**: Elimina un turno específico de la lista
- **Identificación requerida**: DNI + Día + Hora
- **Gestión de memoria**: Libera automáticamente la memoria del turno cancelado

### 6. **Modificar Turno**

- **Función**: `modificarTurno()`
- **Descripción**: Permite editar los datos de un turno existente
- **Proceso**:
  1. Busca por DNI y muestra todos los turnos del cliente
  2. Solicita día y hora para identificar el turno específico
  3. Permite modificar todos los campos
  4. Valida nueva disponibilidad de horario

## ⚙️ Funciones Auxiliares

### `esFinDeSemana(int dia)`

- **Propósito**: Determina si un día cae en fin de semana
- **Días bloqueados en julio 2025**: 5, 6, 12, 13, 19, 20, 26, 27

### `turnoOcupado(struct Turno* lista, int dia, int hora)`

- **Propósito**: Verifica si ya existe un turno en la fecha/hora especificada
- **Retorna**: 1 si está ocupado, 0 si está libre

### `ordenarLista(struct Turno** lista)`

- **Propósito**: Ordena los turnos por día y hora
- **Algoritmo**: Burbuja adaptado para listas enlazadas
- **Criterio**: Primero por día, luego por hora

### `guardarEnArchivo(struct Turno* lista)`

- **Propósito**: Persiste todos los turnos en archivo de texto
- **Formato**: Un turno por línea con datos separados por espacios
- **Archivo**: `turnos_julio2025.txt`

### `cargarDesdeArchivo(struct Turno** lista)`

- **Propósito**: Recupera turnos del archivo al iniciar el programa
- **Comportamiento**: Si no existe el archivo, inicia con lista vacía

## 🚀 Casos de Uso

### Escenario 1: Reserva de turno exitosa

1. Usuario selecciona opción "Reservar turno"
2. Ingresa datos personales (nombre, apellido, DNI, teléfono)
3. Selecciona día hábil
4. Sistema muestra horarios ocupados
5. Usuario elige hora disponible
6. Especifica tipo de servicio
7. Sistema confirma la reserva

### Escenario 2: Día sin disponibilidad

1. Usuario intenta reservar en día saturado
2. Sistema muestra mensaje "No hay horarios disponibles"
3. Ofrece opción de cambiar de día
4. Usuario puede elegir otro día o cancelar

### Escenario 3: Modificación de turno

1. Usuario ingresa DNI
2. Sistema muestra todos los turnos del cliente
3. Usuario especifica cuál turno modificar (día + hora)
4. Sistema permite editar todos los campos
5. Valida nueva disponibilidad
6. Confirma modificación

## 📋 Validaciones del Sistema

| Campo    | Validación               | Mensaje de Error                                      |
| -------- | ------------------------ | ----------------------------------------------------- |
| DNI      | 7 u 8 dígitos            | "ERROR: DNI inválido"                                 |
| Teléfono | 10 dígitos numéricos     | "ERROR: El teléfono debe tener 10 dígitos numéricos"  |
| Día      | 1-31, no fines de semana | "ERROR: Día inválido o fin de semana"                 |
| Hora     | 8-15, sin solapamiento   | "ERROR: Horario inválido" / "ERROR: Turno ya ocupado" |
| Apellido | Máximo 15 caracteres     | Truncamiento automático                               |
| Nombre   | Máximo 15 caracteres     | Truncamiento automático                               |
| Servicio | Máximo 10 caracteres     | Truncamiento automático                               |

## 🗓️ Calendario Julio 2025

### Días Hábiles Disponibles

```
    Julio 2025
Lu Ma Mi Ju Vi Sa Do
    1  2  3  4  5  6
 7  8  9 10 11 12 13
14 15 16 17 18 19 20
21 22 23 24 25 26 27
28 29 30 31
```

**Días bloqueados (fines de semana)**: 5, 6, 12, 13, 19, 20, 26, 27

**Días disponibles**: 1, 2, 3, 4, 7, 8, 9, 10, 11, 14, 15, 16, 17, 18, 21, 22, 23, 24, 25, 28, 29, 30, 31

**Horarios disponibles**: 8:00, 9:00, 10:00, 11:00, 12:00, 13:00, 14:00, 15:00

## 💾 Formato del Archivo de Datos

El archivo `turnos_julio2025.txt` almacena los datos en formato de texto plano:

```
Garcia Juan 12345678 1234567890 15 10 Consulta
Rodriguez Maria 87654321 0987654321 16 14 Revision
Lopez Carlos 11223344 5556667777 17 9 Tratamiento
```

**Estructura de cada línea**:

```
[Apellido] [Nombre] [DNI] [Telefono] [Dia] [Hora] [Servicio]
```

## 🔒 Características de Seguridad

- **Validación de entrada**: Todos los campos son validados antes de ser almacenados
- **Gestión de memoria**: Liberación automática de memoria en cancelaciones
- **Integridad de datos**: Verificación de disponibilidad antes de confirmar reservas
- **Persistencia segura**: Guardado automático al finalizar el programa

## ⚡ Optimizaciones Implementadas

1. **Lista enlazada**: Gestión eficiente de memoria dinámica
2. **Ordenamiento automático**: Los turnos siempre se muestran cronológicamente
3. **Carga diferida**: Solo carga datos al iniciar y guarda al salir
4. **Validación temprana**: Evita procesamientos innecesarios con datos inválidos

## 🛠️ Mantenimiento y Resolución de Problemas

### Problemas Comunes

#### El programa no guarda los datos

**Solución**: Verificar permisos de escritura en el directorio

#### Error al cargar archivo existente

**Solución**: Verificar formato del archivo `turnos_julio2025.txt`

#### Memoria insuficiente

**Solución**: El sistema maneja automáticamente la falta de memoria, cancelando operaciones si es necesario

### Limpieza del Sistema

Para resetear completamente el sistema:

```bash
rm turnos_julio2025.txt
```

## 🎨 Posibles Mejoras Futuras

- [ ] Interfaz gráfica (GUI)
- [ ] Base de datos SQL
- [ ] Búsqueda por múltiples criterios
- [ ] Recordatorios automáticos
- [ ] Exportación a diferentes formatos
- [ ] Validación de horarios de almuerzo
- [ ] Soporte para múltiples meses
- [ ] Sistema de usuarios y permisos
- [ ] Estadísticas de ocupación
- [ ] Integración con calendario
