//
// Created by iliya on 06.05.2025.
//

#include "YUV.h"
#include <fstream>
#include <iostream>

void YUVImage::setYUVPixel(size_t idx, unsigned char Y, unsigned char U, unsigned char V) {
    int R = static_cast<int>(Y + 1.402 * (V - 128));
    int G = static_cast<int>(Y - 0.344 * (U - 128) - 0.714 * (V - 128));
    int B = static_cast<int>(Y + 1.772 * (U - 128));
    R = std::max(0, std::min(255, R));
    G = std::max(0, std::min(255, G));
    B = std::max(0, std::min(255, B));
    size_t rgb_idx = idx * 3;
    data[rgb_idx + 0] = static_cast<unsigned char>(B);
    data[rgb_idx + 1] = static_cast<unsigned char>(G);
    data[rgb_idx + 2] = static_cast<unsigned char>(R);
}

YUVImage* YUVImage::fromYUV(const std::string& filename, int width, int height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return nullptr;
    }

    YUVImage* img = new YUVImage(width, height);
    if (img->data.empty()) {
        delete img;
        return nullptr;
    }

    int uv_width = (width + 1) / 2;
    int uv_height = (height + 1) / 2 + height % 2;

    std::vector<unsigned char> y_data(width * height);
    std::vector<unsigned char> u_data(uv_width * uv_height);
    std::vector<unsigned char> v_data(uv_width * uv_height);

    file.read(reinterpret_cast<char*>(y_data.data()), width * height);
    if (!file) {
        std::cerr << "Error reading Y data from: " << filename << std::endl;
        delete img;
        return nullptr;
    }
    if (width % 2) file.seekg(1, std::ios::cur);

    file.read(reinterpret_cast<char*>(u_data.data()), uv_width * uv_height);
    if (!file) {
        std::cerr << "Error reading U data from: " << filename << std::endl;
        delete img;
        return nullptr;
    }

    file.read(reinterpret_cast<char*>(v_data.data()), uv_width * uv_height);
    if (!file) {
        std::cerr << "Error reading V data from: " << filename << std::endl;
        delete img;
        return nullptr;
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            int uv_idx = (y / 2) * uv_width + (x / 2);
            img->setYUVPixel(idx, y_data[idx], u_data[uv_idx], v_data[uv_idx]);
        }
    }
    return img;
}

bool YUVImage::saveToYUV(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    int uv_width = (width + 1) / 2;
    int uv_height = (height + 1) / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * 3;
            unsigned char B = data[idx + 0];
            unsigned char G = data[idx + 1];
            unsigned char R = data[idx + 2];
            unsigned char Y = static_cast<unsigned char>(0.299 * R + 0.587 * G + 0.114 * B);
            file.put(Y);
        }
        if (width % 2) file.put(0);
    }

    for (int i = 0; i < uv_height; ++i) {
        for (int j = 0; j < uv_width; ++j) {
            double sum_U = 0.0;
            int count = 0;
            for (int dy = 0; dy < 2; ++dy) {
                for (int dx = 0; dx < 2; ++dx) {
                    int x = 2 * j + dx;
                    int y = 2 * i + dy;
                    if (x < width && y < height) {
                        int idx = (y * width + x) * 3;
                        unsigned char B = data[idx + 0];
                        unsigned char G = data[idx + 1];
                        unsigned char R = data[idx + 2];
                        double U = -0.169 * R - 0.331 * G + 0.500 * B + 128;
                        sum_U += U;
                        count++;
                    }
                }
            }
            unsigned char U_avg = static_cast<unsigned char>(sum_U / count + 0.5);
            file.put(U_avg);
        }
    }

    for (int i = 0; i < uv_height; ++i) {
        for (int j = 0; j < uv_width; ++j) {
            double sum_V = 0.0;
            int count = 0;
            for (int dy = 0; dy < 2; ++dy) {
                for (int dx = 0; dx < 2; ++dx) {
                    int x = 2 * j + dx;
                    int y = 2 * i + dy;
                    if (x < width && y < height) {
                        int idx = (y * width + x) * 3;
                        unsigned char B = data[idx + 0];
                        unsigned char G = data[idx + 1];
                        unsigned char R = data[idx + 2];
                        double V = 0.500 * R - 0.419 * G - 0.081 * B + 128;
                        sum_V += V;
                        count++;
                    }
                }
            }
            unsigned char V_avg = static_cast<unsigned char>(sum_V / count + 0.5);
            file.put(V_avg);
        }
    }

    if (!file) {
        std::cerr << "Cannot write data to file: " << filename << std::endl;
        return false;
    }
    return true;
}
