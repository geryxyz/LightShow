#ifndef LightShow_h
#define LightShow_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"


struct Color {
	float r;
	float g;
	float b;

	Color operator-(const Color& rhs) const;
	Color operator+(const Color& rhs) const;
	Color operator*(const float& rhs) const;
	Color operator*(const Color& rhs) const;

	void put(Adafruit_NeoPixel& pixels, uint8_t index) const;
	void putAll(Adafruit_NeoPixel& pixels, uint8_t count) const;
	void dump() const;
};

struct Colors {
	static const Color black;
	static const Color white;

	static const Color red;
	static const Color green;
	static const Color blue;
};

#define PIXEL_FPS 60

class ColorFade {
private:
	Color from;
	Color to;
	Color amount;
	Color current;

public:
	unsigned long iteration;
	uint32_t wait;

	//duration: in millis
	ColorFade(Color from, uint32_t duration, Color to);
	void reset();
	Color nextColor();
	Color prevColor();
	void play(Adafruit_NeoPixel& pixels, bool backAndForth, uint8_t index);
};

template<uint8_t COUNT>
class MultiColorFade
{
private:
	ColorFade fades[COUNT];
public:
	MultiColorFade(Color froms[COUNT], uint32_t duration, Color tos[COUNT]);
	void forwardPut(Adafruit_NeoPixel& pixels);
	void backwardPut(Adafruit_NeoPixel& pixels);
	unsigned long iteration();
	uint32_t wait();
};

#endif