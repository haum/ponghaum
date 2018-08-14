#include "game_manager.h"

#include "poweroff_screen.h"
#include "wait_players_screen.h"
#include "test_hardware_screen.h"
#include "playing_screen.h"
#include "playing4x_screen.h"
#include "rainbow_screen.h"
#include "scores_screen.h"

GameManager game;

static struct {
	PoweroffScreen poweroff;
	WaitPlayersScreen wait_players;
	TestHardwareScreen test_hardware;
	PlayingScreen playing;
	Playing4xScreen playing4x;
	RainbowScreen rainbow;
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
	if (was_powered && !khroma.power.is_powered())
		init();
	was_powered = khroma.power.is_powered();
	if (khroma.btn1.touched(true) || khroma.btn2.touched(true))
		sleeptimer.start(); // Restart
	sleeptimer.animate();
	if (sleeptimer.get_value() == 1 && scr != &screens.wait_players)
		initscreen();
}

void GameManager::communicate(char type, char msg[4]) {
	scr->onReceived(
		static_cast<GameCommMsg>(type), // Assume correct
		msg
	);
}

void GameManager::restart_game() {
	data.p1score = 0;
	data.p2score = 0;
	data.old_p1score = 0;
	data.old_p2score = 0;
	play();
}

void GameManager::play() {
	if (data.playing4_enabled) {
		scr = &screens.playing4x;
	} else {
		scr = &screens.playing;
	}
	scr->init();
}

void GameManager::initscreen() {
	scr = &screens.wait_players;
	scr->init();
}

void GameManager::rainbow() {
	scr = &screens.rainbow;
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
