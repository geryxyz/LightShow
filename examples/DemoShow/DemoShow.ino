#include <Adafruit_NeoPixel.h>
#include <LightShow.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(9600);
	pixels.begin();
	pixels.setBrightness(32);
}

void loop() {
	ColorFade fade(Colors::red, 100, Colors::blue);
	for (uint8_t i = 0; i < 100; i++) {
		Color color = fade.NextColor();
		color.put(pixels, 0);
		pixels.show();
		delay(50);
		Serial.println();
	}
}
