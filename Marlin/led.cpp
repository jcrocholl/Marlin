#ifdef LEDS

#include "led.h"
#include "temperature.h"

#include "Adafruit_NeoPixel.h"
Adafruit_NeoPixel gNeoPixelStrip = Adafruit_NeoPixel(60, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

#define NEOPIXEL_EFFECT_SOLID_COLOR 0
#define NEOPIXEL_EFFECT_CHASER 1

#define NEOPIXEL_PULSE_HERTZ 5
#define NEOPIXEL_PULSE_LOW_BRIGHTNESS 150
#define NEOPIXEL_PULSE_HIGH_BRIGHTNESS 255
#define NEOPIXEL_UPDATE_FREQUENCY_MILLIS 75;


void setup_led()
{
	//SERIAL_ECHOLN("LEDs initialized.");
	gNeoPixelStrip.begin();
	gNeoPixelStrip.show(); // Set to off.
}

/**
  * The minimum degrees celcius as the first in the pair, and the colour to start the lerp from
  * in the second.
  *
  * Will be clamped on either side.
  */
#define TEMPERATURE_INDEX 0
#define COLOUR_INDEX_R 1
#define COLOUR_INDEX_G 2
#define COLOUR_INDEX_B 3
uint8_t gColourLookUp[][4] = 
{
//	Temp	R    G    B
	{50, 	0,     0, 255},	// Blue
	{80, 	0,   255, 255},	// Cyan
	{110, 	0,   255,   0},	// Green
	{140,	255, 255,   0}, // Yellow
	{170,	255, 100,   0}, // Orange
	{200,	255,   0,   0}, // Red
};

int gSizeOfColourLookUp = sizeof(gColourLookUp)/4/sizeof(uint8_t);

void PrintColourLookUpData(String name, uint8_t* pColourData)
{
	//SERIAL_ECHOLN(name + ": (" + pColourData[COLOUR_INDEX_R] + ", " + pColourData[COLOUR_INDEX_G] + ", " + pColourData[COLOUR_INDEX_B] + ")\n");
}

uint32_t GetColourForTemperature(int temperature)
{
	uint8_t *pPreviousData = gColourLookUp[TEMPERATURE_INDEX];
	uint8_t *pNextData = gColourLookUp[gSizeOfColourLookUp-1];

	for(int i = 0; i < gSizeOfColourLookUp; ++i)
	{
		if(gColourLookUp[i][TEMPERATURE_INDEX] > temperature)
		{
			break;
		}

		// We may have our previous value.
		pPreviousData = gColourLookUp[i];
		
		if(i+1 < gSizeOfColourLookUp)
		{
			if(gColourLookUp[i+1][TEMPERATURE_INDEX] >= temperature)
			{
				pNextData = gColourLookUp[i+1];
				break;
			}
		}
	}

	temperature = constrain( temperature, pPreviousData[TEMPERATURE_INDEX], pNextData[TEMPERATURE_INDEX]);

	int r = pPreviousData[COLOUR_INDEX_R];
	int g = pPreviousData[COLOUR_INDEX_G];
	int b = pPreviousData[COLOUR_INDEX_B];

	// If you don't guard against this, you get divide by zero blamminess.
	if(pPreviousData[TEMPERATURE_INDEX] != pNextData[TEMPERATURE_INDEX])
	{
		r = constrain(map(temperature, pPreviousData[TEMPERATURE_INDEX], pNextData[TEMPERATURE_INDEX], pPreviousData[COLOUR_INDEX_R], pNextData[COLOUR_INDEX_R]), 0, 255);
		g = constrain(map(temperature, pPreviousData[TEMPERATURE_INDEX], pNextData[TEMPERATURE_INDEX], pPreviousData[COLOUR_INDEX_G], pNextData[COLOUR_INDEX_G]), 0, 255);
		b = constrain(map(temperature, pPreviousData[TEMPERATURE_INDEX], pNextData[TEMPERATURE_INDEX], pPreviousData[COLOUR_INDEX_B], pNextData[COLOUR_INDEX_B]), 0, 255);
	}

/*
	PrintColourLookUpData("Prev: ", pPreviousData);
	PrintColourLookUpData("Next: ", pNextData);
	*/

	//Serial.println("T: " + String(temperature) + " " + String(pPreviousData[TEMPERATURE_INDEX]) + " " + String(pNextData[TEMPERATURE_INDEX]) + " " + pPreviousData[COLOUR_INDEX_B] + " " + pNextData[COLOUR_INDEX_B]);

	uint32_t colour = Adafruit_NeoPixel::Color(r,g,b);

	return colour;
}


int gLastPixelUpdated = 0;

/**
  * Set the neo pixels according to colour. 
  */
void SetNeoPixelsTemperature(int temperature, byte effect)
{
	switch(effect)
	{
		default:
		/*
			SERIAL_ECHOLN("Unsupported effect " + String(effect) + " requested.  Defaulting to NEOPIXEL_EFFECT_SOLID_COLOR.");
			*/
		case NEOPIXEL_EFFECT_CHASER:
			{
				unsigned int time = millis();

				float lowBrightness = (255-NEOPIXEL_PULSE_LOW_BRIGHTNESS)/255.0f;
				float highBrightness = (255-NEOPIXEL_PULSE_HIGH_BRIGHTNESS)/255.0f;

				float percentBrightness = (sin(time*3.14 * NEOPIXEL_PULSE_HERTZ)*50+50)/100.0f;

				float brightness = 1;
				//float brightness = (percentBrightness * (highBrightness-lowBrightness)) + lowBrightness;

				//gNeoPixelStrip.setBrightness(brightness);

				uint32_t colour = GetColourForTemperature(temperature)*brightness;
				gNeoPixelStrip.setPixelColor(gLastPixelUpdated, colour);

				gLastPixelUpdated++;
				if(gLastPixelUpdated >= 60)
					gLastPixelUpdated = 0;

				gNeoPixelStrip.show();
			}
			break;
		case NEOPIXEL_EFFECT_SOLID_COLOR:
			{
				unsigned int time = millis();

				uint8_t brightness = map(sin(time*3.14 * NEOPIXEL_PULSE_HERTZ)*100, -100, 100, NEOPIXEL_PULSE_LOW_BRIGHTNESS, NEOPIXEL_PULSE_HIGH_BRIGHTNESS);
				gNeoPixelStrip.setBrightness(brightness);

				uint32_t colour = GetColourForTemperature(temperature);
				for(int i = 0; i < gNeoPixelStrip.numPixels(); ++i)
				{
					gNeoPixelStrip.setPixelColor(i, colour);
				}
				gNeoPixelStrip.show();
			}
			break;
	}
}

int gNextNeoPixelUpdate = 0;
void led_update()
{
	unsigned long time = millis();
	if(gNextNeoPixelUpdate < time)
	{
		gNextNeoPixelUpdate = time + NEOPIXEL_UPDATE_FREQUENCY_MILLIS;
		// TODO: Parameterize the extruder temperature we care about.
		//SetNeoPixelsTemperature(degHotend(0), NEOPIXEL_EFFECT_CHASER);
		SetNeoPixelsTemperature(degHotend(0), NEOPIXEL_EFFECT_SOLID_COLOR);
	}
}


#endif // LEDS
