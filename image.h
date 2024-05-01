#pragma once
#include <cstdint>
#include <iostream>

class Image {
public:
	Image(uint16_t rows, uint16_t columns): m_rows(rows), m_columns(columns) {
		pixels = new uint8_t[m_rows * m_columns];
	}
	~Image() {
		std::cout << "freeing pixel memory.\n";
		delete[] pixels;
	}
	bool imageSizeIsValid() {
		return m_rows <= 1024 && m_columns <= 1024;
	}

	int pixelParser(bool shouldBrightenFullImage, int brightnessFactor, const std::shared_ptr<Image> imageToAdd)
	{
		int attenuatedCount = 0;
		for (int x = 0; x < m_rows; x++) {
			for (int y = 0; y < m_columns; y++) {
				int pixelIndex = x * m_columns + y;
				uint8_t brightnessFactorToAdd = (shouldBrightenFullImage) ? brightnessFactor : imageToAdd->pixels[pixelIndex];
				if (int(pixels[pixelIndex]) + brightnessFactorToAdd > 255) {
					++attenuatedCount;
					pixels[pixelIndex] = 255;
				}
				else {
					pixels[pixelIndex] += brightnessFactorToAdd;
				}
			}
		}
		return attenuatedCount;

	}

	const uint16_t m_rows;
	const uint16_t m_columns;
	uint8_t* pixels; // max 1k x 1k image
};
