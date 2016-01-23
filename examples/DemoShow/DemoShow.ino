#include <Adafruit_NeoPixel.h>
#include <LightShow.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, 6, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(9600);
	pixels.begin();
	pixels.setBrightness(255);
	Colors::black.putAll(pixels, 3);
	pixels.show();
}

#define PIXEL_FPS 60

void loop() {
	uint32_t waitBetweenScenario = 3000;
	uint32_t durationInMillisecond = 3000;

	Colors::black.putAll(pixels, 3);
	pixels.show();
	delay(waitBetweenScenario);
	
	ColorFade redToGreen(Colors::red, durationInMillisecond, Colors::green);
	ColorFade greenToBlue(Colors::green, durationInMillisecond, Colors::blue);
	ColorFade blueToRed(Colors::blue, durationInMillisecond, Colors::red);
	redToGreen.play(pixels, false, 0);
	greenToBlue.play(pixels, false, 0);
	blueToRed.play(pixels, false, 0);

	Colors::black.putAll(pixels, 3);
	pixels.show();
	delay(waitBetweenScenario);
	
	ColorFade nino(Colors::red, 500, Colors::blue);
	for (uint8_t i = 0; i < 5; i++) {
		bool backAndForth = true;
		nino.play(pixels, backAndForth, 0);
	}

	Colors::black.putAll(pixels, 3);
	pixels.show();
	delay(waitBetweenScenario);

	Color froms[3] = {
		Colors::red,
		Colors::green,
		Colors::blue,
	};
	Color tos[3] = {
		Colors::blue,
		Colors::red,
		Colors::green,
	};
	MultiColorFade<3> fade(froms, 5000, tos);
	fade.play(pixels, false);
}
