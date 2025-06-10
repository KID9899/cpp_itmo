//
// Created by iliya on 05.05.2025.
//

// valgrind --leak-check=full --show-leak-kinds=all ./hw4 --input ./inp/A\(512x512\).yuv --output ./out/A.bmp --width 512 --height 512 --input-format yuv --output-format bmp

#include "image.h"
#include "formats/BMP.h"
#include "formats/YUV.h"
#include <iostream>
#include <string>
#include <memory>

struct Arguments {
    bool compare_mode = false;
    std::string compare_file1;
    std::string compare_file2;
    std::string compare_format;
    std::string input_file;
    std::string output_file;
    std::string input_format;
    std::string output_format;
    int width = 0;
    int height = 0;
    int up_size = 1;
    int down_size = 1;
    bool to_gray_scale = false;
};

bool parseArguments(Arguments& args, int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "---compare" && i + 2 < argc) {
            args.compare_mode = true;
            args.compare_file1 = argv[++i];
            args.compare_file2 = argv[++i];
        } else if (arg == "--format" && i + 1 < argc) {
            args.compare_format = argv[++i];
        } else if (arg == "--input" && i + 1 < argc) {
            args.input_file = argv[++i];
        } else if (arg == "--output" && i + 1 < argc) {
            args.output_file = argv[++i];
        } else if (arg == "--input-format" && i + 1 < argc) {
            args.input_format = argv[++i];
        } else if (arg == "--output-format" && i + 1 < argc) {
            args.output_format = argv[++i];
        } else if (arg == "--width" && i + 1 < argc) {
            args.width = std::stoi(argv[++i]);
        } else if (arg == "--height" && i + 1 < argc) {
            args.height = std::stoi(argv[++i]);
        } else if (arg == "--up-size" && i + 1 < argc) {
            args.up_size = std::stoi(argv[++i]);
        } else if (arg == "--down-size" && i + 1 < argc) {
            args.down_size = std::stoi(argv[++i]);
        } else if (arg == "--to-gray-scale") {
            args.to_gray_scale = true;
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return 1;
        }
    }
    return 0;
}

std::unique_ptr<Image> loadImage(const Arguments& args) {
    if (args.input_file.empty() || args.input_format.empty()) {
        std::cerr << "Missing input file or format." << std::endl;
        return nullptr;
    }

    std::unique_ptr<Image> img;
    if (args.input_format == "bmp") {
        img.reset(BMPImage::fromBMP(args.input_file));
    } else if (args.input_format == "yuv") {
        if (args.width <= 0 || args.height <= 0) {
            std::cerr << "Width and height are required for YUV input." << std::endl;
            return nullptr;
        }
        img.reset(YUVImage::fromYUV(args.input_file, args.width, args.height));
    } else {
        std::cerr << "Invalid input format: " << args.input_format << ". Use 'bmp' or 'yuv'." << std::endl;
        return nullptr;
    }

    if (!img) {
        std::cerr << "Failed to load image: " << args.input_file << std::endl;
    }
    return img;
}

bool processImage(std::unique_ptr<Image>& img, const Arguments& args) {
    if (args.down_size < 1 || args.up_size < 1) {
        std::cerr << "Size factors must be at least 1." << std::endl;
        return 1;
    }

    if (args.down_size > 1) {
        std::unique_ptr<Image> downscaled(img->downscale(args.down_size));
        if (!downscaled) {
            std::cerr << "Failed to downscale image." << std::endl;
            return 1;
        }
        img = std::move(downscaled);
    }

    if (args.up_size > 1) {
        std::unique_ptr<Image> upscaled(img->upscale(args.up_size));
        if (!upscaled) {
            std::cerr << "Failed to upscale image." << std::endl;
            return 1;
        }
        img = std::move(upscaled);
    }

    if (args.to_gray_scale) {
        img->toGrayscale();
    }

    return 0;
}

bool saveImage(const std::unique_ptr<Image>& img, const Arguments& args) {
    if (args.output_file.empty() || args.output_format.empty()) {
        std::cerr << "Missing output file or format." << std::endl;
        return 1;
    }

    bool success = 1;
    if (args.output_format == "bmp") {
        BMPImage* bmp_img = static_cast<BMPImage*>(img.get());
        if (bmp_img) {
            success = !(bmp_img->saveToBMP(args.output_file));
        } else {
            success = 1;
        }
    } else if (args.output_format == "yuv") {
        YUVImage* yuv_img = static_cast<YUVImage*>(img.get());
        if (yuv_img) {
            success = !(yuv_img->saveToYUV(args.output_file));
        } else {
            success = 1;
        }
    } else {
        std::cerr << "Invalid output format: " << args.output_format << ". Use 'bmp' or 'yuv'." << std::endl;
        return 1;
    }

    if (success) {
        std::cerr << "Failed to save image: " << args.output_file << std::endl;
    }
    return success;
}

bool compareImages(const Arguments& args) {
    std::unique_ptr<Image> img1, img2;
    if (args.compare_format == "bmp") {
        img1.reset(BMPImage::fromBMP(args.compare_file1));
        img2.reset(BMPImage::fromBMP(args.compare_file2));
    } else if (args.compare_format == "yuv") {
        if (args.width <= 0 || args.height <= 0) {
            std::cerr << "Width and height are required for YUV comparison." << std::endl;
            return 1;
        }
        img1.reset(YUVImage::fromYUV(args.compare_file1, args.width, args.height));
        img2.reset(YUVImage::fromYUV(args.compare_file2, args.width, args.height));
    } else {
        std::cerr << "Invalid format: " << args.compare_format << ". Use 'bmp' or 'yuv'." << std::endl;
        return 1;
    }

    if (!img1 || !img2) {
        std::cerr << "Failed to load images for comparison." << std::endl;
        return 1;
    }

    double mse = img1->computeMSE(*img2);
    if (mse >= 0) {
        std::cout << "MSE: " << mse << std::endl;
        return 0;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    Arguments args;
    if (parseArguments(args, argc, argv)) {
        return 1;
    }
    if (args.compare_mode) {
        if (compareImages(args)) {
            return 1;
        }
    } else {
        std::unique_ptr<Image> img = loadImage(args);
        if (!img) {
            return 1;
        }
        if (processImage(img, args)) {
            return 1;
        }
        if (saveImage(img, args)) {
            return 1;
        }
    }
    return 0;
}