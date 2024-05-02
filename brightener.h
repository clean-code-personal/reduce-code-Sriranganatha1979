#include <cstdint>
#include "image.h"

class ImageBrightener {
    private:
        std::shared_ptr<Image> m_inputImage;
    public:
        ImageBrightener(std::shared_ptr<Image> inputImage);
        bool BrightenWholeImage(int& attenuatedCount);
        bool AddBrighteningImage(std::shared_ptr<Image> imageToAdd, int& attenuatedCount);
        int pixelAdderWithAttentuation(uint8_t sourcepixel, int pixelIndex, uint8_t pixelsToAdd, int& attentuatedCount);
};
