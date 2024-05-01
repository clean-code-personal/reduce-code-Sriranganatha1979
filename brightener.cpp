#include "brightener.h"

ImageBrightener::ImageBrightener(std::shared_ptr<Image> inputImage): m_inputImage(inputImage) {
}

bool ImageBrightener::BrightenWholeImage(int& attenuatedPixelCount) {
    if (!m_inputImage->imageSizeIsValid()) {
        return false;
    }

    // For brightening, we add a certain grayscale (25) to every pixel.
    // While brightening, some pixels may cross the max brightness. They are
    // called 'attenuated' pixels
    m_inputImage->pixelRunner([&attenuatedPixelCount](uint8_t pixelGrayscale, int pixelIndex) {
        uint8_t outputGrayscale = pixelGrayscale;
        if (outputGrayscale > (255 - 25)) {
            ++attenuatedPixelCount;
            outputGrayscale = 255;
        }
        else {
            outputGrayscale += 25;
        }

        return outputGrayscale;
        });
    return true;
}

bool ImageBrightener::AddBrighteningImage(const std::shared_ptr<Image> imageToAdd, int& attenuatedPixelCount) {
    if (!m_inputImage->imageSizeIsValid()) {
        return false;
    }

    if (imageToAdd->m_rows != m_inputImage->m_rows || imageToAdd->m_columns != m_inputImage->m_columns) {
        return false;
    }

    m_inputImage->pixelRunner([&attenuatedPixelCount, imageToAdd](uint8_t pixelGrayscale, int pixelIndex) {
        uint8_t outputGrayscale = pixelGrayscale;
        uint8_t pixelsToAdd = imageToAdd->pixels[pixelIndex];
        if (outputGrayscale > (255 - pixelsToAdd)) {
            ++attenuatedPixelCount;
            outputGrayscale = 255;
        }
        else {
            outputGrayscale += pixelsToAdd;
        }

        return outputGrayscale;
        });
    return true;
}

