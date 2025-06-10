//
// Created by iliya on 05.05.2025.
//

#include "image.h"
#include <iostream>

Image::Image(int width, int height) : width(width), height(height), data(width * height * 3) {
    if (width <= 0 || height <= 0) {
        std::cerr << "Invalid image dimensions: " << width << "x" << height << std::endl;
        this->width = 0;
        this->height = 0;
        this->data.clear();
    }
}

void Image::toGrayscale() {
    for (size_t i = 0; i < data.size(); i += 3) {
        unsigned char B = data[i];
        unsigned char G = data[i + 1];
        unsigned char R = data[i + 2];
        unsigned char gray = static_cast<unsigned char>(0.299 * R + 0.587 * G + 0.114 * B);
        data[i] = gray;
        data[i + 1] = gray;
        data[i + 2] = gray;
    }
}

Image* Image::downscale(int factor) const {
    if (factor <= 1) return new Image(width, height);
    int new_width = width / factor;
    int new_height = height / factor;
    Image* new_img = new Image(new_width, new_height);
    if (new_img->data.empty()) {
        delete new_img;
        return nullptr;
    }

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int sum_b = 0, sum_g = 0, sum_r = 0;
            int count = 0;
            for (int dy = 0; dy < factor; ++dy) {
                for (int dx = 0; dx < factor; ++dx) {
                    int orig_x = x * factor + dx;
                    int orig_y = y * factor + dy;
                    if (orig_x < width && orig_y < height) {
                        int idx = (orig_y * width + orig_x) * 3;
                        sum_b += data[idx];
                        sum_g += data[idx + 1];
                        sum_r += data[idx + 2];
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

Image* Image::upscale(int factor) const {
    if (factor <= 1) return new Image(width, height);
    int new_width = width * factor;
    int new_height = height * factor;
    Image* new_img = new Image(new_width, new_height);
    if (new_img->data.empty()) {
        delete new_img;
        return nullptr;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            unsigned char b = data[idx];
            unsigned char g = data[idx + 1];
            unsigned char r = data[idx + 2];
            for (int dy = 0; dy < factor; ++dy) {
                for (int dx = 0; dx < factor; ++dx) {
                    int new_x = x * factor + dx;
                    int new_y = y * factor + dy;
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

double Image::computeMSE(const Image& other) const {
    if (width != other.width || height != other.height) {
        std::cerr << "Images have different dimensions." << std::endl;
        return -1.0;
    }
    double sum = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        int diff = static_cast<int>(data[i]) - static_cast<int>(other.data[i]);
        sum += static_cast<double>(diff * diff);
    }
    return sum / static_cast<double>(data.size());
}
