#include "brightener.h"

ImageBrightener::ImageBrightener(std::shared_ptr<Image> inputImage): m_inputImage(inputImage) {
}

bool ImageBrightener::BrightenWholeImage(int& attenuatedCount) {
    if (!m_inputImage->imageSizeIsValid()) {
        return false;
    }

    // For brightening, we add a certain grayscale (25) to every pixel.
    // While brightening, some pixels may cross the max brightness. They are
    // called 'attenuated' pixels
    attenuatedCount = m_inputImage->pixelParser(true, 25, 0);
    return true;
}

bool ImageBrightener::AddBrighteningImage(const std::shared_ptr<Image> imageToAdd, int& attenuatedCount) {
    if (!m_inputImage->imageSizeIsValid()) {
        return false;
    }

    if (imageToAdd->m_rows != m_inputImage->m_rows || imageToAdd->m_columns != m_inputImage->m_columns) {
        return false;
    }
    attenuatedCount = m_inputImage->pixelParser(false, 0, imageToAdd);
    return true;
}
