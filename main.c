/*
** EPITECH PROJECT, 2025
** TESSERACT VISUALIZATION
** File description:
** Implementation of a 4D hypercube (tesseract)
*/

#include "main.h"

static int events(void)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(WINDOW, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(WINDOW);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyP)
            TESSERACT->rotation_speed += 0.01;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyM)
            TESSERACT->rotation_speed -= 0.01;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF)
            TESSERACT->fov += 0.1;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyG)
            TESSERACT->fov -= 0.1;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyV)
            TESSERACT->scale += 10.0;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyC)
            TESSERACT->scale -= 10.0;
    }
    return SUCCESS;
}

int run(void)
{
    while (sfRenderWindow_isOpen(WINDOW)) {
        sfRenderWindow_clear(WINDOW, sfBlack);
        events();
        update_tesseract();
        sfRenderWindow_display(WINDOW);
    }
    return SUCCESS;
}

int main(void)
{
    init_tesseract();
    if (init_hypercube() == ERROR)
        return ERROR;
    create_window(800, 600, "Tesseract Visualization");
    run();
    destroy_tesseract();
    destroy_window();
    return SUCCESS;
}
