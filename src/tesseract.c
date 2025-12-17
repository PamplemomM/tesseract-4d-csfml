


#include "../include/header_hypercube.h"

tesseract_t **get_tesseract(void)
{
    static tesseract_t *tesseract = NULL;

    return &tesseract;
}

int init_tesseract_values(void)
{
    tesseract_t *tesseract = malloc(sizeof(tesseract_t) * 1);

    if (tesseract == NULL)
        return ERROR;
    tesseract->pos = (sfVector2f){400, 300};
    tesseract->scale = 100.0;
    tesseract->fov = 4.0;
    tesseract->rotation_speed = 0.01;
    tesseract->angle_xy = 0.0;
    tesseract->angle_xz = 0.0;
    tesseract->angle_xw = 0.0;
    tesseract->angle_yz = 0.0;
    tesseract->angle_yw = 0.0;
    tesseract->angle_zw = 0.0;
    tesseract->lines = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(tesseract->lines, sfLines);
    sfVertexArray_resize(tesseract->lines, 2);
    *get_tesseract() = tesseract;
    return SUCCESS;
}

int destroy_tesseract(void)
{
    tesseract_t *tesseract = TESSERACT;

    if (tesseract == NULL)
        return ERROR;
    sfVertexArray_destroy(tesseract->lines);
    free(tesseract);
    *get_tesseract() = NULL;
    return SUCCESS;
}

int move_vertices(sfVertexArray *array, sfVector2f pos)
{
    int cnt = sfVertexArray_getVertexCount(array);
    sfVertex *current = NULL;

    for (int i = 0; i < cnt; i++) {
        current = sfVertexArray_getVertex(array, i);
        current->position.x += pos.x;
        current->position.y += pos.y;
    }
    printf("Moving\n");
    return SUCCESS;
}
