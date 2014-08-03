#include "hmi_leds.h"
#include "hmi_manager.h"

#ifdef BUILD_PC
#include <SDL2/SDL.h>
extern SDL_Surface * screen;
extern unsigned int pixel_size;
extern unsigned int pixel_jump;
#endif

void HmiLeds::clear() {
#ifdef BUILD_PC
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
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
#endif
}
