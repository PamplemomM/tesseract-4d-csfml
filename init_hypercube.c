/*
** EPITECH PROJECT, 2025
** init_hypercube.c
** File description:
** Initialization of a 4D hypercube (tesseract)
*/

#include "main.h"

static int init_hypercube_inside(int val, int w, int z)
{
    vector_4f_t *vertices = TESSERACT->vertices;

    for (int y = -1; y <= 1; y += 2) {
        for (int x = -1; x <= 1; x += 2) {
            vertices[val].x = x;
            vertices[val].y = y;
            vertices[val].z = z;
            vertices[val].w = w;
            val++;
        }
    }
    return val;
}

static int create_hypercube_inside(int val, int i, int j)
{
    int cpt = 0;
    vector_4f_t *vertices = TESSERACT->vertices;
    edge_t *edges = TESSERACT->edges;

    if (vertices[i].x != vertices[j].x)
        cpt++;
    if (vertices[i].y != vertices[j].y)
        cpt++;
    if (vertices[i].z != vertices[j].z)
        cpt++;
    if (vertices[i].w != vertices[j].w)
        cpt++;
    if (cpt == 1 && val < 32) {
        edges[val].from = i;
        edges[val].to = j;
        val++;
    }
    return val;
}

int init_hypercube(void)
{
    int val = 0;

    for (int w = -1; w <= 1; w += 2) {
        for (int z = -1; z <= 1; z += 2)
        val = init_hypercube_inside(val, w, z);
    }
    val = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = i + 1; j < SIZE; j++)
        val = create_hypercube_inside(val, i, j);
    }
    return SUCCESS;
}
