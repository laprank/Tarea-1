# Sistema de Gestión de Pacientes en Hospital

## Descripción

Este sistema de gestión hospitalaria permite a los usuarios registrar pacientes, asignar prioridades, ver la lista de espera y atender a los pacientes según su prioridad. Está diseñado para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos con mayor necesidad reciban atención prioritaria.

## Instrucciones para Compilar y Ejecutar en Repl.it

Para una configuración y ejecución rápida, sigue estos pasos:

1. Visita [Repl.it](https://repl.it/).
2. Inicia sesión o crea una nueva cuenta si aún no tienes una.
3. En tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/username/sistema-gestion-pacientes.git`.
5. Repl.it clonará el repositorio y preparará un entorno de ejecución.
6. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionalidades Actuales:

1. **Registrar Paciente:** Permite registrar un nuevo paciente con su nombre, edad y síntomas.
   
2. **Asignar Prioridad:** Permite asignar prioridad a un paciente registrado (Baja, Media, Alta).
   
3. **Mostrar Lista de Espera:** Muestra la lista de pacientes en espera, ordenados por prioridad y hora de registro.

4. **Atender Siguiente Paciente:** Atiende al siguiente paciente en la lista de espera, respetando su prioridad.

5. **Mostrar Pacientes por Prioridad:** Permite mostrar una lista de pacientes ordenada por orden de llegada de la prioridad que se desee ver.

### Problemas Conocidos:

- La funcionalidad de exportar e importar la lista de espera desde/hacia un archivo CSV está en desarrollo.

### Áreas de Mejora:

- Mejorar la interfaz de usuario para una experiencia más amigable.
- Permitir la edición de datos de pacientes.

## Ejemplo de Uso

1. **Registrar un Nuevo Paciente:**
   - Se registra un nuevo paciente proporcionando su nombre, edad y síntomas.
   
2. **Asignar Prioridad a un Paciente:**
   - Después de una evaluación, se puede asignar una prioridad (Baja, Media, Alta) a un paciente registrado.

3. **Mostrar la Lista de Espera:**
   - Se muestra la lista de pacientes en espera, ordenados por prioridad y hora de registro.

4. **Atender al Siguiente Paciente:**
   - Se atiende al siguiente paciente en la lista de espera, respetando su prioridad.

5. **Mostrar Pacientes por Prioridad:**
   - Permite seleccionar una prioridad (Baja, Media, Alta) y muestra una lista de pacientes ordenada por orden de llegada de esa prioridad.

## Contribuciones

### Franco Ugarte:

- Implementó todas las funciones del sistema.
- Realizó documentación y comentarios en el código.
- Diseñó y redactó el README.

---

Este README proporciona una visión general del sistema de gestión hospitalaria y guía sobre su instalación, funcionalidades y uso en Repl.it.
