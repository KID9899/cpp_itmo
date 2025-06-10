//
// Created by iliya on 05.05.2025.
//

#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

class Image {
public:
    Image(int width, int height);
    virtual ~Image() = default;

    void toGrayscale();
    Image* downscale(int factor) const;
    Image* upscale(int factor) const;
    double computeMSE(const Image& other) const;

protected:
    int width;
    int height;
    std::vector<unsigned char> data;
};

#endif // IMAGE_H