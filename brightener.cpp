#include "brightener.h"

ImageBrightener::ImageBrightener(std::shared_ptr<Image> inputImage): m_inputImage(inputImage) {
}

bool ImageBrightener::BrightenWholeImage(int& attenuatedPixelCount) {
    if (!m_inputImage->imageSizeIsValid()) {
        return false;
    }    

    m_inputImage->pixelRunner(
        [&attenuatedPixelCount, this](uint8_t pixelGrayscale, int pixelIndex) {
            // For brightening, we add a certain grayscale (25) to every pixel.
            // While brightening, some pixels may cross the max brightness. They are
            // called 'attenuated' pixels
            uint8_t brightnessToAdd = 25;
            return this->pixelAdderWithAttentuation(pixelGrayscale, pixelIndex, brightnessToAdd, attenuatedPixelCount);
        } );
    return true;
}

bool ImageBrightener::AddBrighteningImage(const std::shared_ptr<Image> imageToAdd, int& attenuatedPixelCount) {
    if (!m_inputImage->imageSizeIsValid()) {
        return false;
    }

    if (imageToAdd->m_rows != m_inputImage->m_rows || imageToAdd->m_columns != m_inputImage->m_columns) {
        return false;
    }

    m_inputImage->pixelRunner(
        [&attenuatedPixelCount, imageToAdd, this](uint8_t pixelGrayscale, int pixelIndex) {
            uint8_t brightnessToAdd = imageToAdd->pixels[pixelIndex];
            return this->pixelAdderWithAttentuation(pixelGrayscale, pixelIndex, brightnessToAdd, attenuatedPixelCount);
        } );
    return true;
}

int ImageBrightener::pixelAdderWithAttentuation(uint8_t sourcepixel, int pixelIndex, uint8_t brightnessToAdd, int& attentuatedCount)
{
    if (sourcepixel > (255 - brightnessToAdd)) {
        ++attentuatedCount;
        sourcepixel = 255;
    }
    else {
        sourcepixel += brightnessToAdd;
    }

    return sourcepixel;
}
