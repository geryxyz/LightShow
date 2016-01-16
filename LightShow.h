#ifndef LightShow_h
#define LightShow_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>


struct Color {
	float r;
	float g;
	float b;

	Color operator-(const Color& rhs);
	Color operator+(const Color& rhs);
	Color operator*(const float& rhs);
	Color operator*(const Color& rhs);

	void put(Adafruit_NeoPixel& pixels, uint8_t index);

	void dump();
};

struct Colors {
	static const Color black;
	static const Color white;

	static const Color red;
	static const Color green;
	static const Color blue;
};

class ColorFade {
private:
	Color from;
	Color to;
	Color amount;
	Color current;

public:
	ColorFade(Color from, uint32_t iteration, Color to);
	Color NextColor();
};

#endif