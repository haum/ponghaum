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
	sleeptimer.set_duration(1000.f * 60);
	sleeptimer.start();
}

void GameManager::init() {
	scr = &screens.poweroff;
	scr->init();
}

void GameManager::animate() {
	scr->animate();
	if (hmi.btn_power.slpressed())
		init();
	if (hmi.btn1.touched(true) || hmi.btn2.touched(true))
		sleeptimer.start(); // Restart
	sleeptimer.animate();
	if (sleeptimer.get_value() == 1 && scr != &screens.wait_players)
		initscreen();
}

void GameManager::restart_game() {
	data.p1score = 2;
	data.p2score = 2;
	show_scores();
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
