#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.c"

int main(int argc, char* argv[]) {
    const char* input_file = NULL;
    const char* output_file = NULL;
    int width = 0;
    int height = 0;
    int up_size = 1;
    int down_size = 1;
    int to_gray_scale = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "--width") == 0 && i + 1 < argc) {
            width = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--height") == 0 && i + 1 < argc) {
            height = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--up-size") == 0 && i + 1 < argc) {
            up_size = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--down-size") == 0 && i + 1 < argc) {
            down_size = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--to-gray-scale") == 0) {
            to_gray_scale = 1;
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[i]);
            return 1;
        }
    }

    if (!input_file || !output_file || width <= 0 || height <= 0) {
        fprintf(stderr, "Missing required arguments.\n");
        return 1;
    }

    if (up_size < 1 || down_size < 1) {
        fprintf(stderr, "Size factors must be at least 1.\n");
        return 1;
    }

    Image* img = create_image(width, height);
    if (!img) {
        fprintf(stderr, "Failed to create Image.\n");
        return 1;
    }
    if (readYUV(img, input_file)) {
        destroy_image(img);
        return 1;
    }
    if (down_size > 1) {
        Image* downscaled = downscale(img, down_size);
        destroy_image(img);
        if (!downscaled) {
            fprintf(stderr, "Failed to downscale image.\n");
            return 1;
        }
        img = downscaled;
    }
    if (up_size > 1) {
        Image* upscaled = upscale(img, up_size);
        destroy_image(img);
        if (!upscaled) {
            fprintf(stderr, "Failed to upscale image.\n");
            return 1;
        }
        img = upscaled;
    }
    if (to_gray_scale) {
        toGrayscale(img);
    }

    if (writeBMP(output_file, img)) {
        destroy_image(img);
        return 1;
    }
    destroy_image(img);
    return 0;
}