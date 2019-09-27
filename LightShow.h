#ifndef LightShow_h
#define LightShow_h

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class Color {
private:
	int16_t r;
	int16_t g;
	int16_t b;

public:
	Color operator-(const Color& rhs) const;
	Color operator+(const Color& rhs) const;
	Color operator*(const float& rhs) const;
	Color operator*(const Color& rhs) const;

	Color();
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(int16_t r, int16_t g, int16_t b);
	Color(const Color& color);
	void put(Adafruit_NeoPixel& pixels, uint8_t index) const;
	void putAll(Adafruit_NeoPixel& pixels, uint8_t count) const;
	void dump() const;
	uint8_t getR();
	uint8_t getG();
	uint8_t getB();
};

template<uint8_t COUNT>
void put(Color colors[COUNT], Adafruit_NeoPixel& pixels) {
	for (uint8_t i = 0; i < COUNT; i++) {
		colors[i].put(pixels, i);
	}
}

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
	uint32_t duration;

public:
	unsigned long iteration;
	uint32_t wait;

	//duration: in millis
	ColorFade();
	ColorFade(Color from, uint32_t duration, Color to);
	void reset();
	Color nextColor();
	Color prevColor();
	void play(Adafruit_NeoPixel& pixels, bool backAndForth, uint8_t index);
	void dump();
};

#define FADE(from, duration, to, pixels, index, back) { ColorFade(from, duration, to).play(pixels, back, index); }

template<uint8_t COUNT>
class MultiColorFade
{
private:
	ColorFade fades[COUNT];
	uint32_t duration;
public:
	MultiColorFade(Color froms[COUNT], uint32_t duration, Color tos[COUNT]);
	void reset();
	void forwardPut(Adafruit_NeoPixel& pixels);
	void backwardPut(Adafruit_NeoPixel& pixels);
	unsigned long iteration();
	uint32_t wait();
	void play(Adafruit_NeoPixel& pixels, bool backAndForth);
	void dump();
};

#define MULTIFADE(count, froms, duration, tos, pixels, back) { MultiColorFade<count>(froms, duration, tos).play(pixels, back); }

template<uint8_t COUNT>
MultiColorFade<COUNT>::MultiColorFade(Color froms[COUNT], uint32_t duration, Color tos[COUNT]) {
	for (uint8_t i = 0; i < COUNT; i++) {
		this->fades[i] = ColorFade(froms[i], duration, tos[i]);
	}
	this->duration = duration;
}

template<uint8_t COUNT>
void MultiColorFade<COUNT>::reset() {
	for (uint8_t i = 0; i < COUNT; i++) {
		this->fades[i].reset();
	}
}

template<uint8_t COUNT>
void MultiColorFade<COUNT>::forwardPut(Adafruit_NeoPixel& pixels) {
	for (uint8_t i = 0; i < COUNT; i++) {
		this->fades[i].nextColor().put(pixels, i);
	}
}

template<uint8_t COUNT>
void MultiColorFade<COUNT>::backwardPut(Adafruit_NeoPixel& pixels) {
	for (uint8_t i = 0; i < COUNT; i++) {
		this->fades[i].prevColor().put(pixels, i);
	}
}

template<uint8_t COUNT>
unsigned long MultiColorFade<COUNT>::iteration() {
	return this->fades[0].iteration;
}

template<uint8_t COUNT>
uint32_t MultiColorFade<COUNT>::wait() {
	return this->fades[0].wait;
}

template<uint8_t COUNT>
void MultiColorFade<COUNT>::play(Adafruit_NeoPixel& pixels, bool backAndForth) {
	this->reset();
	for (uint32_t i = 0; i < this->iteration(); i++) {
		this->forwardPut(pixels);
		pixels.show();
		delay(this->wait());
	}
	if (backAndForth) {
		for (uint32_t i = 0; i < this->iteration(); i++) {
			this->backwardPut(pixels);
			pixels.show();
			delay(this->wait());
		}
	}
}

template<uint8_t COUNT>
void MultiColorFade<COUNT>::dump() {
	for (uint8_t i = 0; i < COUNT; i++) {
		this->fades[i].dump();
		Serial.println(F("--------------"));
	}
}

#endif