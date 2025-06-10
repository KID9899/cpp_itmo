//
// Created by iliya on 27.03.2025.
//

#include "image.h"

void setYUVPixel(Image* img, size_t idx, unsigned char Y, unsigned char U, unsigned char V) {

    int R = (int) (Y + 1.402 * (V - 128));
    int G = (int) (Y - 0.344 * (U - 128) - 0.714 * (V - 128));
    int B = (int) (Y + 1.772 * (U - 128));

    R = (R < 0) ? 0 : ((R > 255) ? 255 : R);
    G = (G < 0) ? 0 : ((G > 255) ? 255 : G);
    B = (B < 0) ? 0 : ((B > 255) ? 255 : B);

    int rgb_idx = idx * 3;
    img->data[rgb_idx + 0] = (unsigned char) B;
    img->data[rgb_idx + 1] = (unsigned char) G;
    img->data[rgb_idx + 2] = (unsigned char) R;

}

int readYUV(Image* img, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return 0;
    }

    int width = img->width;
    int height = img->height;
    int uv_width = (width + 1) / 2;
    int uv_height = (height + 1) / 2 + height % 2;

    unsigned char* y_data = (unsigned char*)malloc(width * height);
    unsigned char* u_data = (unsigned char*)malloc(uv_width * uv_height);
    unsigned char* v_data = (unsigned char*)malloc(uv_width * uv_height);

    if (!y_data || !u_data || !v_data) {
        fprintf(stderr, "Error allocating memory.\n");
        goto finally;
    }

    for (int i = 0; i < height; i++) {
        if (fread(y_data + i * width, 1, width, file) != width) {
            fprintf(stderr, "Error reading Y.\n");
            goto finally;
        }
        if (width % 2) {
            fseek(file, 1, SEEK_CUR);
        }
    }

    for (int i = 0; i < uv_height; i++) {
        if (fread(u_data + i * uv_width, 1, uv_width, file) != uv_width) {
            fprintf(stderr, "Error reading U.\n");
            goto finally;
        }
    }

    for (int i = 0; i < uv_height; i++) {
        if (fread(v_data + i * uv_width, 1, uv_width, file) != uv_width) {
            fprintf(stderr, "Error reading V.\n");
            goto finally;
        }
    }

    for (int y = 0; y < img->height; ++y) {
        for (int x = 0; x < img->width; ++x) {
            int idx = y * width + x;
            int uv_idx = (y / 2) * uv_width + (x / 2);
            setYUVPixel(img, idx, y_data[idx], u_data[uv_idx], v_data[uv_idx]);

        }
    }

    if (y_data)
        free(y_data);
    if (u_data)
        free(u_data);
    if (v_data)
        free(v_data);
    fclose(file);
    return 0;

finally:
    if (y_data)
        free(y_data);
    if (u_data)
        free(u_data);
    if (v_data)
        free(v_data);
    fclose(file);
    return 1;
}
