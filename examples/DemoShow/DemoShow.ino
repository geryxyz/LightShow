#include <Adafruit_NeoPixel.h>
#include <LightShow.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(9600);
	pixels.begin();
	pixels.setBrightness(255);
}

#define PIXEL_FPS 60

void loop() {
	uint32_t durationInMillisecond = 1000;
	ColorFade redToGreen(Colors::red, durationInMillisecond, Colors::green);
	for (uint8_t i = 0; i < redToGreen.iteration; i++) {
		Color color = redToGreen.NextColor();
		color.put(pixels, 0);
		pixels.show();
		delay(redToGreen.wait);
	}
	ColorFade greenToBlue(Colors::green, durationInMillisecond, Colors::blue);
	for (uint8_t i = 0; i < greenToBlue.iteration; i++) {
		Color color = greenToBlue.NextColor();
		color.put(pixels, 0);
		pixels.show();
		delay(greenToBlue.wait);
	}
	ColorFade blueToRed(Colors::blue, durationInMillisecond, Colors::red);
	for (uint8_t i = 0; i < blueToRed.iteration; i++) {
		Color color = blueToRed.NextColor();
		color.put(pixels, 0);
		pixels.show();
		delay(blueToRed.wait);
	}
}
