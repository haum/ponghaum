#include "game_manager.h"
#include "../hmi/hmi_manager.h"

#include "wait_players_screen.h"

GameManager game;

static struct {
	WaitPlayersScreen wait_players;
} screens;

static GameScreen *scr = 0;

GameManager::GameManager() : state(GameState_WAIT_PLAYERS) {
	scr = &screens.wait_players;
}

void GameManager::init() {
	scr = &screens.wait_players;
	scr->init();
}

void GameManager::animate() {
	scr->animate();
}
