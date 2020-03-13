//
//  main.cpp
//  YetAnotherRender
//
//  Created by Pavel Kondrashkov on 3/13/20.
//  Copyright © 2020 pkondrashkov. All rights reserved.
//

#include <iostream>

void draw_line(int x0, int y0, int x1, int y1);

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "tgaimage.h"

#include "math.h"

const int width = 500;
const int height = 500;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

TGAImage image_tga(width, height, TGAImage::RGB);

struct Image {
    const int width;
    const int height;
    const int channel_number;
    uint8_t *pixels;
};
struct Color {
    int r, g, b;
};

///compare with other API
void image_set_pixel(Image *image, int x, int y, Color color) {
    if (!image->pixels
        || x < 0 || y < 0
        || x >= image->width || y >= image->height) {
        return;
    }

    int index = image->width * y + x;
    if (index < 0) return;
    index *= image->channel_number;
    image->pixels[index++] = color.r;
    image->pixels[index++] = color.g;
    image->pixels[index++] = color.b;
}

Image image = { width, height, 3 };

int main(int argc, char **argv) {
    image.pixels = (uint8_t *)calloc(image.width * image.height * image.channel_number, sizeof(image.pixels));

    draw_line(50, 50, 250, 450);
    draw_line(250, 450, 450, 340);
    draw_line(450, 340, 50, 50);


    stbi_flip_vertically_on_write(true); /// sets origin at left bottom
    stbi_write_png("render.png",
                   image.width,
                   image.height,
                   image.channel_number,
                   image.pixels,
                   image.width * image.channel_number);
    free(image.pixels);

    image_tga.flip_vertically(); /// sets origin at left bottom
    image_tga.write_tga_file("output.tga");

    return 0;
}

void draw_line(int x0, int y0, int x1, int y1) {
    if (abs(x1 - x0) > abs(y1 - y0)) {
        if (x0 > x1) {
            swap(&x0, &x1);
            swap(&y0, &y1);
        }
        int *values;
        interpolate(x0, y0, x1, y1, &values);
        for (int x = x0; x < x1; x++) {
            image_set_pixel(&image, x, values[x - x0], { 255, 0, 0 });
            image_tga.set(x, values[x - x0], red);
        }
    } else {
        if (y0 > y1) {
            swap(&x0, &x1);
            swap(&y0, &y1);
        }
        int *values;
        interpolate(y0, x0, y1, x1, &values);
        for (int y = y0; y < y1; y++) {
            image_set_pixel(&image, values[y - y0], y, { 255, 0, 0 });
            image_tga.set(values[y - y0], y, red);
        }
    }
}
