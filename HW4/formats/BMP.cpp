//
// Created by iliya on 06.05.2025.
//

#include "BMP.h"
#include <fstream>
#include <iostream>

BMPImage* BMPImage::fromBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return nullptr;
    }

    char magic[2];
    file.read(magic, 2);
    if (magic[0] != 'B' || magic[1] != 'M') {
        std::cerr << "Not a BMP file: " << filename << std::endl;
        return nullptr;
    }

    file.seekg(18, std::ios::beg);
    int width, height;
    file.read(reinterpret_cast<char*>(&width), 4);
    file.read(reinterpret_cast<char*>(&height), 4);
    if (width <= 0 || height <= 0) {
        std::cerr << "Invalid dimensions in BMP: " << filename << std::endl;
        return nullptr;
    }

    file.seekg(28, std::ios::beg);
    short bit_count;
    file.read(reinterpret_cast<char*>(&bit_count), 2);
    if (bit_count != 24) {
        std::cerr << "Unsupported bit count: " << bit_count << " in " << filename << std::endl;
        return nullptr;
    }

    file.seekg(10, std::ios::beg);
    int data_offset;
    file.read(reinterpret_cast<char*>(&data_offset), 4);
    file.seekg(data_offset, std::ios::beg);

    BMPImage* img = new BMPImage(width, height);
    if (img->data.empty()) {
        delete img;
        return nullptr;
    }

    int row_padded = (width * 3 + 3) & (~3);
    std::vector<unsigned char> row(row_padded);
    for (int y = 0; y < height; ++y) {
        file.read(reinterpret_cast<char*>(row.data()), row_padded);
        int y_img = height - 1 - y; // BMP is bottom-up
        for (int x = 0; x < width; ++x) {
            int idx = (y_img * width + x) * 3;
            int row_idx = x * 3;
            img->data[idx + 0] = row[row_idx + 0]; // B
            img->data[idx + 1] = row[row_idx + 1]; // G
            img->data[idx + 2] = row[row_idx + 2]; // R
        }
    }
    return img;
}

bool BMPImage::saveToBMP(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    int row_padded = (width * 3 + 3) & (~3);
    int data_size = row_padded * height;
    int file_size = 54 + data_size;

    file.put('B');
    file.put('M');
    file.write(reinterpret_cast<const char*>(&file_size), 4);
    file.write("\0\0\0\0", 4);
    int offset = 54;
    file.write(reinterpret_cast<const char*>(&offset), 4);
    int header_size = 40;
    file.write(reinterpret_cast<const char*>(&header_size), 4);
    file.write(reinterpret_cast<const char*>(&width), 4);
    file.write(reinterpret_cast<const char*>(&height), 4);
    short planes = 1;
    file.write(reinterpret_cast<const char*>(&planes), 2);
    short bit_count = 24;
    file.write(reinterpret_cast<const char*>(&bit_count), 2);
    int zero = 0;
    file.write(reinterpret_cast<const char*>(&zero), 4);
    file.write(reinterpret_cast<const char*>(&data_size), 4);
    file.write(reinterpret_cast<const char*>(&zero), 4);
    file.write(reinterpret_cast<const char*>(&zero), 4);
    file.write(reinterpret_cast<const char*>(&zero), 4);
    file.write(reinterpret_cast<const char*>(&zero), 4);

    for (int y = height - 1; y >= 0; --y) {
        file.write(reinterpret_cast<const char*>(data.data() + (y * width * 3)), width * 3);
        for (int p = 0; p < row_padded - width * 3; ++p) {
            file.put(0);
        }
    }
    if (!file) {
        std::cerr << "Cannot write data to file: " << filename << std::endl;
        return false;
    }
    return true;
}
