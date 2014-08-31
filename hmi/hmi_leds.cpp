#include "hmi_leds.h"
#include "hmi_manager.h"

#ifdef BUILD_PC
#include <SDL2/SDL.h>
extern SDL_Surface * screen;
extern unsigned int pixel_size;
extern unsigned int pixel_jump;
void pc_update_screen();
#else
#include <Arduino.h>
#include <FastLED.h>
CRGB fastleds[2*HMI_WIDTH+1];
#endif

void HmiLeds::init() {
#ifndef BUILD_PC
	FastLED.addLeds<NEOPIXEL, ARDUINO_PINS__FASTLED_DATA>(fastleds, sizeof(fastleds)/sizeof(*fastleds));
#endif
}

void HmiLeds::clear() {
#ifdef BUILD_PC
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
#else
	memset(fastleds, 0, sizeof(fastleds));
#endif
}

void HmiLeds::set(int led, unsigned char r, unsigned char g, unsigned char b) {
	if (led < -HMI_WIDTH || led > HMI_WIDTH) return;
#ifdef BUILD_PC
	if (screen) {
		SDL_Rect led_rect;
		led_rect.x = (HMI_WIDTH + led) * pixel_jump;
		led_rect.y = (100 - pixel_size) / 2;
		led_rect.w = pixel_size;
		led_rect.h = pixel_size;
		SDL_FillRect(screen, &led_rect, SDL_MapRGB(screen->format, r, g, b));
	}
#else
	fastleds[led + HMI_WIDTH].r = r / 2;
	fastleds[led + HMI_WIDTH].b = b / 2;
	fastleds[led + HMI_WIDTH].g = g / 2;
#endif
}

void HmiLeds::update() {
#ifdef BUILD_PC
	pc_update_screen();
#else
	FastLED.show();
#endif
}
