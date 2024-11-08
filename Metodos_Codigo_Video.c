#include <stdio.h>
#include <stdlib.h>

// Tamaño máximo de bloques en disco
#define DISK_SIZE 100

// Estructura para simular el disco con bloques
int disk[DISK_SIZE] = {0}; // 0 indica bloque libre, 1 indica bloque ocupado

// Función para imprimir el estado del disco (para ver la asignación de bloques)
void printDisk() {
    printf("Estado del disco:\n");
    for (int i = 0; i < DISK_SIZE; i++) {
        printf("[%d]", disk[i]);
        if ((i + 1) % 10 == 0) printf("\n"); // Salto de línea cada 10 bloques para mejor visualización
    }
    printf("\n");
}

// Función de asignación contigua
void asignacionContigua(int startBlock, int fileSize) {
    printf("Asignación contigua:\n");

    // Verificar si hay suficiente espacio contiguo desde el bloque inicial
    int canAllocate = 1;
    for (int i = startBlock; i < startBlock + fileSize; i++) {
        if (disk[i] == 1) { // Si el bloque ya está ocupado
            canAllocate = 0;
            break;
        }
    }

    if (canAllocate) {
        // Asignar los bloques contiguamente
        for (int i = startBlock; i < startBlock + fileSize; i++) {
            disk[i] = 1;
        }
        printf("Archivo asignado de manera contigua desde el bloque %d\n", startBlock);
    } else {
        printf("Error: No hay espacio contiguo suficiente para el archivo.\n");
    }

    printDisk(); // Mostrar el estado del disco después de la asignación
}

// Función de asignación ligada
void asignacionLigada(int fileSize) {
    printf("Asignación ligada:\n");

    int prevBlock = -1; // Mantiene el bloque anterior para establecer los enlaces
    int blocksAssigned = 0;

    for (int i = 0; i < DISK_SIZE && blocksAssigned < fileSize; i++) {
        if (disk[i] == 0) { // Si el bloque está libre
            disk[i] = 1;    // Marcar el bloque como ocupado
            blocksAssigned++;

            if (prevBlock != -1) {
                printf("Bloque %d -> ", prevBlock); // Enlazar al bloque anterior
            }
            printf("Bloque %d\n", i);

            prevBlock = i; // Actualizar el bloque anterior
        }
    }

    if (blocksAssigned < fileSize) {
        printf("Error: No hay suficientes bloques libres para la asignación ligada.\n");
    }

    printDisk(); // Mostrar el estado del disco después de la asignación
}

// Función de asignación indexada
void asignacionIndexada(int fileSize) {
    printf("Asignación indexada:\n");

    int indexBlock = -1; // Bloque de índice (donde se almacenan los punteros a los bloques de datos)

    // Buscar un bloque libre para el índice
    for (int i = 0; i < DISK_SIZE; i++) {
        if (disk[i] == 0) {
            indexBlock = i;
            disk[i] = 1; // Marcar el bloque de índice como ocupado
            printf("Bloque de índice asignado en el bloque %d\n", indexBlock);
            break;
        }
    }

    if (indexBlock == -1) {
        printf("Error: No hay bloques libres para el bloque de índice.\n");
        return;
    }

    int blocksAssigned = 0;
    // Asignar bloques de datos y registrar sus direcciones en el bloque de índice
    for (int i = 0; i < DISK_SIZE && blocksAssigned < fileSize; i++) {
        if (disk[i] == 0) { // Si el bloque está libre
            disk[i] = 1;    // Marcar el bloque como ocupado
            blocksAssigned++;
            printf("Bloque %d apuntado por índice en %d\n", i, indexBlock);
        }
    }

    if (blocksAssigned < fileSize) {
        printf("Error: No hay suficientes bloques libres para la asignación indexada.\n");
    }

    printDisk(); // Mostrar el estado del disco después de la asignación
}

// Función principal para probar los métodos de asignación
int main() {
    // Limpiar la consola
    system("clear");

    printf("Simulación de métodos de asignación de espacio en disco:\n\n");

    // Simulación de asignación contigua
    asignacionContigua(10, 5);

    // Simulación de asignación ligada
    asignacionLigada(5);

    // Simulación de asignación indexada
    asignacionIndexada(5);

    return 0;
}
