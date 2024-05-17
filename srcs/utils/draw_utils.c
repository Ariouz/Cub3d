#include "cub3d.h"

void    draw_line_to_img(t_img *img, int beginX, int beginY, int endX, int endY, int color)
{
    double deltaX;
    double deltaY;
    double pixelX;
    double pixelY;
    int pixels;
    
    deltaX = endX - beginX;
    deltaY = endY - beginY;
    pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
    deltaX /= pixels;
    deltaY /= pixels;
    pixelX = beginX;
    pixelY = beginY;
    while (pixels != 0)
    {
        put_pixel_img(*img, pixelX, pixelY, color);
        pixelX += deltaX;
        pixelY += deltaY;
        pixels--;
    }
}

void    draw_rect_to_img(t_img *img, int beginX, int beginY, int endX, int endY, int color, int width)
{
    int i;
    int j;
    (void) width;

    i = 0;
    while (i < endY - beginY)
    {
        j = 0;
        while (j < endX - beginX)
        {
            put_pixel_img(*img, j + beginX, i + beginY, color);
            j++;
        }
        i++;
    }
}