//
// Created by iliya on 27.03.2025.
//

#include "image.h"
#include <stdio.h>
#include <stdlib.h>


#define safe_fwrite(data, size, count, stream) if(fwrite(data, size, count, stream) != count) goto printerror

int writeBMP(const char* filename, const Image* img) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return 1;
    }

    int width = img->width;
    int height = img->height;
    int row_padded = (width * 3 + 3) & (~3);
    int data_size = row_padded * height;

    fputc('B', file);
    fputc('M', file);
    int file_size = 54 + data_size;
    safe_fwrite(&file_size, 4, 1, file);
    safe_fwrite("\0\0\0\0", 4, 1, file);
    int offset = 54;
    safe_fwrite(&offset, 4, 1, file);

    int header_size = 40;
    safe_fwrite(&header_size, 4, 1, file);
    safe_fwrite(&width, 4, 1, file);
    safe_fwrite(&height, 4, 1, file);
    short planes = 1;
    safe_fwrite(&planes, 2, 1, file);
    short bit_count = 24;
    safe_fwrite(&bit_count, 2, 1, file);
    int compression = 0;
    safe_fwrite(&compression, 4, 1, file);
    safe_fwrite(&data_size, 4, 1, file);
    int x_pixels_per_meter = 0;
    safe_fwrite(&x_pixels_per_meter, 4, 1, file);
    int y_pixels_per_meter = 0;
    safe_fwrite(&y_pixels_per_meter, 4, 1, file);
    int colors_used = 0;
    safe_fwrite(&colors_used, 4, 1, file);
    int colors_important = 0;
    safe_fwrite(&colors_important, 4, 1, file);

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            fputc(img->data[idx], file);     // B
            fputc(img->data[idx + 1], file); // G
            fputc(img->data[idx + 2], file); // R
        }
        for (int p = 0; p < row_padded - width * 3; ++p) {
            fputc(0, file);
        }
    }
    fclose(file);
    return 0;

printerror:
    fclose(file);
    fprintf(stderr, "Cannot write data to file: %s\n", filename);
    return 1;
}
