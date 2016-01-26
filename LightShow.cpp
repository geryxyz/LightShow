#include "Arduino.h"

#include "LightShow.h"
#include <Adafruit_NeoPixel.h>

#define COLORPRECISION 100

Color Color::operator-(const Color& rhs) const {
	Color newColor(
		this->r - rhs.r,
		this->g - rhs.g,
		this->b - rhs.b
	);
	return newColor;
}

Color Color::operator+(const Color& rhs) const {
	Color newColor(
		this->r + rhs.r,
		this->g + rhs.g,
		this->b + rhs.b
	);
	return newColor;
}

Color Color::operator*(const float& rhs) const {
	Color newColor(
		(int16_t)(this->r * rhs),
		(int16_t)(this->g * rhs),
		(int16_t)(this->b * rhs)
	);
	return newColor;
}

Color Color::operator*(const Color& rhs) const {
	Color newColor(
		(this->r + rhs.r)/(int16_t)2,
		(this->g + rhs.g)/(int16_t)2,
		(this->b + rhs.b)/(int16_t)2
	);
	return newColor;
}

Color::Color() {
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
	this->r = r * COLORPRECISION;
	this->g = g * COLORPRECISION;
	this->b = b * COLORPRECISION;
}

Color::Color(int16_t r, int16_t g, int16_t b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color::Color(const Color& color) {
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
}

void Color::put(Adafruit_NeoPixel& pixels, uint8_t index) const {
	pixels.setPixelColor(
		index,
		(uint8_t)constrain(this->r / (uint16_t)COLORPRECISION, 0, 255),
		(uint8_t)constrain(this->g / (uint16_t)COLORPRECISION, 0, 255),
		(uint8_t)constrain(this->b / (uint16_t)COLORPRECISION, 0, 255)
	);
}

void Color::putAll(Adafruit_NeoPixel& pixels, uint8_t count) const {
	for (uint8_t i = 0; i < count; i++) {
		this->put(pixels, i);
	}
}

void Color::dump() const {
	Serial.print(F("R = "));
	Serial.print(this->r); Serial.print(F(" G = "));
	Serial.print(this->g); Serial.print(F(" B = "));
	Serial.print(this->b);
}

ColorFade::ColorFade() {
	;
}

ColorFade::ColorFade(Color from, uint32_t duration, Color to) {
	this->iteration = ((float)duration / 1000.0f) * PIXEL_FPS;
	this->wait = 1000 / PIXEL_FPS;
	this->from = from;
	this->to = to;
	this->current = from;
	Color range = to - from;
	this->amount = range * (1.0f / (float)(this->iteration - 1));
	this->duration = duration;
}

void ColorFade::reset() {
	this->current = this->from;
}

Color ColorFade::nextColor() {
	this->current.dump();
	Serial.println();
	Color temp = this->current;
	this->current = temp + this->amount;
	return temp;
}

Color ColorFade::prevColor() {
	this->current = this->current - this->amount;
	return this->current;
}

void ColorFade::play(Adafruit_NeoPixel& pixels, bool backAndForth, uint8_t index) {
	this->reset();
	for (uint32_t i = 0; i < this->iteration; i++) {
		this->nextColor().put(pixels, index);
		pixels.show();
		delay(this->wait);
	}
	if (backAndForth) {
		for (uint32_t i = 0; i < this->iteration; i++) {
			this->prevColor().put(pixels, index);
			pixels.show();
			delay(this->wait);
		}
	}
}

void ColorFade::dump() {
	Serial.print(F("from: "));
	this->from.dump();
	Serial.println();
	Serial.print(F("to: "));
	this->to.dump();
	Serial.println();
	Serial.print(F("duration = "));
	Serial.println(this->duration);
	Serial.print(F("iteration = "));
	Serial.println(this->iteration);
	Serial.print(F("wait = "));
	Serial.println(this->wait);
}

const Color Colors::black((uint8_t)0, (uint8_t)0, (uint8_t)0);
const Color Colors::white((uint8_t)255, (uint8_t)255, (uint8_t)255);

const Color Colors::red((uint8_t)255, (uint8_t)0, (uint8_t)0);
const Color Colors::green((uint8_t)0, (uint8_t)255, (uint8_t)0);
const Color Colors::blue((uint8_t)0, (uint8_t)0, (uint8_t)255);