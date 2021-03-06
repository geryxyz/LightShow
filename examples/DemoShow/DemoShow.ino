#include <Adafruit_NeoPixel.h>
#include <LightShow.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(9, 6, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(9600);
	pixels.begin();
	pixels.setBrightness(255);
	Colors::black.putAll(pixels, 3);
	pixels.show();
}

//setting the frame rate for the fadings
#define PIXEL_FPS 60

void cleanCut() {
	Colors::black.putAll(pixels, 3);
	pixels.show();
	delay(1000);
}

uint32_t durationInMillisecond = 3000;

void loop() {
	//operation between two color
	cleanCut();
	Color yellow = Colors::red + Colors::green; //component wise addition
	Color magenta = Colors::white - Colors::green; //component wise substraction
	Color mix = yellow * magenta; //component wise average
	yellow.put(pixels, 0);
	magenta.put(pixels, 1);
	mix.put(pixels, 2);
	pixels.show();
	delay(5000);

	//operation between a color and a number
	cleanCut();
	Color lightMagenta = magenta * 1.0f;
	Color midMagenta = magenta * .25f;
	Color darkMagenta = magenta * .05f;
	lightMagenta.put(pixels, 0);
	midMagenta.put(pixels, 1);
	darkMagenta.put(pixels, 2);
	pixels.show();
	delay(5000);

	//showing color on all pixels
	cleanCut();
	(Colors::red * Colors::green).putAll(pixels, 3);
	pixels.show();
	delay(1000);
	(Colors::red * Colors::blue).putAll(pixels, 3);
	pixels.show();
	delay(1000);
	(Colors::blue * Colors::green).putAll(pixels, 3);
	pixels.show();
	delay(1000);

	//single pixel (color) fading
	cleanCut();
	ColorFade redToGreen(Colors::red, durationInMillisecond, Colors::green);
	ColorFade greenToBlue(Colors::green, durationInMillisecond, Colors::blue);
	ColorFade blueToRed(Colors::blue, durationInMillisecond, Colors::red);
	redToGreen.play(pixels, false, 0);
	greenToBlue.play(pixels, false, 0);
	blueToRed.play(pixels, false, 0);

	//back and forth mode for fading
	cleanCut();	
	ColorFade nino(Colors::red, 500, Colors::blue);
	for (uint8_t i = 0; i < 5; i++) {
		bool backAndForth = true;
		nino.play(pixels, backAndForth, 0);
	}

	//multi pixel (color) fading
	{
	cleanCut();
	Color froms[3] = {
		Colors::red,
		Colors::red,
		Colors::red
	};
	Color tos[3] = {
		Colors::white,
		Colors::green,
		Colors::blue
	};
	MultiColorFade<3> fade(froms, 1000, tos);
	fade.play(pixels, true);
	}

	//stack size optimized fading
	{
	cleanCut();
	FADE(Colors::black, 1000, Colors::red, pixels, 0, false)
	FADE(Colors::red, 1000, Colors::blue, pixels, 0, false)
	FADE(Colors::blue, 1000, Colors::black, pixels, 0, false)
	}

	//stack size optimized fading
	{
	cleanCut();
	Color froms[3] = {
		Colors::black,
		Colors::black,
		Colors::black
	};
	Color tos[3] = {
		Colors::red,
		Colors::red,
		Colors::red
	};
	MULTIFADE(3, froms, 1000, tos, pixels, true)
	}
}
