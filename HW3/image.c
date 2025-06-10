//
// Created by iliya on 27.03.2025.
//

#include "image.h"
#include "YUV.c"
#include "BMP.c"

Image* create_image(int w, int h) {
    Image* img = (Image*)malloc(sizeof(Image));
    if (!img) return NULL;
    img->width = w;
    img->height = h;
    img->data = (unsigned char*)malloc(w * h * 3);
    if (!img->data) {
        free(img);
        return NULL;
    }
    return img;
}

void destroy_image(Image* img) {
    if (img) {
        free(img->data);
        free(img);
    }
}

Image* downscale(const Image* img, int k) {
    if (k <= 1) return create_image(img->width, img->height);

    int new_width = img->width / k;
    int new_height = img->height / k;
    Image* new_img = create_image(new_width, new_height);
    if (!new_img) return NULL;

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int sum_b = 0, sum_g = 0, sum_r = 0;
            int count = 0;
            for (int dy = 0; dy < k; ++dy) {
                for (int dx = 0; dx < k; ++dx) {
                    int orig_x = x * k + dx;
                    int orig_y = y * k + dy;
                    if (orig_x < img->width && orig_y < img->height) {
                        int idx = (orig_y * img->width + orig_x) * 3;
                        sum_b += img->data[idx];
                        sum_g += img->data[idx + 1];
                        sum_r += img->data[idx + 2];
                        count++;
                    }
                }
            }
            int new_idx = (y * new_width + x) * 3;
            new_img->data[new_idx] = sum_b / count;
            new_img->data[new_idx + 1] = sum_g / count;
            new_img->data[new_idx + 2] = sum_r / count;
        }
    }
    return new_img;
}

Image* upscale(const Image* img, int k) {
    if (k <= 1) return create_image(img->width, img->height);

    int new_width = img->width * k;
    int new_height = img->height * k;
    Image* new_img = create_image(new_width, new_height);
    if (!new_img) return NULL;

    for (int y = 0; y < img->height; ++y) {
        for (int x = 0; x < img->width; ++x) {
            int idx = (y * img->width + x) * 3;
            unsigned char b = img->data[idx];
            unsigned char g = img->data[idx + 1];
            unsigned char r = img->data[idx + 2];
            for (int dy = 0; dy < k; ++dy) {
                for (int dx = 0; dx < k; ++dx) {
                    int new_x = x * k + dx;
                    int new_y = y * k + dy;
                    int new_idx = (new_y * new_width + new_x) * 3;
                    new_img->data[new_idx] = b;
                    new_img->data[new_idx + 1] = g;
                    new_img->data[new_idx + 2] = r;
                }
            }
        }
    }
    return new_img;
}

void toGrayscale(Image* img) {
    for (size_t i = 0; i < (size_t)img->width * img->height * 3; i += 3) {
        unsigned char b = img->data[i];
        unsigned char g = img->data[i + 1];
        unsigned char r = img->data[i + 2];
        unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
        img->data[i] = gray;
        img->data[i + 1] = gray;
        img->data[i + 2] = gray;
    }
}


