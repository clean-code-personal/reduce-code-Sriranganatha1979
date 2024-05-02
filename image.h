#pragma once
#include <cstdint>
#include <iostream>
#include <functional>

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

	void pixelRunner(std::function<uint8_t(uint8_t, int)> pixelProcessor) {
		std::cout << "-- pixelRunner: lambda version\n";
		for (int x = 0; x < m_rows; x++) {
			for (int y = 0; y < m_columns; y++) {
				int pixelIndex = x * m_columns + y;
				pixels[pixelIndex] = pixelProcessor(pixels[pixelIndex], pixelIndex);
			}
		}
	}

	const uint16_t m_rows;
	const uint16_t m_columns;
	uint8_t* pixels; // max 1k x 1k image
};
