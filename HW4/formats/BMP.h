//
// Created by iliya on 06.05.2025.
//

#ifndef BMP_H
#define BMP_H

#include "../image.h"
#include <string>

class BMPImage : public Image {
public:
    BMPImage(int width, int height) : Image(width, height) {}
    static BMPImage* fromBMP(const std::string& filename);
    bool saveToBMP(const std::string& filename) const;
};

#endif // BMP_H
