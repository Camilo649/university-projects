#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "APIG24.h"

int main() {
    
    printf("Probando proyecto Discreta II\n");

    Grafo G = ConstruirGrafo();
    if (G == NULL) {
        fprintf(stderr, "ERROR: Fallo al leer el grafo.\n");
        fprintf(stderr, "Cerrando el programa ...\n");
        exit(1);
    }
    u32 num_vertices = NumeroDeVertices(G);
    u32 num_lados = NumeroDeLados(G);
    u32 delta = Delta(G);

    printf("Estructura del grafo\n\n");
    printf("El número de vertices: %u\n", num_vertices);
    printf("El número de lados: %u\n", num_lados);
    printf("El Delta: %u.\n", delta);

    // Mostrar información de los vértices y sus vecinos
    for (u32 i = 0; i < G->vertices_num; ++i) {
        printf("Vértice %u\n", i);
        printf("  Color: %u\n", G->vertices[i]->color);
        printf("  Grado: %u\n", G->vertices[i]->grado);
        printf("  Vecinos:");
        for (u32 j = 0; j < G->vertices[i]->grado; ++j) {
            printf(" %u", G->vertices[i]->vecinos->residentes[j]->id);
        }
        printf("\n");
    }

    // Mostrar los vecinos de cada vértice
    for (u32 i = 0; i < G->vertices_num; ++i) {
        printf("Vecinos del vértice %u:", i);
        for (u32 j = 0; j < G->vertices[i]->grado; ++j) {
            u32 vecino_id = Vecino(j, i, G);
            printf(" %u", vecino_id);
        }
        printf("\n");
    }

    //libero memoria
    DestruirGrafo(G);

    printf("Fin de la prueba\n\n");
    return 0;
}