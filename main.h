/*
** EPITECH PROJECT, 2025
** header_event.h
** File description:
** Header file for the events.
*/

#ifndef EVENT_H
    #define EVENT_H

    #include <SFML/Graphics.h>
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>

    // defines:
    #define SUCCESS 0
    #define ERROR 84
    #define TRUE 1
    #define FALSE 0

    #define SIZE 16

    #define FOV 4.0
    #define SCALE 100.0

    #define WINDOW (*get_window())
    #define TESSERACT (*get_tesseract())


typedef struct {
    float x;
    float y;
    float z;
    float w;
} vector_4f_t;

typedef struct {
    int from;
    int to;
} edge_t;

typedef struct tesseract_s {
    float scale;
    float fov;
    float rotation_speed;
    vector_4f_t vertices[16];
    edge_t edges[32];
    sfVertexArray *lines;
    float angle_xy;
    float angle_xz;
    float angle_xw;
    float angle_yz;
    float angle_yw;
    float angle_zw;
} tesseract_t;


// --- init_hypercube.c ---
int init_hypercube(void);

// --- tesseract.c ---
tesseract_t **get_tesseract(void);
int init_tesseract(void);
int destroy_tesseract(void);

// --- update_tesseract.c ---
int update_tesseract(void);

// --- window.c ---
sfRenderWindow **get_window(void);
void create_window(unsigned int width, unsigned int height, char const *name);
void destroy_window(void);

#endif /* EVENT_H */
