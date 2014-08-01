#include "game_manager.h"
#include "../hmi/hmi_manager.h"

GameManager game;

GameManager::GameManager() : state(GameState_SIMPLE_DEMO) {
}

void GameManager::init() {
}

void GameManager::animate() {
	switch (state) {
		case GameState_SIMPLE_DEMO:
			hmi.leds.clear();
			for (int i = 0; i < HMI_NB_LEDS / 2; ++i) {
				if (hmi.btn1.clicked())
					hmi.leds.set(i, 0xff, 0, 0);
				else if (hmi.btn1.pressed())
					hmi.leds.set(i, 0x66, 0, 0);
				else
					hmi.leds.set(i, 0x22, 0, 0);
			}
			for (int i = HMI_NB_LEDS / 2; i < HMI_NB_LEDS; ++i) {
				if (hmi.btn2.clicked())
					hmi.leds.set(i, 0, 0xff, 0);
				else if (hmi.btn2.pressed())
					hmi.leds.set(i, 0, 0x66, 0);
				else
					hmi.leds.set(i, 0, 0x22, 0);
			}
			break;
	}
}
