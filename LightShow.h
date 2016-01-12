#ifndef LightShow_h
#define LightShow_h

#include "Arduino.h"

struct LongColor {
	int32_t r; 
	int32_t g; 
	int32_t b; 

	void dump();
};

struct ByteColor {
	uint8_t r;
	uint8_t g;
	uint8_t b;

	ByteColor operator-(const ByteColor& rhs);
	ByteColor operator+(const ByteColor& rhs);
	ByteColor operator*(const float& rhs);
	ByteColor operator*(const ByteColor& rhs);
	operator LongColor() const;
	void dump();
};

class Colors {
	static const ByteColor black;
	static const ByteColor white;

	static const ByteColor red;
	static const ByteColor green;
	static const ByteColor blue;
};

const ByteColor Colors::black = {0, 0, 0};
const ByteColor Colors::white = {255, 255, 255};

const ByteColor Colors::red = {255, 0, 0};
const ByteColor Colors::green = {0, 255, 0};
const ByteColor Colors::blue = {0, 0, 255};

class ColorFade {
private:
	LongColor from;
	LongColor to;
	LongColor amount;
	LongColor current;

public:
	ColorFade(LongColor from, uint32_t iteration, LongColor to);
	ByteColor NextColor();
};

#endif