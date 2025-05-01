/*
** EPITECH PROJECT, 2025
** window_csfml.c
** File description:
** Window related functions.
*/

#include "main.h"

sfRenderWindow **get_window(void)
{
    static sfRenderWindow *window = NULL;

    return &window;
}

void create_window(unsigned int width, unsigned int height, char const *name)
{
    sfVideoMode video_mode;

    video_mode.width = width;
    video_mode.height = height;
    video_mode.bitsPerPixel = 32;
    WINDOW = sfRenderWindow_create(video_mode, name,
    sfDefaultStyle, NULL);
    sfRenderWindow_setFramerateLimit(WINDOW, 60);
    sfRenderWindow_setKeyRepeatEnabled(WINDOW, sfFalse);
}

void destroy_window(void)
{
    if (WINDOW == NULL)
        return;
    sfRenderWindow_destroy(WINDOW);
}
