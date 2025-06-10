//
// Created by iliya on 06.05.2025.
//

#ifndef YUV_H
#define YUV_H

#include "../image.h"
#include <string>

class YUVImage : public Image {
public:
    YUVImage(int width, int height) : Image(width, height) {};
    static YUVImage* fromYUV(const std::string& filename, int width, int height);
    bool saveToYUV(const std::string& filename) const;

private:
    void setYUVPixel(size_t idx, unsigned char Y, unsigned char U, unsigned char V);
};

#endif // YUV_H
