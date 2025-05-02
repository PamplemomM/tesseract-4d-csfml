/*
** EPITECH PROJECT, 2025
** update_tesseract.c
** File description:
** Update the tesseract.
*/

#include "main.h"

static int set_from_to(float *fromf, float *froms, float *tof, float *tos)
{
    *fromf = *tof;
    *froms = *tos;
    return SUCCESS;
}

static vector_4f_t get_4d_rotation_next(vector_4f_t res, float y, float z,
    float w)
{
    tesseract_t *t = TESSERACT;

    set_from_to(&y, &z, &res.y, &res.z);
    res.y = y * cos(t->angle_yz) - z * sin(t->angle_yz);
    res.z = y * sin(t->angle_yz) + z * cos(t->angle_yz);
    set_from_to(&y, &w, &res.y, &res.w);
    res.y = y * cos(t->angle_yw) - w * sin(t->angle_yw);
    res.w = y * sin(t->angle_yw) + w * cos(t->angle_yw);
    set_from_to(&z, &w, &res.z, &res.w);
    res.z = z * cos(t->angle_zw) - w * sin(t->angle_zw);
    res.w = z * sin(t->angle_zw) + w * cos(t->angle_zw);
    return res;
}

static vector_4f_t get_4d_rotation(vector_4f_t res)
{
    tesseract_t *t = TESSERACT;
    float x = res.x;
    float y = res.y;
    float z = res.z;
    float w = res.w;

    res.x = x * cos(t->angle_xy) - y * sin(t->angle_xy);
    res.y = x * sin(t->angle_xy) + y * cos(t->angle_xy);
    x = res.x;
    res.x = x * cos(t->angle_xz) - z * sin(t->angle_xz);
    res.z = x * sin(t->angle_xz) + z * cos(t->angle_xz);
    x = res.x;
    res.x = x * cos(t->angle_xw) - w * sin(t->angle_xw);
    res.w = x * sin(t->angle_xw) + w * cos(t->angle_xw);
    return get_4d_rotation_next(res, y, z, w);
}

static sfVector3f project_4d_to_3d(vector_4f_t p, float fov)
{
    sfVector3f res;
    float factor = fov / (fov + p.w);

    res.x = p.x * factor;
    res.y = p.y * factor;
    res.z = p.z * factor;
    printf("Setting the projection: %f %f %f %f\n", p.x, p.y, p.z, p.w);
    return res;
}

static sfVector2f project_3d_to_2d(sfVector3f p, float fov)
{
    sfVector2f result;
    float factor = fov / (fov + p.z);

    result.x = p.x * factor;
    result.y = p.y * factor;
    return result;
}

static int update_rotations(void)
{
    tesseract_t *t = TESSERACT;

    t->angle_xy += t->rotation_speed;
    t->angle_xz += t->rotation_speed;
    t->angle_xw += t->rotation_speed;
    t->angle_yz += t->rotation_speed;
    t->angle_yw += t->rotation_speed;
    t->angle_zw += t->rotation_speed;
    printf("%f %f %f %f %f %f\n", t->angle_xy, t->angle_xz, t->angle_xw,
        t->angle_yz, t->angle_yw, t->angle_zw);
    return SUCCESS;
}

static int project_vertexes(sfVector3f projected_3d[SIZE],
    sfVector2f projected_2d[SIZE])
{
    vector_4f_t *vertices = TESSERACT->vertices;
    vector_4f_t rotation;

    for (int i = 0; i < SIZE; i++) {
        rotation = get_4d_rotation(vertices[i]);
        projected_3d[i] = project_4d_to_3d(rotation, TESSERACT->fov);
        projected_2d[i] = project_3d_to_2d(projected_3d[i], TESSERACT->fov);
        projected_2d[i].x = projected_2d[i].x * TESSERACT->scale + 800 / 2.0;
        projected_2d[i].y = projected_2d[i].y * TESSERACT->scale + 600 / 2.0;
    }
    return SUCCESS;
}

static int draw_edges(sfVector2f projected_2d[SIZE])
{
    sfVertex *v1 = NULL;
    sfVertex *v2 = NULL;
    sfVertexArray *lines = TESSERACT->lines;
    edge_t *edges = TESSERACT->edges;

    for (int i = 0; i < 32; i++) {
        v1 = sfVertexArray_getVertex(lines, 0);
        v2 = sfVertexArray_getVertex(lines, 1);
        v1->position = (sfVector2f){projected_2d[edges[i].from].x,
            projected_2d[edges[i].from].y};
        v2->position = (sfVector2f){projected_2d[edges[i].to].x,
            projected_2d[edges[i].to].y};
        sfRenderWindow_drawVertexArray(WINDOW, lines, NULL);
    }
    return SUCCESS;
}

static int draw_circles(sfVector2f projected_2d[SIZE])
{
    sfCircleShape *circle = sfCircleShape_create();
    sfVector2f position;
    int size = 5;

    for (int i = 0; i < SIZE; i++) {
        position.x = projected_2d[i].x - size;
        position.y = projected_2d[i].y - size;
        sfCircleShape_setRadius(circle, size);
        sfCircleShape_setPosition(circle, position);
        sfRenderWindow_drawCircleShape(WINDOW, circle, NULL);
    }
    sfCircleShape_destroy(circle);
    return SUCCESS;
}

int update_tesseract(void)
{
    static sfVector3f projected_3d[SIZE];
    static sfVector2f projected_2d[SIZE];

    update_rotations();
    project_vertexes(projected_3d, projected_2d);
    draw_edges(projected_2d);
    draw_circles(projected_2d);
    return SUCCESS;
}
