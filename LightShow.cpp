#include "Arduino.h"
#include "LightShow.h"

ByteColor ByteColor::operator-(const ByteColor& rhs) {
	int8_t r = this->r - rhs.r;
	int8_t g = this->g - rhs.g;
	int8_t b = this->b - rhs.b;
	ByteColor newColor = {
		r > 0 ? r : 0,
		g > 0 ? g : 0,
		b > 0 ? b : 0,
	};
	return newColor;
}

ByteColor ByteColor::operator+(const ByteColor& rhs) {
	uint16_t r = this->r + rhs.r;
	uint16_t g = this->g + rhs.g;
	uint16_t b = this->b + rhs.b;
	ByteColor newColor = {
		r < 256 ? r : 255,
		g < 256 ? g : 255,
		b < 256 ? b : 255
	};
	return newColor;
}

ByteColor ByteColor::operator*(const float& rhs) {
	ByteColor newColor = {
		rhs < 1.0f ? this->r * rhs : 255,
		rhs < 1.0f ? this->g * rhs : 255,
		rhs < 1.0f ? this->b * rhs : 255
	};
	return newColor;
}

ByteColor ByteColor::operator*(const ByteColor& rhs) {
	ByteColor newColor = {
		(((uint16_t)this->r) + rhs.r)/2,
		(((uint16_t)this->g) + rhs.g)/2,
		(((uint16_t)this->b) + rhs.b)/2
	};
	return newColor;
}

ByteColor::operator LongColor() const {
	LongColor color = {
		this->r,
		this->g,
		this->b
	};
	return color;
}

void ByteColor::dump() {
	Serial.print(this->r); Serial.print(";");
	Serial.print(this->g); Serial.print(";");
	Serial.print(this->b);
}

#define COLORPRECISION 10000

ColorFade::ColorFade(LongColor from, uint32_t iteration, LongColor to) {
	this->from = from;
	this->to = to;
	this->current = from;
	LongColor range = {
		to.r - from.r,
		to.g - from.g,
		to.b - from.b
	};
	this->amount = {
		(range.r * COLORPRECISION) / iteration,
		(range.g * COLORPRECISION) / iteration,
		(range.b * COLORPRECISION) / iteration
	};
}

ByteColor ColorFade::NextColor() {
	LongColor temp = this->current;
	this->current = {
		(this->current.r * COLORPRECISION + this->amount.r) / COLORPRECISION,
		(this->current.g * COLORPRECISION + this->amount.g) / COLORPRECISION,
		(this->current.b * COLORPRECISION + this->amount.b) / COLORPRECISION
	};
	ByteColor newColor = {
		constrain(temp.r, 0, 255),
		constrain(temp.g, 0, 255),
		constrain(temp.b, 0, 255)
	};
	return newColor;
}

void LongColor::dump() {
	Serial.print(this->r); Serial.print(";");
	Serial.print(this->g); Serial.print(";");
	Serial.print(this->b);
}