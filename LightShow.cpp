#include "Arduino.h"

#include "LightShow.h"
#include <Adafruit_NeoPixel.h>

Color Color::operator-(const Color& rhs) const {
	Color newColor = {
		this->r - rhs.r,
		this->g - rhs.g,
		this->b - rhs.b,
	};
	return newColor;
}

Color Color::operator+(const Color& rhs) const {
	Color newColor = {
		this->r + rhs.r,
		this->g + rhs.g,
		this->b + rhs.b
	};
	return newColor;
}

Color Color::operator*(const float& rhs) const {
	Color newColor = {
		this->r * rhs,
		this->g * rhs,
		this->b * rhs
	};
	return newColor;
}

Color Color::operator*(const Color& rhs) const {
	Color newColor = {
		(this->r + rhs.r)/2,
		(this->g + rhs.g)/2,
		(this->b + rhs.b)/2
	};
	return newColor;
}

void Color::put(Adafruit_NeoPixel& pixels, uint8_t index) {
	pixels.setPixelColor(
		index,
		(uint8_t)constrain(this->r, 0, 255),
		(uint8_t)constrain(this->g, 0, 255),
		(uint8_t)constrain(this->b, 0, 255)
	);
}


void Color::dump() {
	Serial.print("R = ");
	Serial.print(this->r); Serial.print(" G = ");
	Serial.print(this->g); Serial.print(" B = ");
	Serial.print(this->b);
}

ColorFade::ColorFade(Color from, uint32_t duration, Color to) {
	this->iteration = ((float)duration / 1000.0f) * PIXEL_FPS;
	this->wait = 1000 / PIXEL_FPS;
	this->from = from;
	this->to = to;
	this->current = from;
	Color range = to - from;
	this->amount = range * (1.0f / (float)(this->iteration - 1));
}

Color ColorFade::NextColor() {
	Color temp = this->current;
	this->current = temp + this->amount;
	return temp;
}

Color ColorFade::PrevColor() {
	Color temp = this->current;
	this->current = temp - this->amount;
	return temp;
}

const Color Colors::black = {0, 0, 0};
const Color Colors::white = {255, 255, 255};

const Color Colors::red = {255, 0, 0};
const Color Colors::green = {0, 255, 0};
const Color Colors::blue = {0, 0, 255};