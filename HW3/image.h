//
// Created by iliya on 27.03.2025.
//

#ifndef CPP_ITMO_IMAGE_H
#define CPP_ITMO_IMAGE_H

#include <stdio.h>

typedef struct {
    int width;
    int height;
    unsigned char* data;
} Image;

Image* create_image(int w, int h);
void destroy_image(Image* img);
int readYUV(Image* img, const char* filename);
Image* downscale(const Image* img, int down_size);
Image* upscale(const Image* img, int up_size);
void toGrayscale(Image* img);
void writeBMP(const char* filename, const Image* img);

#endif //CPP_ITMO_IMAGE_H
