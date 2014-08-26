#include "game_manager.h"
#include "../hmi/hmi_manager.h"

#include "poweroff_screen.h"
#include "wait_players_screen.h"
#include "test_hardware_screen.h"
#include "playing_screen.h"
#include "scores_screen.h"

GameManager game;

static struct {
	PoweroffScreen poweroff;
	WaitPlayersScreen wait_players;
	TestHardwareScreen test_hardware;
	PlayingScreen playing;
	ScoresScreen scores;
} screens;

static GameScreen *scr = 0;

GameManager::GameManager() : state(GameState_WAIT_PLAYERS) {
	scr = &screens.poweroff;
}

void GameManager::init() {
	scr = &screens.poweroff;
	scr->init();
}

void GameManager::animate() {
	scr->animate();
}

void GameManager::restart_game() {
	data.p1score = 0;
	data.p2score = 0;
	play();
}

void GameManager::play() {
	scr = &screens.playing;
	scr->init();
}

void GameManager::initscreen() {
	scr = &screens.wait_players;
	scr->init();
}

void GameManager::show_scores() {
	scr = &screens.scores;
	scr->init();
}

void GameManager::test_hardware() {
	scr = &screens.test_hardware;
	scr->init();
}
